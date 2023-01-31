CC := gcc

CFLAGS := -Wall -pthread

SERVER_HDRS := src/Server/ServerBase.h src/Utility/Lib.h src/DataStructure/Queue.h src/Utility/Utility.h src/Utility/Signal.h src/DataStructure/Vector.h src/DataStructure/String.h src/DataStructure/FileSystem.h

SERVER_SRCS := src/Server/server.c src/Server/ServerBase.c src/Utility/Lib.c src/DataStructure/Queue.c src/Utility/Utility.c src/Utility/Signal.c src/DataStructure/Vector.c src/DataStructure/String.c src/DataStructure/FileSystem.c

SERVER_OBJS := $(SERVER_SRCS:.c=.o)

SERVER_EXEC := server

SERVANT_HDRS := src/Servant/ServantBase.h src/Utility/Signal.h src/Utility/Lib.h src/Utility/Utility.h src/DataStructure/String.h src/DataStructure/FileSystem.h src/DataStructure/Vector.h

SERVANT_SRCS := src/Servant/servant.c src/Servant/ServantBase.c src/Utility/Signal.c src/Utility/Lib.c src/Utility/Utility.c src/DataStructure/String.c src/DataStructure/FileSystem.c src/DataStructure/Vector.c

SERVANT_OBJS := $(SERVANT_SRCS:.c=.o)

SERVANT_EXEC := servant

CLIENT_HDRS := src/Client/ClientBase.h src/Utility/Lib.h src/Utility/Signal.h src/Utility/Utility.h src/DataStructure/String.h

CLIENT_SRCS := src/Client/client.c src/Client/ClientBase.c src/Utility/Lib.c src/Utility/Utility.c src/DataStructure/String.c src/Utility/Signal.c

CLIENT_OBJS := $(CLIENT_SRCS:.c=.o)

CLIENT_EXEC := client

all: $(SERVER_EXEC) $(SERVANT_EXEC) $(CLIENT_EXEC)

$(SERVER_EXEC): $(SERVER_OBJS) $(SERVER_HDRS)
	$(CC) -o $@ $(SERVER_OBJS) $(CFLAGS)

$(SERVANT_EXEC): $(SERVANT_OBJS) $(SERVANT_HDRS)
	$(CC) -o $@ $(SERVANT_OBJS) $(CFLAGS)

$(CLIENT_EXEC): $(CLIENT_OBJS) $(CLIENT_HDRS)
	$(CC) -o $@ $(CLIENT_OBJS) $(CFLAGS)

clean:
	rm -f $(SERVER_EXEC) $(SERVER_OBJS) $(SERVANT_EXEC) $(SERVANT_OBJS) $(CLIENT_EXEC) $(CLIENT_OBJS)