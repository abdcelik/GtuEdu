CC := gcc

CFLAGS := -Wall -pthread -lm

HDRS := src/BASIS.h src/LIB.h src/MATRIX.h src/String.h

SRCS := src/main.c src/BASIS.c src/LIB.c src/MATRIX.c src/String.c

OBJS := $(SRCS:.c=.o)

EXEC := hw5

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)