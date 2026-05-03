# Translate-C

A Zig package for translating C code into Zig code, intended to replace
`@cImport` and `zig translate-c`.

This is the main branch, which tracks master branch of Zig. Other branches
track other versions of Zig.

## Usage

Add `translate-c` to your `build.zig.zon` with this command:

```sh-session
$ zig fetch --save git+https://codeberg.org/ziglang/translate-c
info: resolved to commit 1aa9ec052415feeaa0494190ae35a94849a24399
```

Then, within your `build.zig`, write something like this:

```zig
// An abstraction to make using translate-c as simple as possible.
const Translator = @import("translate_c").Translator;

// You *can* pass `target` and/or `optimize` in the options struct here, but it's typically
// not necessary. You usually want to build for the host target, which is the default.
const translate_c = b.dependency("translate_c", .{});

const t: Translator = .init(translate_c, .{
    .c_source_file = b.path("to_translate.h"),
    .target = target,
    .optimize = optimize,
});
// If you want, you can now call methods on `Translator` to add include paths (etc).

// Depend on the translated C code as a Zig module.
some_module.addImport("translated", t.mod);
// ...or, if you want to, just use the output file directly.
const translated_to_zig: LazyPath = t.output_file;
```

For a more complete usage, take a look at the [Examples](#examples).

## Options

```zig
/// Should static functions be translated as `pub`.
pub_static: bool,
/// Should function bodies be translated.
func_bodies: bool,
/// Should macro names of literals be preserved.
keep_macro_literals: bool,
/// Should struct fields be default initialized.
default_init: bool,
/// Control when to treat a trailing array as a flexible array member.
/// Mirrors the -fstrict-flex-arrays=<n> compiler flag.
strict_flex_arrays: StrictFlexArraysLevel,

pub const StrictFlexArraysLevel = enum {
    /// Any trailing array member is a flexible array.
    @"0",
    /// Trailing arrays of size 0, 1, or undefined are flexible.
    @"1",
    /// Trailing arrays of size 0 or undefined are flexible (default).
    @"2",
    /// Only trailing arrays of undefined size are flexible.
    @"3",
};
```

## Examples

This repository contains a few examples in the `examples/` directory. You can test that all of the examples
work by running `zig build all` in that directory.

Within a specific example's directory, run `zig build test` to test that example. Most also have a step
called `run` or similar which you can use to run the compiled program without hiding stdout.

- [import header](examples/import_header/build.zig)
- [compile c](examples/compile_c/build.zig)
- [use static library](examples/use_static_lib/build.zig)
