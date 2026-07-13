SRC := 	\
		src/lexer/lexer.c \
		src/parser/parser.c \
		src/ast/ast.c \
		src/eval/eval.c 
UTILS := utils/vector/vector.c
MAIN := main.c

CSYSTEMFLAGS := \
				-Wall \
				-Wextra\
				-Werror\
				-g
CBUILDFLAGS :=	\
				-Iutils\
				-Iutils/vector \
				-Iutils/defines \
				-Isrc \
				-Isrc/lexer \
				-Isrc/parser \
				-Isrc/ast \
				-Isrc/eval


SRCS := $(SRC) $(UTILS) $(MAIN)
OBJS := $(SRCS:%.c=build/%.o)

TARGET := build/lang

CC = gcc

.PHONY: all run clean

all: $(TARGET)

run: $(TARGET)
	./$(TARGET) $(ARGS)

$(TARGET): $(OBJS)
	@echo "Linking $@"
	@$(CC) $(CSYSTEMFLAGS) $(CBUILDFLAGS) $^ -o $@

build/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	@$(CC) $(CSYSTEMFLAGS) $(CBUILDFLAGS) -c $< -o $@

clean:
	@echo "Cleaing up..."
	@rm -rf build




