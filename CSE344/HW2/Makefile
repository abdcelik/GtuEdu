CC := gcc

CFLAGS := -Wall -ansi -std=gnu99 -Wextra -Wshadow -lm

SRCS := main.c

OBJS := $(SRCS:.c=.o)

EXEC := processM

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	-rm -f *.o core *.core