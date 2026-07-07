# Lexer

Lexer escrito em C responsável por transformar o código-fonte em uma sequência de tokens.

Ele realiza a leitura caractere por caractere, ignorando espaços e comentários, reconhecendo palavras-chave, identificadores, números, strings e operadores.

---

## Estruturas

### `Lexer`

Estrutura interna responsável por controlar a leitura do arquivo.

```c
CLASS(Lexer, {
    char* file;      // buffer contendo o código fonte
    char* pos;       // posição atual da leitura
    size_t line;     // linha atual
});
```

### `Token`

Representa uma unidade léxica da linguagem.

```c
CLASS(Token, {
    TokenType type;  // tipo do token
    size_t line;     // linha onde apareceu
    char word[256];  // texto do token
});
```

---

## Uso básico

Criar um lexer:

```c
Lexer* lexer = newLexer("main.lang");
```

Ler tokens individualmente:

```c
for(;;){
    Token* token = Lexer__LexerNext(lexer);

    // usar token

    if(token->type == TOKEN_EOF)
        break;
}

freeLexer(lexer);
```

---

## Tokenização completa

Para enviar os tokens para o parser, todos os tokens podem ser armazenados em um `Vector<Token*>`.

```c
_Vector* LexerVector(Lexer* lexer){
    _Vector* vector = VectorF.new();
    vector->__init__(true, vector, sizeof(Token*));

    for(;;){
        Token* token = Lexer__LexerNext(lexer);

        vector = VectorF.append(vector, &token);

        if(token->type == TOKEN_EOF)
            break;
    }

    return vector;
}
```

Uso:

```c
Lexer* lexer = newLexer("main.lang");

_Vector* tokens = LexerVector(lexer);
```

---

## Tokens

### Palavras-chave

```text
main
function
return
if
else
for
while
infinitWhile
break
continue
var
true
false
```

---

### Literais

Número:

```text
123
42
```

String:

```text
"Hello World"
```

Booleanos:

```text
true
false
```

---

### Identificadores

Exemplo:

```text
variable
my_function
_value
```

---

## Operadores

### Simples

```text
+ - * / = > < ! & | ^ ~
```

### Compostos

```text
==
!=
>=
<=
&&
||
++
--
+=
-=
*=
/=
<<
>>
<<=
>>=
```

---

## Comentários

Comentários são ignorados pelo lexer.

Linha:

```c
// comentário
```

Múltiplas linhas:

```c
/*
   comentário
*/
```

---

## Fluxo

Código fonte:

```c
var x = 10;
```

Passa pelo lexer:

```text
Lexer__LexerNext()
```

Resultado:

```text
TOKEN_VAR
TOKEN_IDENTIFIER
TOKEN_EQUAL
TOKEN_NUMBER
TOKEN_SEMICOLON
TOKEN_EOF
```

---

## Funções

| Função | Descrição |
|--------|-----------|
| `newLexer(file)` | Cria um lexer e carrega o arquivo para memória |
| `freeLexer(lexer)` | Libera o lexer e o buffer interno |
| `Lexer__LexerNext(lexer)` | Retorna o próximo token |
| `LexerVector(lexer)` | Gera um vector contendo todos os tokens |

---

## Observações

- O lexer trabalha com o arquivo inteiro carregado em memória.
- Comentários não chegam ao parser.
- Operadores compostos são reconhecidos durante a tokenização.
- `TOKEN_UNDEFINED` é usado para caracteres desconhecidos.
- `TOKEN_EOF` indica o fim do arquivo.
- O campo `line` é mantido para mensagens de erro futuras.