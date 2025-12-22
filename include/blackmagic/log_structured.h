#include "blackmagic/for.h"
#include "blackmagic/log.h"
#include "blackmagic/pair.h"


/**
 * To be used with @ref log_structured.
 */
#define eval(FLAG, EXPRESSION) (#EXPRESSION, FLAG, EXPRESSION)

///@cond
#define _log_value(NAME, FLAG, VALUE) VALUE,

#if LOG_FORMAT == LOG_FORMAT_JSON
#define _log_name(NAME, FLAG, VALUE) "\""NAME "\": %" FLAG ", "
#define log_structured(LEVEL, MESSAGE, ...) log_ ## LEVEL (MESSAGE "\", " FOR(EACH(__VA_ARGS__), PAIR_FLATTEN, _log_name) "\"\":\"%.0u", FOR(EACH(__VA_ARGS__), PAIR_FLATTEN, _log_value) 0)
#else
#define _log_name(NAME, FLAG, VALUE) NAME " = %" FLAG ", "
///@endcond

/**
 * Structured logging.
 *
 * Provide a list of fields of the form (name, flag, value), where flag is the printf format to be used.
 * The @ref eval macro can be used to have the name be the expression itself
 */
#define log_structured(LEVEL, MESSAGE, ...) log_ ## LEVEL (MESSAGE "; " FOR(EACH(__VA_ARGS__), PAIR_FLATTEN, _log_name) "%.0u", FOR(EACH(__VA_ARGS__), PAIR_FLATTEN, _log_value) 0)

///@cond
#endif
///@endcond
