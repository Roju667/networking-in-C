CORE_FLAGS := -g -Wall -Wextra -pedantic

udp_client : udp_client.c
	gcc -o udp_client udp_client.c -lws2_32 $(CORE_FLAGS)

udp_echo_server : udp_echo_server.c
	gcc -o udp_echo udp_echo_server.c -lws2_32 $(CORE_FLAGS)	

clean:
	del *.exe *.o $(objects)