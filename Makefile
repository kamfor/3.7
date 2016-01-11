compile: main.c source/*
	gcc -o proj.o main.c source/* -lm -Wall -pedantic -ansi 
start: proj.o
	./proj.o
debug: proj.o
	gcc -o proj.o main.c source/* -Wall -pedantic -ansi && valgrind --leak-check=yes --track-origins=yes ./proj.o
