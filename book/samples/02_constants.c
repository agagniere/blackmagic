#include <stdio.h>  // dprintf
#include <stdlib.h> // EXIT_*
#include <string.h> // strchr
#include <unistd.h> // *_FILENO

/* Reducing the amount of magic numbers */
int main(int arg_count, char** arg_values)
{
	if (arg_count <= 1 || strchr(arg_values[1], '-') == NULL)
	{
		dprintf(STDERR_FILENO, "Expected an argument\n");
		return EXIT_FAILURE;
	}
	dprintf(STDOUT_FILENO, "Received argument: %s\n", arg_values[1] + 1);
	return EXIT_SUCCESS;
}
