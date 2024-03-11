#include <stdio.h>  // dprintf
#include <stdlib.h> // NULL, EXIT_*
#include <string.h> // strchr
#include <unistd.h> // *_FILENO

/* Reducing the amount of magic numbers */
int main(int arg_count, char** arg_values, char** environment)
{
	char* equal;

	dprintf(STDOUT_FILENO, "# Environment\n| Name | Value |\n|:-|:-|\n");
	do
	{
		if ((equal = strchr(*environment, '=')) == NULL)
		{
			dprintf(STDERR_FILENO, "Expected an assignation but got \"%s\"\n", *environment);
			return EXIT_FAILURE;
		}
		*equal = '\0';
		dprintf(STDOUT_FILENO, "|`%s`|`%1.30s`|\n", *environment, equal + 1);
	} while (*++environment);
	return EXIT_SUCCESS;
}
