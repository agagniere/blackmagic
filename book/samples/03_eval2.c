#include <stdio.h>  // printf
#include <string.h> // strlen

#define log_eval_integer(EXPRESSION) printf("%s = %i\n", #EXPRESSION, EXPRESSION)

int main(int arg_count, char** arg_values)
{
	log_eval_integer(2 + 2);
	log_eval_integer(strlen(*arg_values));
}
