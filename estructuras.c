#include "estructuras.h"


int comparador_gimnasios (void* gimnasio_1, void* gimnasio_2){
    if(!gimnasio_1 || !gimnasio_2)
        return ERROR;

    if(((gimnasio_t*)gimnasio_1)->dificultad < ((gimnasio_t*)gimnasio_2)->dificultad){
        return MENOR;
    }else{
        return MAYOR;
    }
}


void liberar_pokemon (pokemon_t* pokemon){
    free(pokemon);
}


void liberar_equipo(lista_t* equipo){
    while(!lista_vacia(equipo)){
        liberar_pokemon(lista_primero(equipo));
        lista_desencolar(equipo);
    }
    lista_destruir(equipo);
}



void liberar_jugador(personaje_t* jugador){
	if(!jugador)
		return;
    liberar_equipo(jugador->equipo);
    liberar_equipo(jugador->capturados);
    free(jugador);
}


void liberar_entrenador(entrenador_t* entrenador){
	if(!entrenador)
		return;
    liberar_equipo(entrenador->equipo);
    free(entrenador);
}


void liberar_entrenadores(lista_t* entrenadores){
    while(!lista_vacia(entrenadores)){
        liberar_entrenador(lista_tope(entrenadores));
        lista_desapilar(entrenadores);
    }
    lista_destruir(entrenadores);
}


void destructor_gimnasios(void* gimnasio){
	if(!gimnasio)
		return;
    liberar_entrenadores(((gimnasio_t*)gimnasio)->entrenadores);
    free(gimnasio);
}


void liberar_gimnasios(heap_t* gimnasios){
    gimnasio_t* gimnasio_actual = heap_extraer_minimal(gimnasios);
    while(gimnasio_actual){
        destructor_gimnasios(gimnasio_actual);
        gimnasio_actual = heap_extraer_minimal(gimnasios);
    }
    heap_destruir(gimnasios);
}


void leer_primera_letra_de_linea(FILE* archivo_gimnasio, char* letra){
	if(!archivo_gimnasio || !letra)
		return;
    fscanf(archivo_gimnasio, FORMATO_LECTURA_PRIMERA_LETRA, letra);
}

