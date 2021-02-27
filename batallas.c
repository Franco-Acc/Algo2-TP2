
#include "batallas.h"

//Pre: Ambos pokemones deben ser validos (Se supone que la validacion ya fue hecha llegados a este punto)
//Post: El primer pokemon gana cuando es del mismo tipo o del 'ventajoso' respecto a su oponente, en casa de ser
//		cualquier otro caso gana el segundo.
int funcion_batalla_1(void* pkm_1, void* pkm_2){
	if(!pkm_1 || !pkm_2)
		return ERROR;

	pokemon_t* pokemon_jugador = pkm_1;
	pokemon_t* pokemon_entrenador = pkm_2;

	if( (strcmp(pokemon_jugador->tipo, FUEGO)==0 && strcmp(pokemon_entrenador->tipo, AGUA)==0)   ||
		(strcmp(pokemon_jugador->tipo, TIERRA)==0 && strcmp(pokemon_entrenador->tipo, FUEGO)==0) ||
		(strcmp(pokemon_jugador->tipo, AIRE)==0 && strcmp(pokemon_entrenador->tipo, TIERRA)==0)  ||
		(strcmp(pokemon_jugador->tipo, AGUA)==0 && strcmp(pokemon_entrenador->tipo, AIRE)==0)    )
		return GANO_SEGUNDO;
	return GANO_PRIMERO;
}

//Pre: Ambos pokemones deben ser validos
//Post: El primer pokemon gana cuando iguala o supera en velocidad al segundo. En casa contrario gana el segundo
int funcion_batalla_2(void* pkm_1, void* pkm_2){
	if(!pkm_1 || !pkm_2)
		return ERROR;

	pokemon_t* pokemon_jugador = pkm_1;
	pokemon_t* pokemon_entrenador = pkm_2;

	if((pokemon_jugador->velocidad + pokemon_jugador->bonus) >= pokemon_entrenador->velocidad)
		return GANO_PRIMERO;
	return GANO_SEGUNDO;
}

//Pre: Ambos pokemones deben ser validos
//Post: El primer pokemon gana cuando iguala o supera en defensa al segundo. En casa contrario gana el segundo (Pelea de metapods!!).
int funcion_batalla_3(void* pkm_1, void* pkm_2){
	if(!pkm_1 || !pkm_2)
		return ERROR;

	pokemon_t* pokemon_jugador = pkm_1;
	pokemon_t* pokemon_entrenador = pkm_2;

	if((pokemon_jugador->defensa + pokemon_jugador->bonus) >= pokemon_entrenador->defensa)
		return GANO_PRIMERO;
	return GANO_SEGUNDO;
}

//Pre: Ambos pokemones deben ser validos
//Post: El primer pokemon gana cuando iguala o supera en ataque al segundo. En casa contrario gana el segundo.
int funcion_batalla_4(void* pkm_1, void* pkm_2){
	if(!pkm_1 || !pkm_2)
		return ERROR;

	pokemon_t* pokemon_jugador = pkm_1;
	pokemon_t* pokemon_entrenador = pkm_2;

	if((pokemon_jugador->ataque + pokemon_jugador->bonus) >= pokemon_entrenador->ataque)
		return GANO_PRIMERO;
	return GANO_SEGUNDO;
}

//Pre: Ambos pokemones deben ser validos
//Post: El primer pokemon gana cuando el largo de su nombre es igual o superior al nombre del segundo. En casa contrario gana el segundo.
int funcion_batalla_5(void* pkm_1, void* pkm_2){
	if(!pkm_1 || !pkm_2)
		return ERROR;

	pokemon_t* pokemon_jugador = pkm_1;
	pokemon_t* pokemon_entrenador = pkm_2;
	
	if(strlen(pokemon_jugador->nombre) >= strlen(pokemon_entrenador->nombre))
		return GANO_PRIMERO;
	return GANO_SEGUNDO;
}




//NOTA: Los punteros recibidos en las funciones de batalla son igualados a punteros a pokemones para evitar tener que hacer un casteo cada vez que quiero hacer algo con ellos.
//		Lo hice asi para no cambiar la firma de las funciones y que se sigan manejando con void* .
