#include <stdio.h>  // dprintf
#include <stdlib.h> // atoi, NULL, EXIT_*
#include <string.h> // strchr
#include <unistd.h> // *_FILENO

/* Output the environment as a markdown table */
int main(int arg_count, char** arg_values, char** environment)
{
	char*    equal;
	unsigned max = arg_count > 1 ? atoi(arg_values[1]) : 7;

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
	} while (--max > 0 && *++environment);
	return EXIT_SUCCESS;
}
