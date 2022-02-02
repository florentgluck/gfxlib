CC=gcc -std=c11 -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined -g
LIBS=-lSDL2

gfx_example: gfx_example.o gfx.o
	$(CC) $^ -o $@ $(LIBS)

gfx_example.o: gfx_example.c gfx.h
	$(CC) $< -c

gfx.o: gfx.c gfx.h
	$(CC) $< -c

run: gfx_example
	./$<

clean:
	rm -f *.o gfx_example
