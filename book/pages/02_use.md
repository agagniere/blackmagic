# Getting started: using existing macros

Before defining our own macros, let's see how they are used.

## Constants

The most basic usage of macros is constants:

:::{preprocessed} 02_constants
:output: markdown
:::

As you can see in the preprocessed tab, those constants are evaluated before compilation, and replaced by plain literals:

:::{card}
Macros used in the example
^^^
| Macro                | Expansion         |
|:---------------------|:------------------|
| `STDOUT_FILENO`{l=C} | `1`{l=C}          |
| `STDERR_FILENO`{l=C} | `2`{l=C}          |
| `EXIT_FAILURE`{l=C}  | `1`{l=C}          |
| `EXIT_SUCCESS`{l=C}  | `0`{l=C}          |
| `NULL`{l=C}          | `((void*)0)`{l=C} |
:::

:::{dropdown} Why are macros used in this situation ?
:color: primary
:icon: question
:animate: fade-in-slide-down
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

## Debugging constants

Speaking of existing macro constants we can use, there exist certain macro constants, whose value is not always the same...
Such behavior can only be achieved from within the compiler, and we will not be able to create our own.

The C standard requires compilers to define certain special macros, without the need to include any header, including:
- `__FILE__` expands to the name of the file currently compiled, as a C string literal
- `__LINE__` expands to the line number currently compiled, as an integer literal

_Source_: {bdg-link-primary-line}`GNU <https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html>`

Additionnally, the GNU C extension include:
- `__FILE_NAME__` similar to `__FILE__` but only includes the file name, excluding the path

_Source_: {bdg-link-primary-line}`GNU <https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html>`
{bdg-link-secondary-line}`Clang <https://clang.llvm.org/docs/LanguageExtensions.html#builtin-macros>`

While we're at it, let's also mention:
- `__FUNCTION__` (also `__func__`) is a magic constant character array that contains the name of the current function
- `__PRETTY_FUNCTION__` is similar but includes the whole signature, including return type and parameters

:::{warning}
They are not macros, but runtime constants. As the GNU documentation puts it:
> These identifiers are variables, not preprocessor macros, and may not be used to initialize char arrays or be concatenated with string literals.
:::

_Source_: {bdg-link-primary-line}`GNU <https://gcc.gnu.org/onlinedocs/gcc/Function-Names.html>`

:::{preprocessed} 02_debug
:::

## Function-like

Macros can also take parameters:
:::{preprocessed} 02_functionlike
:output: markdown
:::
