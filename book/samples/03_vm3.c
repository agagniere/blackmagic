#define INTEGERS(I, ...) __VA_OPT__({) I __VA_OPT__(, __VA_ARGS__ })

int main()
{
	int i   = INTEGERS(4);
	int s[] = INTEGERS(2, 5, 8);
}
