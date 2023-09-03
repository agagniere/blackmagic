# Getting started with macros

## First steps: using existing macros

Before defining our own macros, let's see how they are used.

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
:start-at: 'int main'
:tab-width: 4
```
:::
::::
