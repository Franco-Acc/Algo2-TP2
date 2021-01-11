#ifndef __GIMNASIO_H__
#define __GIMNASIO_H__

#include "estructuras.h"

void cargar_gimnasios(heap_t* gimnasios);
int enfrentar_gimnasio(personaje_t* jugador, gimnasio_t* gimnasio, bool es_simulacion);


#endif /* __GIMNASIO_H__ */