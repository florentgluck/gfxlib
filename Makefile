#SAN=-fsanitize=address -fsanitize=leak -fsanitize=undefined
SAN=
CC=gcc -std=gnu11 -Wall -Wextra -MMD $(SAN) -g
LIBS=-lSDL2

C_SRCS=$(wildcard *.c)
C_OBJS=$(C_SRCS:.c=.o)
C_DEPS=$(C_OBJS:%.o=%.d)
C_OBJ_COMMON=gfx.o

BIN=gfx_example mouse_example list_drivers_example

all: $(BIN)

gfx_example: $(C_OBJ_COMMON) gfx_example.o
	@echo pipo
	$(CC) $^ -o $@ $(LIBS)

mouse_example: $(C_OBJ_COMMON) mouse_example.o
	$(CC) $^ -o $@ $(LIBS)

list_drivers_example: list_drivers_example.o
	$(CC) $^ -o $@ $(LIBS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f *.o *.d $(BIN)

-include $(C_DEPS)
