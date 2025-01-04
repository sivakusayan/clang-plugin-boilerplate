.PHONY: test clean

#==================================================================
# BUILDING THE PLUGIN
#==================================================================

# A couple of important things here:
# 1. We need to explicitly set the C++ standard.
# 2. We need flags common to all shared objects. This includes
#    '-shared' and '-fPIC'. On Mac, we also need to add '-undefined dynamic_lookup',
#    as that is not set by default on that platform. Otherwise, the linker will
#    complain about undefined symbols.
# 3. We need '-fno-rtti' for reasons I don't completely understand.
CXXFLAGS += -std=c++17 -shared -fPIC -fno-rtti
ifeq ($(shell uname -s),Darwin)
	CXXFLAGS += -undefined dynamic_lookup
endif
print-struct.so: print-struct.cpp
	$(CXX) $(CXXFLAGS) print-struct.cpp -o print-struct.so

#==================================================================
# INVOKING THE PLUGIN
#==================================================================

# If we're on Mac, we should use the version of clang from homebrew (LLVM source clang), 
# instead of Apple's clang. The latter seems to have some default behavior that doesn't 
# play nicely with the plugin.
CLANG_BINARY = clang
ifeq ($(shell uname -s),Darwin)
	CLANG_BINARY = /opt/homebrew/opt/llvm/bin/clang
endif

# Compiles the file in the example folder with the print-struct plugin
# active.
# The verbose "-Xclang" syntax is a little strange, but it seems to
# be a way to pass arguments to the compiler frontend.
test: print-struct.so
	$(CLANG_BINARY) -Xclang -load -Xclang ./print-struct.so  \
					-Xclang -add-plugin -Xclang print-struct \
		  			example/main.c -o example/main.out

clean:
	rm -f print-struct.so
	rm -f example/main.out
