#include <stdio.h> // printf

#define eval(x) printf("%s = %lu\n", #x, x)

unsigned long _factorial(unsigned short n, unsigned long accumulator)
{
	if (n == 1)
		return accumulator;
	__attribute__((musttail)) return _factorial(n - 1, accumulator * n);
}

#define FACTORIAL_(N, ACC, ...) _factorial(N, ACC)
#define FACTORIAL(N, ...)       FACTORIAL_(N, ##__VA_ARGS__, 1)

int main()
{
	eval(FACTORIAL(5));
	eval(FACTORIAL(10));
	eval(FACTORIAL(12));
}
