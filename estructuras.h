#ifndef __ESTRUCTURAS_H__
#define __ESTRUCTURAS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "batallas.h"
#include "lista.h"
#include "heap.h"

#define MAX_DIRECCION 200
#define MAX_NOMBRE 100
#define MAX_NOMBRE_PKM 50
#define MAX_EQUIPO 6
#define MAX_TIPO 10

#define MENOR -1
#define MAYOR  1

#define MAX_BONUS 63

#define OK 0
#define ERROR -1

#define VICTORIA 1
#define DERROTA -1

#define GANO_PRIMERO 1
#define GANO_SEGUNDO -1

#define SI 'Y'
#define NO 'N'

#define GIMNASIO 'G'
#define LIDER 'L'
#define ENTRENADOR 'E'
#define POKEMON 'P'

#define INGRESAR_JUGADOR 'E'
#define INGRESAR_GIMNASIO 'A'
#define JUGAR 'I'
#define SIMULAR 'S'

#define PROXIMO 'N'
#define REINTENTAR 'R'
#define RENDIRSE 'F'
#define CAMBIAR_EQUIPO 'C'
#define TOMAR_PRESTADO 'T'

#define BATALLA 'B'
#define MOSTRAR_JUGADOR 'E'
#define MOSTRAR_GIMNASIO 'G'


#define AGUA "Agua"
#define TIERRA "Tierra"
#define FUEGO "Fuego"
#define AIRE "Aire"

#define FORMATO_LECTURA_PRIMERA_LETRA "%c;"

#define FORMATO_LECTURA_GIMNASIO "%99[^;];%u;%u\n"
#define CANT_ITEMS_GIMNASIO 3

#define FORMATO_LECTURA_ENTRENADOR "%99[^\n]\n"
#define CANT_ITEMS_ENTRENADOR 1

#define FORMATO_LECTURA_POKEMON "%49[^;];%19[^;];%u;%u;%u\n"
#define CANT_ITEMS_POKEMON 5

#define FORMATO_LECTURA_PERSONAJE "%99[^;];%99[^\n]\n"
#define CANT_ITEMS_PERSONAJE 2

#define ROJO "\e[31m"
#define VERDE "\e[32m"
#define AMARILLO "\e[33m"
#define NORMAL "\e[0m"


typedef struct pokemon{
	char nombre[MAX_NOMBRE_PKM];
	char tipo[MAX_TIPO];
	size_t velocidad;
	size_t defensa;
	size_t ataque;
	size_t bonus;
}pokemon_t;

typedef int (*funcion_batalla)(void*, void *);

typedef struct gimnasio{
    char nombre[MAX_NOMBRE];
    size_t dificultad;
    funcion_batalla reglas_de_batalla;
    lista_t* entrenadores;
} gimnasio_t;

typedef struct entrenador{
    char nombre[MAX_NOMBRE];
    lista_t* equipo;
} entrenador_t;

typedef struct personaje{
    char nombre[MAX_NOMBRE];
    char ciudad_natal[MAX_NOMBRE];
    size_t medallas_ganadas;
    lista_t* equipo;
    lista_t* capturados;
} personaje_t;


//Libera la memoria reservada para un pokemon.
void liberar_pokemon (pokemon_t* pokemon);

//Libera la memoria reservada para todo el equipo (incluyendo los pokemones que contiene).
void liberar_equipo(lista_t* equipo);

//Libera la memoria reservada para el jugador (incluyendo su equipo y capturados).
void liberar_jugador(personaje_t* jugador);

//Libera la memoria reservada para el entrenador (incluyendo su equipo).
void liberar_entrenador(entrenador_t* entrenador);

//Libera la memoria reservada para todos los entrenadores de la lista (incluyendo la lista en si).
void liberar_entrenadores(lista_t* entrenadores);

//Libera la memoria reservada para un gimnasio (incluyendo todos sus entrenadores).
void destructor_gimnasios(void* gimnasio);

//Libera la memoria reservada para todos gimnasios del juego (incluyendo todos sus entrenadores)
void liberar_gimnasios(heap_t* gimnasios);

//Compara 2 gimnasios segun su dificultad, devuelve MAYOR si el primero es mayor o igual al segundo,
//MENOR si el primero es menor al segundo o ERROR si falta alguno de los gimnasios.
int comparador_gimnasios (void* gimnasio_1, void* gimnasio_2);

//Lee la primera letra de la linea del archivo pasado, colocando dicha letra en la variable pasada por referencia.
void leer_primera_letra_de_linea(FILE* archivo_gimnasio, char* letra);

//Pide al usuario la direccion de un archivo y la almacena en la variable pasada.
void pedir_direccion(char* direccion);


#endif /* __ESTRUCTURAS_H__ */