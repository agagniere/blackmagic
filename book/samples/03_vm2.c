#define ROTATE(A, ...) __VA_ARGS__, A
#define TWICE(...)     __VA_ARGS__, __VA_ARGS__

int main()
{
	const short rotate[] = {ROTATE(1, 2, 3, 4)};
	const short twice[]  = {TWICE(1, 2, 3)};
}
