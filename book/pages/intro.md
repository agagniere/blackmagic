# Prepro... something ?

If you are reading this book, it means you already know what the C preprocessor is, right ? ...right ? Did you even write C before ?

Yes ? Then let's start from there. The preprocessor is what you interact with when you start a line with `#`.
It is used most notably to `#incude`{l=C} an other file, _i.e._ to paste the verbatim content of that file, in place of the include directive.

Let's say that again, what the preprocessor does, is to replace an expression, like `#include <toto.h>`{l=C} with characters, here the content of `toto.h`.

```{note}
No assumption is made about the content of the included file, it technically doesn't have to be valid C, or even code at all...
```

And that's all it does: it replaces expressions with text, be it when it replaces
 - `NULL`{l=C} with `((void*)0)`,
 - `#if 0`{l=C}, `#endif`{l=C} and the 1978 lines in between with... nothing, effectively deleting them
 - `#if 1`{l=C}, `#endif`{l=C} and the 326 lines in between with... those 326 lines, being as useful as a cow watching a train pass

Mmh yes it also has a `#define`{l=C} directive... for the user to define more expressions to be replaced with text!
It's called macros by the way, and might prove useful in the future.

{attribution="GCC Documentation"}
> A **macro** is a fragment of code which has been given a name. Whenever the name is used, it is replaced by the contents of the macro.

That's it, you now understand most of what there is to understand about the C preprocessor...

...but the devil is in the details, so before jumping into the next chapter, we'll review our knowledge of C compilation.
