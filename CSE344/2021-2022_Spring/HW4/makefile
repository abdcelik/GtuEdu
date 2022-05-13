CC := gcc

CFLAGS := -Wall -pthread

HDRS := src/BASIS.h src/LIB.h

SRCS := src/main.c src/BASIS.c src/LIB.c

OBJS := $(SRCS:.c=.o)

EXEC := hw4

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)