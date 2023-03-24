#SAN=-fsanitize=address -fsanitize=leak -fsanitize=undefined
SAN=
CC=gcc -std=gnu11 -Wall -Wextra $(SAN) -g
LIBS=-lSDL2

all: gfx_example list_drivers

gfx_example: gfx_example.o gfx.o
	$(CC) $^ -o $@ $(LIBS)

gfx_example.o: gfx_example.c gfx.h
	$(CC) $< -c

gfx.o: gfx.c gfx.h
	$(CC) $< -c

list_drivers: list_drivers.c
	$(CC) $^ -o $@ $(LIBS)

run: gfx_example list_drivers
	./list_drivers
	./gfx_example

clean:
	rm -f *.o gfx_example list_drivers
