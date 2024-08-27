#include <sys/types.h> // uint*_t

#include <inttypes.h> // PRI*
#include <stdio.h>    // printf

#define FIBONACCI(N, A, B, ...) fibonacci(N, A, B)
#define fibonacci(N, ...)       FIBONACCI(N, ##__VA_ARGS__, 1, 1)

uint64_t fibonacci(uint16_t n, uint64_t f0, uint64_t f1)
{
	switch (n)
	{
	case 0: return f0;
	case 1: return f1;
	default: return fibonacci(n - 1, f1, f0 + f1);
	}
}

int main()
{
	printf("%" PRIu64 "\n", fibonacci(6));
	printf("%" PRIu64 "\n", fibonacci(7, 0, 1));
	printf("%" PRIu64 "\n", fibonacci(5, 1, 2));
}
