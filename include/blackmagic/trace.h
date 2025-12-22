#pragma once

#include "blackmagic/log.h"
#include "blackmagic/log_structured.h"

#include <string.h> // strerror
#include <time.h>

#define BLACKMAGIC_ScopedTrace struct blackmagic_trace __attribute__((cleanup(blackmagic_trace_scopeend)))

#define BLACKMAGIC_timespec_diff(A, B) ((B.tv_sec - A.tv_sec) * 1000000000UL + B.tv_nsec - A.tv_nsec)

#define BLACKMAGIC_Scope(NAME) blackmagic_trace_scopestart(NAME, __FILE__, __func__, __LINE__)

struct blackmagic_trace
{
	struct timespec start;
	const char*     scope_name;
	const char*     file_name;
	const char*     function_name;
	unsigned        line_number;
};

static inline struct blackmagic_trace
blackmagic_trace_scopestart(const char* scope_name,
                            const char* file_name,
                            const char* function_name,
                            unsigned    line_number)
{
	struct timespec start = {0};
	int status = clock_gettime(CLOCK_MONOTONIC_RAW, &start);

#ifndef NDEBUG
	if (status != 0)
		log_error("Unable to get time: %s", strerror(status));
#endif
	return (struct blackmagic_trace){
		start         = start,
		scope_name    = scope_name,
		file_name     = file_name,
		function_name = function_name,
		line_number   = line_number,
	};
}

#ifndef LOG_LEVEL_SPAN
#	define LOG_LEVEL_SPAN 5
#endif

#if LOG_LEVEL >= LOG_LEVEL_SPAN
#define log_span(MESSAGE, ...) \
	log__log(LOG_LEVEL_SPAN, "SPAN", COLOR(PURPLE), MESSAGE __VA_OPT__(, ) __VA_ARGS__)
#else
#define log_span(M, ...)
#endif

static inline void blackmagic_trace_scopeend(struct blackmagic_trace* self) {
	struct timespec end = {0};
	int status = clock_gettime(CLOCK_MONOTONIC_RAW, &end);

#ifndef NDEBUG
	if (status != 0)
		log_error("Unable to get time: %s", strerror(status));
#endif
	log_structured(span,
	         "",
	         ("trace_scope", "s", self->scope_name),
	         ("trace_file", "s", self->file_name),
	         ("trace_function", "s", self->function_name),
	         ("trace_line", "u", self->line_number),
	         ("duration_ns", "lu", BLACKMAGIC_timespec_diff(self->start, end)));
}
