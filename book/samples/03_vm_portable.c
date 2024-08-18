#define logger(...) printf("[log] " __VA_ARGS__)

int main(int ac, char** av)
{
	logger("Hello\n");
	logger("argument count: %i\n", ac);
	logger("program name  : %s\n", *av);
}
