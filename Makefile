FLAGS=-Wall -Werror -Wextra

all: main

main: main.o stack.o graph.o
	gcc main.o stack.o graph.o -o main -lm

main.o: main.c
	gcc $(FLAGS) -c main.c

stack.o: stack.c stack.h
	gcc $(FLAGS) -c stack.c

graph.o: graph.c graph.h
	gcc $(FLAGS) -c graph.c

clean:
	rm -rf *.o main
