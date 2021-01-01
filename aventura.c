
#include <stdio.h>
#include <string.h>

#include "batallas.h"
#include "aventura.h"
#include "lista.h"
#include "abb.h"
#include "heap.h"

#define GIMNASIO 'G'
#define LIDER 'L'
#define ENTRENADOR 'E'
#define POKEMON 'P'

#define FORMATO_LECTURA_PRIMERA_LETRA "%c;"

#define FORMATO_LECTURA_GIMNASIO "%[^;];%u;%u\n"
#define CANT_ITEMS_GIMNASIO 3

#define FORMATO_LECTURA_ENTRENADOR "%[^\n]\n"
#define CANT_ITEMS_ENTRENADOR 1

#define FORMATO_LECTURA_POKEMON "%[^;];%[^;];%u;%u;%u\n"
#define CANT_ITEMS_POKEMON 5


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


int comparador_gimnasios (void* gimnasio_1, void* gimnasio_2){
	if(((gimnasio_t*)gimnasio_1)->dificultad < ((gimnasio_t*)gimnasio_2)->dificultad)
		return -1;
	else
		return 1;
}


void liberar_pokemnon (pokemon_t* pokemon){
	free(pokemon);
}


void liberar_equipo(lista_t* equipo){
	while(!lista_vacia(equipo)){
		liberar_pokemnon(lista_primero(equipo));
		lista_desencolar(equipo);
	}
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
}

void destructor_gimnasios(void* gimnasio){
	liberar_entrenadores(((gimnasio_t*)gimnasio)->entrenadores);
	free(gimnasio);
}



char leer_primera_letra_de_linea(FILE* archivo_gimnasio){
	char letra;
	fscanf(archivo_gimnasio, FORMATO_LECTURA_PRIMERA_LETRA, &letra);
	return letra;
}


funcion_batalla determinar_funcion(size_t n){
	if(n==1)
		return funcion_batalla_1;
	if(n==2)
		return funcion_batalla_2;
	if(n==3)
		return funcion_batalla_3;
	if(n==4)
		return funcion_batalla_4;
	else
		return funcion_batalla_5;
}

bool leer_linea_gimnasio(FILE* archivo_gimnasio, gimnasio_t* un_gimnasio, int cant_items_esperados){
	size_t reglas;
	int leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_GIMNASIO, un_gimnasio->nombre, &(un_gimnasio->dificultad), &reglas);
	un_gimnasio->reglas_de_batalla = determinar_funcion(reglas);
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

	if(lista_apilar(gimnasio->entrenadores, nuevo_entrenador)==ERROR)
		return false;

	return true;
}


bool leer_linea_entrenador(FILE* archivo_gimnasio, gimnasio_t* un_gimnasio, int cant_items_esperados){
	char nombre_entrenador[MAX_NOMBRE];
	int leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_ENTRENADOR, nombre_entrenador);
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



bool leer_linea_pokemon(FILE* archivo_gimnasio, gimnasio_t* un_gimnasio, int cant_items_esperados){
	pokemon_t* nuevo_pkm = calloc(1, sizeof(pokemon_t));
	int leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_POKEMON, nuevo_pkm->nombre, nuevo_pkm->tipo, &(nuevo_pkm->velocidad), &(nuevo_pkm->ataque), &(nuevo_pkm->defensa));
	if(leidos != cant_items_esperados){
		free(nuevo_pkm);
		return false;
	}
	return agregar_nuevo_pokemon(lista_tope(un_gimnasio->entrenadores), nuevo_pkm);
}



gimnasio_t* leer_archivo(FILE* archivo_gimnasio){

	gimnasio_t* un_gimnasio = calloc(1, sizeof(gimnasio_t));
	if(!un_gimnasio)
		return NULL;

	bool todo_ok = true;


	char tipo_linea = leer_primera_letra_de_linea(archivo_gimnasio);
	todo_ok = leer_linea_gimnasio(archivo_gimnasio, un_gimnasio, CANT_ITEMS_GIMNASIO);  //la primera linea siempre debe ser la del gimnasio
	
	while(todo_ok){
		tipo_linea = leer_primera_letra_de_linea(archivo_gimnasio);

		if(tipo_linea == ENTRENADOR || tipo_linea == LIDER){
			todo_ok = leer_linea_entrenador(archivo_gimnasio, un_gimnasio, CANT_ITEMS_ENTRENADOR);
		}else if(tipo_linea == POKEMON){
			todo_ok = leer_linea_pokemon(archivo_gimnasio, un_gimnasio, CANT_ITEMS_POKEMON);
		}else{
			todo_ok = false;
		}
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
					lista_desencolar(un_entrenador->equipo);
				}
				lista_destruir(un_entrenador->equipo);
			}
			free(un_entrenador);
			lista_desapilar(gimnasio->entrenadores);
		}
		lista_destruir(gimnasio->entrenadores);
	}
	free(gimnasio);
}

int cargar_gimnasio(heap_t* heap, char* direccion_gimasio){
	if(!heap ||!direccion_gimasio)
		return ERROR;

	FILE* archivo_gimnasio = fopen(direccion_gimasio, "r");
	if(!archivo_gimnasio){
		printf("Error al abrir el archivo de gimnasio seleccionado\n");
		return ERROR;
	}

	gimnasio_t* nuevo_gimnasio = leer_archivo(archivo_gimnasio);

	if(!nuevo_gimnasio){
		fclose(archivo_gimnasio);
		return ERROR;
	}

	if(heap_insertar(heap, nuevo_gimnasio)==ERROR){
		liberar_gimnasio(nuevo_gimnasio);
		fclose(archivo_gimnasio);
		return ERROR;
	}
	fclose(archivo_gimnasio);
	return OK;
}



void imprimir_pokemon(pokemon_t* pokemon){
	printf("\t%s\n", pokemon->nombre);
	printf("Tipo: %s\n", pokemon->tipo);
	printf("V: %u\t", pokemon->velocidad);
	printf("A: %u\t", pokemon->ataque);
	printf("D: %u\n", pokemon->defensa);
}

void mostrar_equipo(lista_t* equipo){
	lista_iterador_t* iterador_equipo = lista_iterador_crear(equipo);
	while(lista_iterador_tiene_siguiente(iterador_equipo)){
		pokemon_t* pokemon_actual = lista_iterador_elemento_actual(iterador_equipo);
		imprimir_pokemon(pokemon_actual);
		lista_iterador_avanzar(iterador_equipo);
	}
}



void imprimir_entrenador(entrenador_t* entrenador){
	printf("%s\n", entrenador->nombre);
	mostrar_equipo(entrenador->equipo);

}



void imprimir_entrenadores(lista_t* entrenadores){
	lista_iterador_t* iterador_entrenadores = lista_iterador_crear(entrenadores);
	while(lista_iterador_tiene_siguiente(iterador_entrenadores)){
		entrenador_t* entrenador_actual = lista_iterador_elemento_actual(iterador_entrenadores);
		printf("\n");
		imprimir_entrenador(entrenador_actual);
		lista_iterador_avanzar(iterador_entrenadores);
	}
}


void imprimir_gimnasio(gimnasio_t* gimnasio){
	printf("%s\n", gimnasio->nombre);
	printf("Dificultad del Gimnasio: %u\n", gimnasio->dificultad);
	printf("Entrenadores totales: %u\n", lista_elementos(gimnasio->entrenadores));
	imprimir_entrenadores(gimnasio->entrenadores);
}


void mostrar_gimnasios(heap_t* gimnasios){
	if(!gimnasios)
		return;

	gimnasio_t* gimnasio = heap_extraer_minimal(gimnasios);

	while(gimnasio){
		imprimir_gimnasio(gimnasio);
		printf("\n\n\n");
		gimnasio = heap_extraer_minimal(gimnasios);
	}
	printf(" Ya no hay más gimnasios para mostrar\n");
}



int main(){
	heap_t* gimnasios = heap_crear(comparador_gimnasios, destructor_gimnasios);
	if(!gimnasios)
		return ERROR;

	if(cargar_gimnasio(gimnasios, "Gimnasios/Kanto/Misty.txt")==ERROR)
		return ERROR;
	if(cargar_gimnasio(gimnasios, "Gimnasios/Kanto/Brock.txt")==ERROR)
		return ERROR;

	mostrar_gimnasios(gimnasios);
	return 0;
}


