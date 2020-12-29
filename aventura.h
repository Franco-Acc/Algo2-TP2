#ifndef __AVENTURA_H__
#define __AVENTURA_H__

#define MAX_DIRECCION 100
#define MAX_NOMBRE 100

typedef int (*funcion_batalla)(void*, void *)


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


int cargar_gimnasio(heap_t* heap, char direccion_gimasio[MAX_DIRECCION]);






#endif /* __AVENTURA_H__ */