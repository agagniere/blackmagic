# Quotes about macros

{attribution="Bjarne Stroustrup"}
> I intensely dislike macros, but macros are deeply ingrained in the C and C++ eco systems. Among other uses, they act as a plaster over language weaknesses. They allow us to fall back to token manipulation. That’s what makes them poison to tool builders and consequently the root cause of the C++ community’s serious weakness when it comes to tools. I didn’t see a single facility for totally replacing macros while still remaining sufficiently flexible and efficient. Instead, I started an effort to gradually replace uses of macros with used of better-behaved features, such as consts, inline functions, name spaces, templates, initializer lists, constexpr. We are almost there! Static reflection might complete that effort (and feature macros could disrupt progress on tools). I know of no single language facility that could completely replace macros. I suspect that one that could would share many of the weaknesses of macros.

{attribution="Andrew Kelly"}
> C code is usually very simple to read, because it’s just functions and data. That’s the best case scenario. It does have just another different programming language on top of it, which is the C pre-processor. It’s not C, it’s a different language that’s based on text concatenation and people abuse that language too much.
>
> And then, it’s just too hard to figure out what’s going on. You see a function call, is it a function call? If you’re not super familiar with the code you’re reading, you’re always wondering, “Is that a macro? It might be a macro.” Right?

```{admonition} Source
* <https://www.stroustrup.com/P0976-the-evils-of-paradigms.pdf>
* <https://corecursive.com/067-zig-with-andrew-kelley>
```
