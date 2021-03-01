#include "estructuras.h"

//Compara 2 gimnasios usando como criterio la dificultad. Si el primer gimnasio es mas facil devuelve MENOR y si es mas dificil devuelve MAYOR. En caso de que falte alguno de los gimnasios devuelve ERROR.
int comparador_gimnasios (void* gimnasio_1, void* gimnasio_2){
    if(!gimnasio_1 || !gimnasio_2)
        return ERROR;

    if(((gimnasio_t*)gimnasio_1)->dificultad < ((gimnasio_t*)gimnasio_2)->dificultad){
        return MENOR;
    }else{
        return MAYOR;
    }
}

//Libera la memoria reservada para el pokemon dado.
void liberar_pokemon (pokemon_t* pokemon){
    free(pokemon);
}

//Libera la memoria reservada para el equipo dado, incluyendo todos los pokemones que contenga.
void liberar_equipo(lista_t* equipo){
    while(!lista_vacia(equipo)){
        liberar_pokemon(lista_primero(equipo));
        lista_desencolar(equipo);
    }
    lista_destruir(equipo);
}


//Libera la memoria reservada para el personaje dado, incluyendo todo su equipo y capturados.
void liberar_jugador(personaje_t* jugador){
	if(!jugador)
		return;
    liberar_equipo(jugador->equipo);
    liberar_equipo(jugador->capturados);
    free(jugador);
}

//Libera la memoria reservada para el entrenador dado, incluyendo su equipo.
void liberar_entrenador(entrenador_t* entrenador){
	if(!entrenador)
		return;
    liberar_equipo(entrenador->equipo);
    free(entrenador);
}

//Libera la memoria reservada para todos los entrenadores que se encuentren en la lista y la lista en si.
void liberar_entrenadores(lista_t* entrenadores){
    while(!lista_vacia(entrenadores)){
        liberar_entrenador(lista_tope(entrenadores));
        lista_desapilar(entrenadores);
    }
    lista_destruir(entrenadores);
}

//Libera la memoria reservada para el gimnasio dado, incluyendo todos los entrenadores que contenga.
void destructor_gimnasios(void* gimnasio){
	if(!gimnasio)
		return;
    liberar_entrenadores(((gimnasio_t*)gimnasio)->entrenadores);
    free(gimnasio);
}

//Libera la memoria reservada para todos los gimnasios que se encuentren en el heap y el heap en si.
void liberar_gimnasios(heap_t* gimnasios){
    gimnasio_t* gimnasio_actual = heap_extraer_minimal(gimnasios);
    while(gimnasio_actual){
        destructor_gimnasios(gimnasio_actual);
        gimnasio_actual = heap_extraer_minimal(gimnasios);
    }
    heap_destruir(gimnasios);
}


//Devuelve true si el pokemon es valido y false si no.
bool es_pkm_valido(pokemon_t* pokemon){
	if(!pokemon){
		return false;
	}

	if(strcmp(pokemon->tipo, AGUA)==0){
		return true;
	}else if(strcmp(pokemon->tipo, TIERRA)==0){
		return true;
	}else if(strcmp(pokemon->tipo, FUEGO)==0){
		return true;
	}else if(strcmp(pokemon->tipo, AIRE)==0){
		return true;
	}else{
		return false;
	}
}
