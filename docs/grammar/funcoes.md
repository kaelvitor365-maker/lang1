# FUNÇÕES

## DECLARAÇÃO

toda função é construída a partir de um literal de função, seguido de um nome que a identifica:
```
func(name: type, name: type): retType { body } name
```

sendo:

* `func` a palavra reservada que inicia o literal de função
* `name: type` cada parâmetro, separado por vírgula, seguindo a mesma forma `nome: tipo` usada na declaração de variáveis
* `retType` o tipo de retorno da função
* `body` o bloco de comandos executado quando a função é chamada
* `name` o nome que identifica a função, usado posteriormente para chamá-la

## PARÂMETROS

os parâmetros são opcionais — uma função pode não receber nenhum:
```
func(): retType { body } name
```

quando existem, são separados por vírgula:
```
func(a: int, b: int): int { body } soma
```

## VALOR PADRÃO

um parâmetro pode ter um valor padrão, atribuído caso a chamada não forneça um valor para ele — seguindo a mesma forma usada na declaração de variáveis:
```
func(a: int, b: int = 10): int { body } soma
```

nesse caso, chamar `soma(5)` é equivalente a chamar `soma(5, 10)`.

## TIPO DE RETORNO

o `retType` pode ser omitido quando a função não retorna valor algum (`void` implícito):
```
func(a: int) { body } imprimeValor
```

quando presente, define o tipo do valor devolvido pela função através da palavra reservada `return`.

## RETURN

dentro do `body`, a palavra reservada `return` encerra a execução da função e devolve um valor ao ponto de chamada:
```
return expression;
```

* quando a função possui `retType`, `expression` deve resultar em um valor compatível com esse tipo
* quando a função não possui `retType` (retorno `void`), `return` pode ser usado sem `expression`, apenas para encerrar a execução antes do fim do `body`:
```
return;
```

## EXEMPLO

```
func(a: int, b: int): int {
    return a + b;
} soma

func(nome: string) {
    if(nome == "") return;
} validaNome
```