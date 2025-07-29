#pragma once

/**
 * @file
 * Generate functions for enumerations
 */

#include "blackmagic/codegen.h" // ADD_COMMA_FLAT
#include "blackmagic/for.h"     // FOR EACH
#include "blackmagic/join.h"    // JOIN2
#include "blackmagic/pair.h"    // PAIR_*
#include "blackmagic/token.h"   // STRINGIZE

#include <stdbool.h> // bool
#include <string.h>  // strcmp

///@cond
#define CASE_RETURN_STRING(K, V) \
	case (V): return STRINGIZE(K);
#define STRCMP_STRINGIZE_RETURN(S, P)           \
	if (strcmp(STRINGIZE(PAIR_FIRST P), S) == 0) \
		return PAIR_LAST P;
#define STRCMP_RETURN(S, P)          \
	if (strcmp(PAIR_LAST P, S) == 0) \
		return PAIR_FIRST P;
#define EV_MAX(NAME) JOIN2(NAME, upper_bound)
#define ES_MAX(NAME) JOIN2(NAME, count)
///@endcond

/** Declare an enum with custom values, with string conversions.
@section exEV Example
@code{.c}
DECLARE_ENUM_WITH_VALUES(
	cardinal,
	(EAST,	0b0001),
	(WEST,	0b0010),
	(NORTH, 0b0100),
	(SOUTH, 0b1000)
)
@endcode
Evaluates to:
@code{.c}
enum cardinal
{
	EAST  = 0b0001,
	WEST  = 0b0010,
	NORTH = 0b0100,
	SOUTH = 0b1000,
	cardinal_upper_bound
};

static inline const char* cardinal_to_cstring(enum cardinal value)
{
	switch (value)
	{
	case (0b0001): return "EAST";
	case (0b0010): return "WEST";
	case (0b0100): return "NORTH";
	case (0b1000): return "SOUTH";
	default: return NULL;
	}
}

static inline bool cardinal_is_valid(long value)
{
	return cardinal_to_cstring((enum cardinal)value) != NULL;
}

static inline bool cardinal_has_next(enum cardinal* it)
{
	do
	{
		*it = (enum cardinal)(1 + *it);
	} while ((long)*it < (long)cardinal_upper_bound && !cardinal_is_valid((long)*it));
	return (long)*it < (long)cardinal_upper_bound;
}

static inline enum cardinal cardinal_from_cstring(const char* string)
{
	if (strcmp("EAST", string) == 0)
		return 0b0001;
	if (strcmp("WEST", string) == 0)
		return 0b0010;
	if (strcmp("NORTH", string) == 0)
		return 0b0100;
	if (strcmp("SOUTH", string) == 0)
		return 0b1000;
	return cardinal_upper_bound;
}
@endcode

@since 0.1
*/
#define DECLARE_ENUM_WITH_VALUES(NAME, ...)                                            \
	enum NAME                                                                          \
	{                                                                                  \
		FOR(EACH(__VA_ARGS__), ADD_COMMA_FLAT, PAIR_ASSIGN) EV_MAX(NAME)               \
	};                                                                                 \
	static inline const char* JOIN2(NAME, to_cstring)(enum NAME value)                 \
	{                                                                                  \
		switch (value)                                                                 \
		{                                                                              \
			FOR(EACH(__VA_ARGS__), PAIR_FLATTEN, CASE_RETURN_STRING)                   \
		default: return NULL;                                                          \
		}                                                                              \
	}                                                                                  \
	static inline bool JOIN2(NAME, is_valid)(long value)                               \
	{                                                                                  \
		return JOIN2(NAME, to_cstring)((enum NAME)value) != NULL;                      \
	}                                                                                  \
	static inline bool JOIN2(NAME, has_next)(enum NAME * it)                           \
	{                                                                                  \
		do                                                                             \
		{                                                                              \
			*it = (enum NAME)(1 + *it);                                                \
		} while ((long)*it < (long)EV_MAX(NAME) && !JOIN2(NAME, is_valid)((long)*it)); \
		return (long)*it < (long)EV_MAX(NAME);                                         \
	}                                                                                  \
	static inline enum NAME JOIN2(NAME, from_cstring)(const char* string)              \
	{                                                                                  \
		FOR(EACH(__VA_ARGS__), STRCMP_STRINGIZE_RETURN, string)                        \
		return EV_MAX(NAME);                                                           \
	}

/** Declare an enum with custom strings.
@section exES Example
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
Evaluates to:
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

static inline bool grocery_is_valid(long value)
{
	return (0 <= value && value < grocery_count);
}

static inline const char* grocery_to_cstring(enum grocery value)
{
	static const char* const table[] = {
		"Egg", "Milk", "Bread", "Soup", "Yeast", "Pasta",
	};
	if (!grocery_is_valid((long)value))
		return NULL;
	return table[value];
}

static inline bool grocery_has_next(enum grocery* it)
{
	do
	{
		*it = (enum grocery)(1 + *it);
	} while ((long)*it < (long)grocery_count && !grocery_is_valid((long)*it));
	return (long)*it < (long)grocery_count;
}

static inline enum grocery grocery_from_cstring(const char* string)
{
	if (strcmp("Egg", string) == 0)
		return ITEM_EGG;
	if (strcmp("Milk", string) == 0)
		return ITEM_MILK;
	if (strcmp("Bread", string) == 0)
		return ITEM_BREAD;
	if (strcmp("Soup", string) == 0)
		return ITEM_SOUP;
	if (strcmp("Yeast", string) == 0)
		return ITEM_YEAST;
	if (strcmp("Pasta", string) == 0)
		return ITEM_PASTA;
	return grocery_count;
}
@endcode

@since 0.1
*/
#define DECLARE_ENUM_WITH_STRINGS(NAME, ...)                                                      \
	enum NAME                                                                                     \
	{                                                                                             \
		FOR(EACH(__VA_ARGS__), ADD_COMMA_FLAT, PAIR_FIRST) ES_MAX(NAME)                           \
	};                                                                                            \
	static inline bool JOIN2(NAME, is_valid)(long value)                                          \
	{                                                                                             \
		return (0 <= value && value < ES_MAX(NAME));                                              \
	}                                                                                             \
	static inline const char* JOIN2(NAME, to_cstring)(enum NAME value)                            \
	{                                                                                             \
		static const char* const table[] = { FOR(EACH(__VA_ARGS__), ADD_COMMA_FLAT, PAIR_LAST) }; \
		if (!JOIN2(NAME, is_valid)((long)value))                                                  \
			return NULL;                                                                          \
		return table[value];                                                                      \
	}                                                                                             \
	static inline bool JOIN2(NAME, has_next)(enum NAME * it)                                      \
	{                                                                                             \
		do                                                                                        \
		{                                                                                         \
			*it = (enum NAME)(1 + *it);                                                           \
		} while ((long)*it < (long)ES_MAX(NAME) && !JOIN2(NAME, is_valid)((long)*it));            \
		return (long)*it < (long)ES_MAX(NAME);                                                    \
	}                                                                                             \
	static inline enum NAME JOIN2(NAME, from_cstring)(const char* string)                         \
	{                                                                                             \
		FOR(EACH(__VA_ARGS__), STRCMP_RETURN, string)                                             \
		return ES_MAX(NAME);                                                                      \
	}
