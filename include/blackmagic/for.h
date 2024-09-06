#pragma once

#include "blackmagic/arg_count.h" // ARG_COUNT
#include "blackmagic/token.h" // CONCAT

/**
 * @file
 * Generate code by calling a macro repeatedly
 */

/** To be used with @ref FOR */
#define EACH(...) ARG_COUNT(__VA_ARGS__) __VA_OPT__(,) __VA_ARGS__

/**
 * Call @p MACRO on each item of the @p LIST, forwarding extra arguments if any.
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
#define FOR_(N, ...)  CONCAT(FOR_, N)(__VA_ARGS__)
#define FOR_0(M, ...)
#define FOR_1(A, M, ...)          M(__VA_ARGS__ __VA_OPT__(,) A)
#define FOR_2(A, B, M, ...)       M(__VA_ARGS__ __VA_OPT__(,) A) M(__VA_ARGS__ __VA_OPT__(,) B)
#define FOR_3(A, B, C, M, ...)    M(__VA_ARGS__ __VA_OPT__(,) A) M(__VA_ARGS__ __VA_OPT__(,) B) M(__VA_ARGS__ __VA_OPT__(,) C)
#define FOR_4(A, B, C, D, M, ...) M(__VA_ARGS__ __VA_OPT__(,) A) M(__VA_ARGS__ __VA_OPT__(,) B) M(__VA_ARGS__ __VA_OPT__(,) C) M(__VA_ARGS__ __VA_OPT__(, ) D)
#define FOR_5(A, B, C, D, E, M, ...) \
	M(__VA_ARGS__ __VA_OPT__(,) A) \
	FOR_4(B, C, D, E, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_6(A, B, C, D, E, F, M, ...) \
	FOR_3(A, B, C, M __VA_OPT__(,) __VA_ARGS__)	\
	FOR_3(D, E, F, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_7(A, B, C, D, E, F, G, M, ...) \
	M(__VA_ARGS__ __VA_OPT__(,) A) \
	FOR_6(B, C, D, E, F, G, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_8(A, B, C, D, E, F, G, H, M, ...) \
	FOR_4(A, B, C, D, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_4(E, F, G, H, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_9(A, B, C, D, E, F, G, H, I, M, ...) \
	M(__VA_ARGS__ __VA_OPT__(,) A) \
	FOR_8(B, C, D, E, F, G, H, I, M __VA_OPT__(,) __VA_ARGS__)
#define FOR_10(A, B, C, D, E, F, G, H, I, J, M, ...) \
	FOR_5(A, B, C, D, E, M __VA_OPT__(,) __VA_ARGS__) \
	FOR_5(F, G, H, I, J, M __VA_OPT__(,) __VA_ARGS__)
///@endcond
