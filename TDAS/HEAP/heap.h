#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdbool.h>
#include <stdlib.h>

/*
 * Comparador de elementos. Recibe dos elementos del heap y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
typedef int (*heap_comparador)(void*, void*);

/*
 * Destructor de elementos. Solo se utiliza al destruir el heao ya que se
 * entiende que el usuario ya no tiene interes en los elementos almacenados,
 * en caso contrario deberia usar heap_obtener_minimal.
 */
typedef void (*heap_liberar_elemento)(void*);


typedef struct heap{
  void** vector;
  size_t tope;
  heap_comparador comparador;
  heap_liberar_elemento destructor;
} heap_t;

/*
 * Crea el heap y reserva la memoria necesaria de la estructura.
 * El heap puede ser creado con destrucor NULL pero debe tener comparador obligatoriamente.
 * Devuelve un puntero al heap creado o NULL en caso de error.
 */
heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor);

/*
 * Inserta un elemento en el heap.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 * El heap admite elementos con valores repetidos.
 */
int heap_insertar(heap_t* heap, void* elemento);

/*
 * Devuelve true si el heap está vacio y false si no lo está o no existe.
 * El heap admite elementos con valores repetidos.
 */
bool heap_vacio(heap_t heap);

/*
 *Devuelve el elemento almacenado en la raiz o NULL si el heap esta vacio.
 *La nueva raiz luego de la extraccion sera el ultimo elemento del ultimo nivel completo.
 */
void* heap_extraer_minimal(heap_t* heap);

void heap_destruir(heap_t* heap);

#endif /* __HEAP_H__ */