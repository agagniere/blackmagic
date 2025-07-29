#pragma once

/**
 * @file
 * White magic: Straightforward macros
 */

/**
 * Number of elements of a C array.
 *
 * __Example__
 * @code{.c}
 * short    foo[]  = {21, 84, 57};
 * unsigned length = ARRAY_LENGTH(foo);
 * @endcode
 * Will result in `length = 3`
 * @since 0.2
 */
#define ARRAY_LENGTH(ARRAY) (sizeof(ARRAY) / sizeof(*(ARRAY)))

/** Highest of two numbers */
#define max(A, B) ({ typeof(A) _a = (A); typeof(B) _b = (B); _a >= _b ? _a : _b; })

/** Lowest of two numbers */
#define min(A, B) ({ typeof(A) _a = (A); typeof(B) _b = (B); _a <= _b ? _a : _b; })
