
# Copyright 2015 Connor Taffe <cpaynetaffe@gmail.com>
# This program is free software licensed under the MIT license.

# This makefile generates a static library,
# this library contains all the data structures used.

CFLAGS += -g

SRC = chan.c list.c
OBJ = $(SRC:.c=.o)
LIB = chan.a

$(LIB): test $(OBJ)
	ar rcs $(LIB) $(OBJ)


$(OBJ):
	$(CC) $(CFLAGS) -c $(SRC)

# test for proper functionality
test: $(OBJ)
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -o test $(OBJ) main.o
	./test
	$(RM) test main.o

chan.o: chan.h list.h
list.o: list.h

clean:
	$(RM) $(OBJ) $(LIB)
