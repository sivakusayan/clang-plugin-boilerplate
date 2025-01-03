An extremely minimal plugin to use with Clang version 20.
Note that this was only tested on Ubuntu 24.04.1 LTS.

## Requirements

The only thing you'll need is your C++ compiler of choice, and to have the `clang`
and `llvm` header files installed somewhere on your machine. The easiest way to
do this is to install `clang` using the instructions on its repo.

## Building and Running

The `makefile` gives you how to install each step. Running `make test` will build the plugin, then build the example file with it.
You can inspect each step independently.
