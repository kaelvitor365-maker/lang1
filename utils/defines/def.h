#pragma once

#define INTERN_NAME(name) struct name##_t

#define CAST_TO(type, val) ((type)(val))


#define len(object) ((object)->__size)
#define capacity(object) ((object)->__capacity)
#define size_value(object) ((object)->__size_value)
#define VECTOR_FOR_EACH(object, type_with_nameVar, body) for(__it__Vector* _it = VectorF.begin(object); _it->__pos != VectorF.end(object); _it = VectorF.next(_it)){ type_with_nameVar = VectorF.getIterator(_it); body  }


#define FUNCTIONS(name, ...) (*name)(__VA_ARGS__);
#define CLASS(name, scope) INTERN_NAME(name) scope; typedef INTERN_NAME(name) name;
#define ENUM(name, ...) typedef enum { __VA_ARGS__} name;

#define WITH_LEXER(name, __arq, body) do{ Lexer* name = newLexer(__arq); body freeLexer(name); }while(0)