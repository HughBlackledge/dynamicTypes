# Write a makefile to compile main.cpp
all: main

main: main.cpp dyn.cpp functions.cpp types.cpp string_overloads.cpp object.cpp dynamicTypes.cpp
	g++ -std=c++2a -o main main.cpp

debug: main.cpp dyn.cpp functions.cpp types.cpp string_overloads.cpp dynamicTypes.cpp
	g++ -std=c++2a -g -o main main.cpp

# dynamicTypes: dyn.cpp object.cpp functions.cpp types.cpp string_overloads.cpp
# 	g++ -std=c++2a -o main dyn.cpp object.cpp functions.cpp types.cpp string_overloads.cpp

# can it also check if dyn.cpp or functions.cpp or types.cpp or string_overloads.cpp have been changed
# and recompile main.cpp if they have?

clean:
	rm main

run: all
	./main
run_debug: debug
	gdb ./main