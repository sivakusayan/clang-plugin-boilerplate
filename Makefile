.PHONY: test clean

# Builds the Clang plugin. Note that clang plugins are shared objects,
# so we must pass the "-shared" and "-fPIC" compilation flags.
# Furthermore, the "-fno-rtti" flag is needed for reasons I don't 
# completely understand.
print-struct.so: print-struct.cpp
	$(CXX) -fno-rtti -shared -fPIC print-struct.cpp -o print-struct.so

# Compiles the file in the example folder with the print-struct plugin
# active.
# The verbose "-Xclang" syntax is a little strange, but it seems to
# be a way to pass arguments to the compiler frontend.
test: print-struct.so
	clang -Xclang -load -Xclang ./print-struct.so  \
		  -Xclang -add-plugin -Xclang print-struct \
		  example/main.c -o example/main.out

clean:
	rm -f print-struct.so
	rm -f example/main.out
