#include <stdio.h>

#define ARG_10(A, B, C, D, E, F, G, H, I, J, ...) J
#define ARG_COUNT(...) ARG_10(__VA_ARGS__ __VA_OPT__(,) 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

int main()
{
	printf("()         : %i\n", ARG_COUNT());
	printf("(foo)      : %i\n", ARG_COUNT(foo));
	printf("('A', 'B') : %i\n", ARG_COUNT('A', 'B'));
	printf("(1,2,3,4,5): %i\n", ARG_COUNT(1, 2, 3, 4, 5));
}
