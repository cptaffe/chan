
# Copyright 2015 Connor Taffe <cpaynetaffe@gmail.com>
# This program is free software licensed under the MIT license.

# This makefile generates a static library,
# this library contains all the data structures used.

CFLAGS += -g -I$(INCLUDE)

SRC = chan.c list.c
OBJ = $(SRC:.c=.o)
LIB = ds.a

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)


$(OBJ):
	$(CC) $(CFLAGS) -c $(SRC)

chan.o: chan.h list.h
list.o: list.h

clean:
	$(RM) $(OBJ) $(LIB)
