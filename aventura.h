#ifndef __AVENTURA_H__
#define __AVENTURA_H__

#define MAX_DIRECCION 100

typedef int (*funcion_batalla)(void*, void *)


typedef struct gimnasio{
	char nombre[];
	size_t dificultad;
	funcion_batalla reglas_de_batalla;
	lista_t* entrenadores;
} gimnasio_t;

typedef struct entrenador{
	char nombre[];
	pokemon_t equipo[MAX_EQUIPO];
	lista_t* capturados;
} entrenador_t;


int cargar_gimnasio(heap_t* heap, char direccion_gimasio[MAX_DIRECCION]);






#endif /* __AVENTURA_H__ */