# Parsing

## Bash Manual
Bash Reference Manual을 정독하며 정리한 Shell의 실행 순서는 다음과 같다. 

1. 파일(쉘 스크립트 참조), 인수로 제공된 문자열에서 -c 호출 옵션(Bash 호출 참조) 또는 사용자 단말기에서 입력을 읽습니다.
2. 인용문에 설명된 인용 규칙을 준수하여 입력을 단어와 연산자로 나눕니다. 이 토큰들은 메타문자로 구분됩니다. 이 단계에 의해 별칭 확장이 수행됩니다(알리어스 참조).
3. 토큰을 단순 명령과 복합 명령으로 구문 분석합니다(쉘 명령 참조).
4. 다양한 셸 확장(셸 확장 참조)을 수행하여 확장된 토큰을 파일 이름 목록(파일 이름 확장 참조)과 명령 및 인수로 나눕니다.
5. 필요한 모든 리디렉션을 수행하고(Redirections 참조) 인수 목록에서 리디렉션 연산자 및 해당 피연산자를 제거합니다.
6. 명령을 실행합니다(명령 실행 참조).
7. 선택적으로 명령이 완료될 때까지 기다렸다가 종료 상태를 수집합니다(종료 상태 참조).  

<br>

들어온 입력을 토큰화하여 구분한 뒤, 토큰을 여러 종류의 명령으로 구문 분석해야 한다. 


### Tokenize
토큰의 종류를 word, pipe 문자, or, and 논리 연산자, Redirection 기호(Heredoc도 포함), 괄호 기호로 나눴다. 이에 해당하지 않는 모든 경우는 에러 처리했다. 

``` c

typedef enum e_token_category
{
	T_WORD,
	T_PIPE,
	T_OR,
	T_AND,
	T_IN_RE,
	T_OUT_RE,
	T_HERE_RE,
	T_APPEND_RE,
	T_LPARENT,
	T_RPARENT,
	T_ERROR,
	T_HEAD
}	t_token_category;

```

들어온 입력을 순회하며 토큰화한 뒤, 미리 만들어 놓은 연결리스트에 저장했다. 연결리스트의 구조와 순회하는 함수는 다음과 같다.

``` c

// 토큰 구조체
typedef struct s_token
{
	char				*content; // 저장하고 있는 내용
	t_token_category	category; // 토큰 종류
	struct s_token		*next;
}	t_token;


// 문자열을 토큰화하는 함수
void	tokenize(char *input, t_token *head)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (input[++i] != '\0')
	{
		while (input[i] != '\0' && check_blank(input[i]))
			i++;
		if ((size_t)i >= ft_strlen(input))
			break ;
		if (input[i] == '&' || input[i] == '|' || input[i] == '<' || \
		input[i] == '>' || input[i] == '(' || input[i] == ')')
			tokenize_branch(input, head, &i, &flag);
		else
			tokenize_word_branch(input + i, head, &i);
	}
	update_parent_token(head);
	update_error_token(head);
}

```



### BNF
BNF(Backus-Naur Form)는 형식 문법을 정의하기 위한 표기법이다. 이는 언어의 Syntax를 명확하고 체계적으로 표현하는 데 도움을 준다. 앞에서 만든 토큰들을 단순 명령과 복합 명령으로 분석하기 위해 우리만의 BNF를 정의했다.

```
<ALPHA> ::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|
             A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z

<DIGIT> ::= 0|1|2|3|4|5|6|7|8|9

<NUMBER> ::= <DIGIT>
           | <NUMBER> <DIGIT>

<WORD> ::= <ALPHA>
         | <WORD> <ALPHA>
         | <WORD> '_'

<WORD-LIST> ::= <WORD>
             |  <WORD-LIST> <WORD>

<REDIRECTION> ::=  '>' <WORD>
                |  '<' <WORD>
                |  <NUMBER> '>' <WORD>
                |  <NUMBER> '<' <WORD>
                |  '>>' <WORD>
                |  <NUMBER> '>>' <WORD>
                |  '<<' <WORD>
                |  <NUMBER> '<<' <WORD>

<SIMPLE-COMMAND-ELEMENT> ::= <WORD>
                          |  <REDIRECTION>

<SIMPLE-COMMAND> ::=  <SIMPLE-COMMAND-ELEMENT>
                   |  <SIMPLE-COMMAND> <SIMPLE-COMMAND-ELEMENT>

<COMMAND> ::=  <SIMPLE-COMMAND>

<SIMPLE-LIST1> ::=  <SIMPLE-LIST1> '&&' <SIMPLE-LIST1>
                 |  <SIMPLE-LIST1> '||' <SIMPLE-LIST1>

<PIPELINE> ::= <COMMAND> '|' <COMMAND>
       |  <COMMAND>

```

분석한 명령 단위를 올바르게 저장하기 위해 트리에 저장했다. 트리를 만들어 저장한 이유는, 논리 연산자의 우선순위를 명확하게 표현할 수 있기 때문이다. 또한 각 명령어 단위를 계층적으로 표현할 수 있다. 처음에는 LCRS 구조로 구현하려다가, 같은 계층에 있는 자식들을 선형적으로 표현하는 것이 좀 더 직관적인 것 같아 vector를 구현해 트리를 만들었다. 

<br>

먼저 명령어 단위의 분류는 다음과 같다. 
``` c

typedef enum e_tree_category
{
	TREE_ROOT,
	TREE_LIST,
	TREE_LPARENT,
	TREE_RPARENT,
	TREE_AND,
	TREE_OR,
	TREE_PIPELINE,
	TREE_CMD,
	TREE_PIPE,
	TREE_SIMPLE_CMD,
	TREE_SUBSHELL,
	TREE_SIMPLE_CMD_ELEMENT,
	TREE_WORD,
	TREE_RE,
	TREE_ERROR
}	t_tree_category;

typedef struct s_node
{
	t_vector		*child;
	t_token			*token;
	t_tree_category	category;
}	t_node;

```

다음은 vector의 구조체와 기능들이다.

``` c

typedef struct s_vector
{
	void	**arr;
	int		data_type;
	int		size;
	int		capacity;
}	t_vector;

t_vector	*init_vector(int capacity);
void		push_back(t_vector *vector, void *node);
int			vector_find(t_vector *vector, void *f_node);
void		copy_vector(void **dst, void **src, int size);
void		free_vector(t_vector *vector);

```

vector의 메모리를 void로 정의하고, data_type에 따라 메모리를 다르게 해석하려고 했지만 뜻대로 잘 되지는 않았다. 어차피 문자열만 저장할 것이기 때문에 다용도로 쓸 수는 없었다. 노드를 push_back 할 때, 일어나는 메모리 재할당은 다음과 같이 구현했다.

``` c

void	push_back(t_vector *vector, void *node)
{
	void	**tmp;

    // 양이 가득차면 2배 늘려준다!
	if (vector->size == vector->capacity)
	{
		tmp = malloc(sizeof(void *) * (vector->capacity * 2));
		null_guard(tmp);
		vector->capacity *= 2;
		copy_vector(tmp, vector->arr, vector->size);
        // 기존의 메모리는 해제한다.
		free(vector->arr);
		vector->arr = tmp;
	}
	vector->arr[vector->size] = node;
	vector->size++;
}

```

이제 토큰 리스트를 순회하면서 올바른 명령어 단위로 해석한다. Tree의 계층 구조는 (LIST, L_PARENT, R_PARENT), (PIPELINE, &&, ||), (CMD, PIPE), (SIMPLE CMD, SUBSHELL), (SIMPLE CMD ELEMENT), (WORD, REDIRECTION, ERROR) 순이다. 

``` c

void	make_tree(t_node *root, t_token **lst)
{
	t_token	*token;
	t_node	*node;

	token = *lst;
	node = create_node(token, TREE_LIST);
	make_tree_layer1(node, &token);
	add_child(root, node);
}

```

make_tree_layer1이라는 이름으로 지은 것은 참 안타깝지만 42Seoul의 Norm 규정 때문에 어쩔 수 없었다. 이렇게 명령어 단위를 트리에 저장해 놓으면, 실행부는 트리를 재귀적으로 순회하면서 실행을 이어나가면 되기 때문에 아주 편리했다. 


### 기타 예외 처리 && 까다로웠던 부분
까다로웠던 부분은 역시 이상한 입력이 들어왔을 때 처리해주는 부분이다. 문자열을 순회하며 error 토큰으로 분류하는 작업을 했는데, 짝이 맞지 않는 괄호 토큰이나 혼자 존재하는 파이프 토큰, 연산자 토큰들을 처음에 분류할 뾰족한 수가 떠오르지 않았다. 결국 토큰 리스트를 다시 순회하며 분류하는 작업을 진행했는데, 지금 생각해보면 꼭 error 토큰으로 분류하지 않고 나중에 실행하기 전에 일괄적으로 확인해도 좋았을 것 같다. 그 방법이 시간 복잡도 측면에서 더 좋을 것 같다.

