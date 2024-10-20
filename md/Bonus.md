# Bonus

## Wildcard
Wildcard는 파일명이나 디렉토리를 간편하게 찾기 위해 사용되는 개념이다. Minishell에서 구현해야 하는 Wildcard는 '*'이다. '*'의 앞이나 뒤에 패턴을 추가해 그에 맞는 패턴을 찾는 데 사용할 수 있다. 몇 가지 예시를 들어보겠다.

``` c

* // 모든 패턴

***** // *과 같은 패턴(* 여러개 == * 하나)

*.txt // .txt로 끝나는 패턴

file* // file로 시작하는 패턴

*abc* // 사이에 abc가 껴있는 패턴

```

Wildcard 패턴을 '*'로만 이루어져 있는 경우, '*' + 패턴, 패턴 + '*', '*' + 패턴 + '*' 4가지 경우로 분류해 구현을 했다. 

``` c

t_vector	*expand_wildcard(char *pattern)
{
	char		cwd[MAX_DIRLEN];
	t_vector	*vector;
	DIR			*dir;

	// 현재 디렉토리가 존재하는지 확인
	if (!check_cur_dir(cwd, &dir))
		return (NULL);
	// '*'로만 이루어진 경우
	if (check_only_wc(pattern))
	{
		vector = only_wc_vector(pattern, dir);
		closedir(dir);
		return (vector);
	}
	// 나머지 경우
	vector = expand_wildcard_branch(pattern, dir);
	closedir(dir);
	return (vector);
}

```

현재 디렉토리에 있는 파일들을 확인하기 위해서, readdir 함수를 사용했다. '*'로 시작하는 경우와 '*'로 끝나는 경우에 패턴을 확인하는 방식이 아주 조금 달랐는데, 함수를 하나 더 만들기에는 너무 중복된 코드가 많이 생길 것이라고 생각했다. 그래서 edge_wc_vector 함수의 마지막 매개변수로 패턴을 확인하는 함수를 받아올 수 있게 함수 포인터로 정의했다. 또한 check_front_wc와 ft_strncmp의 형식을 똑같이 맞춰줬다. 

``` c

t_vector	*expand_wildcard_branch(char *pattern, DIR *dir)
{
	t_vector	*vector;
	char		*tmp;

	if (check_edge_wildcard(pattern))
	{
		// * 로 시작하는 경우
		if (pattern[0] == '*')
		{
			while (*pattern == '*')
				pattern++;
			vector = edge_wc_vector(pattern, dir, check_front_wc);
			no_pattern_matches(vector, pattern, NULL);
		}
		// * 로 끝나는 경우
		else
		{
			tmp = cut_wildcard(pattern);
			vector = edge_wc_vector(tmp, dir, ft_strncmp);
			no_pattern_matches(vector, pattern, tmp);
		}
	}
	else
		vector = middle_wc_vector(pattern, dir);
	return (vector);
}

// 마지막 변수로 함수를 받아온다.
t_vector	*edge_wc_vector(char *pattern, DIR *dir,  int (*f)(const char *, const char *, size_t))
{
	char			*ret;
	struct dirent	*entry;
	t_vector		*vector;

	vector = init_vector(INIT_SIZE);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		// 패턴이 일치하면 해당 파일을 vector에 추가
		if (entry->d_name[0] != '.' && !f(entry->d_name, pattern, ft_strlen(pattern)))
		{
			ret = ft_strdup(entry->d_name);
			null_guard(ret);
			push_back(vector, (void *)ret);
		}
	}
	return (vector);
}

```

'*' 사이에 있는 패턴을 확인하는 부분이 좀 까다로웠다. 패턴을 '*'을 기준으로 split 한 후에, 각 패턴이 원래 문자열에 들어있는지 확인했다. 

``` c

int	check_mixed_wc(char *str, char *pattern, char **patterns)
{
	int		i;
	int		len;

	i = -1;
	while (patterns[++i] != NULL)
	{
		len = ft_strlen(patterns[i]);
		// 맨 앞이 '*'로 시작하지 않을 때, 패턴 확인
		if (i == 0 && find_pattern_front(str, pattern, patterns[i], len))
			return (0);
		else if (patterns[i + 1] != NULL)
		{
			// str에 패턴 있는지 확인
			if (find_pattern_in_str(&str, patterns[i], len) < 0)
				return (0);
			continue ;
		}
		else if ((pattern[ft_strlen(pattern) - 1] != '*' && \
		check_mixed_wc_branch(str, patterns[i], len) < 0) || \
		!ft_strnstr(str, patterns[i], ft_strlen(str)))
			return (0);
		move_str(&str, len);
	}
	return (1);
}

```

그 때 만들었을 때는 굉장히 코드를 잘 짰다고 생각했는데, 지금 와서 보니 무슨 말인지 하나도 알 수가 없다. 당시 기록을 해 놓았다면 그래도 지금 이해가 조금 됐을텐데, 그마저도 없다. 앞으로 프로젝트 진행할 때는 매일매일 기록을 남길 예정이다. 기록이 가장 큰 자산이다. 지금 다시 만든다면, 재귀적으로 patterns 배열을 확인하며 패턴이 일치하는지 확인할 것 같다.


## &&, || 
논리 연산자의 경우, 선행 조건의 참 거짓 여부에 따라 뒤에 있는 조건이 실행이 결정된다.

A && B -> A가 참이면 B 실행, A 거짓이면 B 실행 X
A || B -> A가 참이면 B 실행 X, A 거짓이면 B 실행

각 조건에 해당하는 pipeline의 실행 결과를 저장해놨다가 논리 연산자가 등장했을 때, 실행 결과의 여부에 따라 뒤의 pipeline을 실행할지 말지 결정해줬다. 

``` c

int	exec_and(t_node *root, t_node *node, t_dict *dic)
{
	if (!check_pipeline(root))
	{
		syntax_error(node->token->content);
		dic->exit_status = 258;
		return (-1);
	}
	if (!dic->exit_status)
	{
		dic->exec_flag = 0;
		return (1);
	}
	else
	{
		// 앞의 pipeline이 비정상 종료일 때, 실행 플래그를 바꾼다
		dic->exec_flag = 1;
		return (1);
	}
}

int	exec_or(t_node *root, t_node *node, t_dict *dic)
{
	if (!check_pipeline(root))
	{
		syntax_error(node->token->content);
		dic->exit_status = 258;
		return (-1);
	}
	if (!dic->exit_status)
	{
		// 앞의 pipeline이 정상 종료이면, 실행 플래그를 바꾼다
		dic->exec_flag = 1;
		return (1);
	}
	else
	{
		dic->exec_flag = 0;
		return (1);
	}
}

```