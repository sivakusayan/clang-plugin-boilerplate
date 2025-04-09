This repository holds a barebones `clang` [plugin](https://clang.llvm.org/docs/ClangPlugins.html) that prints the name of all named structures in a C program.
It consists of:

- `print-struct.cpp`: The code for the plugin in question
- `example/main.c`: An extremely simple C program to demonstrate the plugin's functionality
- A makefile that demonstrates how to build and run the plugin

This repository does not have an example of building on Windows. If that is what you need, I recommend
you take a look at the [clang-tutor](https://github.com/banach-space/clang-tutor) repository, which has examples of building `clang` plugins with `cmake`.

## Table of Contents

- [What's a clang plugin?](#whats-a-clang-plugin)
- [Building and Running](#building-and-running)
  - [Ubuntu](#ubuntu)
  - [MacOS](#macos)
- [Troubleshooting](#troubleshooting)
- [Credits](#credits)

## What's a clang plugin?

A `clang` plugin is just a [shared object](https://en.wikipedia.org/wiki/Shared_library) that `clang` loads at runtime. It allows you to do all sorts of fancy things,
from creating custom compiler errors to automatically modifying code (with certain restrictions).

## Building and Running

### Ubuntu

If you have built and installed `clang` from source, you should already have all the development header files necessary.
In that case, building the plugin and running it on `example/main.c` should be as simple as running:
```
make test
```
Otherwise, if you don't have the necessary header files, you'll need to install the relevant development packages:

```
sudo apt install libclang-dev llvm-dev
make test CXXFLAGS="-I/usr/lib/llvm-18/include"
```

### MacOS

Building the plugin and running it on `example/main.c` should be as simple as installing the development header files then invoking `make`.
Make sure you let the compiler know where the header files are located:

```
brew install llvm
make test CXXFLAGS="-I/opt/homebrew/opt/llvm/include"
```

## Troubleshooting

Make sure that the version of `clang` that you are using to invoke the plugin has the same version as the `clang` and `llvm` development header files
you installed. Otherwise, you might get perplexing ABI errors.

Otherwise, if you're still having trouble, I would recommend you take a look at how [CI builds and tests](/.github/workflows) this repository, as those provide
minimal examples of working environments.

## Credits

Thanks to the [clang-plugins-demo](https://github.com/nsumner/clang-plugins-demo) and the [clang-tutor](https://github.com/banach-space/clang-tutor) repositories for providing working examples
that I could use to troubleshoot issues with!
Those repositories also provide great examples of `clang` plugins that you can play around with.
