#include "heap.h"
#include <stdio.h>

#define ERROR -1;
#define OK	   0;

void swap(void* vector[], size_t pos_1, size_t pos_2){
	void* puntero_aux = vector[pos_1];
	vector[pos_1] = vector[pos_2];
	vector[pos_2] = puntero_aux;
}

size_t posicion_padre(size_t n){
	return((n-1)/2);
}

size_t posicion_hijo_izquierdo(size_t n){
	return((2*n)+1);
}

size_t posicion_hijo_derecho(size_t n){
	return((2*n)+2);
}

void sift_up(heap_t* heap, size_t n){
	if(n==0)
		return;
	size_t pos_padre = posicion_padre(n);
	if(heap->comparador(heap->vector[n], heap->vector[pos_padre])<0){
		swap(heap->vector, n, pos_padre);
		sift_up(heap, pos_padre);
	}
}

void sift_down(heap_t* heap, size_t n){
	if(n >= heap->tope)
		return;
	
	size_t pos_hijo_izq = posicion_hijo_izquierdo(n);
	size_t pos_hijo_der = posicion_hijo_derecho(n);
	size_t pos_hijo_menor;

	if(pos_hijo_izq >= heap->tope)
		return;
	
	pos_hijo_menor = pos_hijo_izq;

	if(pos_hijo_der < heap->tope)
		if(heap->comparador(heap->vector[pos_hijo_izq], heap->vector[pos_hijo_der])>0)
			pos_hijo_menor = pos_hijo_der;


	if(heap->comparador(heap->vector[n], heap->vector[pos_hijo_menor])>0){
		swap(heap->vector, n, pos_hijo_menor);
		sift_down(heap, pos_hijo_menor);
	}
}




heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor){
	if(!comparador)
		return NULL;
	heap_t* un_heap = calloc(1, sizeof(heap_t));
	
	if(!un_heap)
		return NULL;

	un_heap->comparador = comparador;
	un_heap->destructor = destructor;

	return un_heap;
}


int heap_insertar(heap_t* heap, void* elemento){
	void** vector_aux = realloc(heap->vector, sizeof(void*) * heap->tope+1);
	if(!vector_aux)
		return ERROR;
	
	heap->vector = vector_aux;
	heap->vector[heap->tope] = elemento;
	heap->tope++;
	
	sift_up(heap, heap->tope-1);
		
	return OK;
}


void* heap_extraer_minimal(heap_t* heap){
	
	if(!heap)
		return NULL;
	
	if(!heap->vector || heap->tope == 0)
		return NULL;

	void* minimal = heap->vector[0];
	swap(heap->vector, 0, heap->tope-1);

	void** vector_aux = realloc(heap->vector, sizeof(void*) * heap->tope-1);
	if(!vector_aux){
		swap(heap->vector, 0, heap->tope-1);
		return NULL;
	}
	heap->vector = vector_aux;
	heap->tope--;

	if(heap->tope > 0)
		sift_down(heap, 0);
	
	return minimal;
}


void heap_destruir(heap_t* heap){
	if(!heap)
		return;

	if(heap->destructor)
		for(int i=0; i < heap->tope ;i++)
			heap->destructor(heap->vector[i]);
		
	free(heap->vector);
	free(heap);
}

bool heap_vacio(heap_t* heap){
	if(!heap)
		return false;
	if((heap->tope) > 0)
		return false;
	return true;
}








