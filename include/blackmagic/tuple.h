#pragma once

#include "blackmagic/token.h" // CONCAT

/**
 * @file
 * Manipulate tuples
 */

/** Extract the first element of a tuple */
#define TUPLE_FIRST(A, ...) A
/** Extract the second element of a tuple */
#define TUPLE_SECOND(A, B, ...) B
/** Extract the third element of a tuple */
#define TUPLE_THIRD(A, B, C, ...) C

/** Extract the Nth element of a tuple */
#define TUPLE_GET(N, TUPLE) CONCAT(TUPLE_GET_, N) TUPLE

#define TUPLE_GET_0(A, ...) A
#define TUPLE_GET_1(A,B, ...) B
#define TUPLE_GET_2(A,B,C, ...) C
#define TUPLE_GET_3(A,B,C,D, ...) D
#define TUPLE_GET_4(A,B,C,D,E, ...) E
#define TUPLE_GET_5(A,B,C,D,E,F, ...) F
#define TUPLE_GET_6(A,B,C,D,E,F,G, ...) G
