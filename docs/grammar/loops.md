## LOOP'S

Temos 3 tipos de loop:

|loop|descrição|
|----|---------|
|`while`|ele executa um loop até a `cond`(condição) ser falsa|
|`do ... while`|ele executa obrigatoriamente o escopo, e depois verifica se a `cond`(condição) é verdadeira|
|`for`|ele tem um `init`(inicialização) que você declara uma variavel, ou inicializa uma variavel. O loop irá executar até o `cond`(condição) ser falso. e a cada final de loop terá uma incrementação de sua escolha|

todas as `cond` seguem a mesma regra de avaliação das condicionais: o valor é convertido para inteiro, sendo verdadeiro quando diferente de `0`.

### WHILE

O `while` funciona da seguinte maneira:
a palavra `while`, uma `cond` e um corpo.
```
while(cond){
    body
}
```

### DO ... WHILE

o `do ... while` funciona da seguinte maneira:
a palavra `do`, o escopo e então a palvra `while` e a condição.
```
do{
    body
}while(cond);
```

### FOR

O `for` funciona da seguinte maneira:
a palavra `for`, um `init`, uma `cond`, e um `inc/dec`.
```
for(init; cond; inc/dec){
    body
}
```

### CONTROLE DE LOOP'S

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
    i += 1;
    if(i == 2){
        i += 2;
        continue;
    }
    if(i == 10) break;
}

for(i = 0; i < 100; i = i + 1){

    if(i == 4) continue;
    i = i + 1;

    if(i == 50) break;
}

do{
    i += 1;
}while(i < 10)
```