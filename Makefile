CC = gcc
CFLAGS = -Wall
DEPS = interface/my_pthread_t.h

main: my_pthread_t.o
	$(CC) -o main main.c my_pthread_t.o $(CFLAGS)

my_pthread_t.o: interface/my_pthread_t.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make_context: 
	gcc -o make_context examples/make_context.c

clean:
	rm -rf *.o make_context