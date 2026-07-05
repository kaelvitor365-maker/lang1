#pragma once

#define INTERN_NAME(name) struct name##_t
#define PTR(type) type* 
#define USE_PTR(ptr) (*ptr) 
#define CAST_TO(type, val) ((type)(val))

#define len(object) ((object)->__size)


#define FUNCTIONS(name, ...) (*name)(__VA_ARGS__);
#define CLASS(name, scope) INTERN_NAME(name) scope; typedef INTERN_NAME(name) name;
#define ENUM(name, ...) typedef enum { __VA_ARGS__} name;
