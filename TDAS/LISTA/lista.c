#include "lista.h"
#include <stdlib.h>


//Pre:
//Post: Devuelve true si la lista es valida y false si no lo es.
bool es_lista_valida(lista_t* lista){
	if(!lista)
		return false;

	if(((lista->nodo_fin)==NULL) && ((lista->nodo_inicio)!=NULL))
		return false;

	if(((lista->nodo_fin)!=NULL) && ((lista->nodo_inicio)==NULL))
		return false;

	if(((lista->nodo_fin)==NULL) && ((lista->nodo_inicio)==NULL) && ((lista->cantidad)>0))
		return false;

	if((((lista->nodo_fin)!=NULL) || ((lista->nodo_inicio)!=NULL)) && ((lista->cantidad)==0))
		return false;

	return true;
}


lista_iterador_t* lista_iterador_crear(lista_t* lista){
	
	if(!es_lista_valida(lista))
		return NULL;
	
	lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
	if(!iterador)
		return NULL;

	iterador->lista = lista;

	if(lista_vacia(lista))
		iterador->corriente = NULL;
	else
		iterador->corriente = lista->nodo_inicio;

	return iterador;
}


bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if(!iterador)
		return false;

	if(iterador->lista == NULL)
		return false;

	if(iterador->corriente == NULL)
		return false;

	return true;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){
	if(!iterador)
		return false;

	if(iterador->lista == NULL)
		return false;
	
	if(iterador->corriente == NULL)
		return false;

	nodo_t* nodo_aux;
	nodo_aux = iterador->corriente->siguiente;
	iterador->corriente = nodo_aux;

	if((iterador->corriente) == NULL)
		return false;

	return true;
}


void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
	if(!iterador)
		return NULL;
	if((iterador->lista)==NULL)
		return NULL;
	if((iterador->corriente)==NULL)
		return NULL;
	return(iterador->corriente->elemento);
}


void lista_iterador_destruir(lista_iterador_t* iterador){
	free(iterador);
}


lista_t* lista_crear(){
	lista_t* lista = calloc(sizeof(lista_t), 1);
    if(!lista)
    	return NULL;

    return lista;
}


void lista_destruir(lista_t* lista){
	if(!es_lista_valida(lista))
		return;

	if(!(lista->nodo_inicio)){
		free(lista);
		return;
	}

	nodo_t* ptr_aux = NULL;
	nodo_t* nodo_actual = lista->nodo_inicio;
	while(nodo_actual != NULL){
		ptr_aux = nodo_actual->siguiente;
		free(nodo_actual);
		nodo_actual = ptr_aux;
	}
	free(lista);
}


void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	if(!es_lista_valida(lista))
		return NULL;
	if(lista_vacia(lista))
		return NULL;
	if(posicion>(lista_elementos(lista)-1))
		return NULL;

	nodo_t* nodo_actual = lista->nodo_inicio;

	for(int i=0; i<posicion ;i++)
		nodo_actual = nodo_actual->siguiente;

	return(nodo_actual->elemento);
}


void* lista_ultimo(lista_t* lista){
	if(!es_lista_valida(lista))
		return NULL;
	if(lista_vacia(lista))
		return NULL;
	return(lista->nodo_fin->elemento);
}


bool lista_vacia(lista_t* lista){
	if(!lista)
		return true;
	if((lista->cantidad==0) && (lista->nodo_inicio==NULL) && (lista->nodo_fin==NULL))
		return true;
	return false;
}


size_t lista_elementos(lista_t* lista){
	if(!es_lista_valida(lista))
		return 0;

	return(lista->cantidad);
}


int lista_insertar(lista_t* lista, void* elemento){
	if(!es_lista_valida(lista))
		return -1;

	nodo_t*	nuevo_nodo = calloc(sizeof(nodo_t), 1);
	if(!nuevo_nodo)
		return -1;
	
	nuevo_nodo->elemento = elemento;

	if(((lista->nodo_fin)==NULL) && ((lista->nodo_inicio)==NULL)){
		lista->nodo_fin = nuevo_nodo;
		lista->nodo_inicio = nuevo_nodo;
		(lista->cantidad)++;
		return 0;
	}

	lista->nodo_fin->siguiente = nuevo_nodo;
	lista->nodo_fin = nuevo_nodo;
	(lista->cantidad)++;

	return 0;
}


int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	if(!es_lista_valida(lista))
		return -1;

	if((lista_elementos(lista)==0) || lista_elementos(lista)<=posicion)
		return lista_insertar(lista, elemento);

	nodo_t* nuevo_nodo = malloc(sizeof(nodo_t));
	if(!nuevo_nodo)
		return -1;
	
	nodo_t* nodo_aux = lista->nodo_inicio;
	nuevo_nodo->elemento = elemento;

	if(posicion==0){
		nuevo_nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevo_nodo;
		(lista->cantidad)++; 
		return 0;
	}

	for(int i=1; i<posicion ;i++)
		nodo_aux = nodo_aux->siguiente;

	nuevo_nodo->siguiente = nodo_aux->siguiente;
	nodo_aux->siguiente = nuevo_nodo;
	(lista->cantidad)++; 
	return 0;
}


int lista_borrar(lista_t* lista){
	if(!es_lista_valida(lista))
		return -1;
	if(lista_elementos(lista)==0)
		return -1;

	nodo_t* nodo_aux = lista->nodo_inicio;

	if(nodo_aux->siguiente == NULL){
		free(nodo_aux);
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
		(lista->cantidad)--;
		return 0;
	}

	while(nodo_aux->siguiente != lista->nodo_fin)
		nodo_aux = nodo_aux->siguiente;

	free(lista->nodo_fin);
	nodo_aux->siguiente = NULL;
	lista->nodo_fin = nodo_aux;
	(lista->cantidad)--;
	return 0;
}


int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	if(!es_lista_valida(lista))
		return -1;
	if(lista_elementos(lista)==0)
		return -1;
	if(posicion>=(lista_elementos(lista)-1))
		return lista_borrar(lista);

	nodo_t* nodo_actual = lista->nodo_inicio;
	nodo_t* nodo_aux;

	if(posicion==0){
		nodo_aux = nodo_actual->siguiente;
		free(nodo_actual);
		lista->nodo_inicio = nodo_aux;
		(lista->cantidad)--;
		return 0;
	}

	for(int i=0; i<(posicion-1) ;i++)
		nodo_actual = nodo_actual->siguiente;

	nodo_aux = nodo_actual->siguiente->siguiente;
	free(nodo_actual->siguiente);
	nodo_actual->siguiente = nodo_aux;
	(lista->cantidad)--;
	return 0;
}


int lista_apilar(lista_t* lista, void* elemento){
	return(lista_insertar(lista, elemento));
}


int lista_desapilar(lista_t* lista){
	return(lista_borrar(lista));
}


void* lista_tope(lista_t* lista){
	return(lista_ultimo(lista));
}


int lista_encolar(lista_t* lista, void* elemento){
	return(lista_insertar(lista, elemento));
}


int lista_desencolar(lista_t* lista){
	return(lista_borrar_de_posicion(lista, 0));
}


void* lista_primero(lista_t* lista){
	return(lista_elemento_en_posicion(lista, 0));
}


size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void* contexto){
	if(!es_lista_valida(lista))
		return 0;
	if(lista_vacia(lista))
		return 0;
	 if(!funcion)
	 	return 0;
	
	nodo_t* nodo_actual = lista->nodo_inicio;
	size_t contador = 0;
	bool puedo_seguir = true;
	while(puedo_seguir){
		if(!funcion(nodo_actual->elemento, contexto))
			puedo_seguir = false;
		contador++;
		nodo_actual = nodo_actual->siguiente;
		if(nodo_actual==NULL)
			puedo_seguir = false;
	}
	return(contador);
}