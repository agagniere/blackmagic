#pragma once

#include "tools.h"

/* GCC builtins */

#define PRIVATE_OVERLOAD(x, name, T) __builtin_choose_expr(__builtin_types_compatible_p(typeof(x), T), name(T) (x),

#define R_PAREN_V(...) )

#define overload(x, name, ...)                        \
    FOR(EACH(__VA_ARGS__), PRIVATE_OVERLOAD, x, name) \
        (void)0                                       \
    FOR(EACH(__VA_ARGS__), R_PAREN_V, IGNORED)

/* C11 keyword */

#define PRIVATE_GENERIC(name, T) T:name(T),

#define Generic(x, name, ...)                        \
    _Generic(x, FOR(EACH(__VA_ARGS__), PRIVATE_GENERIC, name))
