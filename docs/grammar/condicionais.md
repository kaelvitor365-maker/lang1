# CONDICIONAIS

## IF / ELSE

a estrutura condicional segue a seguinte forma:
```
if (condition) statement
```
sendo `condition` uma expressão que deve resultar em um valor booleano, e `statement` o que será executado caso a condição seja verdadeira. `statement` pode ser um único comando ou um bloco `{ }`.

opcionalmente, é possível encadear um `else`:
```
if (condition) statement
else statement
```

o `else` também aceita um novo `if`, permitindo encadear múltiplas condições:
```
if (condition) statement
else if (condition) statement
else statement
```

o `else` pode ser explicitamente vazio usando a palavra `nothing`:
```
if (condition) statement
else nothing;
```
nesse caso, nenhum ramo alternativo é executado — é equivalente a não escrever `else` nenhum, mas de forma explícita.

## NOTHING

`nothing` é um statement que representa a ausência intencional de uma ação:
```
if(cond) nothing;

if(cond) {...}
else nothing;
```

ele pode ser usado em qualquer lugar onde um `statement` é esperado, não apenas dentro de um `else`. Serve para deixar explícito que, naquele ponto, nenhuma instrução deveria ser executada — diferenciando um bloco intencionalmente vazio de um esquecimento do programador.

## COMPARAÇÕES

condições geralmente são formadas usando os operadores de comparação (`==`, `!=`, `>`, `<`, `>=`, `<=`) e/ou operadores lógicos (`&&`, `||`, `!`), descritos na seção de expressões.

## AVALIAÇÃO DA CONDIÇÃO

`condition` não precisa resultar estritamente em um valor booleano: o resultado é convertido para um inteiro, e essa conversão é considerada verdadeira quando o valor é diferente de `0`, e falsa quando o valor é igual a `0`.