#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__

#include "estructuras.h"

/*
 *Carga los datso del personaje principal para la partida, para hacerlo pedirá la direccion del archivo al ususario.
 *En caso de ya tener cargado un personaje, este se sobreescribirá.
 *En caso de fallo al reservar la memoria devolvera NULL.
 *En caso de algun error durante la lectura del archivo, se cargara hasta donde se puedo leer correctamente.
 */
void cargar_personaje(personaje_t** jugador);

#endif /* __PERSONAJE_H__ */