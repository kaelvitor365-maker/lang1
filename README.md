
```
lang
├─ includes
│  ├─ ast
│  │  ├─ ASTprinter
│  │  │  └─ ASTprinter.hpp
│  │  ├─ ast.hpp
│  │  ├─ expr.hpp
│  │  ├─ node.hpp
│  │  └─ stmt.hpp
│  ├─ eval.hpp
│  ├─ lexer
│  │  ├─ README.md
│  │  ├─ lexer.hpp
│  │  └─ lexer_utils.hpp
│  ├─ parser.hpp
│  └─ token
│     ├─ README.md
│     ├─ _token.hpp
│     └─ token.hpp
├─ lang_arqs
│  └─ test.lang
├─ main.cpp
├─ makefile
└─ src
   ├─ ast
   │  ├─ ast.cpp
   │  ├─ printExpr.cpp
   │  └─ printStmt.cpp
   ├─ eval
   │  └─ eval.cpp
   ├─ lexer
   │  ├─ _lexer.cpp
   │  ├─ lexer.cpp
   │  └─ lexer_utils.cpp
   ├─ parser
   │  ├─ expression
   │  │  ├─ bitwise.cpp
   │  │  ├─ comparison.cpp
   │  │  ├─ factor.cpp
   │  │  ├─ logical.cpp
   │  │  ├─ postfix.cpp
   │  │  ├─ primary.cpp
   │  │  ├─ term.cpp
   │  │  └─ unary.cpp
   │  └─ parser.cpp
   └─ token
      └─ token.cpp

```