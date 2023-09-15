# microui-raylib

[raylib][raylib] renderer for [microui][microui] in C99

## features

- Tiny: under 200 sloc of C99.
- Handle mouse & keyboard inputs.
- Handle custom fonts.
- Draw controls on screen.
- All symbols are namespaced (prefixed) with either `MURL_` or `murl_`.

## examples

There are some code examples in the [`examples`](examples) folder.

> [!NOTE]
> To compile the examples with the given `Makefile`, make sure you have the
> `microui.c` and `microui.h` files in the `vendor` folder.
> Then simply run `make`.

All available functions are listed in [`src/murl.h`](src/murl.h).

## contributing

New features are not guaranteed to be merged, since I want to keep the
codebase small. Issues, bug reports and bug fixes are welcome.

All contributions will be licensed under [`LICENSE`](LICENSE).

[microui]: https://github.com/rxi/microui
[raylib]: https://www.raylib.com
