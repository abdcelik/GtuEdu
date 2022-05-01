CC := gcc

CFLAGS := -Wall

HDRS := src/BASIS.h src/VECTOR.h src/RULE.h src/LIB.h src/FILE.h

SRCS := src/main.c src/BASIS.c src/VECTOR.c src/RULE.c src/LIB.c src/FILE.c

OBJS := $(SRCS:.c=.o)

EXEC := a.out

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm $(EXEC) $(OBJS)