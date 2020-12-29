
#include <string.h>
#include "batallas.h"

#define AGUA "Agua"
#define TIERRA "Tierra"
#define FUEGO "Fuego"
#define Aire "Aire"


//Pre: Ambos pokemones deben ser validos (Se supine que la validacion ya fue hecha llegados a este punto)
//Post: El primer pokemon solo gana cuando es es del tipo ventajoso respcto a su oponente, en casa de ser
//		del mismo tipo o cualquir otro caso gana el segundo.
int funcion_batalla_1(void* pkm_1, void* pkm_2){
	if( strcmp(pkm_1->tipo, AGUA)==0 && strcmp(pkm_2->tipo, FUEGO)==0   ||
		strcmp(pkm_1->tipo, FUEGO)==0 && strcmp(pkm_2->tipo, TIERRA)==0 ||
		strcmp(pkm_1->tipo, TIERRA)==0 && strcmp(pkm_2->tipo, AIRE)==0  ||
		strcmp(pkm_1->tipo, AIRE)==0 && strcmp(pkm_2->tipo, AGUA)==0      )
		return GANO_PRIMERO;
	return GANO_SEGUNDO;
}

//Pre: Ambos pokemones deben ser validos
//Post: El primer pokemon gana cuando iguala o supera en velocidad al segundo. En casa contrario gana el segundo
int funcion_batalla_2(void* pkm_1, void* pkm_2){
	if(pkm_1->velocidad >= pkm_2->velocidad)
		return GANO_PRIMERO;
	return GANO_SEGUNDO;
}

//Pre: Ambos pokemones deben ser validos
//Post: El primer pokemon gana cuando iguala o supera en defensa al segundo. En casa contrario gana el segundo (Pelea de metapods!!).
int funcion_batalla_3(void* pkm_1, void* pkm_2){
	if(pkm_1->defensa >= pkm_2->defensa)
		return GANO_PRIMERO;
	return GANO_SEGUNDO;
}

//Pre: Ambos pokemones deben ser validos
//Post: El primer pokemon gana cuando iguala o supera en ataque al segundo. En casa contrario gana el segundo.
int funcion_batalla_4(void* pkm_1, void* pkm_2){
	if(pkm_1->ataque >= pkm_2->ataque)
		return GANO_PRIMERO;
	return GANO_SEGUNDO;
}

//Pre: Ambos pokemones deben ser validos
//Post: El primer pokemon gana cuando el largo de su nombre es igual o superior al nombre del segundo. En casa contrario gana el segundo.
int funcion_batalla_5(void* pkm_1, void* pkm_2){
	if(strlen(pkm_1->nombre) >= strlen(pkm_2->nombre))
		return GANO_PRIMERO;
	return GANO_SEGUNDO;
}
