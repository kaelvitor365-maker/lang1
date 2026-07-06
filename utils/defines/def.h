#pragma once

#define INTERN_NAME(name) struct name##_t

#define CAST_TO(type, val) ((type)(val))


#define len(object) ((object)->__size)
#define capacity(object) ((object)->__capacity)
#define size_value(object) ((object)->__size_value)

#define FUNCTIONS(name, ...) (*name)(__VA_ARGS__);
#define CLASS(name, scope) INTERN_NAME(name) scope; typedef INTERN_NAME(name) name;
#define ENUM(name, ...) typedef enum { __VA_ARGS__} name;
