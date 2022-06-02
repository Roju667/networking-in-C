CORE_FLAGS := -g -Wall -Wextra -pedantic

hc_client : hc_client.c
	gcc -o hc_client hc_client.c -lws2_32 $(CORE_FLAGS)

hc_server : hc_server.c
	gcc -o hc_server hc_server.c -lws2_32 $(CORE_FLAGS)	

clean:
	del *.exe *.o $(objects)