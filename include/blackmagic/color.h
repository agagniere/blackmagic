#pragma once

/**
 * @file
 *
 */

#include "blackmagic/token.h" // STRINGIZE
#include "blackmagic/fold.h" // FOLD

/** @name Font style */
///@{
/**
 * Reset font style.
 * A color sequence with only `NORMAL` resets all style, color and background color
 */
#define NORMAL     0
#define BOLD       1 /**< . */
#define DIM        2 /**< . */
#define ITALIC     3 /**< . */
#define UNDERLINED 4 /**< . */
#define NEGATIVE   6 /**< . */
///@}

/** @name Font color */
///@{
#define BLACK      30 /**< . */
#define RED        31 /**< . */
#define GREEN      32 /**< . */
#define YELLOW     33 /**< . */
#define BLUE       34 /**< . */
#define PURPLE     35 /**< . */
#define CYAN       36 /**< . */
#define LIGHT_GREY 37 /**< . */
#define DEFAULT    39 /**< Reset font color */
#define WHITE      97 /**< . */
///@}

/** @name Background color */
///@{
#define BG_BLACK      40 /**< . */
#define BG_RED        41 /**< . */
#define BG_GREEN      42 /**< . */
#define BG_YELLOW     43 /**< . */
#define BG_BLUE       44 /**< . */
#define BG_PURPLE     45 /**< . */
#define BG_CYAN       46 /**< . */
#define BG_LIGHT_GREY 47 /**< . */
#define BG_DEFAULT    49 /**< Reset background color */
#define BG_WHITE      107 /**< . */
///@}

/**
 * Expands to a string literal containig an escape code setting the terminal color.
 * @since 0.1
 */
#define COLOR(...) STRINGIZE(\e[FOLD(COLOR_JOIN __VA_OPT__(,) __VA_ARGS__)m)

#define COLOR_JOIN(A, B) A;B
