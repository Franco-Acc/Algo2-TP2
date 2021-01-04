
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

#define VICTORIA 1
#define DERROTA -1

#define FORMATO_LECTURA_PRIMERA_LETRA "%c;"

#define FORMATO_LECTURA_GIMNASIO "%[^;];%u;%u\n"
#define CANT_ITEMS_GIMNASIO 3

#define FORMATO_LECTURA_ENTRENADOR "%[^\n]\n"
#define CANT_ITEMS_ENTRENADOR 1

#define FORMATO_LECTURA_POKEMON "%[^;];%[^;];%u;%u;%u\n"
#define CANT_ITEMS_POKEMON 5

#define FORMATO_LECTURA_PERSONAJE "%[^\n]\n"
#define CANT_ITEMS_PERSONAJE 1



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

void cargar_gimnasio(heap_t* heap, char* direccion_gimasio){
	if(!heap ||!direccion_gimasio)
		return;

	FILE* archivo_gimnasio = fopen(direccion_gimasio, "r");
	if(!archivo_gimnasio){
		printf("Error al abrir el archivo de gimnasio seleccionado\n");
		return;
	}

	gimnasio_t* nuevo_gimnasio = leer_archivo(archivo_gimnasio);

	if(!nuevo_gimnasio){
		printf("Error al reservar memoria para el gimnasio\n");
		fclose(archivo_gimnasio);
		return;
	}

	if(heap_insertar(heap, nuevo_gimnasio)=){
		liberar_gimnasio(nuevo_gimnasio);
		fclose(archivo_gimnasio);
		printf("Error al insertar el gimnasio en el HEAP\n");
		return;
	}
	fclose(archivo_gimnasio);
	return;
}


bool leer_linea_personaje(FILE* archivo_personaje, personaje_t* personaje, int cant_items_esperados){
	char nombre_personaje[MAX_NOMBRE];
	int leidos = fscanf(archivo_personaje, FORMATO_LECTURA_ENTRENADOR, nombre_personaje);
	if(leidos != cant_items_esperados)
		return false;
	strcpy(personaje->nombre, nombre_personaje);
	return true;
}


bool agregar_nuevo_pokemon_personaje(personaje_t* personaje, pokemon_t* pokemon){
	if(!personaje){
		free(pokemon);
		return false;
	}

	if(!personaje->equipo)
		personaje->equipo = lista_crear();

	if(!personaje->equipo){
		free(pokemon);
		return false;
	}


	if(!personaje->capturados)
		personaje->capturados = lista_crear();

	if(!personaje->capturados){
		free(pokemon);
		lista_destruir(personaje->equipo);
		return false;
	}

	if(lista_elementos(personaje->equipo)<MAX_EQUIPO){
		if(lista_encolar(personaje->equipo, pokemon)==ERROR){
			free(pokemon);
			return false;
		}
	}else{
		if(lista_encolar(personaje->capturados, pokemon)==ERROR){
			free(pokemon);
			return false;
		}
	}
	return true;
}


bool leer_linea_pokemon_personaje(FILE* archivo_personaje, personaje_t* personaje, int cant_items_esperados){
	pokemon_t* nuevo_pkm = calloc(1, sizeof(pokemon_t));
	int leidos = fscanf(archivo_personaje, FORMATO_LECTURA_POKEMON, nuevo_pkm->nombre, nuevo_pkm->tipo, &(nuevo_pkm->velocidad), &(nuevo_pkm->ataque), &(nuevo_pkm->defensa));
	if(leidos != cant_items_esperados){
		free(nuevo_pkm);
		return false;
	}
	return agregar_nuevo_pokemon_personaje(personaje, nuevo_pkm);
}


personaje_t* leer_archivo_personaje(FILE* archivo_personaje){

	personaje_t* personaje = calloc(1, sizeof(personaje_t));
	if(!personaje)
		return NULL;

	bool todo_ok = true;


	char tipo_linea = leer_primera_letra_de_linea(archivo_personaje);
	todo_ok = leer_linea_personaje(archivo_personaje, personaje, CANT_ITEMS_PERSONAJE);  //la primera linea siempre debe ser la del gimnasio
	
	while(todo_ok){
		tipo_linea = leer_primera_letra_de_linea(archivo_personaje);

		if(tipo_linea == POKEMON){
			todo_ok = leer_linea_pokemon_personaje(archivo_personaje, personaje, CANT_ITEMS_POKEMON);
		}else{
			todo_ok = false;
		}
	}
	return personaje;
}



personaje_t* cargar_personaje(char* direccion_personaje){
	if(!direccion_personaje)
		return NULL;

	FILE* archivo_personaje = fopen(direccion_personaje, "r");
	if(!archivo_personaje){
		printf("Error al abrir el archivo de personaje seleccionado\n");
		return NULL;
	}

	personaje_t* personaje = leer_archivo_personaje(archivo_personaje);

	fclose(archivo_personaje);
	return personaje;
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


void trasladar_primer_pokemon(lista_t* lista_original, lista_t* lista_nueva){
	lista_encolar(lista_nueva, lista_primero(lista_original));
	lista_desencolar(lista_original);
}


void restaurar_equipos(lista_t* lista_aux, lista_t* equipo){
	while(!lista_vacia(lista_aux))
		trasladar_primer_pokemon(lista_aux, equipo);
}



int duelo_pokemon(lista_t* equipo_jugador, lista_t* equipo_entrenador, funcion_batalla reglas_de_batalla){
	if(!equipo_jugador || !equipo_entrenador || !reglas_de_batalla)
		return ERROR;

	lista_t* lista_aux_jugador = lista_crear();
	lista_t* lista_aux_entrenador = lista_crear();
	int resultado = 0;

	while(!lista_vacia(equipo_jugador) && !lista_vacia(equipo_entrenador)){
		if(reglas_de_batalla(lista_primero(equipo_jugador), lista_primero(equipo_entrenador))==GANO_PRIMERO)
			trasladar_primer_pokemon(equipo_entrenador, lista_aux_entrenador);
		else
			trasladar_primer_pokemon(equipo_jugador, lista_aux_jugador);
	}

	if(lista_vacia(equipo_entrenador))
		resultado = VICTORIA;
	else
		resultado = DERROTA;

	restaurar_equipos(lista_aux_jugador, equipo_jugador);
	restaurar_equipos(lista_aux_entrenador, equipo_entrenador);
	lista_destruir(lista_aux_jugador);
	lista_destruir(lista_aux_entrenador);
	return resultado;
}


void trasladar_ultimo_entrenador(lista_t* pila_original, lista_t* pila_nueva){
	lista_apilar(pila_nueva, lista_tope(pila_original));
	lista_desapilar(pila_original);
}


void restaurar_gimnasio(lista_t* pila_aux, lista_t* entrenadores){
	while(!lista_vacia(pila_aux))
		trasladar_ultimo_entrenador(pila_aux, entrenadores);
}


int enfrentar_gimnasio(personaje_t* jugador, gimnasio_ẗ* gimnasio){
	if(!jugador || !gimnasio)
		return ERROR;

	lista_t* pila_aux_entrenadores = lista_crear();
	bool fue_derrotado = false;

	while(!lista_vacia(gimnasio->entrenadores) && !fue_derrotado){
		if(duelo_pokemon(jugador->equipo, lista_tope(gimnasio->entrenadores)->equipo)==VICTORIA)
			trasladar_ultimo_entrenador(gimnasio->entrenadores, pila_aux_entrenadores);
		else
			fue_derrotado = true;
	}

	restaurar_gimnasio(pila_aux_entrenadores, gimnasio->entrenadores);
	
	if(fue_derrotado)
		return DERROTA;s
	return VICTORIA;
}


void pedir_direccion(char direccion[MAX_DIRECCION]){
	printf("Ingrese la direccion del archivo: ");
	scanf("%[^\n]", direccion);
}


bool quiere_seguir_cargando(){
	char respuesta;
	printf("Quiere cargar otro gimnasio??\n Y/N : ");
	scanf(" %c", &respuesta);
	if(respuesta==SI)
		return true;
	if(respuesta==NO)
		return false;
	printf("Recurde solo ingresar uno de los carcateres indicados, en mayuscula\n");
	return quiere_seguir_cargando();
}


void cargar_gimnasios(heap_t* gimnasios){
	
	char direccion_gimasio[MAX_DIRECCION];

	printf("Para ingreasar ingresar un gimnasio indique la direccion del archivo, por ejemplo Gimnasios/Kanto/Misty.txt\n");
	printf("En caso de ocurrir algun error, este se indicará y no se cargará en gimnasio\n");
	pedir_direccion(direccion_gimasio);
	cargar_gimnasio(gimnasios, direccion_gimasio);

	while(quiere_seguir_cargando()){
		pedir_direccion(direccion_gimasio);
		cargar_gimnasio(gimnasios, direccion_gimasio);
	}
	return;
}



int cargar_estructuras(personaje_t* jugador, heap_t* gimnasios){
	
	heap_t* gimnasios = heap_crear(comparador_gimnasios, destructor_gimnasios);
	if(!gimnasios)
		return ERROR_FATAL;

	cargar_gimnasios(gimnasios);
	

	cargar_personaje("Personajes/Kanto/Ash.txt");
	
	return OK;
}



int main(){

	heap_t* gimnasios = NULL;
	personaje_t* jugador = NULL;
	if(cargar_estructuras(jugador, gimnasios)==ERROR_FATAL){
		printf("Error crítico en la creacion de estructuras, imposible continuar!!\n");
	}

	mostrar_gimnasios(gimnasios);
	return 0;
}


