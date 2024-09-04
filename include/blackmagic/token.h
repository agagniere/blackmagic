#pragma once

/**
 * @file
 * Token manipulation.
 */

/**
 * Evaluates as a string literal containing @p TEXT, without performing macro expansion.
 *
 * __Example__
 * ```
 * LITERAL_STRINGIZE(__LINE__)
 * ```
 * Evaluates to:
 * ```
 * "__LINE__"
 * ```
 * @param TEXT doesn't even have to be valid C !
 * @since 0.2
 */
#define LITERAL_STRINGIZE(TEXT) #TEXT

/**
 * Evaluates as a string literal containing @p EXPRESSION with its macros expanded.
 *
 * __Example__
 * ```
 * STRINGIZE(__LINE__)
 * ```
 * May evaluate to:
 * ```
 * "21"
 * ```
 * @param EXPRESSION doesn't even have to be valid C !
 * @since 0.2
 */
#define STRINGIZE(EXPRESSION) LITERAL_STRINGIZE(EXPRESSION)

/**
 * Evaluates as a single identifier token, that is @p TEXT1 concatenated with @p TEXT2,
 * not evaluating any macro inside
 * @since 0.2
 */
#define LITERAL_CONCAT(TEXT1, TEXT2) TEXT1 ## TEXT2

/**
 * Evaluates as a single identifier token,
 * that is the evaluation of @p EXPRESSION1 concatenated with the evaluation of @p EXPRESSION2
 * @since 0.2
 */
#define CONCAT(EXPRESSION1, EXPRESSION2) LITERAL_CONCAT(EXPRESSION1, EXPRESSION2)
