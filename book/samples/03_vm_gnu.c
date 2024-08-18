#include <stdio.h> // printf

#define logger(MESSAGE, ...) printf("[log] " MESSAGE "\n", ##__VA_ARGS__)
#define TWICE(...)           __VA_ARGS__, ##__VA_ARGS__

int main()
{
	logger("Hello");
	logger("Hello %s", "World");
	int zero[] = {TWICE()};
	int four[] = {TWICE(2, 4)};
}
