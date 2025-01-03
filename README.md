This repository holds a barebones `clang` plugin that prints the name of all named structures in a C program.
Note that this was only tested on Ubuntu 24.04.1 LTS and `clang` version 20, so your results may vary.
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

The easiest way to satisfy the last two requirements is to follow the steps to [build and install](https://clang.llvm.org/get_started.html) `clang` from source.
By using the latest version of `clang`, you also reduce the chance of mishaps that happen when you tell `clang` to load your plugin, 
perhaps because of header file mismatches.

## Building and Running

The `makefile` gives you how to install each step. Running `make test` will build the plugin, then build the example file with the plugin loaded.
Each recipe is commented, so you can inspect each step independently.
