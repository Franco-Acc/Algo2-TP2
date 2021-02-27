#ifndef __AVENTURA_H__
#define __AVENTURA_H__

#include "estructuras.h"

/*
 *Juega una partida con todos los Menus y salidas por pantalla disponibles.
 */
void jugar(personaje_t* jugador, heap_t* gimnasios, bool es_simulacion);

/*
 *Juega una partida sin los Menus hasta perder en alguna batalla o ganar toda la liga.
 */
void simular(personaje_t* jugador, heap_t* gimnasios);

/*
 *Crea las estructuras necesarias para la partida.
 */
int crear_estructuras(heap_t** gimnasios, personaje_t** jugador);

#endif /* __AVENTURA_H__ */