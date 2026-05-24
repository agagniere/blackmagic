# Getting started: using existing macros

Before writing our own macros, it helps to see what using them looks like.
This chapter surveys macros that require no external dependencies: constants from the standard library and special macros provided by the compiler.

## Constants

The most basic use of macros is as constants:

:::{preprocessed} 02_constants
:output: markdown
:::

As shown in the preprocessed tab, these constants are evaluated before compilation, and replaced by plain literals:

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

An extern constant comes with several drawbacks compared to a macro:
 * **Linkage**: it must be defined in a `.c` file, compiled into a library, and linked against — adding a dependency for a single integer value.
 * **Runtime cost**: the value and its use are in different compilation units, so the compiler cannot inline it; an extra fetch is required at runtime. (With a static library, link-time optimization *may* eliminate this — provided both the library and the caller were compiled with `-flto`.)
 * **Dynamic libraries**: with a `.so`/`.dll`, the runtime fetch is unavoidable — the value cannot be inlined across the dynamic link boundary, and may legitimately differ between runs (e.g. a version number). This can be intentional, but it means the caller has no compile-time guarantee of the value.
 * **No user customization**: a macro's value can depend on macros defined by the user at include time; a constant's value is fixed for all users.

The linkage dependency is the most consequential: libraries that are header-only cannot define extern constants at all. Macros sidestep this entirely.

There is an ill-advised third option: define the constant as `static` in the header. This avoids the linkage problem but creates a separate copy with its own address in each compilation unit that includes it.
:::

## Debugging constants

Some macro constants are special: their value changes depending on *where* in the source they appear.
Such behavior can only be achieved from within the compiler, and we will not be able to create our own.

The C standard requires compilers to define certain special macros, without the need to include any header, including:
- `__FILE__` expands to the name of the file currently compiled, as a C string literal
- `__LINE__` expands to the line number currently compiled, as an integer literal

_Source_: {bdg-link-primary-line}`GNU <https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html>`

Additionally, the GNU C extension include:
- `__FILE_NAME__` similar to `__FILE__` but only includes the file name, excluding the path

_Source_: {bdg-link-primary-line}`GNU <https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html>`
{bdg-link-secondary-line}`Clang <https://clang.llvm.org/docs/LanguageExtensions.html#builtin-macros>`

Related compiler-provided identifiers include:
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

Macros can also take parameters. Unlike functions, they expand at compile-time: there is no call overhead and no type constraints:
:::{preprocessed} 02_functionlike
:output: markdown
:::

With the compiler-provided constants in hand, the [next chapter](03_log.md) puts them to use in a logging utility.

## Recap

This chapter covered:
1. Macros used as constants are replaced by their value before compilation — no runtime cost, no linking required
1. Some compiler-provided macros (`__FILE__`, `__LINE__`) change value depending on where they appear in the source
1. `__func__` is not a macro but a runtime constant — it cannot be concatenated with string literals
1. Function-like macros take parameters and expand at compile-time, with no type constraints
