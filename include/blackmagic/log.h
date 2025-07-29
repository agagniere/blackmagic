#pragma once

/**
 * @file
 * Header-only log library.
 * Just macros that evaluate to fprintf calls, nothing more.
 */

#include "blackmagic/color.h" // COLOR
#include "blackmagic/token.h" // STRINGIZE

#include <stdio.h> // fprintf

/**
 * @name Configuration
 * These settings can be overridden using the compiler's `-D` flag or using a `#define` before `#include`
 */
///@{

#ifndef LOG_FILE
/**
 * Choose the file to output logs to.
 * What is expected is a `FILE*` like `stdout` or `stderr`.
 *
 * Defaults to `stderr`
 */
#	define LOG_FILE stderr
#endif

#ifndef LOG_LEVEL
#	ifdef NDEBUG
#		define LOG_LEVEL LOG_LEVEL_INFO
#	else
/**
 * Choose the compile-time log verbosity level.
 * Logs that are strictly less critical that this level are removed before compilation.
 *
 * The default value is @ref LOG_LEVEL_TRACE for debug builds and @ref LOG_LEVEL_INFO for release builds that define `NDEBUG`.
 */
#		define LOG_LEVEL LOG_LEVEL_TRACE
#	endif
#endif

#ifndef LOG_FORMAT
/** Choose the logs output format. Defaults to @ref LOG_FORMAT_COLOR */
#	define LOG_FORMAT LOG_FORMAT_COLOR
#endif

/**
 * Expected signature of the function designated by the LOG_FUNCTION macro.
 *
 * If users want to be able to capture all logs,
 * to have fancy features whose cost isn't paid by default,
 * the special LOG_FUNCTION macro can be set to a function of this type.
 * All logs will become calls to this function, instead of calls to fprintf.
 *
 * Possible usecases include being able to:
 *   - integrate with another logging utility (e.g. from another language)
 *   - have a run-time log level threshold (e.g. settable by command line)
 *   - have a run-time output file (e.g. settable by config)
 *   - have multiple writers
 *   - perform conditional formatting (e.g. only print the location of errors and warnings)
 *   - add the thread name in the log
 *   - perform formatting and I/O in a separate thread
 *
 * Note that logs discarded by @ref LOG_LEVEL are completely removed at compile-time,
 * and will NOT resolve to calls to the provided function.
 * So if you want to have a run-time threshold in your custom function,
 * be sure to set the compile-time threshold high enough,
 * possibly to @ref LOG_LEVEL_ALL
 */
typedef void(*logging_callback)(unsigned level, const char* level_name, const char* file, const char* function, int line, const char* message, ...);

///@}

/**
 * @name Log levels
 * Possible values of @ref LOG_LEVEL
 */
///@{
#define LOG_LEVEL_NONE    0 /**< Only output the header and forced logs */
#define LOG_LEVEL_FATAL   1 /**< The program will stop */
#define LOG_LEVEL_ERROR   3 /**< The current operation will abort */
#define LOG_LEVEL_WARNING 4 /**< Abnormal situation */
#define LOG_LEVEL_INFO    6 /**< Significant information */
#define LOG_LEVEL_DEBUG   8 /**< Only relevant to the developpers */
#define LOG_LEVEL_TRACE  10 /**< Spam */
#define LOG_LEVEL_ALL    15 /**< Output all logs */
///@}

/**
 * @name Log formats
 * Possible values of @ref LOG_FORMAT
 */
///@{
/** Disable outputting logs */
#define LOG_FORMAT_NONE 0
/** Print logs in a human readable format without colors */
#define LOG_FORMAT_CONSOLE 1
/** Print logs in a human readable format with colors */
#define LOG_FORMAT_COLOR 2
/** Print logs as a markdown table */
#define LOG_FORMAT_MARKDOWN 3
/** Print logs as a stream of JSON objects */
#define LOG_FORMAT_JSON 4
///@}

#if LOG_FORMAT == LOG_FORMAT_MARKDOWN
#	define log_header() fprintf(LOG_FILE, "|Level|File|Function|Line|Message|\n|:-|:-|:-|-:|:-|\n")
#else
#	define log_header() /**< Place this macro once before any log */
#endif

///@cond
#ifdef LOG_FUNCTION
/* Declare the callback */
__attribute__((format(printf, 6, 7)))
void LOG_FUNCTION (unsigned level, const char* level_name, const char* file, const char* function, int line, const char* message, ...);
#	define log__log(LEVEL, LNAME, IGNORED, ...) LOG_FUNCTION(LEVEL, LNAME, __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#	define log__log(IGNORED, ...) log_log(__VA_ARGS__)
#endif

#if LOG_FORMAT == LOG_FORMAT_CONSOLE
#	define log_log(LEVEL, IGNORED, MESSAGE, ...) \
		fprintf(LOG_FILE, \
		        "[%5s " __FILE__ ":%s:" STRINGIZE(__LINE__) "] " MESSAGE "\n", \
		        LEVEL, __func__ __VA_OPT__(, ) __VA_ARGS__)
#elif LOG_FORMAT == LOG_FORMAT_COLOR
#	define log_log(LEVEL, COLOR_STRING, MESSAGE, ...) \
		fprintf(LOG_FILE, \
		        "[" COLOR_STRING "%5s" COLOR(NORMAL) COLOR(DIM) " " __FILE__ ":%s:" STRINGIZE(__LINE__) COLOR(NORMAL) "] " MESSAGE "\n", \
		        LEVEL, __func__ __VA_OPT__(, ) __VA_ARGS__)
#elif LOG_FORMAT == LOG_FORMAT_MARKDOWN
#	define log_log(LEVEL, IGNORED, MESSAGE, ...) \
		fprintf(LOG_FILE, \
		        "|" LEVEL "|`" __FILE__ "`|`%s`|" STRINGIZE(__LINE__) "|" MESSAGE "|\n", \
		        __func__ __VA_OPT__(, ) __VA_ARGS__)
#elif LOG_FORMAT == LOG_FORMAT_JSON
#	define log_log(LEVEL, IGNORED, MESSAGE, ...) \
		fprintf(LOG_FILE, \
		        "---\n{\"level\": \"" LEVEL "\",\"file\": \"" __FILE__ "\", \"function\": \"%s\", \"line\": " STRINGIZE(__LINE__) ", \"message\": " "\"" MESSAGE "\"}\n", \
		        __func__ __VA_OPT__(, ) __VA_ARGS__)
#else
#	define log_log(L, C, M, ...) /* Logs are disabled */
#endif
///@endcond

#if LOG_LEVEL >= LOG_LEVEL_FATAL
/** Report a condition that forces the program to terminate */
#	define log_fatal(MESSAGE, ...) \
		log__log(LOG_LEVEL_FATAL, "FATAL", COLOR(BOLD, WHITE, BG_RED), \
		         MESSAGE __VA_OPT__(, ) __VA_ARGS__)
#else
#	define log_fatal(M, ...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR
/** Report a condition that forces the current operation to be aborted */
#	define log_error(MESSAGE, ...) \
		log__log(LOG_LEVEL_ERROR, "ERROR", COLOR(BOLD, RED), \
		         MESSAGE __VA_OPT__(, ) __VA_ARGS__)
#else
#	define log_error(M, ...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARNING
/** Report an abnormal condition */
#	define log_warning(MESSAGE, ...) \
		log__log(LOG_LEVEL_WARNING, "WARN", COLOR(BOLD, YELLOW), \
		         MESSAGE __VA_OPT__(, ) __VA_ARGS__)
#else
#	define log_warning(M, ...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
/** Report significant information */
#	define log_info(MESSAGE, ...) \
		log__log(LOG_LEVEL_INFO, "INFO", COLOR(BOLD, GREEN), \
		         MESSAGE __VA_OPT__(, ) __VA_ARGS__)
#else
#	define log_info(M, ...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
/** Report information relevant to the developpers */
#	define log_debug(MESSAGE, ...) \
		log__log(LOG_LEVEL_DEBUG, "DEBUG", COLOR(BOLD, BLUE), \
		         MESSAGE __VA_OPT__(, ) __VA_ARGS__)
#else
#	define log_debug(M, ...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_TRACE
/** Spam */
#	define log_trace(MESSAGE, ...) \
		log__log(LOG_LEVEL_TRACE, "TRACE", COLOR(NORMAL), \
		         MESSAGE __VA_OPT__(, ) __VA_ARGS__)
#else
#	define log_trace(M, ...)
#endif

/** Log regardless of level */
#define log_force(MESSAGE, ...) \
	log__log(LOG_LEVEL_NONE, "FORCE", COLOR(BOLD, WHITE, BG_GREEN), \
	         MESSAGE __VA_OPT__(, ) __VA_ARGS__)
