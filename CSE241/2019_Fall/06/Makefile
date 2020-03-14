CC := g++

CFLAGS := -Wall -std=c++11

HDRS := ./src/GTUContainer.h ./src/GTUContainerDerived.h ./src/Node.h ./src/GTUIterator.h ./src/GTUIteratorConst.h ./src/GTUVector.h ./src/GTUSet.h ./src/GTUGlobalFunction.h ./src/GTUException.h

SRCS := ./src/main.cpp

OBJS := $(SRCS:.c=.o)

EXEC := run

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
