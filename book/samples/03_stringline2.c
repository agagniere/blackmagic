#include <stdio.h> // printf

#define STRINGIZE(ARG)         #ARG
#define STRINGIZE_WRAPPER(ARG) STRINGIZE(ARG)

int main(int arg_count, char** arg_values)
{
	printf("Line as integer: %i\n", __LINE__);
	printf("Line as string: %s\n", STRINGIZE_WRAPPER(__LINE__));
	printf("Concatenated: " STRINGIZE_WRAPPER(__LINE__) "\n");
}
