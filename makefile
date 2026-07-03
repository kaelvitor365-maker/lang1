SRC = 	src/lexer/lexerPass1.c \
		src/lexer/lexerPass2.c \
		src/parser/parser.c \
		src/ast/ast.c \
		src/eval/eval.c

UTILS = utils/vector/vector.c

CFLAGS = -Isrc -Iutils -Iutils/defines -Wall -Wextra

all:
	mkdir -p build
	gcc $(CFLAGS) main.c $(SRC) $(UTILS) -o build/lang

run:
	./build/lang $(ARGS)
