#include <inttypes.h> // PRI*
#include <stdio.h>    // printf

#define MARKDOWN_HEADER "|Level|File|Function|Line|Message|\n|:-|:-|:-|-:|:-|\n"

#define log_log(LEVEL, MESSAGE, ...)                          \
	printf("|" LEVEL "|`" __FILE__ "`|`%s`|%i|" MESSAGE "\n", \
	       __func__,                                          \
	       __LINE__ __VA_OPT__(, ) __VA_ARGS__)

#define log_debug(MESSAGE, ...) \
	log_log("DEBUG", MESSAGE __VA_OPT__(, ) __VA_ARGS__)

#define log_debug_eval_1(VARIABLE) log_debug("%s = %i", #VARIABLE, VARIABLE)
#define log_debug_eval_2(VARIABLE) log_debug(#VARIABLE " = %i", VARIABLE)
#define log_debug_eval_3(FORMAT, VARIABLE) \
	log_debug(#VARIABLE " = " FORMAT, VARIABLE)
#define log_debug_eval_4(FLAG, VARIABLE) \
	log_debug(#VARIABLE " = %" FLAG, VARIABLE)

int main(int arg_count, char** arg_values)
{
	printf(MARKDOWN_HEADER);
	log_debug_eval_1(arg_count);
	log_debug_eval_2(arg_count);
	log_debug_eval_3("%p", arg_values);
	log_debug_eval_4(PRIXPTR, arg_values);
}
