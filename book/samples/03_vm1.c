#define FOO(A, B, ...) A + B
#define NOOP(...)

int main()
{
	int n = FOO(1, 2, 3, 4);
	int m = NOOP(1, 2, 3) - FOO(8, 2, 0);
}
