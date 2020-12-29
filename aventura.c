
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
#define FORMATO_LECTURA_POKEMON "%[^;];%i;%i;%i\n"
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



ginasio_t* leer_archivo(FILE* archivo_gimnasio){

	gimnasio_t* un_gimnasio = calloc(1, sizeof(gimnasio_t));
	if(!un_gimnasio)
		return NULL	;

	bool todo_ok = true;


	char tipo_linea = leer_primera_letra_de_linea(archivo_gimnasio);
	todo_ok = leer_linea_gimasio(archivo_gimnasio, un_gimnasio, CANT_ITEMS_GIMNASIO);  //la primera linea siempre debe ser la del gimnasio
	
	while(todo_ok){
		char tipo_linea = leer_primera_letra_de_linea(archivo_gimnasio);
		if(tipo_linea == ENTRENADOR)
			todo_ok = leer_linea_entrandor(archivo_gimnasio, FORMATO_LECTURA_LIDER);
		if(tipo_linea == ENTRENADOR)
			todo_ok = leer_linea(archivo_gimnasio, FORMATO_LECTURA_ENTRENADOR);
	}
		
}




int cargar_gimnasio(hepa_t* heap, char* direccion_gimasio){
	if(!heap ||!direccion_gimasio)
		return ERROR;

	FILE* archivo_gimnasio = fopen(direccion_gimasio, "r");
	if(!archivo_gimnasio){
		printf("Error al abrir el archivo de gimnasio seleccionado\n");
		return ERROR;
	}

	leer_archivo()
		leer_primera_letra_de_linea
		if(letra == 'G')
		if(letra == 'L')
		if(letra == 'P')
		if(letra == 'E')

	if(!nuevo_gimasio)
		return ERROR;
	int leidos = fscanf(archivo_GIMNASIO, FORMATO_LECTURA_GIMNASIO, pokemon_leido.especie, &(pokemon_leido.velocidad), &(pokemon_leido.peso), pokemon_leido.color);
}