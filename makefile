CXX := g++

TARGET := build/lang

SRC := \
	src/lexer/lexer.cpp \
	src/lexer/_lexer.cpp \
	src/lexer/lexer_utils.cpp \
	src/parser/parser.cpp \
	src/parser/expression/primary.cpp \
	src/parser/expression/unary.cpp \
	src/parser/expression/factor.cpp \
	src/parser/expression/term.cpp \
	src/parser/expression/bitwise.cpp \
	src/parser/expression/comparison.cpp \
	src/parser/expression/logical.cpp \
	src/parser/expression/postfix.cpp \
	src/parser/statements/variableDeclaration.cpp \
	src/parser/statements/assingment.cpp \
	src/parser/statements/block.cpp \
	src/parser/statements/ifStatement.cpp \
	src/parser/statements/whileStatement.cpp \
	src/parser/statements/forStatement.cpp \
	src/ast/ast.cpp \
	src/ast/printExpr.cpp \
	src/ast/printStmt.cpp \
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
	-Iincludes/parser \
	-Iincludes/token \
	-Iincludes/ast \
	-Iincludes/ast/ASTprinter \
	-Isrc \
	-Isrc/lexer \
	-Isrc/parser \
	-Isrc/parser/expression \
	-Isrc/parser/statements \
	-Isrc/ast \
	-Isrc/eval


FILE := lang_arqs/test.lang
.PHONY: all run clean rebuild restart tokenize parserize

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

restart: clean run

tokenize:
	./$(TARGET) --Tokenize $(FILE)

parserize:
	./$(TARGET) --Parserize $(FILE)
