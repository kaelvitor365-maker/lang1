#pragma once

#define CLASS(name, scope) struct name##_t scope; typedef struct name##_t name;
#define ENUM(name, ...) typedef enum { __VA_ARGS__} name;
#define CAST_TO(type, val) ((type)(val))
#define len(object) ((object)->__size)
#define VECTOR_FOR_EACH(vector, type, var, body) for(size_t _i = 0; _i < len(vector); ++_i) { type* var = getVector(vector, _i); body}
#define PTR(type) type* 
#define USE_PTR(ptr) (*ptr) 
