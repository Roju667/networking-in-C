CORE_FLAGS := -g -Wall -Wextra -pedantic

low_open : low_open.c
	gcc -o low_open low_open.c $(CORE_FLAGS)

client : client.c
	gcc -o client client.c -lws2_32 $(CORE_FLAGS)

server : server.c
	gcc -o server server.c -lws2_32 $(CORE_FLAGS)	

clean:
	del *.exe *.o $(objects)