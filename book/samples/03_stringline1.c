#include <stdio.h>    // printf

#define STRINGIZE(ARG) # ARG

int main(int arg_count, char** arg_values)
{
	printf("Line as integer: %i\n", __LINE__);
	printf("Line as string: %s\n", STRINGIZE(__LINE__));
	printf("Concatenated: " STRINGIZE(__LINE__) "\n");
}
