# Signal Handling

**Signal**은 커널 또는 다른 프로세스가 특정 이벤트에 대해 프로세스에 알림을 주는 방식이다. 과제에서 다루는 시그널은 **SIGINT**(CTRL + C), **SIGQUIT**(CTRL + \ ) 총 2가지이다. CTRL + D 도 처리해야 하지만 시그널로 처리하지는 않는다(원래는 SIGTERM). 

SIGINT는 Interrupt의 줄임말로, 현재 실행 중인 프로세스를 중단시키는 데 사용된다. SIGQUIT는 Ctrl+\ 를 눌렀을 때 발생하는 신호로, 프로세스는 이 신호를 받아 코어 덤프를 생성하고 종료한다. 코어 덤프는 프로그램이 종료될 당시의 메모리 상태를 그대로 저장한다.

평소에 SIGINT는 발생 시 개행, SIGQUIT는 무시된다. 

```c

void	signal_handler(void)
{
	init_rl_catch_signals();
    // 처리하고 싶은 signal, 함수를 매칭시킨다
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}


void	sigint_handler(void)
{
	g_last_signal = 1;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

```

시그널을 특별하게 처리해야 하는 경우는 3가지 상황이 있다. 

| SIGNAL | SIGINT | SIGQUIT | CTRL + D |
|:-------|:-------| :-------| :-------|
| 입력 대기 | ^C 출력 후 종료 | ^\Quit:3 출력 후 종료 | 종료|
| HEREDOC | 개행 후 종료 | 무시 | 개행 없이 종료 |
| 무한 루프 | ^C 출력 후 종료 | ^\Quit:3 출력 후 종료 | 무시 |

각 상황이 발생했을 때, 그에 맞는 signal handler 함수를 등록해주면 된다. 
입력 대기와 무한 루프 때는 SIG_DFL를 등록하고, HEREDOC 시에는 fork 함수로 새로운 프로세스를 생성하기 전에 SIG_IGN를 등록한 후, 자식 프로세스 내부에서 SIGINT는 SIG_DFL를 새로 등록해주면 된다. SIG_DFL는 기본 동작대로 작동하게 하는 플래그이고, SIG_IGN는 신호를 무시하라는 플래그이다. 

``` c

static void	exec_pipe_cmd(t_cnode *cnd, pid_t pid)
{
	char	**envp;

	if (pid == 0)
	{
		pipe_handler(cnd);
		re_handler(cnd->re_vec, cnd->old_dic, 0);
		if (cnd->b_category == ELSE)
		{
			check_path(cnd->path);
			envp = make_envp(cnd->old_dic);
			null_guard(envp);
            // SIG_DFL 등록
			child_signal_handler();
			if (execve(cnd->path, (char **)cnd->cmd_vec->arr, envp) == -1)
				printf_error(cnd->path, EXE_ERR, 1);
		}
		else
			exit(exec_builtin(cnd, 0, 0));
	}
	if (*cnd->input_fd != -1)
	{
		check_fail(close(*cnd->input_fd));
		check_fail(close(*cnd->output_fd));
	}
	*cnd->output_fd = cnd->fds[1];
	*cnd->input_fd = cnd->fds[0];
}

void	child_signal_handler(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

```

``` c

int	here_doc(t_vector *re_vec, t_dict *dic)
{
	char	*tmp_name;
	pid_t	pid;
	int		i;

	i = -1;
	count_here_doc(re_vec);
	while (++i < re_vec->size)
	{
		if (ft_strncmp(re_vec->arr[i], "<<", 3) == 0)
		{
			if (check_heredoc_syntax(re_vec, dic, i) < 0)
				return (-1);
			i++;
			tmp_name = make_here_name();
            // SIG_IGN 등록
			parent_signal_handler();
			pid = fork();
            // fork 후 새로운 핸들러를 등록해야 한다.
			if (pid == 0)
				exec_here_doc(tmp_name, re_vec->arr[i], dic);
			heredoc_etc(tmp_name, re_vec, i);
			if (check_heredoc_exit(re_vec, dic, i) < 0)
				return (-1);
		}
	}
	return (1);
}

static void	exec_here_doc(char *tmp_name, char *delimeter, t_dict *dic)
{
	char	*s;
	char	*after_deli;
	int		fd;

	fd = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	check_fail(fd);
	after_deli = get_after_deli(delimeter);
	while (1)
	{
        // SIGINT만 SIG_DFL를 등록한다.
		signal(SIGINT, SIG_DFL);
		heredoc_rl_catch_signals();
		s = readline("> \001\033[s\002");
		if (s == NULL)
			heredoc_sigterm_handler();
		check_deli(after_deli, s, fd);
		if (!ft_strchr(delimeter, '\'') || !ft_strchr(delimeter, '\''))
			s = change_env(dic, s, 0);
		ft_putendl_fd(s, fd);
		free(s);
	}
	free(after_deli);
	check_fail(close(fd));
	exit(0);
}

```

## 까다로웠던 점

Signal handling을 구현할 때 까다로웠던 것은 각 시그널에 대해 실행 결과가 어떻게 나오는지 명시된 문서가 따로 없어서, bash로 모두 실험해봐야 한 점이다. 그 당시에 minishell을 진행한 팀들이 많아 서로 얻은 데이터를 공유하며 구현했던 것이 굉장히 재미있었다. 또 기억에 남는 어려웠던 부분은 Signal로 인해 비정상 종료 시, exit code를 맞춰줘야 했던 것이다. 이를 처리하기 위해 따로 함수를 만들었다.

``` c

void	signal_by_exit_status(pid_t pid, t_dict *dic)
{
	int	param;
	int	status;

    // 가장 마지막 PID의 status를 확인한다.
	waitpid(pid, &status, 0);
    // 비정상 종료됐을 때, 
	if (!WIFEXITED(status))
	{
        // 시그널로 인해 종료됐다면,
		if (WIFSIGNALED(status))
		{
            // 128이 시그널 종료 시 기준값
			param = WTERMSIG(status) + 128;
            // SIGINT
			if (param == 130)
				ft_putstr_fd("\n", 2);
            // SIGQUIT
			else if (param == 131)
				ft_putstr_fd(MSG_SIGQUIT, 2);
		}
		else
			param = WEXITSTATUS(status);
	}
	else
		param = WEXITSTATUS(status);
	if (pid != 0)
		dic->exit_status = param;
}

```