# GCC 11.4.0 
CC = gcc
CFLAGS = -Wall -Iinclude

PROJECT = ascii_snake

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,obj/%.o,$(SRC))

obj/%.o: %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

$(PROJECT): $(OBJ)
	$(CC) -o $@ $^ -lm

.PHONY: clean

clean: 
	rm -f $(OBJ) $(PROJECT)
