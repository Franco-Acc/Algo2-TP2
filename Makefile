CC=gcc
CFLAGS= -std=c99 -Wall -Wconversion -Werror -g


compile_aventura: aventura.c batallas.c estructuras.c gimnasio.c interfaz.c menus.c personaje.c heap.c lista.c
	$(CC) $(CFLAGS) aventura.c batallas.c estructuras.c gimnasio.c interfaz.c menus.c personaje.c heap.c lista.c -o aventura

compile_pruebas: pruebas.c batallas.c estructuras.c gimnasio.c interfaz.c menus.c personaje.c heap.c lista.c
	$(CC) $(CFLAGS) pruebas.c batallas.c estructuras.c gimnasio.c interfaz.c menus.c personaje.c heap.c lista.c -o pruebas


aventura: aventura
	./aventura


check_aventura: aventura
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./aventura

check_pruebas: pruebas
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas



debugg_aventura: aventura  
	gdb -tui aventura

debugg_pruebas: pruebas  
	gdb -tui pruebas