# Preprocessor

Let's recap what we have learned so far about the C preprocessor:
 - It is a preliminary compilation step, happening before the compilation proper ([phase 7](00_compilation.md#phase7))
 - Its input is a stream of tokens

What that  means, is that the preprocessor manipulates text, not values:
 - It cannot use the result of expressions like `1 + 3`{l=C}, `sizeof(int)`{l=C}, or `strlen("Hello")`{l=C}[^strlen] that are evaluated during [phase 7](00_compilation.md#phase7).
 - What it _can_ do is more akin to string manipulation that math: it is meant to modify / generate code, not to do computation

[^strlen]: While in theory not different from other functions, `strlen` _may_ be computed at compile-time in practice, as an inlined compiler built-in, when its input is a string literal.

## Directives

As mentioned in the intro, interacting with the preprocessor is done by starting a line with the `#` character, followed by a preprocessing directive:

### File inclusion

`#include <`{l=C} _filename_ `>`{l=C}
: Look for a file called _filename_ in folders provided to the preprocessor[^include] with the `-I` flag, and in standard folders configured at compiler installation

`#include "`{l=c} _filename_ `"`{l=C}
: Same as above, but look into the current directory first

_Source_ : {bdg-link-primary-line}`cppreference <https://en.cppreference.com/w/c/preprocessor/include>`

::::{dropdown} Which directories does my compiler looks into ?
:color: success
:icon: light-bulb
:animate: fade-in

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

### Conditional inclusion

{#if}
`#if`{l=C} _condition_ _A_ `#else`{l=C} _B_ `#endif`{l=C}
: nnnn

`#ifdef`{l=C} _MACRO_
: Equivalent to `#if defined(MACRO)`{l=C}, see [`#if`{l=C}](if)

`#ifndef`{l=C} _MACRO_
: Equivalent to `#if !defined(MACRO)`{l=C}, see [`#if`{l=C}](if)

[^include]: Here we are refering to the preprocessor program, often called `cpp`, that handles phases 1 to 4. More often than not it is called by the compiler, with the relevant flags being forwared as-is.
