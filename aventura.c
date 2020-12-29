
#include <stdio.h>
#include <string.h>

#include "batallas.h"
#include "TDAS/LISTA/lista.h"
#include "TDAS/ABB/abb.h"

#define ERRROR -1;
#define OK 0;

#define GIMNASIO 'G';
#define LIDER 'L';
#define ENTRENADOR 'E';
#define POKEMON 'P';

#define FORMATO_LECTURA_PRIMERA_LETRA "%c;"

#define FORMATO_LECTURA_GIMNASIO "%[^;];%u;%u\n"
#define CANT_ITEMS_GIMNASIO 3

#define FORMATO_LECTURA_ENTRENADOR "%[^\n]\n"
#define CANT_ITEMS_ENTRENADOR 1

#define FORMATO_LECTURA_POKEMON "%[^;];%[^;];%i;%i;%i\n"
#define CANT_ITEMS_POKEMON 4


char leer_primera_letra_de_linea(FILE* archivo_gimnasio){
	char letra;
	fscanf(archivo_gimnasio, FORMATO_LECTURA_PRIMERA_LETRA, &letra);
	return letra;
}


bool leer_linea_gimnasio(FILE* archivo_gimnasio, gimnasio_t* un_gimnasio, size_t cant_items_esperados){
	size_t leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_GIMNASIO, un_gimnasio->nombre, un_gimnasio->dificultad, un_gimnasio->reglas_de_batalla);
	if(leidos != cant_items_esperados)
		return false;
	return true;
}

bool agregar_nuevo_entrenador(gimnasio_t* gimnasio, char nombre_entrenador[]){
	entrenador_t* nuevo_entrenador = calloc(1, sizeof(entrenador_t));
	if(!nuevo_entrenador)
		return false;
	
	strcpy(nuevo_entrenador->nombre, nombre_entrenador);
	
	if(!gimnasio->entrenadores)
		gimnasio->entrenadores = lista_crear();

	if(lista_apilar(gimasio->entrenadores, nuevo_entrenador)==ERROR)
		return false;

	return true;
}


bool leer_linea_entrenador(FILE* archivo_gimnasio, gimnasio_t* un_gimnasio, size_t cant_items_esperados){
	char nombre_entrenador[MAX_NOMBRE];
	size_t leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_ENTRENADOR, nombre_entrenador);
	if(leidos != cant_items_esperados)
		return false;
	return agregar_nuevo_entrenador(un_gimnasio, nombre_entrenador);
}

bool agregar_nuevo_pokemon(entrenador_t* entrenador, pokemon_t* pokemon){
	if(!entrenador){
		free(pokemon);
		return false;
	}

	if(!entrenador->equipo)
		entrenador->equipo = lista_crear();

	if(!entrenador->equipo){
		free(pokemon);
		return false;
	}

	if(lista_elementos(entrenador->equipo)<MAX_EQUIPO){
		if(lista_encolar(entrenador->equipo, pokemon)==ERROR){
			free(pokemon);
			return false;
		}
	}
	return true;
}



bool leer_linea_pokemon(FILE* archivo_gimnasio, gimnasio_t* un_gimnasio, size_t cant_items_esperados){
	pokemon_t* nuevo_pkm = calloc(1, sizeof(pokemon_t));
	size_t leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_POKEMON, nuevo_pkm->nombre, nuevo_pkm->tipo, &(nuevo_pkm->velocidad), &(nuevo_pkm->ataque), &(nuevo_pkm->defensa));
	if(leidos != cant_items_esperados){
		free(nuevo_pkm);
		return false;
	}
	return agregar_nuevo_pokemon(lista_tope(un_gimnasio->entrenadores), nuevo_pkm);
}



ginasio_t* leer_archivo(FILE* archivo_gimnasio){

	gimnasio_t* un_gimnasio = calloc(1, sizeof(gimnasio_t));
	if(!un_gimnasio)
		return NULL	;

	bool todo_ok = true;


	char tipo_linea = leer_primera_letra_de_linea(archivo_gimnasio);
	todo_ok = leer_linea_gimasio(archivo_gimnasio, un_gimnasio, CANT_ITEMS_GIMNASIO);  //la primera linea siempre debe ser la del gimnasio
	
	while(todo_ok){
		char tipo_linea = leer_primera_letra_de_linea(archivo_gimnasio);
		if(tipo_linea == ENTRENADOR || tipo_linea == LIDER)
			todo_ok = leer_linea_entrandor(archivo_gimnasio, FORMATO_LECTURA_ENTRENADOR, CANT_ITEMS_ENTRENADOR);
		if(tipo_linea == POKEMON)
			todo_ok = leer_linea_pokemon(archivo_gimnasio, FORMATO_LECTURA_POKEMON, CANT_ITEMS_POKEMON);
		else
			todo_ok = false;
	}
	return un_gimnasio;
}


void liberar_gimnasio(gimnasio_t* gimnasio){
	if(!gimnasio)
		return;
	if(gimnasio->entrenadores){
		while(!lista_vacia(gimnasio->entrenadores)){
			entrenador_t* un_entrenador = lista_tope(gimnasio->entrenadores);
			if(un_entrenador->equipo){
				while(!lista_vacia(un_entrenador->equipo)){
					free(lista_primero(un_entrenador->equipo));
					lista_desencolar(un_entrenador->equipo)
				}
				lista_destruir(un_entrenador->equipo);
			}
			free(un_entrenador);
			lista_desapilar(gimnasio->entrenadores);
		}
		lista_destruir(gimnasio->entrenadores);
	}
	free(gimnasio;)
}

int cargar_gimnasio(hepa_t* heap, char* direccion_gimasio){
	if(!heap ||!direccion_gimasio)
		return ERROR;

	FILE* archivo_gimnasio = fopen(direccion_gimasio, "r");
	if(!archivo_gimnasio){
		printf("Error al abrir el archivo de gimnasio seleccionado\n");
		return ERROR;
	}

	gimnasio_t* nuevo_gimnasio = leer_archivo(archivo_gimnasio);

	if(!nuevo_gimasio)
		return ERROR;

	if(heap_insertar(heap, nuevo_gimasio)==ERROR){
		liberar_gimnasio(nuevo_gimnasio);
		return ERROR;
	}
	return OK;
}