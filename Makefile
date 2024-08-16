#SAN=-fsanitize=address -fsanitize=leak -fsanitize=undefined
SAN=
CC=gcc -std=gnu17 -Wall -Wextra -MMD $(SAN) -g
LIBS=-lSDL2 -lSDL2_image

SRCS=$(wildcard examples/*.c)
OBJS=$(SRCS:.c=.o)
DEPS=$(SRCS:.c=.d)
BINS=$(SRCS:.c=.bin)

OBJS+=gfx.o
DEPS+=gfx.d

all: $(BINS)

run: $(BINS)
	@for bin in $(BINS); do \
		$$bin ;\
	done\

%.bin: %.o gfx.o
	$(CC) $^ -o $@ $(LIBS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	/bin/rm -f $(OBJS) $(DEPS) $(BINS)

-include $(DEPS)
