#pragma once

/**
 * @file
 * Apply a binary macro on any number of argument
 * @author Antoine GAGNIERE
 */

#include "blackmagic/arg_count.h" // ARG_COUNT
#include "blackmagic/token.h"     // CONCAT

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
