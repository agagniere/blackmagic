#include <stdio.h> // printf

#define MARKDOWN_HEADER "|Level|File|Function|Line|Message|\n|:-|:-|:-|-:|:-|\n"

#define log_log(LEVEL, MESSAGE, ...) \
	printf("|" LEVEL "|`" __FILE__ "`|`%s`|%i|" MESSAGE "\n", __func__, __LINE__ __VA_OPT__(,) __VA_ARGS__)

#define log_debug(MESSAGE, ...) log_log("DEBUG", MESSAGE __VA_OPT__(,) __VA_ARGS__)
#define log_error(MESSAGE, ...) log_log("ERROR", MESSAGE __VA_OPT__(,) __VA_ARGS__)

int main()
{
	printf(MARKDOWN_HEADER);
	log_debug("Hello world !");
	log_error("Failed to open `%s`: %s", "bar.csv", "no such file");
}
