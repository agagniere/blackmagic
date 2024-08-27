#include <stdio.h>

#define ARG_COUNT_1(A, B, C, D, E, F, G, H, I, J, ...) J
#define ARG_COUNT_2(...) ARG_COUNT_1(__VA_ARGS__ __VA_OPT__(,) 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

int main()
{
	printf("0: %i\n", ARG_COUNT_2());
	printf("1: %i\n", ARG_COUNT_2(1));
	printf("2: %i\n", ARG_COUNT_2(1, 2));
}
