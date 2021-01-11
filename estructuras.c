#include "estructuras.h"

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
    liberar_equipo(jugador->equipo);
    liberar_equipo(jugador->capturados);
    free(jugador);
}


void liberar_entrenador(entrenador_t* entrenador){
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

void leer_primera_letra_de_linea(FILE* archivo_gimnasio, char* letra){
    fscanf(archivo_gimnasio, FORMATO_LECTURA_PRIMERA_LETRA, letra);
}

void pedir_direccion(char* direccion){
    printf("\n Ingrese la direccion del archivo: ");
    scanf("%500s", direccion);
}