CC := g++

CFLAGS := -Wall --std=c++11 -lm

HDRS := NP_base.h

SRCS := main.cpp NP_base.cpp

OBJS := $(SRCS:.c=.o)

EXEC := run

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
