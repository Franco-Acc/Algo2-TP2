#include "abb.h"
#include <stdio.h>



//Pre:
//Post: Devuelve true solo en caso de que se trate de un arbol con comparador. 
bool es_arbol_valido(abb_t* arbol){
	if(!arbol)
		return false;
	if(!(arbol->comparador))
		return false;
	return true;
}


/*
 * Crea el arbol y reserva la memoria necesaria de la estructura.
 * Comparador se utiliza para comparar dos elementos.
 * Destructor es invocado sobre cada elemento que sale del arbol,
 * puede ser NULL indicando que no se debe utilizar un destructor.
 *
 * Devuelve un puntero al arbol creado o NULL en caso de error.
 */
abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
	if(!comparador)
		return NULL;
	
	abb_t* nuevo_arbol = calloc(1, sizeof(abb_t));
	if(!nuevo_arbol)
		return NULL;

	nuevo_arbol->comparador = comparador;
	nuevo_arbol->destructor = destructor;
	return nuevo_arbol;
}


//Pre: El comparador recibido debe ser valido.
//Post: Queda insertado el nuevo elemento y reacomodados los punteros o queda como esta en caso de error en la insercion.
nodo_abb_t* insertar_nodo(nodo_abb_t* nodo_actual, void* elemento, abb_comparador comparador){
	
	if(!nodo_actual){
		nodo_abb_t* nuevo_nodo = calloc(1, sizeof(nodo_abb_t));
		if(!nuevo_nodo)
			return NULL;
		nuevo_nodo->elemento = elemento;
		return nuevo_nodo;
	}

	if(comparador(elemento, nodo_actual->elemento)>0)
		nodo_actual->derecha = insertar_nodo(nodo_actual->derecha, elemento, comparador);
	else
		nodo_actual->izquierda = insertar_nodo(nodo_actual->izquierda, elemento, comparador);

	return nodo_actual;
}


/*
 * Inserta un elemento en el arbol.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 * El arbol admite elementos con valores repetidos.
 */
int arbol_insertar(abb_t* arbol, void* elemento){
	if(!es_arbol_valido(arbol))
		return -1;
	
	arbol->nodo_raiz = insertar_nodo(arbol->nodo_raiz, elemento, arbol->comparador);
	return 0;
}




/*
 * Devuelve el elemento almacenado como raiz o NULL si el árbol está
 * vacío o no existe.
 */
void* arbol_raiz(abb_t* arbol){
	if(!es_arbol_valido(arbol))
		return NULL;
	if(arbol_vacio(arbol))
		return NULL;
	return arbol->nodo_raiz->elemento;
}


/*
 * Determina si el árbol está vacío.
 * Devuelve true si está vacío o el arbol es NULL, false si el árbol tiene elementos.
 */
bool arbol_vacio(abb_t* arbol){
	if(!es_arbol_valido(arbol))
		return true;
	if(!(arbol->nodo_raiz))
		return true;
	return false;
}


//Pre: El comparador debe ser valido.
//Post: Devuelve el elemento en el arbol que coincide en clave con el pasado. Si no lo encuentra devuelve NULL.
void* abb_buscar_recu(nodo_abb_t* nodo_actual, void* elemento_buscado, abb_comparador comparador){
	if(!nodo_actual)
		return NULL;
	if(comparador(elemento_buscado, nodo_actual->elemento)<0)
		return abb_buscar_recu(nodo_actual->izquierda, elemento_buscado, comparador);
	if(comparador(elemento_buscado, nodo_actual->elemento)>0)
		return abb_buscar_recu(nodo_actual->derecha, elemento_buscado, comparador);
	return nodo_actual->elemento;
}

/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación).
 *
 * Devuelve el elemento encontrado o NULL si no lo encuentra.
 */
void* arbol_buscar(abb_t* arbol, void* elemento){
	if(!es_arbol_valido(arbol))
		return NULL;
	if(arbol_vacio(arbol))
		return NULL;
	return abb_buscar_recu(arbol->nodo_raiz, elemento, arbol->comparador);
}


//Pre: El nodo actual recibido por primera vez debe ser el que se encuentra a la izquierda del que se quiere buscar el predecesor in order (no debe ser NULL).
//Post: Se borra el nodo que sea predecesor in orden y el elemento que contenia ahora lo contiene el nodo con el elemento que se queria borrar (el nodo con los 2 hijos original). 
nodo_abb_t* reemplazar_por_predecesor_in_orden(nodo_abb_t* nodo_actual, void** elemento_a_reemplazar){
	if(nodo_actual->derecha == NULL){
		(*elemento_a_reemplazar) = nodo_actual->elemento;		
		if(nodo_actual->izquierda == NULL){
			free(nodo_actual);
			return NULL;
		}

		nodo_abb_t* nodo_aux = nodo_actual->izquierda;
		free(nodo_actual);
		return nodo_aux;
	}
	nodo_actual->derecha = reemplazar_por_predecesor_in_orden(nodo_actual->derecha, elemento_a_reemplazar);
	return nodo_actual;
}


//Pre: El comparador debe ser valido y el booleano puede_borrar false
//Post: Si el elemento a borrar estaba en el arbol el mismo fue eliminado y se indica el exito de la operacion modificando el booleano a true, en caso contrario el booleano queda en false.
nodo_abb_t* abb_borrar_recu(nodo_abb_t* nodo_actual, void* elemento_a_borrar, abb_comparador comparador, abb_liberar_elemento destructor, bool* pude_borrar){
	
	if(!nodo_actual)
		return NULL;

	int comparacion = comparador(elemento_a_borrar, nodo_actual->elemento);
	
	if(comparacion==0){
		if(destructor)
			destructor(nodo_actual->elemento);
		
		(*pude_borrar) = true;

		if((!nodo_actual->izquierda) && (!nodo_actual->derecha)){
			free(nodo_actual);
			return NULL;
		}

		if((nodo_actual->izquierda) && (nodo_actual->derecha)){
			nodo_actual->izquierda = reemplazar_por_predecesor_in_orden(nodo_actual->izquierda, &(nodo_actual->elemento));
			return nodo_actual;
		}

		if(nodo_actual->izquierda){
			nodo_abb_t* nodo_aux = nodo_actual->izquierda;
			free(nodo_actual);
			return nodo_aux;
		}

		nodo_abb_t* nodo_aux = nodo_actual->derecha;
		free(nodo_actual);
		return nodo_aux;
	}

	if(comparacion<0)
		nodo_actual->izquierda = abb_borrar_recu(nodo_actual->izquierda, elemento_a_borrar, comparador, destructor, pude_borrar);
	
	if(comparacion>0)
		nodo_actual->derecha = abb_borrar_recu(nodo_actual->derecha, elemento_a_borrar, comparador, destructor, pude_borrar);

	return nodo_actual;
}




/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación) y si lo encuentra lo quita del arbol.
 * Adicionalmente, si encuentra el elemento, invoca el destructor con
 * dicho elemento.
 * Devuelve 0 si pudo eliminar el elemento o -1 en caso contrario.
 */
int arbol_borrar(abb_t* arbol, void* elemento){
	if(!es_arbol_valido(arbol))
		return -1;

	if(arbol_vacio(arbol))
		return -1;
	
	bool pude_borrar = false;
	arbol->nodo_raiz = abb_borrar_recu(arbol->nodo_raiz, elemento, arbol->comparador, arbol->destructor, &pude_borrar);
	
	if(!pude_borrar)
		return -1;
	return 0;
}




/*
 * Destruye el arbol liberando la memoria reservada por el mismo.
 * Adicionalmente invoca el destructor con cada elemento presente en
 * el arbol.
 */
void arbol_destruir(abb_t* arbol){
	if(!es_arbol_valido(arbol))
		return;

	bool fallo_borrado = false;

	while(!arbol_vacio(arbol) && !fallo_borrado){
		if(arbol_borrar(arbol, arbol->nodo_raiz->elemento)==-1)
			fallo_borrado = true;
	}

	if(fallo_borrado)
		return;

	free(arbol);
	
}




//Pre: El array debe ser valido.
//Post: Llena el array con los elementos del arbol inorden. Una vez que se se llena el array ya no sigue insertando y finaliza su recorrido. 
void inorden_recu(nodo_abb_t* nodo_actual, void** array, size_t* elemento_actual, size_t tamanio_array){
	if(!nodo_actual)
		return;
	
	if(nodo_actual->izquierda)
		inorden_recu(nodo_actual->izquierda, array, elemento_actual, tamanio_array);

	if((*elemento_actual) >= tamanio_array)
		return;
	array[*elemento_actual] = nodo_actual->elemento;
	(*elemento_actual)++;

	if(nodo_actual->derecha)
		inorden_recu(nodo_actual->derecha, array, elemento_actual, tamanio_array);
}


/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia inorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(!es_arbol_valido(arbol) || !array)
		return 0;
	if(arbol_vacio(arbol) || tamanio_array==0)
		return 0;
	size_t elementos_colocados = 0;
	inorden_recu(arbol->nodo_raiz, array, &elementos_colocados, tamanio_array);
	return elementos_colocados;
}



//Pre: El array debe ser valido.
//Post: Llena el array con los elementos del arbol inpreorden. Una vez que se se llena el array ya no sigue insertando y finaliza su recorrido.
void preorden_recu(nodo_abb_t* nodo_actual, void** array, size_t* elemento_actual, size_t tamanio_array){
	if(!nodo_actual)
		return;
	if((*elemento_actual) >= tamanio_array)
		return;

	array[*elemento_actual] = nodo_actual->elemento;
	(*elemento_actual)++;
	
	if(nodo_actual->izquierda)
		preorden_recu(nodo_actual->izquierda, array, elemento_actual, tamanio_array);

	if(nodo_actual->derecha)
		preorden_recu(nodo_actual->derecha, array, elemento_actual, tamanio_array);
}


/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia inorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(!es_arbol_valido(arbol) || !array)
		return 0;
	if(arbol_vacio(arbol) || tamanio_array==0)
		return 0;
	size_t elementos_colocados = 0;
	preorden_recu(arbol->nodo_raiz, array, &elementos_colocados, tamanio_array);
	return elementos_colocados;
}



//Pre: El array debe ser valido.
//Post: Llena el array con los elementos del arbol postorden. Una vez que se se llena el array ya no sigue insertando y finaliza su recorrido. 
void postorden_recu(nodo_abb_t* nodo_actual, void** array, size_t* elemento_actual, size_t tamanio_array){
	if(!nodo_actual)
		return;
		
	if(nodo_actual->izquierda)
		postorden_recu(nodo_actual->izquierda, array, elemento_actual, tamanio_array);
	if(nodo_actual->derecha)
		postorden_recu(nodo_actual->derecha, array, elemento_actual, tamanio_array);

	if((*elemento_actual) >= tamanio_array)
		return;

	array[*elemento_actual] = nodo_actual->elemento;
	(*elemento_actual)++;
}


/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia inorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(!es_arbol_valido(arbol) || !array)
		return 0;
	if(arbol_vacio(arbol) || tamanio_array==0)
		return 0;
	size_t elementos_colocados = 0;
	postorden_recu(arbol->nodo_raiz, array, &elementos_colocados, tamanio_array);
	return elementos_colocados;
}





//Pre:La funcion pasada debe ser valida.
//Post: Itera el arbol en inorden, aplicando la funcion en cada elemento hasta que el arbol no tenga mas elementos o la funcion provista devuelva true.
void iterar_inorden(nodo_abb_t* nodo_actual, bool (*funcion)(void*, void*), void* extra, size_t* elementos_iterados, bool* puedo_iterar){
	if(!nodo_actual)
		return;
	if(!(*puedo_iterar))
		return;

	if(nodo_actual->izquierda)
		iterar_inorden(nodo_actual->izquierda, funcion, extra, elementos_iterados, puedo_iterar);

	if(!(*puedo_iterar))
		return;

	if(funcion(nodo_actual->elemento, extra)){
		(*puedo_iterar) = false;
		(*elementos_iterados)++;
		return;
	}
	(*elementos_iterados)++;

	if(nodo_actual->derecha)
		iterar_inorden(nodo_actual->derecha, funcion, extra, elementos_iterados, puedo_iterar);
}

//Pre:La funcion pasada debe ser valida.
//Post: Itera el arbol en preorden, aplicando la funcion en cada elemento hasta que el arbol no tenga mas elementos o la funcion provista devuelva true.
void iterar_preorden(nodo_abb_t* nodo_actual, bool (*funcion)(void*, void*), void* extra, size_t* elementos_iterados, bool* puedo_iterar){
	if(!nodo_actual)
		return;
	if(!(*puedo_iterar))
		return;

	if(funcion(nodo_actual->elemento, extra))
		(*puedo_iterar) = false;
	
	(*elementos_iterados)++;

	if(nodo_actual->izquierda)
		iterar_preorden(nodo_actual->izquierda, funcion, extra, elementos_iterados, puedo_iterar);

	if(nodo_actual->derecha)
		iterar_preorden(nodo_actual->derecha, funcion, extra, elementos_iterados, puedo_iterar);
}


//Pre:La funcion pasada debe ser valida.
//Post: Itera el arbol en postorden, aplicando la funcion en cada elemento hasta que el arbol no tenga mas elementos o la funcion provista devuelva true. 
void iterar_postorden(nodo_abb_t* nodo_actual, bool (*funcion)(void*, void*), void* extra, size_t* elementos_iterados, bool* puedo_iterar){
	
	if(!nodo_actual)
		return;
	if(!(*puedo_iterar))
		return;

	if(nodo_actual->izquierda)
		iterar_postorden(nodo_actual->izquierda, funcion, extra, elementos_iterados, puedo_iterar);

	if(nodo_actual->derecha)
		iterar_postorden(nodo_actual->derecha, funcion, extra, elementos_iterados, puedo_iterar);

	if(!(*puedo_iterar))
		return;

	if(funcion(nodo_actual->elemento, extra))
		(*puedo_iterar) = false;
	
	(*elementos_iterados)++;
}



/*
 * Iterador interno. Recorre el arbol e invoca la funcion con cada
 * elemento del mismo. El puntero 'extra' se pasa como segundo
 * parámetro a la función. Si la función devuelve true, se finaliza el
 * recorrido aun si quedan elementos por recorrer. Si devuelve false
 * se sigue recorriendo mientras queden elementos.
 * El recorrido se realiza de acuerdo al recorrido solicitado.  Los
 * recorridos válidos son: ABB_RECORRER_INORDEN, ABB_RECORRER_PREORDEN
 * y ABB_RECORRER_POSTORDEN.
 * Devuelve la cantidad de elementos que fueron recorridos.
*/
size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){

	if(!es_arbol_valido(arbol) || !funcion)
		return 0;
	if(arbol_vacio(arbol))
		return 0;

	size_t elementos_iterados = 0;
	bool puedo_iterar = true;

	if(recorrido==ABB_RECORRER_INORDEN)
		iterar_inorden(arbol->nodo_raiz, funcion, extra, &elementos_iterados, &puedo_iterar);
	
	if(recorrido==ABB_RECORRER_PREORDEN)
		iterar_preorden(arbol->nodo_raiz, funcion, extra, &elementos_iterados, &puedo_iterar);
	
	if(recorrido==ABB_RECORRER_POSTORDEN)
		iterar_postorden(arbol->nodo_raiz, funcion, extra, &elementos_iterados, &puedo_iterar);

	return elementos_iterados;
}









