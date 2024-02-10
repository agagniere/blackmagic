#include <termios.h> // struct termios

#include <stddef.h> // offsetof
#include <stdio.h>  // printf

int main()
{
	printf("%zu\n", offsetof(struct termios, c_lflag));
}
