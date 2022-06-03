CORE_FLAGS := -g -Wall -Wextra -pedantic

zombie_proc : zombie_proc.c
	gcc -o zombie_proc zombie_proc.c -lws2_32 $(CORE_FLAGS)

clean:
	del *.exe *.o $(objects)