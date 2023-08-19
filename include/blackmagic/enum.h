#pragma once

/**
 * @file enum.h
 * @brief Generate functions for enumerations
 */

#include "tools.h"

#include <stdbool.h>

#define PP_PAIR_APPLY(F, P) F P
#define PP_PAIR_ASSIGN(K, V) K = V
#define PP_PAIR_FIRST(K, V) K
#define PP_PAIR_SECOND(K, V) V
#define PP_TO_STRING_CASE(K, V) case (V): return PP_STR(K);

#define _ECNT(N) _MERGE(N, count)
#define _EMAX(N) _MERGE(N, upper_bound)

/**
@code{.c}
DECLARE_ENUM_WITH_VALUES(
    cardinal,
    (EAST,  1),
    (WEST,  2),
    (NORTH, 4),
    (SOUTH, 8)
)
@endcode
evaluates to:
@code{.c}
enum cardinal
{
	East  = 1,
	West  = 2,
	North = 4,
	South = 8,
	cardinal_upper_bound
};
static inline const char* cstring_from_cardinal(enum cardinal value)
{
	switch (value)
	{
	case (1): return "East";
	case (2): return "West";
	case (4): return "North";
	case (8): return "South";
	default: return ((void*)0);
	}
}
static inline _Bool is_valid_cardinal(long value)
{
	return cstring_from_cardinal((enum cardinal)value) != ((void*)0);
}
static inline _Bool has_next_cardinal(enum cardinal* it)
{
	do
	{
		*it = (enum cardinal)(1 + *it);
	} while ((long)*it < (long)cardinal_upper_bound && !is_valid_cardinal((long)*it));
	return *it < cardinal_upper_bound;
}
@endcode
*/
#define DECLARE_ENUM_WITH_VALUES(NAME, ...)	\
	enum NAME \
	{ \
		FOR(EACH(__VA_ARGS__), ADD_COMMA, PP_PAIR_APPLY, PP_PAIR_ASSIGN) \
		_EMAX(NAME) \
	}; \
	static inline const char* _MERGE(cstring_from, NAME) (enum NAME value) \
	{ \
		switch (value) \
		{ \
		FOR(EACH(__VA_ARGS__), PP_PAIR_APPLY, PP_TO_STRING_CASE) \
		default: return NULL; \
		} \
	} \
	static inline bool _MERGE(is_valid, NAME) (long value) \
	{ \
		return _MERGE(cstring_from, NAME)((enum NAME)value) != NULL; \
	} \
	static inline bool _MERGE(has_next, NAME) (enum NAME* it) \
	{ \
		do { \
			*it = (enum NAME)(1 + *it); \
		} while ((long)*it < (long)_EMAX(NAME) && !_MERGE(is_valid, NAME)((long)*it)); \
		return *it < _EMAX(NAME); \
	}

/**
@code{.c}
DECLARE_ENUM_WITH_STRINGS(
    grocery,
    (ITEM_EGG,   "Egg"),
    (ITEM_MILK,  "Milk"),
    (ITEM_BREAD, "Bread"),
    (ITEM_SOUP,  "Soup"),
    (ITEM_YEAST, "Yeast"),
    (ITEM_PASTA, "Pasta")
)
@endcode
evaluates to:
@code{.c}
enum grocery
{
	ITEM_EGG,
	ITEM_MILK,
	ITEM_BREAD,
	ITEM_SOUP,
	ITEM_YEAST,
	ITEM_PASTA,
	grocery_count
};
static inline _Bool is_valid_grocery(long value)
{
	return (0 <= value && value < grocery_count);
}
static inline const char* cstring_from_grocery(enum grocery value)
{
	static const char* const table[] = {
	    "Egg",
	    "Milk",
	    "Bread",
	    "Soup",
	    "Yeast",
	    "Pasta",
	};
	if (!is_valid_grocery((long)value)) return ((void*)0);
	return table[value];
}
static inline _Bool has_next_grocery(enum grocery* it)
{
	do
	{
		*it = (enum grocery)(1 + *it);
	} while ((long)*it < (long)grocery_count && !is_valid_grocery((long)*it));
	return *it < grocery_count;
}
@endcode
*/
#define DECLARE_ENUM_WITH_STRINGS(NAME, ...) \
	enum NAME \
	{ \
		FOR(EACH(__VA_ARGS__), ADD_COMMA, PP_PAIR_APPLY, PP_PAIR_FIRST) \
		_ECNT(NAME) \
	}; \
	static inline bool _MERGE(is_valid, NAME) (long value) \
	{ \
		return (0 <= value && value < _ECNT(NAME)); \
	} \
	static inline const char* _MERGE(cstring_from, NAME) (enum NAME value) \
	{ \
		static const char* const table[] = { \
			FOR(EACH(__VA_ARGS__), ADD_COMMA, PP_PAIR_APPLY, PP_PAIR_SECOND) \
		}; \
		if (!_MERGE(is_valid, NAME)((long)value)) \
			return NULL; \
		return table[value]; \
	} \
	static inline bool _MERGE(has_next, NAME) (enum NAME* it) \
	{ \
		do { \
			*it = (enum NAME)(1 + *it); \
		} while ((long)*it < (long)_ECNT(NAME) && !_MERGE(is_valid, NAME)((long)*it)); \
		return *it < _ECNT(NAME); \
	}
