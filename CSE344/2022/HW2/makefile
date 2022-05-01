CC := gcc

CFLAGS := -Wall -lm

HDRS := src/BASIS.h src/STRING.h src/LIB.h src/FILE.h src/MATRIX.h src/VECTOR.h

SRCS := src/BASIS.c src/STRING.c src/LIB.c src/FILE.c src/MATRIX.c src/VECTOR.c

PRNT := src/mainP.c 

CHLD := src/childP.c

OBJS := $(SRCS:.c=.o)

PRNTOBJS := $(PRNT:.c=.o)

CHLDOBJS := $(CHLD:.c=.o)

PRNTEXEC := processP

CHLDEXEC := childP

all: $(PRNTEXEC) $(CHLDEXEC)

$(PRNTEXEC): $(PRNTOBJS) $(OBJS) $(HDRS)
	$(CC) -o $@ $(PRNTOBJS) $(OBJS) $(CFLAGS)

$(CHLDEXEC): $(CHLDOBJS) $(OBJS) $(HDRS)
	$(CC) -o $@ $(CHLDOBJS) $(OBJS) $(CFLAGS)

clean:
	rm $(PRNTEXEC) $(CHLDEXEC) $(PRNTOBJS) $(CHLDOBJS) $(OBJS)