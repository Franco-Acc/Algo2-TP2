#ifndef __INTERFAZ_H__
#define __INTERFAZ_H__

#include "estructuras.h"

void mostrar_opciones_menu_inicial();
char pedir_instruccion_inicial();

void mostrar_opciones_menu_victoria(bool ya_robo);
char pedir_instruccion_victoria(bool ya_robo);

void mostrar_opciones_menu_derrota();
char pedir_instruccion_derrota();

void mostrar_gimnasios(heap_t* gimnasios);
void mostrar_equipo(lista_t* equipo);
void imprimir_pokemon(pokemon_t* pokemon);

bool pedir_confirmacion();
int pedir_posicion_pokemon(size_t tope_equipo);
pokemon_t* obtener_pokemon_en_posicion(lista_t* equipo, int posicion);

#endif /* __INTERFAZ_H__ */