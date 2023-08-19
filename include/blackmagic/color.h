#pragma once

#include "blackmagic/tools.h"

#define NORMAL     0
#define BOLD       1
#define DIM        2
#define ITALIC     3
#define UNDERLINED 4
#define NEGATIVE   6

#define BLACK      30
#define RED        31
#define GREEN      32
#define YELLOW     33
#define BLUE       34
#define PURPLE     35
#define CYAN       36
#define LIGHT_GREY 37
#define DEFAULT    39
#define WHITE      97

#define BG_BLACK      40
#define BG_RED        41
#define BG_GREEN      42
#define BG_YELLOW     43
#define BG_BLUE       44
#define BG_PURPLE     45
#define BG_CYAN       46
#define BG_LIGHT_GREY 47
#define BG_DEFAULT    49
#define BG_WHITE      107

#define _COLOR_JOIN(A, B) A;B
#define COLOR(...) PP_STR(\e[FOLD_RIGHT(_COLOR_JOIN, __VA_ARGS__)m)
