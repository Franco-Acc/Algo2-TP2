#ifndef __GIMNASIO_H__
#define __GIMNASIO_H__

#include "estructuras.h"


/*
 *Carga los gimnasios necesarios para la partida, para hacerlo pedirá la direccion del archivo al ususario.
 *Se le preguntará al usuario si desea cargar un nuevo gimnasio una vez cargado el primero.
 *En caso de ya tener cargado un gimnasio, este dejará y se añadirá el nuevo.
 *En caso de algun error durante la lectura del archivo, se cargara hasta donde se puedo leer correctamente.
 */
void cargar_gimnasios(heap_t* gimnasios);

/*
 *El personaje principal se enfrentará los entrenadores del gimnasio pasado.
 *Si es una simulacion se luchará hasta perder algun combate o ganar a todos los entrenadores, sin posibilidad de cambiar o robar pokemones.
 *Si no es una partida simulada se irán mostrando menus que permiten cambiar el equipo, robar pokemon del lider, mostrar info y reintentar el gimnasio en caso de perder.
 */
int enfrentar_gimnasio(personaje_t* jugador, gimnasio_t* gimnasio, bool es_simulacion);


#endif /* __GIMNASIO_H__ */