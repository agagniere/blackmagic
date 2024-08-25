# A log library

Let's use all the tricks learned so far to write our first macros.

It will be the occasion to introduce more tricks, and to create a logging utility header that may be used in real projects.

## Objective

We want logging functions
- that display debug information like the location of the log in the source (file, function, line)
- that have a log level associated, and be able to filter out the most verbose levels if desired
- whose output format can be configured, and have a markdown output format to be rendered here

We will write something like:
```{code-block} C
:caption: What the user writes
log_debug("Hello world !");
log_error("Failed to open `%s`: %s", file_name, strerror(errno));
```

And want something of the form:
```{code-block} Markdown
:caption: What is written to standard output in markdown format
| DEBUG | `folder/file.c` | `main`   | 12 | Hello world !                                       |
| ERROR | `folder/file.c` | `foobar` | 42 | Failed to open `baz.csv`: No such file or directory |
```

:::{dropdown} Details about the markdown syntax
:icon: ellipsis
:color: info
Because a program may output thousands upon thousands of log lines when running, it might be preferable not to print characters that have no effect.

In our instance, there is no need for spaces around `|`, and the two outer `|` can be omitted, so what we actually want to be output is:
```{code-block} Markdown
DEBUG|`folder/file.c`|`main`|12|Hello world !
ERROR|`folder/file.c`|`foobar`|42|Failed to open `baz.csv`: No such file or directory
```
:::

That will be rendered here as:
:::{card}
Mardown table rendered
^^^
| Level | File            | Function | Line | Message                                             |
|:------|:----------------|:---------|-----:|:----------------------------------------------------|
| DEBUG | `folder/file.c` | `main`   |   12 | Hello world !                                       |
| ERROR | `folder/file.c` | `foobar` |   42 | Failed to open `baz.csv`: No such file or directory |
:::

The simplest and most direct way to achieve the desired output is to print it literally:
```{code-block} C
:caption: Step 0 - just print it !
printf("DEBUG|`folder/file.c`|`main`|12|Hello world !\n");
printf("ERROR|`folder/file.c`|`foobar`|42|Failed to open `%s`: %s\n", file_name, strerror(errno));
```

Starting from this, let's use increasingly andvanced tricks to end-up with the desired interface,
while remaining functionnaly equivalent to the simplest solution.

:::{dropdown} Bonus feature
:icon: light-bulb
:color: success

{#bonus}
It could be useful to have a way to automatically include in the log what the computation was, in addition to its result.

An example would be to write:
```{code-block} C
log_eval(2 + 2);
log_eval(strlen(a) - strlen(b));
```
and expect logs that contain:
```{code-block} C
2 + 2 = 4
strlen(a) - strlen(b) = 8
```
:::

## Split string literals

The first trick we can use is not specific to macros: we have seen, in the list of [phases of translation](00_compilation.md#phases-of-translation), that during phase 6, "Adjacent string literals are concatenated".

What that means is that `"Hello" " World"`{l=C} becomes `"Hello World"`{l=C}. More interestingly, it allows to split a string literal on multiple lines, without the need for a way to escape new lines:
```{code-block} C
:caption: Adjacent string literals are concatenated, with no macros involved
const char help[] =
	"Usage:\n"
	"  command [OPTION...] FILE\n\n"
	"Options:\n"
	"  -h, --help      Print this help\n"
	"  -p, --port=INT  Specify the port to listen to\n";
```

This allows us to split the boiler-plate from the "variable" parts of the string:
```{code-block} C
:caption: Step 1 - Isolate the user-provided string
printf("DEBUG"  "|`"  "folder/file.c"  "`|`"  "main"    "`|"  "12"  "|"  "Hello world !"            "\n");
printf("ERROR"  "|`"  "folder/file.c"  "`|`"  "foobar"  "`|"  "42"  "|"  "Failed to open `%s`: %s"  "\n", file_name, strerror(errno));
```

## Current file name

In addition to the user-provided string, a variable part of the log output is the name of the file the log is from.

We don't want the user to have to provide it, as it would then have no guarantee of being up to date and would therefore be useless.

Luckily, the compiler can provide this information, as we have seen in the [last chapter](02_use.md#debugging-constants).
Most conveniently, it is provided as a string literal, allowing us to concatenate it with the rest of the string at compile-time:
```{code-block} C
:caption: Step 2 - Ask the compiler for the file name
printf("DEBUG"  "|`"  __FILE__  "`|`"  "main"    "`|"  "12"  "|"  "Hello world !"            "\n");
printf("ERROR"  "|`"  __FILE__  "`|`"  "foobar"  "`|"  "42"  "|"  "Failed to open `%s`: %s"  "\n", file_name, strerror(errno));
```

:::{note}
In this instance, we use `__FILE__` and not `__FILE_NAME__`, to be able to differentiate files that have the same name in different directories, like `arrays/push.c` and `deque/push.c`.
:::

## Current function and line

OK, the file name was easy, but what about the function name ?

As seen in the [last chapter](02_use.md#debugging-constants), the name of the function is provided by a magic constant `__func__`.
But as it is not a string literal, it cannot be concatenated at compile-time.

So we have to do that at run-time, and we are already using `printf`, so let's use the `%s` flag:
```{code-block} C
:caption: Step 3 - Ask the compiler for the function name
printf("DEBUG"  "|`"  __FILE__  "`|`%s`|"  "12"  "|"  "Hello world !"            "\n", __func__);
printf("ERROR"  "|`"  __FILE__  "`|`%s`|"  "42"  "|"  "Failed to open `%s`: %s"  "\n", __func__, file_name, strerror(errno));
```

As you can see, it is slightly less trivial than the previous step, as it involves adding an argument to `printf`, before the user provided arguments, if any.

:::{note}
`__func__` and `__FUNCTION__` are two names of the exact same variable, so they can be used interchangably. But the lower case `__func__` emphasize the fact that it is not a compile-time macro, as opposed to `__FILE__`.
:::

Next, we have the line number to display. By using the same trick as the function name, we can include it at run-time:
```{code-block} C
:caption: Step 4 - Ask the compiler for the line number
printf("DEBUG"  "|`"  __FILE__  "`|`%s`|%i|"  "Hello world !"            "\n", __func__, __LINE__);
printf("ERROR"  "|`"  __FILE__  "`|`%s`|%i|"  "Failed to open `%s`: %s"  "\n", __func__, __LINE__, file_name, strerror(errno));
```

## Define a simple macro

We can now place the boiler-plate in a macro to be reused:

:::::{card}
Step 5 - Single-parameter macros
^^^
:::{preprocessed} 03_simple_macro
:no-compiler-view:
:output: markdown
:::
:::::

That is nice, but we also want to be able to pass additional arguments to printf, to include values of run-time variables.

Printf can take a [variable number of arguments](https://en.cppreference.com/w/c/io/fprintf), making it what is called a "variadic function".
It is made possible by [a language feature](https://en.cppreference.com/w/c/variadic), that affects how parameters are placed on the stack and accessed by the callee.

Fortunatly, the C language also features a way for macros to be variadic, which is the next trick we'll be using.

## Define a variadic macro

:::::{dropdown} How to define and use variadic macros ?
:icon: question
:color: primary

A variadic macro is a function-like macro that takes a variable number of arguments.

::::{card}
To define a variadic macro we just need to add an ellipsis (`...`{l=C}) after the mandatory arguments, if any:
^^^
:::{preprocessed} 03_vm1
:no-compiler-view:
:output: none
:::
+++
We can see that `FOO` takes 2 or more arguments while `NOOP` takes any number of arguments
::::

::::{card}
The extra arguments can then be pasted using the `__VA_ARGS__` identifier:
^^^
:::{preprocessed} 03_vm2
:no-compiler-view:
:output: none
:::
::::

::::{card}
The magic macro `__VA_OPT__` can be used to remove certain characters when `__VA_ARGS__` is empty:
^^^
:::{preprocessed} 03_vm3
:no-compiler-view:
:output: none
:::
::::
:::::

Let's not rush it, as it is tempting to simply add `...` and `__VA_ARGS__` like so:
```{code-block} prepro
#define log_log(LEVEL, MESSAGE, ...) \
    printf("|" LEVEL "|`" __FILE__ "`|`%s`|%i|" MESSAGE "\n", __func__, __LINE__, __VA_ARGS__)

#define log_error(MESSAGE, ...) log_log("ERROR", MESSAGE, __VA_ARGS__)

log_error("Failed to open %s: %s", filename, error);
```

This code causes a compilation error when passing no additional parameters: `log_error("Out of memory");`{l=C} expands to `printf("[...]", __func__, __LINE__, );`{l=C} with an extraneous comma !

To solve this issue we will use the magic macro `__VA_OPT__`{l=prepro} to remove the comma when `__VA_ARGS__`{l=prepro} is empty:

::::{card}
Step 6 - Variadic macro
^^^
:::{preprocessed} 03_variadic_macro
:output: markdown
:::
::::

::::{dropdown} History lesson
:icon: info
:color: primary

`__VA_OPT__`{l=C} was introduced in C23. Before that, there was no portable way to remove characters when `__VA_ARGS__`{l=C} is empty.

But because removing a comma when there are no arguments is such a common need, GNU introduced a syntax to specifically remove a comma before `__VA_ARGS__`{l=C} (and nothing else !)

:::{preprocessed} 03_vm_gnu
:no-compiler-view:
:output: none
:::

_Source_: {bdg-link-secondary-line}`GNU <https://gcc.gnu.org/onlinedocs/gcc-12.2.0/gcc/Variadic-Macros.html>`

A portable workaround was to always have at least one mandatory argument, and not giving it a name:
:::{preprocessed} 03_vm_portable
:no-compiler-view:
:::

But as you can tell, it adds a lot of limitations.
::::

## Bonus feature: Log an expression and its result

With the logging macros of the previous section, we can already log the value of a variable with its name:
```{code-block} C
int answer = 12;

log_debug("answer = %i", answer);
```
But that requires repeating the name of the variable twice, could there be a way to obtain a string from an identifier ?

Well of course ! We've seen it [here](01_preprocessor.md#the-operators), the preprocessor has the `#` operator, that turns an identifer into a string literal.

:::{important}
We have to keep in mind that this operator can only be applied to a parameter of a function-like macro.
:::

:::::{card}
Transforming an identifier into a string
^^^^^
:::{preprocessed} 03_eval1
:no-compiler-view:
:::
::::{dropdown} How does it work ?
:color: info
:icon: question
Consider the following line of code:
```{code-block} C
printf("%s = %i\n", arg_count, arg_count);
```
It would be [tokenized](00_compilation.md#tokenizing) like this:
:::{card}
Preprocessing input
^^^
{bdg-primary-line}`printf` {bdg-dark-line}`(`
{bdg-success-line}`%s = %i\n` {bdg-dark-line}`,` {material-regular}`space_bar` {bdg-primary-line}`arg_count`
{bdg-dark-line}`,` {material-regular}`space_bar` {bdg-primary-line}`arg_count`
{bdg-dark-line}`)` {bdg-dark-line}`;` {material-regular}`keyboard_return`
:::

What the `#` operator can do is change the token type of {bdg-primary-line}`arg_count` to string literal, {bdg-success-line}`arg_count`, resulting in:
```{code-block} C
printf("%s = %i\n", "arg_count", arg_count);
```
:::::

OK that is working as expected, what about a computation ?

:::::{card}
Transforming arbitrary code into a string
^^^^^
:::{preprocessed} 03_eval2
:no-compiler-view:
:::
::::{dropdown} How does it work ?
:color: info
:icon: question
To be exact, the `#` operator applies to the `VARIABLE` identifier, and creates a string literal from whatever it expands to, which doesn't even need to be valid C !
:::::

Works out of the box, very nice.

Now that it is clear, we can concatenate the string literals at compile time:
```{code-block} prepro
#define log_eval_integer(VARIABLE) printf(#VARIABLE " = %i", VARIABLE)
```

And of course we do not want to have a different macro for every different type, so the macro will take a printf flag as argument:
```{code-block} prepro
#define log_eval(FLAG, VARIABLE) printf(#VARIABLE " = %" FLAG, VARIABLE);
```

:::{tip}
The standard header `inttypes.h` defines macros that expand to a printf flag, that are useful when using fixed-width integer types like `int32_t`, `uint64_t` or `intmax_t`.

_Source_: {bdg-link-primary-line}`cppreference<https://en.cppreference.com/w/c/types/integer>`
:::

Let's finish this feature and integrate it with the logging macros:
:::{preprocessed} 03_eval3
:output: markdown
:::

## Convert the line number to a string literal

Currently, the line number of each log entry is placed at run-time, using the `"%i"`{l=C} printf format.

But why do it at run-time ? `__LINE__` is a macro that expands to an integer literal, meaning its value is accessible at compile-time. It just isn't a string, so we cannot concatenate it as-is.

We've just seen how the `#` operator can create a string literal from arbitrary code, let's use it !

`__LINE__` is not an argument of our `log_log` macro, so we can't write `# __LINE__` directly. Instead we'll define a `STRINGIZE` macro that applies `#` to its argument:

:::{preprocessed} 03_stringline1
:no-compiler-view:
:::

Wait, that is not what we wanted ! We wanted `__LINE__` to be expanded to `8` __before__ being converted to a string !

Turns out using the `#` and `##` operators changes how macro arguments are expanded:

{attribution="GCC Documentation"}
> Macro arguments are completely macro-expanded before they are substituted into a macro body, __unless they are stringized or pasted with other tokens__.

And so, the solution is to have a macro that:
 - takes `__LINE__` as an argument
 - but __does not apply the `#` operator__ on it, for the argument to be expanded
 - and then passes the result to `STRINGIZE`, so that it is converted to a string literal

:::{preprocessed} 03_stringline2
:no-compiler-view:
:::

Success ! We can integrate this in our logging macros:

::::{card}
Step 7 - Line number concaternated at compile-time
^^^
:::{preprocessed} 03_stringline3
:output: markdown
:::
::::

Looks like we achieved several of our objectives:
 - The interface
 - The markdown table output
 - The inclusion of debug info (file, function, line)
 - The bonus objective of logging an expression alongside its result

Two objectives remain:
 - Configurable log level
 - Configurable output format

## Configurable log level

While our logs do have a log level associated, there's currently no way to filter out certain levels.

Because we're only creating a simplistic header-only logging library, we will not allow arbitrary filters (like allowing debug and warning but not info and error), only a threshold level.

What that means is that there will be a target log level, and logs as critical or more are outputted, while others are not.
Which implies that there must be a way to compare levels.

### Run-time comparison

Currently, log levels are just string literals like `"DEBUG"`{l=C} and `"ERROR"`{l=C}, and cannot be compared meaningfully to determine which is "more critical".

Solution: Make log levels integers.

And we are clean coders right ? So we'll define an enum:

```{code-block} C
:tab-width: 4
/** Criticality of a log entry */
enum log_level {
	NONE    /**< Choose this value as threshold to disable log output */,
	FATAL   /**< The program will stop */,
	ERROR   /**< The current operation will be aborted */,
	WARNING /**< Abnormal situation */,
	INFO    /**< Significant information */,
	DEBUG   /**< Only relevant to the developpers */,
	TRACE   /**< Spam */,
};
```
And a global threshold:
```{code-block} C
extern const enum log_level log_level;
```
Then we'll just have to compare the level of a log entry to the threshold to know if it needs to be output:

```{code-block} prepro
#define log_log(LEVEL, MESSAGE, ...)                                                         \
	if (LEVEL <= log_level) printf("|" STRINGIZE_EVALUATED(LEVEL) "|`" /* [...] */);

#define log_debug(MESSAGE, ...) log_log(DEBUG, MESSAGE __VA_OPT__(, ) __VA_ARGS__)

log_level = DEBUG;
log_debug("Hello World !"); // Logged
log_trace("Hello World !"); // Not logged
```
Something like that, right ?


## Recap

In this chapter we've learned:
1. Adjacent literal strings are concatenated automatically at compile-time
1. Logs can be enriched with the magic constants `__FILE__`, `__func__` and `__LINE__`
1. Function-like macros can be variadic, allowing zero or more extra arguments
   1. The extra arguements can be pasted with `__VA_ARGS__`
   1. And `__VA_OPT__()` can be used to remove characters when zero extra arguments are passed
1. The `#` operator can create a string literal from anything
   1. But it affects how macro arguments are expanded
   1. As a consequence when the arguments are macros themselves a wrapper may be used to force expansion
