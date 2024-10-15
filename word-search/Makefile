#Makefile for hw3
#anna andrade
#aandra12
#B4E772

#compiling tags
CC=gcc
CFLAGS= -std=c99 -pedantic -Wall -Wextra

#linking
word_search: word_search.o search_functions.o
	$(CC) -o word_search word_search.o search_functions.o 

test: test_search_functions.o search_functions.o
	$(CC) -o test test_search_functions.o search_functions.o 

#compiling word search function/test function execution block
word_search.o: word_search.c search_functions.h
	$(CC) $(CFLAGS) -c word_search.c 

#compiling search functions that are called in word_search
search_functions.o: search_functions.c search_functions.h
	$(CC) $(CFLAGS) -c search_functions.c 

#remove intermediate files and executable called test to start anew
clean:
	rm -f *.o main
