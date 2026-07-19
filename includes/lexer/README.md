# Lexer

## Visão geral

O `Lexer` é responsável pela análise léxica do código-fonte.

Sua função é ler uma sequência de caracteres e transformá-la em uma sequência de `Tokens` que serão utilizados posteriormente pelo parser.

O lexer identifica elementos da linguagem como:

* palavras reservadas;
* identificadores;
* números;
* strings;
* valores booleanos;
* operadores;
* delimitadores;
* tokens especiais.

O lexer não possui conhecimento sobre a gramática da linguagem. Ele apenas reconhece unidades léxicas válidas.

---

# Funcionamento

O lexer carrega o arquivo inteiro em memória e realiza a leitura utilizando iteradores.

A leitura dos tokens é feita sob demanda. O lexer produz tokens conforme eles são solicitados, evitando a necessidade de gerar toda a sequência antecipadamente.

Os tokens produzidos são armazenados em um buffer interno, permitindo que o parser consuma os tokens conforme necessário.

---

# Buffer de Tokens

O lexer possui um buffer interno responsável por armazenar tokens já produzidos.

Esse buffer permite:

* armazenar tokens antes de serem consumidos;
* realizar operações de leitura sem consumo através do `peekToken()`;
* separar a produção de tokens do consumo realizado pelo parser.

Após a inicialização do lexer, o buffer sempre possui pelo menos um token disponível.

---

# Consumo de Tokens

## nextToken()

A função `nextToken()` retorna o próximo token disponível e remove ele do buffer.

Ela é utilizada quando o token atual já foi processado e o parser deseja avançar para o próximo elemento.

---

## peekToken()

A função `peekToken()` retorna o próximo token disponível sem removê-lo do buffer.

Ela permite que o parser verifique o próximo token antes de decidir qual ação tomar.

---

# Reconhecimento de Tokens

O lexer realiza o reconhecimento dos tokens dividindo a análise em diferentes categorias.

## Espaços

Antes de analisar um token, o lexer remove espaços em branco.

Durante essa etapa também é realizado o controle da linha atual do código-fonte.

---

## Strings

Strings são identificadas quando o lexer encontra o caractere `"`.

Exemplo:

```txt
"Hello World"
```

O resultado é um token do tipo:

```txt
TOKEN_STRING
```

com o valor:

```txt
"Hello World"
```

Caso uma string não seja finalizada corretamente, o lexer produz um:

```txt
TOKEN_INCOMPLETED_STRING
```

---

## Números

Sequências numéricas são convertidas em valores inteiros.

Exemplo:

```txt
12345
```

Resultado:

```txt
TOKEN_NUMBER
```

O valor associado é armazenado como:

```cpp
std::uint64_t
```

---

## Identificadores e palavras reservadas

Quando o lexer encontra uma sequência alfanumérica, ele verifica se ela corresponde a uma palavra reservada.

Exemplo:

```txt
return
```

Produz:

```txt
TOKEN_RETURN
```

Caso a sequência não seja uma palavra reservada:

```txt
variavel
```

Produz:

```txt
TOKEN_IDENTIFIER
```

com o valor:

```txt
"variavel"
```

---

# Operadores

O lexer possui suporte para operadores de diferentes tamanhos.

Os operadores podem possuir:

* um caractere;
* dois caracteres;
* três caracteres.

---

## Operadores de um caractere

São operadores formados por um único símbolo.

Exemplos:

```txt
+
-
*
/
=
<
>
```

São armazenados em uma tabela de busca utilizando:

```cpp
std::unordered_map<char, TokenType>
```

---

## Operadores de dois caracteres

São operadores compostos por dois símbolos.

Exemplos:

```txt
++
+=
==
!=
&&
||
<<
>>
```

São armazenados utilizando:

```cpp
std::unordered_map<std::string, TokenType>
```

---

## Operadores de três caracteres

São operadores compostos por três símbolos.

Exemplos:

```txt
<<=
>>=
```

Também são armazenados utilizando:

```cpp
std::unordered_map<std::string, TokenType>
```

---

# Reconhecimento de operadores inválidos

Para reconhecer operadores, o lexer tenta encontrar a maior sequência possível.

A ordem de tentativa é:

* três caracteres;
* dois caracteres;
* um caractere.

Exemplo:

Entrada:

```txt
**
```

Primeiramente o lexer tenta encontrar um operador:

```txt
**
```

Caso não exista, ele divide a sequência:

```txt
*
*
```

Gerando dois tokens separados:

```txt
TOKEN_MUL
TOKEN_MUL
```

Isso permite que sequências inválidas sejam interpretadas como operadores menores válidos quando possível.

---

# Estruturas internas

## Tabela de operadores

O lexer utiliza tabelas de busca para identificar operadores rapidamente.

Existem três tabelas:

* operadores de um caractere;
* operadores de dois caracteres;
* operadores de três caracteres.

---

## Tabela de palavras reservadas

As palavras reservadas são armazenadas em uma tabela:

```cpp
std::unordered_map<std::string, TokenType>
```

Exemplo:

```cpp
{
    "if" : TOKEN_IF,
    "return" : TOKEN_RETURN
}
```

Isso permite que o lexer diferencie identificadores comuns de palavras especiais da linguagem.

---

# Responsabilidades do Lexer

O lexer é responsável por:

* ler o código-fonte;
* controlar a posição atual da leitura;
* controlar linhas;
* reconhecer tokens;
* armazenar valores associados aos tokens;
* detectar erros léxicos simples.

---

# O que o Lexer não faz

O lexer não é responsável por:

* validar sintaxe;
* verificar tipos;
* construir AST;
* interpretar expressões;
* analisar estruturas da linguagem.

Essas responsabilidades pertencem às próximas etapas do compilador.

---

# Exemplo

Código-fonte:

```cpp
func main(){
    return 10;
}
```

Tokens produzidos:

```txt
TOKEN_FUNC
TOKEN_MAIN
TOKEN_LPAREN
TOKEN_RPAREN
TOKEN_LBRACE
TOKEN_RETURN
TOKEN_NUMBER(10)
TOKEN_SEMICOLON
TOKEN_RBRACE
```
