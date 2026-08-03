# GRAMATICA

## VARIAVEIS

### DECLARAÇÃO

A declaração pode ser feita somente com nome e tipo:
```
var name: type;
```

e a declaração com atribuição pode ser feita com nome, tipo e a expressão:
```
var name: type = expression;
```

## CONDIÇÃO

AS condições podem ser feita com `if` e `else`

### IF

os `if` funciona com `if` e condição:
```
if(cond){
    body
}
```

### IF ... ELSE

O `else` pode ser utilizado após o `if`, da seguinte maneira:
```
if(cond){
    body
}
else{
    body
}
```

### IF ... ELSE IF ... ELSE

O `else if` é uma macro de expansão, criando um `if` `else` dentro do `else`:

```
if(cond){
    body
}
else if(cond){
    body
}
else{
    body
}
```

ao ser expandido, se tornará

```
if(cond){
    body
}
else{
    if(cond){
        body
    }
    else{
        body
    }
}
```

## LOOP'S

Temos 3 tipos de loop:


|loop|descrição|
|----|---------|
|`while`|ele executa um loop até a `cond`(condição) ser falsa|
|`for`|ele tem um `init`(inicialização) que você declara uma variavel, ou inicializa uma variavel. O loop irá executar até o `cond`(condição) ser falso. e a cada final de loop terá uma incrementação de sua escolha|

### WHILE

O `while` funciona da seguinte maneira:
a palavra `while`, uma `cond` e um corpo. 
```
while(cond){
    body
}
```

### FOR

O `for` funciona da seguinte maneira:
a palavra `for`, um `init`, uma `cond`, e um `inc/dec`.
```
for(init; cond; inc/dec){
    body
}
```

Também temos os controles de loops:

|palavra|descrição|
|-------|---------|
|`continue`| ele encerra a sessão de loop e volta ao inicio (no `for` ele executa a incrementação/decrementação antes de voltar ao inicio do loop)|
|`break`| ele finaliza o loop|

### CONTINUE & BREAK

Exemplo para o `continue` e `break`:

```
var i: int = 0;

while(true){
    i = i + 1;
    if(i == 2){
        i = i + 2;
        continue;
    }
    if(i == 10) break;
}

for(i = 0; i < 100; i = i + 1){

    if(i == 4) continue;
    i = i + 1;

    if(i == 50) break;
}

```

## NOTHING

O nothing ele permite que você não crie um bloco, por exemplo:
```
if(cond) nothing;
```
Permite que o if não execute nada (extremamente inutil).

e também funciona em loop's:

`while`:
```
while(cond) nothing;
```
`for`:
```
for(init; cond; inc/dec) nothing;
```

