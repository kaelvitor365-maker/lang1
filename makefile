SRC = 	src/lexer/lexer.c \
		src/parser/parser.c \
		src/ast/ast.c \
		src/eval/eval.c

UTILS = utils/vector/vector.c

CFLAGS = -Isrc -Iutils -Iutils/defines -Iutils/vector -Wall -Wextra

all:
	mkdir -p build
	gcc $(CFLAGS) main.c $(SRC) $(UTILS) -o build/lang

run:
	mkdir -p build
	gcc $(CFLAGS) main.c $(SRC) $(UTILS) -o build/lang
	./build/lang
