# A log library

Let's use all the tricks learned so far to write our first macros.

## Objective

We want logging functions
- that display debug information like the location of the log in the source (file, function, line)
- that have a log level associated, and be able to filter out the most verbose levels if desired
- whose output format can be chosen, and have a markdown output format to be rendered here (in addition to the default console output format)

We will write something like:
```{code-block} C
:caption: What the user writes
log_debug("Hello world !");
log_error("Failed to open `%s`: %s", file_name, strerror(errno));
```

And want something of the form:
```{code-block} Markdown
:caption: What is written to standard output in markdown format
| DEBUG | `folder/file.c` | `main` | 12 | Hello world ! |
| ERROR | `folder/file.c` | `foobar` | 42 | Failed to open `baz.csv`: No such file or directory |
```

That will be rendered here as:
:::{card}
Mardown table rendered
^^^
| Level | File            | Function | Line | Message                                             |
|:------|:----------------|:---------|-----:|:----------------------------------------------------|
| DEBUG | `folder/file.c` | `main`   |   12 | Hello world !                                       |
| ERROR | `folder/file.c` | `foobar` |   42 | Failed to open `baz.csv`: No such file or directory |
:::

## Concatenate string literals at compile time

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
