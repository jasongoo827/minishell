# etc
기타 여러 가지 디테일들에 대해 좀 더 소개를 하면 좋을 것 같아서 따로 페이지를 작성했다. 

## 환경변수
bash에서 쓰이는 env, export 등 환경변수가 필요한 명령어들을 위해, 환경변수를 읽어와 연결리스트에 저장했다. 환경변수가 key=value 형태로 저장되어 있기 때문에 각 노드들에 key, value 값을 나누어 저장했고, 환경변수의 변화가 생겼을 때 적절하게 변경해줬다. 

``` c

// 양방향 연결리스트
typedef struct s_dnode
{
	struct s_dnode	*prev;
	struct s_dnode	*next;
	char			*key;
	char			*value;
	int				check_env;
	int				is_ambg;
}	t_dnode;

// 이름은 dictionary지만, 진짜 dictionary는 아니다.
typedef struct s_dict
{
	t_dnode	*head;
	t_dnode	*tail;
	int		env_size;
	int		exit_status;
	int		exec_flag;
}	t_dict;

```

해당 과제에서 하나 이상의 전역변수를 사용하는 것이 금지되어 있기 때문에, dictionary를 처음에 만들어 main loop 안에 계속 들고 다녔다. 또한 exit_status, exec_flag 같이 실행 과정에 필요한 변수들도 dictionary에 보관했다. 

## volatile, sig_atomic_t
과제 지시문 중 이런 말이 있었다. 

Avoid using more than one global variable to indicate a received signal. Consider
the implications: this approach ensures that your signal handler will not access your
main data structures.

처음에 signal handler가 main data structures에 접근할 수 없어야 한다는 말이 무엇인지 몰랐다. 그래서 별 생각 없이 signal handling 구현을 했고, 평가를 받으려고 했다. 평가를 받기 전, 평가 로그를 뒤지다가 volatile, sig_atomic_t 키워드를 쓰지 않아 fail을 받았다는 로그를 발견했다. 그 때서야 다시 위의 지시문에 관심을 갖게 됐고, 그 로그를 남긴 seojilee에게 물어봐 두 키워드들에 대해 알게 됐다. 

signal handling 시 주의 해야 할 것은, 프로그램 실행 도중에 언제든지 signal handler가 호출될 수 있기 때문에 메인 프로그램에서 사용하는 변수에 대한 보호가 필요하다. 그 과정에서 volatile, sig_atomic_t가 필요한 것이다.

``` c

int flag = 0;

void signal_handler(int sig) {
    if (sig == SIGINT) {
        flag = 1;
    }
}

int main() {
    signal(SIGINT, signal_handler);

	// flag가 1이 되길 기다리고 있음.
    while (flag == 0) {
        printf("Waiting for signal...\n");
        sleep(1);
    }

    return 0;
}

```

위와 같은 예제에서 signal_handler와 main이 동시에 flag 값에 접근하고 있다. 이 경우 flag 값이 어떻게 될 지 확실히 보장할 수 없다. volatile sig_atomic_t 키워드를 붙이면, 최적화를 방지하고 원자적 접근을 보장해 주기 때문에 동시에 접근하는 것을 막을 수 있다. 최적화를 방지하는 이유는 컴파일러가 flag를 캐시하거나 레지스터에 저장해 두고 이를 반복적으로 읽도록 해놨을 수 있기 때문이다. 

``` c

// 전역 변수에 volatile sig_atomic_t를 붙여준다!
volatile sig_atomic_t	g_last_signal = 0;

```


## 에러 처리
에러 발생 시 나와야 하는 메시지들을 매크로로 정의해놨다가 출력했다. 또한 메모리 할당 실패 시 null check를 하는 코드가 항상 코드를 지저분하게 만들어서 따로 함수를 만들었다. 이는 코드 수를 줄이는 데 아주 효과적이었다. 

``` c

// error.h
#ifndef ERROR_H
# define ERROR_H

# define MALLOC_ERR "Memory Allocate Error\n"
# define SYNTAX_ERR "minishell: syntax error near unexpected token "
# define CNF_ERR "command not found"
# define PER_ERR "Permission denied"
# define DIR_ERR "is a directory"
# define NOF_ERR "No such file or directory"
# define EXE_ERR "Exec format error"
# define AMB_ERR "ambiguous redirect"
# define HER_ERR "maximum here-document count exceeded"
# define CDD_ERR "error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory"

void	exit_error(char *str);
void	null_guard(void *str);
void	syntax_error(char *str);
void	printf_error(char *error, char *err_message, int i);
int		check_fail(int n);

#endif

// null_guard function
void	null_guard(void *str)
{
	if (str == NULL)
		exit_error(MALLOC_ERR);
}

// 원래 코드
ret = ft_ft_substr(str, 0, len);
if (ret == NULL)
	exit(1);

// null_guard 적용 코드(3줄 -> 1줄)
null_guard(ret = ft_substr(str, 0, len));

```


## ANSI 코드
이 과제는 bash와 출력이 똑같게 나와야 하기 때문에 꽤 고생을 한 부분이 있다. 다행히 Minishell을 한 여러 사람들 덕분에 ANSI 코드를 써서 터미널 커서를 다루는 방법을 알게 됐고, 최대한 똑같게 구현할 수 있었다. 

``` c

// CTRL + D 눌렀을 때 작동. 실제로 sigterm은 아니다.
void	sigterm_handler(t_dict *dic)
{
	// 커서 위치 복원
	ft_putstr_fd("\033[u", 2);
	// 커서 아래로 옮기기
	ft_putstr_fd("\033[1B", 2);
	// 커서 위로 옮기기
	ft_putstr_fd("\033[1A", 2);
	ft_putstr_fd(MSG_SIGTERM, 2);
	if (g_last_signal == 1)
		exit(g_last_signal);
	else
		exit(dic->exit_status);
}

// 커서 위치 저장
input = readline("minishell> \001\033[s\002");

``` 