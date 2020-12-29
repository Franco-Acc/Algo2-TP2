
#include <stdio.h>
#include <string.h>

#include "batallas.h"
#include "TDAS/LISTA/lista.h"
#include "TDAS/ABB/abb.h"

#define ERRROR -1;
#define OK 0;


//	PRIMERO IMPLEMENTATE EL HEAP

abb_t* determinar_posicion_heap(size_t dificultad){

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

	int leidos = fscanf(archivo_GIMNASIO, FORMATO_LECTURA_GIMNASIO, pokemon_leido.especie, &(pokemon_leido.velocidad), &(pokemon_leido.peso), pokemon_leido.color);
}