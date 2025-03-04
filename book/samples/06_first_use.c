#include <stdio.h>

#include "blackmagic/token.h" // STRINGIZE

#define ARG_10(A, B, C, D, E, F, G, H, I, J, ...) J
#define ARG_COUNT(...) ARG_10(__VA_ARGS__ __VA_OPT__(,) 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define SPELL_0 "zero"
#define SPELL_1 "one"
#define SPELL_2 "two"
#define SPELL_3 "three"
#define SPELL_4 "four"
#define SPELL_5 "five"

#define SPELL_(N) SPELL_ ## N
#define SPELL(N) SPELL_(N)

#define FOO(...) printf("FOO was called with " SPELL(ARG_COUNT(__VA_ARGS__)) " (" STRINGIZE(ARG_COUNT(__VA_ARGS__)) ") arguments\n")

int main()
{
	FOO();
	FOO(1, 2);
	FOO(1, 2, 3, 4, 5);
}
