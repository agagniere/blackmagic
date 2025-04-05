#pragma once

#include "blackmagic/arg_count.h" // ARG_COUNT
#include "blackmagic/token.h"     // CONCAT

/**
 * @file
 * Generate code by calling a macro repeatedly
 */

/** To be used with @ref FOR */
#define EACH(...) ARG_COUNT(__VA_ARGS__) __VA_OPT__(,) __VA_ARGS__

/**
 * Call @p MACRO on each item of the @p LIST, forwarding extra arguments if any.
 *
 * __Example__
 * @code{.c}
 * FOR(EACH(A, B, C), F, X, Y)
 * @endcode
 * will expand to:
 * @code{.c}
 * F(X, Y, A)
 * F(X, Y, B)
 * F(X, Y, C)
 * @endcode
 * @param LIST shall be of the form `EACH(P0, P1, ..., Pn-1)`
 * @param MACRO shall be a function-like macro
 * @since 0.2
 */
#define FOR(LIST, MACRO, ...) FOR_(LIST, MACRO __VA_OPT__(,) __VA_ARGS__)

///@cond
#define FOR_(N, ...) CONCAT(FOR_, N)(__VA_ARGS__)
#define FOR_0(M, ...)
#define FOR_1(A, M, ...)    M(__VA_ARGS__ __VA_OPT__(,) A)
#define FOR_2(A, B, M, ...) M(__VA_ARGS__ __VA_OPT__(,) A) M(__VA_ARGS__ __VA_OPT__(,) B)
#define FOR_3(A, B, C, M, ...) \
	M(__VA_ARGS__ __VA_OPT__(,) A) \
	M(__VA_ARGS__ __VA_OPT__(,) B) \
	M(__VA_ARGS__ __VA_OPT__(,) C)
#define FOR_4(A, B, C, D, M, ...) \
	M(__VA_ARGS__ __VA_OPT__(,) A) M(__VA_ARGS__ __VA_OPT__(,) B) \
	M(__VA_ARGS__ __VA_OPT__(,) C) M(__VA_ARGS__ __VA_OPT__(,) D)
#define FOR_5(A, B, C, D, E, M, ...) \
	M(__VA_ARGS__ __VA_OPT__(,) A) \
	FOR_4(B, C, D, E, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_6(A, B, C, D, E, F, M, ...) \
	FOR_3(A, B, C, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_3(D, E, F, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_7(A, B, C, D, E, F, G, M, ...) \
	M(__VA_ARGS__ __VA_OPT__(,) A) \
	FOR_6(B, C, D, E, F, G, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_8(A, B, C, D, E, F, G, H, M, ...) \
	FOR_4(A, B, C, D, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_4(E, F, G, H, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_9(A, B, C, D, E, F, G, H, I, M, ...) \
	FOR_3(A, B, C, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_3(D, E, F, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_3(G, H, I, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_10(A, B, C, D, E, F, G, H, I, J, M, ...) \
	FOR_5(A, B, C, D, E, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_5(F, G, H, I, J, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_11(A, B, C, D, E, F, G, H, I, J, K, M, ...) \
	M(__VA_ARGS__ __VA_OPT__(,) A) \
	FOR_10(B, C, D, E, F, G, H, I, J, K, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_12(A, B, C, D, E, F, G, H, I, J, K, L, M, ...) \
	FOR_4(A, B, C, D, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_4(E, F, G, H, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_4(I, J, K, L, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_13(A, B, C, D, E, F, G, H, I, J, K, L, N, M, ...) \
	M(__VA_ARGS__ __VA_OPT__(,) A) \
	FOR_12(B, C, D, E, F, G, H, I, J, K, L, N, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_14(A, B, C, D, E, F, G, H, I, J, K, L, N, O, M, ...) \
	FOR_7(A, B, C, D, E, F, G, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_7(H, I, J, K, L, N, O, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_15(A, B, C, D, E, F, G, H, I, J, K, L, N, O, P, M, ...) \
	FOR_5(A, B, C, D, E, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_5(F, G, H, I, J, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_5(K, L, N, O, P, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_16(A, B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, M, ...) \
	FOR_4(A, B, C, D, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_4(E, F, G, H, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_4(I, J, K, L, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_4(N, O, P, Q, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_17(A, B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, M, ...) \
	M(__VA_ARGS__ __VA_OPT__(, ) A) \
	FOR_16(B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_18(A, B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, S, M, ...) \
	FOR_9(A, B, C, D, E, F, G, H, I, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_9(J, K, L, N, O, P, Q, R, S, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_19(A, B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, S, T, M, ...) \
	M(__VA_ARGS__ __VA_OPT__(, ) A) \
	FOR_18(B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, S, T, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_20(A, B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, S, T, U, M, ...) \
	FOR_5(A, B, C, D, E, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_5(F, G, H, I, J, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_5(K, L, N, O, P, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_5(Q, R, S, T, U, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_21(A, B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, S, T, U, V, M, ...) \
	FOR_7(A, B, C, D, E, F, G, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_7(H, I, J, K, L, N, O, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_7(P, Q, R, S, T, U, V, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_22(A, B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, S, T, U, V, W, M, ...) \
	FOR_11(A, B, C, D, E, F, G, H, I, J, K, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_11(L, N, O, P, Q, R, S, T, U, V, W, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_23(A, B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, S, T, U, V, W, X, M, ...) \
	M(__VA_ARGS__ __VA_OPT__(, ) A) \
	FOR_22(B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, S, T, U, V, W, X, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_24(A, B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, S, T, U, V, W, X, Y, M, ...) \
	FOR_12(A, B, C, D, E, F, G, H, I, J, K, L, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_12(N, O, P, Q, R, S, T, U, V, W, X, Y, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_25(A, B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, M, ...) \
	M(__VA_ARGS__ __VA_OPT__(, ) A) \
	FOR_24(B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_26(A, B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, AA, M, ...) \
	FOR_13(A, B, C, D, E, F, G, H, I, J, K, L, N, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_13(O, P, Q, R, S, T, U, V, W, X, Y, Z, AA, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_27(A, B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, AA, AB, M, ...) \
	M(__VA_ARGS__ __VA_OPT__(, ) A) \
	FOR_26(B, C, D, E, F, G, H, I, J, K, L, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, AA, AB, M __VA_OPT__(,) __VA_ARGS__)
///@endcond
