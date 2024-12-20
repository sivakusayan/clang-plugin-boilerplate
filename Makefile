.PHONY: build clean

print-struct.so: print-struct.cpp
	clang++ -fno-rtti -shared -fPIC print-struct.cpp -o print-struct.so

test: print-struct.so
	clang -Xclang -load -Xclang ./print-struct.so -Xclang -add-plugin -Xclang print-struct example/main.c -o example/main.out

clean:
	rm -f print-struct.so
