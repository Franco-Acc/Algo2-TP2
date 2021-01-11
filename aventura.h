#ifndef __AVENTURA_H__
#define __AVENTURA_H__

#include "estructuras.h"

void jugar(personaje_t* jugador, heap_t* gimnasios);
void simular(personaje_t* jugador, heap_t* gimnasios);
void destructor_gimnasios(void* gimnasio);
int comparador_gimnasios (void* gimnasio_1, void* gimnasio_2);

#endif /* __AVENTURA_H__ */