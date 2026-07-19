# Token

## Visão geral

Um `Token` representa uma unidade léxica da linguagem produzida pelo lexer.

O lexer é responsável por analisar o código-fonte e transformar uma sequência de caracteres em uma sequência de tokens. Cada token representa uma parte significativa do código, contendo informações sobre seu tipo, sua localização e, quando necessário, um valor associado.

O parser utiliza a sequência de tokens produzida pelo lexer para construir a Árvore Sintática Abstrata (AST), que representa a estrutura lógica do programa.

Por exemplo, o código:

```
let x = 10;
```

é transformado pelo lexer em uma sequência de tokens:

```
TOKEN_VAR
TOKEN_IDENTIFIER("x")
TOKEN_EQUAL
TOKEN_NUMBER(10)
TOKEN_SEMICOLON
```

Cada token possui uma função específica na interpretação da linguagem.

---

# Estrutura do Token

Um token possui três informações principais:

* **type**: indica a categoria do token.
* **line**: indica a linha do código-fonte onde o token foi encontrado.
* **value**: armazena um valor associado ao token, quando necessário.

Exemplo:

```cpp
Token{
    .type = TokenType::TOKEN_NUMBER,
    .line = 5,
    .value = uint64_t{42}
};
```

Nesse caso, o token representa um número encontrado na linha 5 do código.

---

# Tipos de Tokens

Os tipos de tokens são definidos através da enumeração `TokenType`.

Eles são divididos em diferentes categorias:

## Palavras reservadas

Representam palavras que possuem significado especial dentro da linguagem.

Exemplos:

```
func
return
if
else
while
for
```

Essas palavras não podem ser utilizadas como identificadores, pois possuem funções específicas na sintaxe da linguagem.

---

## Literais

Representam valores escritos diretamente pelo programador.

### Números

Exemplo:

```
12345
```

São armazenados utilizando:

```cpp
std::uint64_t
```

---

### Strings

Exemplo:

```
"Olá mundo"
```

São armazenadas utilizando:

```cpp
std::string
```

---

### Booleanos

Exemplos:

```
true
false
```

São armazenados utilizando:

```cpp
bool
```

---

### Identificadores

Representam nomes definidos pelo programador, como variáveis e funções.

Exemplos:

```
contador
nome_usuario
calcularValor
```

São armazenados utilizando:

```cpp
std::string
```

---

# Operadores

Os operadores são tokens que representam operações realizadas pela linguagem.

## Operadores aritméticos

Representam operações matemáticas.

Exemplos:

```
+
-
*
/
++
--
```

---

## Operadores de atribuição

Representam atribuição de valores.

Exemplos:

```
=
+=
-=
*=
/=
```

---

## Operadores de comparação

Representam comparações entre valores.

Exemplos:

```
>
<
>=
<=
==
!=
```

---

## Operadores lógicos

Representam operações booleanas.

Exemplos:

```
&&
||
!
```

---

## Operadores bitwise

Representam operações em nível de bits.

Exemplos:

```
&
|
^
~
<<
>>
```

---

# Delimitadores

São caracteres utilizados para estruturar o código-fonte.

Exemplos:

```
(
)
{
}
[
]
;
:
,
.
```

Eles são utilizados para representar agrupamentos, blocos de código, listas, separação de instruções e outros elementos sintáticos.

---

# Tokens especiais

## EOF

Representa o fim do arquivo.

Ele informa ao parser que não existem mais tokens disponíveis.

Exemplo:

```
TOKEN_EOF
```

---

## String incompleta

Representa uma string que não foi finalizada corretamente.

Exemplo:

```
"Olá mundo
```

Gera:

```
TOKEN_INCOMPLETED_STRING
```

---

## Token inválido

Representa uma sequência de caracteres que não pertence à linguagem.

Exemplo:

```
???
```

Gera:

```
TOKEN_INVALID
```

---

# Armazenamento de valores

O campo `value` utiliza `std::variant` para permitir diferentes tipos de dados:

```cpp
std::variant<
    std::monostate,
    std::uint64_t,
    std::string,
    bool
>
```

Os estados possíveis são:

| Tipo             | Utilização                   |
| ---------------- | ---------------------------- |
| `std::monostate` | Tokens que não possuem valor |
| `std::uint64_t`  | Literais numéricos           |
| `std::string`    | Strings e identificadores    |
| `bool`           | Valores booleanos            |

---

# Tokens sem valor

Alguns tokens possuem significado apenas pelo seu tipo.

Por exemplo, o operador:

```
+
```

não precisa armazenar nenhum dado adicional.

Ele é representado como:

```cpp
Token{
    .type = TokenType::TOKEN_PLUS,
    .value = std::monostate{}
};
```

O parser consegue identificar o operador apenas através do `TokenType`.

