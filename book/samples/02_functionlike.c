#include <termios.h> // struct termios

#if __has_include("linux/stddef.h")
# include <linux/stddef.h> // sizeof_field
#else
# define sizeof_field(Type, Member) sizeof(((Type){}).Member)
#endif
#include <stddef.h>       // offsetof
#include <stdio.h>        // printf

int main()
{
	printf("| Position | Size |\n|-:|-:|\n");
	printf("| %zu | %zu |\n", offsetof(struct termios, c_iflag), sizeof_field(struct termios, c_iflag));
	printf("| %zu | %zu |\n", offsetof(struct termios, c_cflag), sizeof_field(struct termios, c_cflag));
	printf("| %zu | %zu |\n", offsetof(struct termios, c_lflag), sizeof_field(struct termios, c_lflag));
	printf("| %zu | %zu |\n", offsetof(struct termios, c_cc), sizeof_field(struct termios, c_cc));
}
