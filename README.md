This repository holds a barebones `clang` plugin that prints the name of all named structures in a C program.
Note that this was only tested on Ubuntu 24.04.1 LTS and `clang` version 18, so your results may vary.
The repository consists of:

- `print-struct.cpp`: The code for the plugin in question
- `example/main.c`: An extremely simple C program to demonstrate the plugin's functionality
- A makefile that demonstrates how to build and run the plugin

## Requirements

You'll need:
- A C++ compiler of your choice
  - You can override the C++ compiler that `make` chooses by defining the `CXX` environment variable
- The `clang` compiler
- An installed set of `clang` and `llvm` development header files.

The slowest, but probably least error-prone way to satisfy the last two requirements is to follow the steps to [build and install](https://clang.llvm.org/get_started.html) `clang` from source.
By using the latest version of `clang`, you reduce the chance of mishaps that happen when you tell `clang` to load your plugin, perhaps because of header file mismatches. This also gives you
a nice excuse to hack on `clang` if you wish!

Alternatively, you can just install the `clang` and `llvm` development packages. On Ubuntu, you should be able to run:

```
sudo apt install libclang-dev llvm-dev
```

## Building and Running

Building the plugin and running it on the example C file should be as simple as:

```
make test
```

If you're getting complaints about missing header files, you probably need to add a `CXXFLAG` to specify what the include paths are for the `clang` and `llvm` development header files. If you installed
`libclang-dev` and `llvm-dev` on Ubuntu above, you should be able to run:

```
make test CXXFLAGS="-I/usr/lib/llvm-18/include"
```

If you're still having trouble building, I would recommend you take a look at the [CI file](/.github/workflows/ci.yml) for a minimal example of successfully building this plugin.
