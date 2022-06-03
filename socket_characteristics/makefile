CORE_FLAGS := -g -Wall -Wextra -pedantic

socket_char : socket_char.c
	gcc -o socket_char socket_char.c -lws2_32 $(CORE_FLAGS)

clean:
	del *.exe *.o $(objects)