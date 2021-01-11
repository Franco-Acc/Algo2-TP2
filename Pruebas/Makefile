CC=gcc
CFLAGS= -std=c99 -Wall -Wconversion -Werror -g

compile: *.c
	$(CC) $(CFLAGS) *.c -o pruebas

check: pruebas
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas

debugg: pruebas  
	gdb -tui pruebas
