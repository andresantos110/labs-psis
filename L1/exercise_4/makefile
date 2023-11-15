CC=gcc
CFLAGS= -Wall -g -O3 -fPIC -ldl -shared
RM= rm -f 

all: main lib1.so lib2.so

main:  lib1.so lib2.so
	$(CC) -g -o main lib.h main.c

clean:
	$(RM) *.o *.so

lib1.so: lib1.c
	$(CC) $(CFLAGS) lib1.c -o lib1.so

lib2.so: lib2.c
	$(CC) $(CFLAGS) lib2.c -o lib2.so



