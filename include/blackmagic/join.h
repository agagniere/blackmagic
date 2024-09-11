#pragma once

#include "blackmagic/token.h" // CONCAT
#include "blackmagic/fold.h" // FOLD

/**
 * @file
 * Concatenate, with a separator
 */

/** Create an identifier with a prefix/suffix. */
#define JOIN2(A, B) CONCAT(CONCAT(A, _), B)

/**
 * Create an identifier consisting of all arguments separated by underscores.
 *
 * __Example__
 * @code{.c}
 * JOIN(prefix, name, __COUNTER__)
 * @endcode
 * May evaluate to:
 * @code{.c}
 * prefix_name_2
 * @endcode
 * @since 0.2
 */
#define JOIN(...) FOLD(JOIN2 __VA_OPT__(,) __VA_ARGS__)
