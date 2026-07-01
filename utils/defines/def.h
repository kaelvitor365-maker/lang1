#pragma once

#define CLASS(name, scope) struct name##_t scope; typedef struct name##_t name
#define ENUM(name, scope) enum name##_t scope; typedef enum name##_t name
#define CAST_TO(type, val) ((type)(val))
#define len(object) ((object)->__size)
#define VECTOR_FOR_EACH(vector, type, var, body) for(size_t _i = 0; _i < len(vector); ++i) { type* var = getVector(vector, _i); body}