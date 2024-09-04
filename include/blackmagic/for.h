#pragma once

/**
 * @file
 * Generate code by calling a macro repeatedly
 */

/** To be used with @ref FOR */
#define EACH(...) ARG_COUNT(__VA_ARGS__) __VA_OPT__(,) __VA_ARGS__

/**
 * Call @p MACRO on each item of the @p LIST, forwarding extra arguments if any
 * # Example
 * @code{.c}
 * FOR(EACH(A, B, C), F, X, Y)
 * @endcode
 * will expand to:
 * @code{.c}
 * F(A, X, Y)
 * F(B, X, Y)
 * F(C, X, Y)
 * @endcode
 * @param LIST shall be of the form `EACH(P0, P1, ..., Pn-1)`
 * @param MACRO shall be a function-like macro
 */
#define FOR(LIST, MACRO, ...) _FOR(LIST, MACRO __VA_OPT__(,) __VA_ARGS__)
