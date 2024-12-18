all: align-packed.so

align-packed.so: align-packed.cpp
	clang++ -fno-rtti -shared -fPIC align-packed.cpp -o align-packed.so

test: align-packed.so
	clang example/main.c -fplugin=$(shell pwd)/align-packed.so -Xclang -plugin -Xclang hello-world

clean:
	rm align-packed.so
