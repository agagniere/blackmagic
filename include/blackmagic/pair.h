#pragma once

/**
 * @file
 * Manipulate pairs
 */

/** Extract the first element of a pair */
#define PAIR_FIRST(A, B) A
/** Extract the second element of a pair */
#define PAIR_LAST(A, B) B

/** Expand to both elements of a pair following each other */
#define PAIR_FLATTEN(A, B) A B
/** Expands to an assignation */
#define PAIR_ASSIGN(A, B) A = B
