#include <stdio.h>
#include <stdbool.h>

void foo(void)
{
	printf(__FILE_NAME__ "@%s:%i\n", __FUNCTION__, __LINE__);
}

bool bar(int i)
{
	printf("In file " __FILE__ " in function %s at line %i: %i\n", __PRETTY_FUNCTION__, __LINE__, i);
	return true;
}

int main()
{
	foo();
	bar(42);
}
