CC := gcc

CFLAGS := -Wall -ansi -std=gnu99

HDRS := src/Srch_Basis.h src/FILESYS.h

SRCS := src/main.c src/Srch_Basis.c src/FILESYS.c

OBJS := $(SRCS:.c=.o)

EXEC := myFind

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	-rm -f src/*.o core src/*.core