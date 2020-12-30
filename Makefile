CC=gcc
CFLAGS= -std=c99 -Wall -Wconversion -Werror -g

compile: *.c
	$(CC) $(CFLAGS) *.c -o aventura

check: aventura
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./aventura

debugg: aventura
	gdb -tui $(evento_pesca)
