# Getting started: using existing macros

Before defining our own macros, let's see how they are used.

## Constants

The most basic usage of macros is constants:
::::{tab-set}
:::{tab-item} Compiler view
```{literalinclude} ../samples/02_constants.c
:language: C
:tab-width: 4
```
:::
:::{tab-item} Preprocessor view
```{literalinclude} ../samples/02_constants.c
:language: prepro
:tab-width: 4
```
:::
:::{tab-item} Preprocessed
```{literalinclude} ../preprocessed/02_constants.i
:language: C
:tab-width: 4
```
:::
::::

As you can see in the preprocessed tab, those constants are evaluated before compilation, and replaced by a plain literal.

:::{dropdown} Why are macros used in this situation ?
:color: primary
:icon: question
Why wasn't a constant used instead ? For instance, `extern FILE *const stderr;`{l=C} is a constant, why wasn't `STDERR_FILENO`{l=C} defined as `extern int const stderr_fileno;`{l=C} ?

Differences include:
 * A constant has to be defined in a `.c` source file
 * that will be compiled into a library
 * So to use it one must link to that library
 * It can't be inlined as the value isn't known at compile-time
 * At run-time, the constant's value needs to be fetched (extra instruction(s))
 * In the case of dynamic libraries (`.so`/`.dll`), the value can be changed between runs.
 * Also, the value of a macro can depend on macros defined by the user when including the header, while a constant has the same value for all users.

So, using macros saves a few instructions and bytes, which might seem pointless nowadays. It should also be noted that many libraries are "header-only" and so don't have the option of defining an extern constant.

There is an ill-advised third option: define the constant as static and define it in the header. It will create a copy with its own address in each compilation unit that includes it.
:::

## Function-like

Macros can also take parameters:
