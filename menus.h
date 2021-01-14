#ifndef __MENUS_H__
#define __MENUS_H__

#include "estructuras.h"

//Permite al usuario mostrar la info del gimnasio actual y del personaje principal, cambiar el equipo actual y avanzar a la siguiente batalla.
void menu_gimnasio(personaje_t* jugador, gimnasio_t* gimnasio);

//Muestra al usuario la informacion de los pokemones que se enfrentan y el resultado del dicho enfrentamiento
//Detiene el juego hasta que el usuario quiera continuar.
void menu_combate(pokemon_t* pokemon_jugador, pokemon_t* pokemon_entrenador, int resultado_combate);

//Permite al usuario tomar prestado un pokemon del lider de gimnasio que venció, cambiar el equipo actual y avanzar al siguiente gimnasio.
void menu_victoria(personaje_t* jugador, entrenador_t* lider, bool ya_robo);

//Permite al usuario cambiar el equipo actual, reintentar el gimnasio actual y rendirse.
//Devuelve REINTENTAR o RENDIRSE.
char menu_derrota(personaje_t* jugador);

//Permite al usuario cargar los gimnasios y el personaje principal para la partida, jugar una partida y simular una partida.
//Devuelve JUGAR o SIMULAR.
char menu_inicial(personaje_t** jugador, heap_t* gimnasios);

#endif /* __MENUS_H__ */