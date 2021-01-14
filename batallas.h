#ifndef __BATALLAS_H__
#define __BATALLAS_H__

#include "estructuras.h"
/*
 * Se deberan implementar las 5 funciones de batalla.
 * Las reglas para decidir al ganador las inventan ustedes
 * 
 * Si el ganador es el primer pokemon, se devolvera 1
 * Si el ganador es el segundo pokemon, se devolvera -1
 * 
 * No habran empates.
 */

/*
 *El primer pokemon gana cuando es del mismo tipo o del 'ventajoso' respecto a su oponente, en caso de ser
 *cualquier otro caso gana el segundo.
 */
int funcion_batalla_1(void* pkm_1, void* pkm_2);

/*
 *El primer pokemon gana cuando iguala o supera en velocidad al segundo. En casa contrario gana el segundo.
 */
int funcion_batalla_2(void* pkm_1, void* pkm_2);

/*
 *El primer pokemon gana cuando iguala o supera en defensa al segundo. En casa contrario gana el segundo (Pelea de metapods!!).
 */
int funcion_batalla_3(void* pkm_1, void* pkm_2);

/*
 *El primer pokemon gana cuando iguala o supera en ataque al segundo. En casa contrario gana el segundo.
 */
int funcion_batalla_4(void* pkm_1, void* pkm_2);

/*
 *El primer pokemon gana cuando el largo de su nombre es igual o superior al nombre del segundo. En casa contrario gana el segundo.
 */
int funcion_batalla_5(void* pkm_1, void* pkm_2);


#endif /* __BATALLAS_H__ */