CXX := g++

TARGET := build/lang

SRC := \
	src/lexer/lexer.cpp \
	src/lexer/_lexer.cpp \
	src/lexer/lexer_utils.cpp \
	src/parser/parser.cpp \
	src/ast/ast.cpp \
	src/eval/eval.cpp \
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
	-Isrc \
	-Isrc/lexer \
	-Isrc/parser \
	-Isrc/ast \
	-Isrc/eval

.PHONY: all run clean rebuild

all: $(TARGET)

run: $(TARGET)
	./$(TARGET) $(ARGS)

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