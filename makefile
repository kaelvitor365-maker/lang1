CXX := g++

TARGET := build/lang

SRC := \
	src/lexer/lexer.cpp \
	src/lexer/_lexer.cpp \
	src/lexer/lexer_utils.cpp \
	src/parser/parser.cpp \
	src/parser/implements/primary.cpp \
	src/parser/implements/unary.cpp \
	src/parser/implements/factor.cpp \
	src/parser/implements/term.cpp \
	src/parser/implements/bitwise.cpp \
	src/parser/implements/comparison.cpp\
	src/parser/implements/logical.cpp \
	src/parser/implements/postfix.cpp \
	src/ast/ast.cpp \
	src/ast/print.cpp \
	src/eval/eval.cpp \
	src/token/token.cpp \
	main.cpp

OBJS := $(patsubst %.cpp,build/%.o,$(SRC))

CXXFLAGS := \
	-std=c++20 \
	-Wall \
	-Wextra \
	-Werror \
	-g \
	-Iincludes \
	-Iincludes/lexer \
	-Iincludes/token \
	-Iincludes/ast \
	-Iincludes/ast/ASTprinter \
	-Isrc \
	-Isrc/lexer \
	-Isrc/parser \
	-Isrc/parser/implements \
	-Isrc/ast \
	-Isrc/eval


FILE := lang_arqs/test.lang
.PHONY: all run clean rebuild

all: $(TARGET)

run: $(TARGET)
	./$(TARGET) $(FLAG) $(FILE)

$(TARGET): $(OBJS)
	@echo "Linking $@"
	@mkdir -p $(dir $@)
	@$(CXX) $(OBJS) -o $@

build/%.o: %.cpp
	@echo "Compiling $<"
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Cleaning..."
	@rm -rf build

rebuild: clean all