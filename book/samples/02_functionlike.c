#include <termios.h> // struct termios

#include <stddef.h> // offsetof
#include <stdio.h>  // printf

#if __has_include("linux/stddef.h")
#	include <linux/stddef.h> // sizeof_field
#endif
#ifndef sizeof_field
#	define sizeof_field(Type, Member) sizeof(((Type){}).Member)
#endif

/** Learn about the memory layout of the termios struct */
int main()
{
	printf("__Termios structure__:\n| Name | Position | Size |\n|:-|-:|-:|\n");
	printf("|`c_iflag`|%zu|%zu|\n",
	       offsetof(struct termios, c_iflag),
	       sizeof_field(struct termios, c_iflag));
	printf("|`c_cflag`|%zu|%zu|\n",
	       offsetof(struct termios, c_cflag),
	       sizeof_field(struct termios, c_cflag));
	printf("|`c_lflag`|%zu|%zu|\n",
	       offsetof(struct termios, c_lflag),
	       sizeof_field(struct termios, c_lflag));
	printf("|`c_cc`|%zu|%zu|\n",
	       offsetof(struct termios, c_cc),
	       sizeof_field(struct termios, c_cc));
}
