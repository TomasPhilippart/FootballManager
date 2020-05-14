CC=gcc -Wall -Wextra -Werror -ansi -pedantic -g 
CFLAGS=-I.
DEPS = hashtable.h wrapper_futebol.h
OBJ = hashtable.o wrapper_futebol.o proj.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
 
futebol: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
