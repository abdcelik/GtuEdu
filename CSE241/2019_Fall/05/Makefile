CC := g++

CFLAGS := -Wall --std=c++11

HDRS := AbstractBoard.h BoardVector.h BoardArray1D.h BoardArray2D.h

SRCS := main.cpp AbstractBoard.cpp BoardVector.cpp BoardArray1D.cpp BoardArray2D.cpp

OBJS := $(SRCS:.c=.o)

EXEC := run

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
