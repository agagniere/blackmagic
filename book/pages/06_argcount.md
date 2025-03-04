# Counting arguments

:::{admonition} Work In Progress
:class: warning
This page is a draft
:::

If you've made it this far, congratulations !
You've completed the introduction.

We will now start abusing macros and delve into black magic.

The pivotal trick is going to be able to count the number of arguments given to a variadic macro.

## Objective

We want a macro `ARG_COUNT(...)`{l=C} that expands to an integer literal representing the number of arguments passed to it.
It shall be usable from other macros

```{code-block} C
:caption: Usage
int zero  = ARG_COUNT();
int one   = ARG_COUNT(A);
int three = ARG_COUNT(A, B, C);

#define FOO(...) printf("FOO was called with %i arguments", ARG_COUNT(__VA_ARGS__))

FOO("one", "two");
```

```{code-block} C
:caption: Expected result
int zero  = 0;
int one   = 1;
int three = 3;

printf("Foo was called with %i arguments", 2);
```

## Solution

Let's look at the simplest solution:

:::{preprocessed} 06_implementation
:::

Two macros are involved:
- The `ARG_10`{l=C} macro takes any number of arguments, and expands to the tenth argument.
- The `ARG_COUNT`{l=C} macro takes any number of arguments, forwards them to `ARG_10`{l=C}, adding the 10 arguments `9, 8, 7, 6, 5, 4, 3, 2, 1, 0`{l=C}.

We can then see that if no arguments is passed to `ARG_COUNT`{l=C}, the 10th argument is `0`, and for every argument added, the extra arguements are pushed to the right.

It is quite similar to the optional argument trick shown in the previous chapter: a variadic macro allows the user not to provide enough arguement to another macro, that in turn discards extraneous arguments.

## Usage example

OK, great, we have a macro that can count the number of arguments given to it.
What does this enable us to do ?

:::{preprocessed} 06_first_use
:::
