.PHONY: build clean

print-struct.so: print-struct.cpp
	clang++ -fno-rtti -shared -fPIC print-struct.cpp -o print-struct.so

test: print-struct.so
	clang example/main.c -fplugin=$(shell pwd)/print-struct.so -Xclang -plugin -Xclang print-struct 

clean:
	rm -f print-struct.so
