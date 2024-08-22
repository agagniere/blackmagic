#include <fcntl.h> // open, O_*

#include <errno.h>  // errno
#include <stdio.h>  // printf
#include <string.h> // strerror

#define STRINGIZE_LITERAL(TEXT)   #TEXT
#define STRINGIZE_EVALUATED(EXPR) STRINGIZE_LITERAL(EXPR)

#define MARKDOWN_HEADER "|Level|File|Function|Line|Message|\n|:-|:-|:-|-:|:-|\n"

#define log_log(LEVEL, MESSAGE, ...)                                                         \
	printf("|" LEVEL "|`" __FILE__ "`|`%s`|" STRINGIZE_EVALUATED(__LINE__) "|" MESSAGE "\n", \
	       __func__ __VA_OPT__(, ) __VA_ARGS__)

#define log_debug(MESSAGE, ...) log_log("DEBUG", MESSAGE __VA_OPT__(, ) __VA_ARGS__)
#define log_error(MESSAGE, ...) log_log("ERROR", MESSAGE __VA_OPT__(, ) __VA_ARGS__)

void foobar(const char* file_name)
{
	if (open(file_name, O_RDONLY) < 0)
		log_error("Failed to open `%s`: %s", file_name, strerror(errno));
}

int main()
{
	printf(MARKDOWN_HEADER);
	log_debug("Hello World !");
	foobar("bar.csv");
}
