This repository holds a barebones `clang` [plugin](https://clang.llvm.org/docs/ClangPlugins.html) that prints the name of all named structures in a C program.
It consists of:

- `print-struct.cpp`: The code for the plugin in question
- `example/main.c`: An extremely simple C program to demonstrate the plugin's functionality
- A makefile that demonstrates how to build and run the plugin

This repository does not have an example of building on Windows. If that is what you need, I recommend
you take a look at the [clang-tutor](https://github.com/banach-space/clang-tutor) repository, which has examples of building `clang` plugins with `cmake`.

## Requirements

You'll need:
- A C++ compiler of your choice
  - You can override the C++ compiler that `make` chooses by defining the `CXX` environment variable
- An installed set of `clang` and `llvm` development header files. You can get these a few different ways:
    - You can get these header files by [building and installing](https://clang.llvm.org/get_started.html) `clang` from source.
    - (Ubuntu) Install the `clang` and `llvm` development packages by running `sudo apt install libclang-dev llvm-dev`
    - (MacOS) Install `llvm` with homebrew by running `brew install llvm`
- A `clang` compiler whose version matches the version of the header files you have installed
    - If you don't follow this step, you might get some confusing ABI related issues.

## Building and Running

Building the plugin and running it on `example/main.c` should be as simple as running:

```
make test
```

If you're getting complaints about missing header files, you probably need to add a `CXXFLAG` to specify what the include paths are for the `clang` and `llvm` development header files.
For example:

- (Ubuntu) Assuming you installed `libclang-dev` and `llvm-dev`, you should be able to run `make test CXXFLAGS="-I/usr/lib/llvm-18/include"`
- (MacOS) Assuming you installed `llvm` with brew, you should be able to run `make test CXXFLAGS="-I/opt/homebrew/opt/llvm/include"`

If you're still having trouble building, I would recommend you take a look at how [CI builds and tests](/.github/workflows) this repository, as those provide
minimal examples of a successful build.

## Credits

Thanks to the [clang-plugins-demo](https://github.com/nsumner/clang-plugins-demo) and the [clang-tutor](https://github.com/banach-space/clang-tutor) repositories for providing working examples
that I could use to troubleshoot issues with!
Those repositories also provide great examples of `clang` plugins that you can play around with.
