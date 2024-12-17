all: align-packed.so

align-packed.so: align-packed.cpp
	clang++ -fno-rtti -shared -fPIC align-packed.cpp -o align-packed.so -D_GLIBCXX_USE_CXX23_ABI=0

test: align-packed.so
	clang example/main.c -fplugin="/home/sayan/Development/Repos/clang-plugin-align-packed/align-packed.so" -Xclang -plugin -Xclang hello-world

clean:
	rm align-packed.so
