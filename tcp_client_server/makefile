CORE_FLAGS := -g -Wall -Wextra -pedantic

client : client.c
	gcc -o client client.c -lws2_32 $(CORE_FLAGS)

server : server.c
	gcc -o server server.c -lws2_32 $(CORE_FLAGS)	

clean:
	del *.exe *.o $(objects)