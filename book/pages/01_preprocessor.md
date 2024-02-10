# Preprocessor

Let's recap what we have learned so far about the C preprocessor:
 - It is a preliminary compilation step, happening before the compilation proper ([phase 7](phase7))
 - Its input is a stream of tokens

What that  means, is that the preprocessor manipulates text, not values:
 - It cannot use the result of expressions like `1 + 3`{l=C}, `sizeof(int)`{l=C}, or `strlen("Hello")`{l=C}[^strlen] that are evaluated during [phase 7](phase7).
 - What it _can_ do is more akin to string manipulation than math: it is meant to modify / generate code, not to do computation

[^strlen]: While in theory not different from other functions, `strlen` _may_ be computed at compile-time in practice, as an inlined compiler built-in, when its input is a string literal.

Interacting with the preprocessor is done by starting a line with the `#` character, followed by a preprocessing directive. (Any number of spaces can be present before and after the `#` character)

## Directives

### File inclusion

`#include <`{l=C} _filename_ `>`{l=C}
: Look for a file called _filename_ in folders provided to the preprocessor[^include] with the `-I` flag, and in standard folders configured at compiler installation.
  Once the file is found, its content is pasted verbatim in place of the `#include`{l=C} line

[^include]: Here we are refering to the preprocessor program, often called `cpp`, that handles phases 1 to 4. More often than not it is called by the compiler, with the relevant flags being forwarded as-is.

`#include "`{l=c} _filename_ `"`{l=C}
: Same as above, but look into the current directory first

_Source_ : {bdg-link-primary-line}`cppreference <https://en.cppreference.com/w/c/preprocessor/include>`

```{note}
No assumption is made about the content of the included file, it technically doesn't have to be valid C, or even code at all...
```

::::{dropdown} Which directories does my compiler look into ?
:color: success
:icon: light-bulb
:animate: fade-in-slide-down

To list the folders where you compiler's preprocessor looks for files, you can execute the following command:
```bash
$(cc -print-prog-name=cpp) -v < /dev/null
```
```{code-block} shell-session
:caption: Possible output
:emphasize-lines: 1, 10

$ `cc -print-prog-name=cpp` -v < /dev/null
 ...
 #include "..." search starts here:
 #include <...> search starts here:
  /usr/lib/gcc/x86_64-linux-gnu/11/include
  /usr/local/include
  /usr/include/x86_64-linux-gnu
  /usr/include
 ...
$ `cc -print-prog-name=cpp` -I ~/mylib/include -iquote ./include -v < /dev/null
 ...
 #include "..." search starts here:
  ./include
 #include <...> search starts here:
  /home/user/mylib/include
  /usr/lib/gcc/x86_64-linux-gnu/11/include
  /usr/local/include
  /usr/include/x86_64-linux-gnu
  /usr/include
 ...
```
_Source_: {bdg-link-secondary-line}`stack overflow <https://stackoverflow.com/questions/344317/where-does-gcc-look-for-c-and-c-header-files>`
::::

### Macros

`#define`{l=C} _identifier_ _replacement_
: After this line, anytime _identifier_ appears in the source code, it will be replaced by _replacement_

`#define`{l=C} _identifier_
: Equivalent to `#define identifier 1`{l=C}

_Source_: {bdg-link-primary-line}`cppreference <https://en.cppreference.com/w/c/preprocessor/replace>`

### Conditional inclusion

`#if`{l=C} _condition_ _A_ `#else`{l=C} _B_ `#endif`{l=C}
: Evaluates _condition_ (so at preprocessor-time), then replaces the whole `#if`{l=C}...`#endif`{l=C} block with _A_ or _B_ depending on the result.

`#ifdef`{l=C} _MACRO_
: Equivalent to `#if defined(MACRO)`{l=C}

`#ifndef`{l=C} _MACRO_
: Equivalent to `#if !defined(MACRO)`{l=C}

`#elif`{l=C} _condition2_ _B_ `#endif`{l=C}
: Convenient way to chain multiple conditions without nesting, equivalent to:
  ```C
  #else
  #  if condition2
  B
  #  endif
  #endif
  ```

`#elifdef`{l=C} _MACRO_
: Added in C23 for constistency, equivalent to `#elif defined(MACRO)`{l=C}

`#elifndef`{l=C} _MACRO_
: Added in C23 for constistency, equivalent to `#elif !defined(MACRO)`{l=C}

_Source_: {bdg-link-primary-line}`cppreference <https://en.cppreference.com/w/c/preprocessor/conditional>`

::::{dropdown} How is the condition evaluated ?
:icon: alert
:color: secondary
:animate: fade-in-slide-down

The `#if`{l=C} block needs to be resolved at preprocessor-time, so its condition is evaluated with limited capabilities:
- only integer literals and macros that evaluate to an integer literal can be used in the condition
- all identifiers unknown to the preprocessor are replaced with `0`{l=C}

Said differently:
anything that is not a macro is replaced by `0`{l=C}, even if it has a value known at compile time (_e.g._ comparing to an enumerator is actually comparing to 0).

:::{danger}
It means that typos are silently replaced by `0`{l=C}
:::

::::

## The operators

We have seen [previously](00_compilation.md#tokenizing) that the input of the preprocessor is a stream of tokens, each with a type.

It should be of no surprise then, that the 2 preprocessor operators are about manipulating tokens.

`#`
: Set token type to string literal
: {bdg-primary-line}`name` {octicon}`arrow-right` {bdg-success-line}`name`

`##`
: Concatenate 2 tokens
: {bdg-primary-line}`some` {bdg-primary-line}`thing` {octicon}`arrow-right` {bdg-primary-line}`something`

It is only when expanding a macro that the preprocessor takes these operators into account.
It means they can only be used within the definition of a macro.
