#ifndef __MENUS_H__
#define __MENUS_H__

#include "estructuras.h"

void menu_combate(pokemon_t* pokemon_jugador, pokemon_t* pokemon_entrenador, int resultado_combate);
void menu_victoria(personaje_t* jugador, entrenador_t* lider);
char menu_derrota(personaje_t* jugador);
char menu_inicial(personaje_t** jugador, heap_t* gimnasios);

#endif /* __MENUS_H__ */