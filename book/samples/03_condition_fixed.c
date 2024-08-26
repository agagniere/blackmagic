#include <fcntl.h> // open

#include <errno.h>  // errno
#include <stdio.h>  // printf
#include <string.h> // strerror

#define log(LEVEL, MESSAGE, ...)                                            \
	do                                                                      \
	{                                                                       \
		if (LEVEL <= threshold)                                             \
			printf("[" #LEVEL "] " MESSAGE "\n" __VA_OPT__(,) __VA_ARGS__); \
	} while (0)

enum log_level
{
	ERROR,
	INFO,
	DEBUG
};

enum log_level threshold = INFO;

int main()
{
	int         fd;
	const char* filename  = "inexistant.txt";

	fd = open(filename, O_RDONLY);
	log(DEBUG, "File descriptor: %i", fd);

	if (fd < 0)
		log(DEBUG, "Unable to open %s: %s", filename, strerror(errno));
	else
		log(INFO, "Successfully opened %s", filename);

	if (fd > 0)
		log(INFO, "Valid FD: %i", fd);
	else if (fd == 0)
		log(ERROR, "Zero FD !?");
	else
		log(ERROR, "Open failed (fd=%i) and set errno to %i: %s", fd, errno, strerror(errno));
}
