CFLAGS= -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

correr: lista_se
	./lista_se

compilar: lista.c pruebas.c
	gcc $(CFLAGS) lista.c pruebas.c -o lista_se

compilar_minipruebas: lista.c lista_minipruebas.c
	gcc $(CFLAGS) lista.c lista_minipruebas.c -o lista_mini

valgrind: lista_se
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_se

valgrind_minipruebas: lista_mini
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_mini
