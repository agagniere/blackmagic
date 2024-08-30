#include <stdio.h>

#define ARG_10(A, B, C, D, E, F, G, H, I, J, ...) J
#define ARG_COUNT(...) ARG_10(__VA_ARGS__ __VA_OPT__(,) 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define FOO(...) printf("FOO was called with %i arguments\n", ARG_COUNT(__VA_ARGS__))

#define SPELL_0 "zero"
#define SPELL_1 "one"
#define SPELL_2 "two"
#define SPELL_3 "three"
#define SPELL_4 "four"

#define SPELL(N) SPELL_ ## N

int main()
{
	FOO();
	FOO(1, 2, 3, 4, 5);

	printf("%s %s\n", SPELL(4), SPELL(2));
}
