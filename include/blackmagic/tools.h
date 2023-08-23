#pragma once

#include "private_tools.h"
#include "private_for.h"

/*
** Fundamentals
*/

// start array length
/** The number of elements of a C array */
#define PREPRO_ARRAY_LENGTH(A) (sizeof(A) / sizeof(*(A)))
// end array length

// start stringize
/** Evaluates as a string literal from @p TEXT, not evaluating any macro inside */
#define PREPRO_STRINGIZE_NOEVAL(TEXT) #TEXT

/** Evaluates as a string literal from @p EXPRESSION, after having evaluated its macros */
#define PREPRO_STRINGIZE(EXPRESSION) PREPRO_STRINGIZE_NOEVAL(EXPRESSION)
// end stringize

// start concatenate
/**
 * Evaluates as a single identifier token, that is @p TEXT1 concatenated with @p TEXT2,
 * not evaluating any macro inside
 */
#define PREPRO_CONCAT_NOEVAL(TEXT1, TEXT2) TEXT1 ## TEXT2
/**
 * Evaluates as a single identifier token,
 * that is the evaluation of @p EXPRESSION1 concatenated with the evaluation of @p EXPRESSION2
 */
#define PREPRO_CONCAT(EXPRESSION1, EXPRESSION2) PREPRO_CONCAT_NOEVAL(EXPRESSION1, EXPRESSION2)
// end concatenate


#define PP_MAX(A, B)      (A > B ? A : B)
#define PP_MIN(A, B)      (A < B ? A : B)

#define ARG_COUNT(...)    _ARGCNT1(__VA_ARGS__)
#define ID(...)           __VA_ARGS__
#define ADD_COMMA(F, ...) F(__VA_ARGS__),

/*
** Higher level
*/

#define EACH(...)         ARG_COUNT(__VA_ARGS__), __VA_ARGS__
#define FOR(...)          _FOR(__VA_ARGS__)

#define FOLD_RIGHT(F, ...) _FOLDR(F, __VA_ARGS__)

#define CAT(...)          FOLD_RIGHT(PP_CAT, __VA_ARGS__)
#define MERGE(...)        FOLD_RIGHT(_MERGE, __VA_ARGS__)

/*
** Numbers manipulation tools
*/

#define MIN(...) _MINMAX(_LESSER, __VA_ARGS__)
#define MAX(...) _MINMAX(_GREATER, __VA_ARGS__)
#define ABS(V)   MAX(V, -(V))
