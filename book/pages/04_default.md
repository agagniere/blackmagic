# Optional arguments: simple case

:::{admonition} Work In Progress
:class: warning
This page is a draft
:::

Let's see how the tricks introduced in the previous chapter can be used to simulate optional arguments with a default value.

:::{admonition} Definition
:class: info
Optional arguments is a language feature that allows the caller of a function not to provide certain arguments, in which case a default value is used, chosen by the callee.
:::

Here is an example in C++:
```{code-block} C++
uint64_t fibonacci(uint8_t n, uint64_t f0 = 0, uint64_t f1 = 1)
{
	switch (n)
	{
	case 0: return f0;
	case 1: return f1;
	default: return fibonacci(n - 1, f1, f0 + f1);
	}
}
```
This allows having the expected interface with a single argument, while also allowing the caller to choose the first two terms of the sequence.

The caller may then write:
```{code-block} C++
// Starting with 0 1
fibonacci(7); // 13
fibonacci(7, 0); // 13
fibonacci(7, 0, 1); // 13

// Starting with 1 1
fibonacci(6, 1); // 13
fibonacci(6, 1, 1); // 13

// Historical sequence
fibonacci(5, 1, 2); // 13

// Custom sequence
fibonacci(5, 5, 10); // 40
```

We are going to demonstrate how to achieve a similar interface in C.

## Single optional argument

Let's start with a simpler example: the factorial of an integer.

:::::{dropdown} Why is there a second argument to factorial ?
The most straightforward implementation looks like:
```{code-block} C
unsigned long factorial(unsigned char n)
{
	if (n <= 1)
		return 1;
	return n * factorial(n - 1);
}
```

And in fact, it is all you need, because your compiler will most likely optimize it to a loop with constant memory usage.
But to please your computer science professor we'll write an implementation with explicit tail call optimization.

```{code-block} C
:caption: How it is usually done in C
static // Tell the compiler this function will not be called outside this compilation unit, so it won't create a symbol for it and just inline it
unsigned long factorial_aux(unsigned char n, unsigned long accumulator)
{
	if (n <= 1)
		return accumulator;
	__attribute__((musttail)) // We can even ask the compiler to issue an error if tail recursion isn't possible
	return factorial_aux(n - 1, n * accumulator);
}

unsigned long factorial(unsigned char n)
{
	return factorial_aux(n, 1);
}
```
What you can see is that the `factorial`{l=C} function is just a wrapper to provide a default value. Which is perfectly fine as the auxillary function will be inlined inside, but let's act like it's an unforgivable _faux pas_. Using obscure preprocessor tricks to solve non-existant problems is what we are here for anyway.

Also, if you really care about performance, just use a lookup-table: there's only 20 factorial values that can fit on 64 bits
:::::

::::{card}
A first attempt is to replace the wrapper function with a wrapper macro that has the same name:
```{code-block} prepro
:caption: in factorial.h
unsigned long factorial(unsigned char n, unsigned long);

#define factorial(N) factorial(N, 1)
```

```{code-block} C
:caption: in factorial.c
unsigned long factorial(unsigned char n, unsigned long accumulator)
{
	if (n <= 1)
		return accumulator;
	__attribute__((musttail))
	return factorial(n - 1, n * accumulator);
}
```
```{code-block} C
:caption: user code
#include <factorial.h>

int main()
{
	unsigned long x = factorial(10);
}
```

This works because:
- in the header, the function declaration is not affected by the macro as the latter is defined after.
- macros cannot be recursive, so once `factorial(10)`{l=C} is replaced by `factorial(10, 1)`, no further expansion is performed
- `factorial.c` does not include `factorial.h`, so it is not affected by the macro
::::

:::{preprocessed} 04_factorial
:::

---

:::{preprocessed} 04_ones
:::
