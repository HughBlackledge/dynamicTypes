# Write a makefile to compile main.cpp
all: main

main: main.cpp dyn.cpp functions.cpp types.cpp string_overloads.cpp object.cpp dynamicTypes.cpp
	g++ -std=c++2a -o main main.cpp

clean:
	rm main

run: all
	./main
run_debug: debug
	gdb ./main