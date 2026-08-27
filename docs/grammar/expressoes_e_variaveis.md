# VARIAVEIS

## DECLARAÇÃO

todas as variaveis seguem a seguinte forma de declaração:
```
var name: type (= expression)?;
```
sendo necessario usar a palavra `var`, inferir um nome no `name`, uma tipagem no `type` e opcional inicializar

## EXPRESSÕES

nas expressões contemos

|simbolo|descrição|
|-------|---------|
|`+`| ele define uma soma entre valores|
|`-`| ele define um subtração entre valores|
|`*`| ele define uma multiplicação entre valores|
|`/`| ele define uma divisão entre valores|
|`%`| ele define que haverá uma divisão e será retornado o resto inteiro dessa divisão|
|`\|`| ele define um operador or bit a bit|
|`&`| ele define um operador and bit a bit|
|`^`| ele define um operador xor bit a bit|
|`~`| ele define um operador not bit a bit|
|`>>`| ele define uma movimentação de bit para a direita|
|`<<`| ele define uma movimentação de bit para a esquerda|
|`&&`| ele define um operador and booleano|
|`\|\|`| ele define um operador or booleano|
|`!`| ele define um operador not booleano|
|`==`| ele define uma comparação de igualdades e retorna um booleano|
|`!=`| ele define uma comparação de diferença e retorna um booleano|
|`>`| ele define uma comparação de "maior que" e retorna um booleano|
|`<`| ele define uma comparação de "menor que" e retorna um booleano|
|`>=`| ele define uma comparação de "maior ou igual" e retorna um booleano|
|`<=`| ele define uma comparação de "menor ou igual" e retorna um booleano|

## ATRIBUIÇÃO

além da atribuição simples (`=`), usada na declaração de variáveis, a linguagem também suporta atribuição composta, que aplica a operação indicada antes de atribuir o resultado à variável:

|simbolo|descrição|
|-------|---------|
|`=`| atribui o valor da expressão diretamente à variável|
|`+=`| soma o valor da expressão à variável e atribui o resultado|
|`-=`| subtrai o valor da expressão da variável e atribui o resultado|
|`*=`| multiplica a variável pelo valor da expressão e atribui o resultado|
|`/=`| divide a variável pelo valor da expressão e atribui o resultado|
|`%=`| divide a variável pelo valor da expressão e atribui o resto da divisão|
|`&=`| aplica and bit a bit entre a variável e a expressão e atribui o resultado|
|`\|=`| aplica or bit a bit entre a variável e a expressão e atribui o resultado|
|`^=`| aplica xor bit a bit entre a variável e a expressão e atribui o resultado|
|`~=`| aplica not bit a bit sobre a expressão e atribui o resultado à variável|
|`<<=`| desloca os bits da variável para a esquerda pelo valor da expressão e atribui o resultado|
|`>>=`| desloca os bits da variável para a direita pelo valor da expressão e atribui o resultado|
