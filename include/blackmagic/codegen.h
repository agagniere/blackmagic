#pragma once

/** @file */

/** Expands to its arguments */
#define IDENTITY(...) __VA_ARGS__

/** Apply @F to the rest of the arguments, adding a comma at the end. */
#define ADD_COMMA(F, ...) F(__VA_ARGS__),

#define ADD_COMMA_FLAT(A, B) A B,
