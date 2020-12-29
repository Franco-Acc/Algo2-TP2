CFLAGS= -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

correr: abb
	./abb

compilar: abb.c pruebas.c
	gcc $(CFLAGS) abb.c pruebas.c -o abb

compilar_minipruebas: abb.c abb_minipruebas.c
	gcc $(CFLAGS) abb.c abb_minipruebas.c -o abb_mini

valgrind: abb
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb

valgrind_minipruebas: abb_mini
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb_mini

debugg: abb  
	gdb -tui abb

