# Optional arguments: General case

:::{admonition} Work In Progress
:class: warning
This page is a draft
:::

OK so we now know how to have a few optional arguments with a default value, but what if we want to do something entierly different depending on the number of arguments provided ?

## Objective

A `range` macro similar to the python builtin function, that allows one to iterate over a range of integers:
- `range(STOP)`{l=python} iterates from 0 to _STOP_, _STOP_ excluded
- `range(START, STOP)`{l=python} iterates from _START_ to _STOP_, _STOP_ excluded
- `range(START, STOP, STEP)`{l=python} iterates from _START_ to _STOP_ by steps of _STEP_, _STOP_ excluded

Examples:
- `range(5)`: `0 1 2 3 4`
- `range(3, 8)`: `3 4 5 6 7`
- `range(2, 7, 3)`: `2 5`

How will it look like in C ? Well it's up to you, here are a few propositions:
:::::{tab-set}
::::{tab-item} Syntax 1
```{code-block} C
:caption: Indented correctly by you text editor by default
for (int in_range(i, 5))
	/* 0 1 2 3 4 */;
for (int in_range(i, 3, 8))
	/* 3 4 5 6 7 */;
for (int in_range(i, 2, 7, 3))
	/* 2 5 */;
```
::::
::::{tab-item} Syntax 2
```{code-block} C
:caption: Single parenthesis level
for_in_range(int, i, 5)
	/* 0 1 2 3 4 */;
for_in_range(int, i, 3, 8)
	/* 3 4 5 6 7 */;
for_in_range(int, i, 2, 7, 3)
	/* 2 5 */;
```
::::
::::{tab-item} Syntax 3
```{code-block} C
:caption: Explicit variable declaration
int i;
for_in_range(i, 5)
	/* 0 1 2 3 4 */;
for_in_range(i, 3, 8)
	/* 3 4 5 6 7 */;
for_in_range(i, 2, 7, 3)
	/* 2 5 */;
```
::::
:::::
