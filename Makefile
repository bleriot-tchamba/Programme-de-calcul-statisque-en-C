all:main

main: main.c
	gcc main.c -o Executable/main -lm
	./Executable/main
