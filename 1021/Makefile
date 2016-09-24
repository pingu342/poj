all: a.out test

CFLAGS=-Wall

a.out: main.o
	$(CC) $^

#test: test.o
#	$(CC) $^ -o test

clean:
	rm -f a.out test *.o
