#include <stdio.h>
#include <stdbool.h>

void foo(void)
{
	printf("%s@%s:%i\n", __FILE_NAME__, __FUNCTION__, __LINE__);
}

bool bar(int arg)
{
	printf("In file %s in function %s at line %i: arg=%i\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, arg);
	return true;
}

int main()
{
	foo();
	bar(42);
}
