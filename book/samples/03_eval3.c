#include <inttypes.h> // PRI*
#include <stdio.h>    // printf

#define MARKDOWN_HEADER "|Level|File|Function|Line|Message|\n|:-|:-|:-|-:|:-|\n"

#define log_log(LEVEL, MESSAGE, ...)                          \
	printf("|" LEVEL "|`" __FILE__ "`|`%s`|%i|" MESSAGE "\n", \
	       __func__, __LINE__ __VA_OPT__(,) __VA_ARGS__)

#define log_debug(MESSAGE, ...) \
	log_log("DEBUG", MESSAGE __VA_OPT__(,) __VA_ARGS__)

#define log_debug_eval(FLAG, EXPRESSION) \
	log_debug(#EXPRESSION " = %" FLAG, EXPRESSION)

void foo(uint8_t answer)
{
	log_debug_eval(PRIu8, answer);
}

int main(int arg_count, char** arg_values)
{
	printf(MARKDOWN_HEADER);
	log_debug_eval("i", arg_count);
	foo('*');
	log_debug_eval("p", arg_values);
}
