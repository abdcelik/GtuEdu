CC := gcc

CFLAGS := -Wall -lrt -pthread

CLIENT_HDRS := src/CLIENTBASIS.h src/LIB.h src/STRING.h src/MATRIX.h

CLIENT_SRCS := src/client.c src/CLIENTBASIS.c src/LIB.c src/STRING.c src/MATRIX.c

CLIENT_OBJS := $(CLIENT_SRCS:.c=.o)

CLIENT_EXEC := client

SERVER_HDRS := src/SERVERBASIS.h src/DEAMON.h src/LIB.h src/STRING.h src/MATRIX.h

SERVER_SRCS := src/server.c src/SERVERBASIS.c src/DEAMON.c src/LIB.c src/STRING.c src/MATRIX.c

SERVER_OBJS := $(SERVER_SRCS:.c=.o)

SERVER_EXEC := serverY

all: $(CLIENT_EXEC) $(SERVER_EXEC)

$(CLIENT_EXEC): $(CLIENT_OBJS) $(CLIENT_HDRS)
	$(CC) -o $@ $(CLIENT_OBJS) $(CFLAGS)

$(SERVER_EXEC): $(SERVER_OBJS) $(SERVER_HDRS)
	$(CC) -o $@ $(SERVER_OBJS) $(CFLAGS)

clean:
	rm -f $(CLIENT_EXEC) $(SERVER_EXEC) $(CLIENT_OBJS) $(SERVER_OBJS)