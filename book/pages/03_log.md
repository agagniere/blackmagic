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
Because a program may output thousands up on thousands of log lines when running, it might be preferable not to print characters that have no effect.

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
:caption: Step 0: just print it !
printf("DEBUG|`folder/file.c`|`main`|12|Hello world !\n");
printf("ERROR|`folder/file.c`|`foobar`|42|Failed to open `%s`: %s\n", file_name, strerror(errno));
```

## Concatenate string literals at compile-time

The first trick we can use is not specific to macros: we have seen, in the list of [phases of translation](00_compilation.md#phases-of-translation), that during phase 6, "Adjacent string literals are concatenated".

What that means is that `"Hello" " World"`{l=C} becomes `"Hello World"`{l=C}. More interestingly, it allows to split a string literal on multiple lines, without the need for a way to escape new lines:
```{code-block} C
:caption: Adjacent string literals with no macros involved
const char help[] =
	"Usage:\n"
	"  command [OPTION...] FILE\n\n"
	"Options:\n"
	"  -h, --help      Print this help\n"
	"  -p, --port=INT  Specify the port to listen to\n";
```

This allows us to split the boiler-plate from the "variable" parts of the string:
```{code-block} C
:caption: Step 1: Isolate the user-provided string
printf("DEBUG"  "|`"  "folder/file.c"  "`|`main`|"    "12"  "|"  "Hello world !"            "\n");
printf("ERROR"  "|`"  "folder/file.c"  "`|`foobar`|"  "42"  "|"  "Failed to open `%s`: %s"  "\n", file_name, strerror(errno));
```

## Current file name

In addition to the user-provided string, a variable part of the log output is the name of the file the log is from.

We don't want the user to have to provide it, as it would then have no guarantee of beiing up to date and therefore would be useless.

Luckily, the compiler can provide this information, as we have seen in the [last chapter](02_use.md#debugging-constants).
Most conviniently, it is provided as a string literal, allowing us to concatenate it with the rest of the string at compile-time:
```{code-block} C
:caption: Step 2: Ask the compiler for the file name
printf("DEBUG"  "|`"  __FILE__  "`|`main`|"    "12"  "|"  "Hello world !"            "\n");
printf("ERROR"  "|`"  __FILE__  "`|`foobar`|"  "42"  "|"  "Failed to open `%s`: %s"  "\n", file_name, strerror(errno));
```

:::{note}
In this instance, we use `__FILE__` and not `__FILE_NAME__`, to be able to differentiate files that have the same name in different directories, like `arrays/push.c` and `deque/push.c`.
:::

