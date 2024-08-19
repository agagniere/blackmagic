#include <stdio.h> // printf

#define log_eval_integer(VARIABLE) printf("%s = %i\n", #VARIABLE, VARIABLE)

int main(int arg_count, char** arg_values)
{
	log_eval_integer(arg_count);
}
