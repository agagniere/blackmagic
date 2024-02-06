#include <stdio.h>  // dprintf
#include <stdlib.h> // EXIT_*
#include <string.h> // strchr
#include <unistd.h> // STDERR_FILENO

int main(int arg_count, char** arg_values)
{
	if (strchr(arg_values[1], '-') == NULL)
	{
		dprintf(STDERR_FILENO, "Expected an argument\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
