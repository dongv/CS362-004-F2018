CFLAGS= -Wall -fpic -coverage -lm -std=c99

ctest: testme.c 
	gcc -o test -g testme.c $(CFLAGS)

rtest:
	./test 
	
all: ctest rtest
	