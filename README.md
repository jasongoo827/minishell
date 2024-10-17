# Minishell

## 만든이들

jgoo(구재우) / mkong(공민구)

## 프로젝트 소개
프로젝트의 목표는 간단한 쉘을 만드는 것입니다. 쉘은 IT의 태초부터 함께 했습니다.

그 당시, 모든 개발자들은 1과 0으로만 이루어진 스위치로 컴퓨터와 통신하는 것은 굉장히 성가시다는 점에 동의했습니다.

영어와 비슷한 언어로 작성된 명령어의 줄을 이용해 컴퓨터와 소통하는 프로그램을 만들겠다는 아이디어를 떠올린 것도 당연한 수순이었죠.

감사하게도 `Minishell` 과 함께라면, `Windows` 가 존재하지 않았을 시절 사람들이 겪었던 문제를 마주해 볼 수 있을 겁니다.


![Minishell](images/Introduction.png)


## Mandatory Part

| Program name | minishell |
|:-------|:-------|
| Turn in files | Makefile, *.h, *.c |
| Makefile | all, clean, fclean, re |
| External functs. | readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs |
| Description | Write a shell

## Bonus Part
Your program has to implement:
-  && and || with parenthesis for priorities.
-  Wildcards * should work for the current working directory.

<br>

## 구현 과정
구현은 입력된 명령어를 해석하는 파싱부, 해석된 명령어를 실행하는 실행부로 나누어 진행했다. 

## 구현 시 필수적으로 참고해야 할 사이트

- [Bash Manual](https://www.gnu.org/software/bash/manual/bash.html) : Bash가 어떻게 구현되어 있는지 자세히 명세되어 있다. Builtin Commands 부분까지는 자세히 읽어보는 것을 추천한다.

- [Bash BNF](https://cmdse.github.io/pages/appendix/bash-grammar.html) : BNF syntax가 명세된 사이트다. 이를 참고해 우리만의 BNF를 정의했다.



## 프로젝트를 직접 테스트 하고 싶다면..

```sh
## macOS 환경이 아니면 실행이 안 될 수 있습니다. 
git clone https://github.com/jasongoo827/minishell.git

make

## .o 파일 정리
make clean

## 테스트 한 후에 파일 원래대로 정리
make fclean

```
