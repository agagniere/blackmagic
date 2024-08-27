# Optional arguments: simple case

:::{admonition} Work In Progress
:class: warning
This page is a draft
:::

Let's see how the tricks introduced in the previous chapter can be used to simulate optional arguments with a default value.

:::{admonition} Definition
:class: info
An optional argument is a language feature that allows the caller of a function not to provide certain arguments, with the effect that a default value is used.
:::

For example in C++:
```{code-block} C++
uint64_t fibonacci(unsigned n, uint64_t f0 = 0, uint64_t f1 = 1)
{
	switch (n)
	{
	case 0: return f0;
	case 1: return f1;
	default: return fibonacci(n - 1, f1, f0 + f1);
	}
}
```
This allows choosing the first two terms of the sequence (and also performing tail recursion with a single function).

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

We are going to demonstrate how this can be done in C

---

:::{preprocessed} 04_factorial
:::

---

:::{preprocessed} 04_ones
:::
