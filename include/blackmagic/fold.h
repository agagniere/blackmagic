#pragma once

/**
 * @file
 * Apply a binary macro on any number of argument
 */

#include "blackmagic/arg_count.h" // ARG_COUNT
#include "blackmagic/token.h"     // CONCAT

/** @name Configuration */
///@{
#ifndef FOLD
/** Default fold to use, can be overridden */
#	define FOLD TREE_FOLD
#endif
///@}

/**
 * Apply the binary macro @p M on pairs of inputs, in a tree-like fashion.
 * __Example__
 * @code{.c}
 * TREE_FOLD(F, A, B, C, D)
 * @endcode
 * expands to:
 * @code{.c}
 * F(F(A, B), F(C, D))
 * @endcode
 * @since 0.2
 */
#define TREE_FOLD(M, ...) CONCAT(TREE_FOLD_, ARG_COUNT(__VA_ARGS__))(M __VA_OPT__(,) __VA_ARGS__)

/**
 * Apply the binary macro @p M on pairs of inputs, first grouping the right-most arguments.
 * __Example__
 * @code{.c}
 * FOLD_RIGHT(F, A, B, C, D)
 * @endcode
 * expands to:
 * @code{.c}
 * F(A, F(B, F(C, D)))
 * @endcode
 * @since 0.2
 */
#define FOLD_RIGHT(M, ...) CONCAT(FOLD_RIGHT_, ARG_COUNT(__VA_ARGS__))(M __VA_OPT__(,) __VA_ARGS__)

/// @cond
#define TREE_FOLD_0(M)
#define TREE_FOLD_1(M, A)                            A
#define TREE_FOLD_2(M, A, B)                         M(A, B)
#define TREE_FOLD_3(M, A, B, C)                      M(A, M(B, C))
#define TREE_FOLD_4(M, A, B, C, D)                   M(M(A, B), M(C, D))
#define TREE_FOLD_5(M, A, ...)                       M(A, TREE_FOLD_4(M, __VA_ARGS__))
#define TREE_FOLD_6(M, A, B, ...)                    M(M(A, B), TREE_FOLD_4(M, __VA_ARGS__))
#define TREE_FOLD_7(M, A, B, C, ...)                 M(M(A, M(B, C)), TREE_FOLD_4(M, __VA_ARGS__))
#define TREE_FOLD_8(M, A, B, C, D, E, F, G, H)       M(M(M(A, B), M(C, D)), M(M(E, F), M(G, H)))
#define TREE_FOLD_9(M, A, ...)                       M(A, TREE_FOLD_8(M, __VA_ARGS__))
#define TREE_FOLD_10(M, A, B, ...)                   M(M(A, B), TREE_FOLD_8(M, __VA_ARGS__))
#define TREE_FOLD_11(M, A, B, C, ...)                M(M(A, M(B, C)), TREE_FOLD_8(M, __VA_ARGS__))
#define TREE_FOLD_12(M, A, B, C, D, ...)             M(M(M(A, B), M(C, D)), TREE_FOLD_8(M, __VA_ARGS__))
#define TREE_FOLD_13(M, A, B, C, D, E, ...)          M(TREE_FOLD_5(M, A, B, C, D, E), TREE_FOLD_8(M, __VA_ARGS__))
#define TREE_FOLD_14(M, A, B, C, D, E, F, ...)       M(TREE_FOLD_6(M, A, B, C, D, E, F), TREE_FOLD_8(M, __VA_ARGS__))
#define TREE_FOLD_15(M, A, B, C, D, E, F, G, ...)    M(TREE_FOLD_7(M, A, B, C, D, E, F, G), TREE_FOLD_8(M, __VA_ARGS__))
#define TREE_FOLD_16(M, A, B, C, D, E, F, G, H, ...) M(TREE_FOLD_8(M, A, B, C, D, E, F, G, H), TREE_FOLD_8(M, __VA_ARGS__))
#define TREE_FOLD_17(M, A, ...)                      M(A, TREE_FOLD_16(M, __VA_ARGS__))
#define TREE_FOLD_18(M, A, B, ...)                   M(M(A, B), TREE_FOLD_16(M, __VA_ARGS__))
#define TREE_FOLD_19(M, A, B, C, ...)                M(M(A, M(B, C)), TREE_FOLD_16(M, __VA_ARGS__))
#define TREE_FOLD_20(M, A, B, C, D, ...)             M(M(M(A, B), M(C, D)), TREE_FOLD_16(M, __VA_ARGS__))

#define FOLD_RIGHT_0(M)
#define FOLD_RIGHT_1(M, A)             A
#define FOLD_RIGHT_2(M, A, B)          M(A, B)
#define FOLD_RIGHT_3(M, A, B, C)       M(A, M(B, C))
#define FOLD_RIGHT_4(M, A, B, C, D)    M(A, M(B, M(C, D)))
#define FOLD_RIGHT_5(M, A, B, C, D, E) M(A, M(B, M(C, M(D, E))))
#define FOLD_RIGHT_6(M, A, ...)        M(A, FOLD_RIGHT_5(M, __VA_ARGS__))
#define FOLD_RIGHT_7(M, A, B, ...)     M(A, M(B, FOLD_RIGHT_5(M, __VA_ARGS__)))
#define FOLD_RIGHT_8(M, A, B, C, ...)  M(A, M(B, M(C, FOLD_RIGHT_5(M, __VA_ARGS__))))
#define FOLD_RIGHT_9(M, A, ...)        M(A, FOLD_RIGHT_8(M, __VA_ARGS__))
#define FOLD_RIGHT_10(M, A, ...)       M(A, FOLD_RIGHT_9(M, __VA_ARGS__))
#define FOLD_RIGHT_11(M, A, ...)       M(A, FOLD_RIGHT_10(M, __VA_ARGS__))
#define FOLD_RIGHT_12(M, A, ...)       M(A, FOLD_RIGHT_11(M, __VA_ARGS__))
#define FOLD_RIGHT_13(M, A, ...)       M(A, FOLD_RIGHT_12(M, __VA_ARGS__))
#define FOLD_RIGHT_14(M, A, ...)       M(A, FOLD_RIGHT_13(M, __VA_ARGS__))
#define FOLD_RIGHT_15(M, A, ...)       M(A, FOLD_RIGHT_14(M, __VA_ARGS__))
#define FOLD_RIGHT_16(M, A, ...)       M(A, FOLD_RIGHT_15(M, __VA_ARGS__))
#define FOLD_RIGHT_17(M, A, ...)       M(A, FOLD_RIGHT_16(M, __VA_ARGS__))
#define FOLD_RIGHT_18(M, A, ...)       M(A, FOLD_RIGHT_17(M, __VA_ARGS__))
#define FOLD_RIGHT_19(M, A, ...)       M(A, FOLD_RIGHT_18(M, __VA_ARGS__))
#define FOLD_RIGHT_20(M, A, ...)       M(A, FOLD_RIGHT_19(M, __VA_ARGS__))
///@endcond
