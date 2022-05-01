CC := gcc

CFLAGS := -Wall -lrt -pthread

HDRS := src/LIB.h src/UNNAMED.h src/NAMED.h

SRCS := src/LIB.c

PART1SRC := src/main_part1.c src/UNNAMED.c

PART2SRC := src/main_part2.c src/NAMED.c

OBJS := $(SRCS:.c=.o)

PART1OBJ := $(PART1SRC:.c=.o)

PART2OBJ := $(PART2SRC:.c=.o)

PART1EXEC := hw3unnamed

PART2EXEC := hw3named

all: $(PART1EXEC) $(PART2EXEC)

$(PART1EXEC): $(PART1OBJ) $(OBJS) $(HDRS)
	$(CC) -o $@ $(PART1OBJ) $(OBJS) $(CFLAGS)

$(PART2EXEC): $(PART2OBJ) $(OBJS) $(HDRS)
	$(CC) -o $@ $(PART2OBJ) $(OBJS) $(CFLAGS)

clean:
	rm -f $(PART1EXEC) $(PART2EXEC) $(PART1OBJ) $(PART2OBJ) $(OBJS)