CORE_FLAGS := -g -Wall -Wextra -pedantic

ordering : ordering.c
	gcc -o ordering ordering.c -lws2_32 $(CORE_FLAGS)

clean:
	del *.exe *.o *.txt $(objects)