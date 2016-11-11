CC=g++
DEBUG=-g
CFLAGS=$(DEBUG) -c
SERVER_SOURCE=server.cpp
SERVER_INCLUDE=-I. -I./include -I./include
SERVER_LIB=./lib/libxmlrpc_server_abyss++.a ./lib/libxmlrpc_server++.a ./lib/libxmlrpc_abyss++.a ./lib/libxmlrpc_server_abyss.a ./lib/libxmlrpc_server.a ./lib/libxmlrpc_abyss.a -lssl -lcrypto ./lib/libxmlrpc++.a ./lib/libxmlrpc_util++.a ./lib/libxmlrpc.a ./lib/libxmlrpc_xmlparse.a ./lib/libxmlrpc_xmltok.a ./lib/libxmlrpc_util.a -lpthread -lsqlite3   

CLIENT_SOURCE=client.cpp
CLIENT_INCLUDE=-I. -I./include -I./include
CLIENT_LIB=./lib/libxmlrpc_client++.a ./lib/libxmlrpc_client.a ./lib/libxmlrpc++.a ./lib/libxmlrpc_util++.a ./lib/libxmlrpc.a ./lib/libxmlrpc_xmlparse.a ./lib/libxmlrpc_xmltok.a ./lib/libxmlrpc_util.a -lpthread -L/usr/lib/x86_64-linux-gnu -lcurl ./lib/libxmlrpc_packetsocket.a -lncurses   


all:
	$(CC) $(CFLAGS) $(SERVER_INCLUDE) server.cpp  -o server.o 
	$(CC) -o server server.o $(SERVER_LIB)
	$(CC) $(CFLAGS) $(CLIENT_INCLUDE) client.cpp
	$(CC) -o client client.o $(CLIENT_LIB)

server:
	./server

client:
	./client

clean:
	rm -rf *.o server client


