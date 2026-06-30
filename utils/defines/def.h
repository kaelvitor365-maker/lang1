#pragma once

#define CLASS(name, scope) struct name##_t scope; typedef struct name##_t name
#define ENUM(name, scope) enum name##_t scope; typedef enum name##_t name