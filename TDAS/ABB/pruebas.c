#include "abb.h"
#include "pa2mm.h"
#include <string.h>

#define INORDEN "inorden"
#define PREORDEN "preorden"
#define POSTORDEN "postorden"

#define MENOR -1
#define MAYOR 1
#define IGUALES 0

#define MAX_PALABRA 30
#define MAX_PALABRA 30
#define MAX_ELEMENTOS 10
#define MAX_ARRAY 5

#define CANT_ELEMENTOS_ARBOL 10
#define ABB_RECORRER_INVALIDO 70


//Pre: El array debe contener punteros a enteros.
//Post: Se imprimen por pantalla lo elementos del array pasado y se devuelve true.
bool mostrar_elementos_array(void* array_1[], size_t tope){
	for(size_t i=0; i<tope ;i++)
		printf("%i ", *(int*)array_1[i]);
	return true;
}

//Pre: El array debe contener punteros a enteros y el tope debe ser válido.
//Post: DEvuelve true si los elementos de ambos arreglos coinciden y false si alguno no lo hace.
bool son_elementos_esperados(int elementos_esperados[], void** array, int tope){
	bool coinciden_todos = true;
	for(int i=0; i<tope ;i++){
		if(elementos_esperados[i]!=(*(int*)array[i]))
			coinciden_todos = false;
	}
	return coinciden_todos;
}



//Pre: DEben ser punteros a enteros.
//Post: Compara dos enteros, si el primero es menor devuelve -1 y si es mas grande 1. Si son iguales devuelve 0.
int abb_comparar_enteros(void* primer_elemento, void* segundo_elemento){
	if((*(int*)primer_elemento) > (*(int*)segundo_elemento))
		return MAYOR;
	if((*(int*)primer_elemento) < (*(int*)segundo_elemento))
		return MENOR;
	return IGUALES;
}

//Pre:
//Post: No libera nada pues los elementos estan en el stack.
void abb_liberar_entero(void* elemento_a_destruir){
}


//Pre:
//Post: Se realizan las pruebas correspondientes a la creacion de un arbol.
void probar_creacion_arbol(){
    abb_t* un_arbol = NULL;

    pa2m_afirmar((un_arbol = arbol_crear(NULL, NULL)) == NULL, "No puedo crear un arbol sin comparador ni destructor");
    pa2m_afirmar((un_arbol = arbol_crear(NULL, abb_liberar_entero)) == NULL, "No puedo crear un arbol con destructor pero sin comparador");
    pa2m_afirmar((un_arbol = arbol_crear(abb_comparar_enteros, NULL)) != NULL, "Puedo crear un arbol con comparador pero sin destructor");
    free(un_arbol);
    pa2m_afirmar((un_arbol = arbol_crear(abb_comparar_enteros, abb_liberar_entero)) != NULL, "Puedo crear un arbol con comparador y destructor");

    pa2m_afirmar(un_arbol->nodo_raiz == NULL, "Un Arbol se crea con nodo raiz Nulo");
    pa2m_afirmar(un_arbol->comparador == abb_comparar_enteros, "Un Arbol se crea con el comparador dado");
 	free(un_arbol);
}

//Pre:
//Post: Se realizan las pruebas correspondientes a la insercion de elementos de un arbol.
void probar_insercion(){

	pa2m_afirmar((arbol_insertar(NULL, NULL)) == -1, "No puedo insertar algo en un arbol nulo o no valido");
    abb_t* un_arbol = arbol_crear(abb_comparar_enteros, abb_liberar_entero);
    int elementos[MAX_ELEMENTOS] = {5,2,8,1,3,0,4,9,6,7};
    void* array_1[MAX_ARRAY];

    pa2m_afirmar((arbol_insertar(un_arbol, elementos+0)) == 0, "Puedo insertar un elemento en un arbol vacio");
    pa2m_afirmar(un_arbol->nodo_raiz != NULL, "La raiz del arbol ya no es NULL");
    pa2m_afirmar(un_arbol->nodo_raiz->elemento == elementos+0, "El elemento insertado es el correcto");
    pa2m_afirmar((un_arbol->nodo_raiz->izquierda==NULL)&&(un_arbol->nodo_raiz->derecha==NULL), "La nueva raiz no tiene ningun hijo");

    pa2m_afirmar((arbol_insertar(un_arbol, elementos+1)) == 0, "Puedo insertar un elemento en un arbol no vacio");
    pa2m_afirmar(*(int*)(un_arbol->nodo_raiz->izquierda->elemento) == elementos[1], "El elemento incertado es el correcto");
    pa2m_afirmar((un_arbol->nodo_raiz->izquierda!=NULL)&&(un_arbol->nodo_raiz->derecha==NULL), "La raiz ya no tiene ambos hijos NULL");
    pa2m_afirmar((un_arbol->nodo_raiz->izquierda->izquierda==NULL)&&(un_arbol->nodo_raiz->izquierda->derecha==NULL), "El elemento incertado es una hoja");
    int elementos_esperados_1[] = {2,5};
    pa2m_afirmar(((arbol_recorrido_inorden(un_arbol, array_1, MAX_ARRAY)) == MAX_ARRAY-3) && son_elementos_esperados(elementos_esperados_1, array_1, MAX_ARRAY-3) && mostrar_elementos_array(array_1, MAX_ARRAY-3), "Elementos actuales en el arbol");

    pa2m_afirmar((arbol_insertar(un_arbol, elementos+0)) == 0, "Puedo insertar un elemento que ya se encuentra en el arbol (repetido)");
    int elementos_esperados_2[] = {2,5,5};
    pa2m_afirmar(((arbol_recorrido_inorden(un_arbol, array_1, MAX_ARRAY)) == MAX_ARRAY-2) && son_elementos_esperados(elementos_esperados_2, array_1, MAX_ARRAY-2) && mostrar_elementos_array(array_1, MAX_ARRAY-2), "Elementos actuales en el arbol");
	
	pa2m_afirmar((arbol_insertar(un_arbol, elementos+8)) == 0, "Inserto otro elemento para que la raiz tenga 2 hijos");
	int elementos_esperados_3[] = {2,5,5,6};
    pa2m_afirmar(((arbol_recorrido_inorden(un_arbol, array_1, MAX_ARRAY)) == MAX_ARRAY-1) && son_elementos_esperados(elementos_esperados_3, array_1, MAX_ARRAY-1) && mostrar_elementos_array(array_1, MAX_ARRAY-1), "Elementos actuales en el arbol");


    pa2m_afirmar((arbol_borrar(un_arbol, elementos+0)) == 0, "Puedo borrar el elemento repitido, en este caso se borra la raiz porque es el primero en encontrarse");
    int elementos_esperados_4[] = {2,5,6};
    pa2m_afirmar(((arbol_recorrido_inorden(un_arbol, array_1, MAX_ARRAY)) == MAX_ARRAY-2) && son_elementos_esperados(elementos_esperados_4, array_1, MAX_ARRAY-2) && mostrar_elementos_array(array_1, MAX_ARRAY-2), "Elementos actuales en el arbol");
    pa2m_afirmar((arbol_raiz(un_arbol)) == elementos+0, "El elemento fue borrado correctamente y reemplazado por su predecesor inorden, que resultó ser su copia.");


    arbol_destruir(un_arbol);
}

//Pre:
//Post: Se realizan las pruebas correspondientes al borrado de elementos de un arbol.
void probar_borrado(){

	pa2m_afirmar((arbol_borrar(NULL, NULL)) == -1, "Intentar borrar en un arbol Nulo devuelve error");
	abb_t* un_arbol = arbol_crear(abb_comparar_enteros, abb_liberar_entero);
	pa2m_afirmar((arbol_borrar(un_arbol, NULL)) == -1, "Intentar borrar en un arbol Vacio devuelve error");
	int elementos[MAX_ELEMENTOS] = {5,2,8,1,3,0,4,9,6,7};
	int elemento_fuera = 10;
	for(int i=0; i<10 ;i++)
		arbol_insertar(un_arbol, elementos+i);

	pa2m_afirmar(arbol_borrar(un_arbol, &elemento_fuera) == -1, "Intentar borrar un elemento que no está en el arbol devuelve error");
	pa2m_afirmar(arbol_borrar(un_arbol, elementos+5) == 0, "Puedo borrar una hoja del arbol normalmente");
	pa2m_afirmar(arbol_borrar(un_arbol, elementos+4) == 0, "Puedo borrar un nodo con un hijo del arbol normalmente");
	pa2m_afirmar(arbol_borrar(un_arbol, elementos+2) == 0, "Puedo borrar un nodo con dos hijos del arbol normalmente");
	pa2m_afirmar(arbol_borrar(un_arbol, elementos+0) == 0, "Puedo borrar una vez la raiz del arbol normalmente");
	pa2m_afirmar(*(int*)(arbol_raiz(un_arbol)) == 4, "La nueva raiz es la esperada");
	pa2m_afirmar(arbol_borrar(un_arbol, elementos+6) == 0, "Puedo borrar otra vez raiz del arbol normalmente");
	pa2m_afirmar(*(int*)(arbol_raiz(un_arbol)) == 2, "La nueva raiz es la esperada");
	
	arbol_borrar(un_arbol, elementos+1);
	arbol_borrar(un_arbol, elementos+3);
	arbol_borrar(un_arbol, elementos+6);
	arbol_borrar(un_arbol, elementos+7);
	arbol_borrar(un_arbol, elementos+8);
	arbol_borrar(un_arbol, elementos+9);

	pa2m_afirmar(arbol_vacio(un_arbol), "Puedo borrar todos los elementos del arbol y este queda vacio");

	free(un_arbol);
}


//Pre:
//Post: Se realizan las pruebas correspondientes a la destrucción de un arbol.
void probar_destruccion(){
	
	arbol_destruir(NULL);
	pa2m_afirmar(true, "Intentar destruir un arbol Nulo no produce efecto alguno (la cosa no explota)");

	abb_t* un_arbol = arbol_crear(abb_comparar_enteros, NULL);
	arbol_destruir(un_arbol);
	pa2m_afirmar(true, "Intentar destruir un arbol con destructor Nulo no explota, solo indica que no debe molestarse en liberar los lementos guardados en el arbol");

	un_arbol = arbol_crear(abb_comparar_enteros, abb_liberar_entero);
	arbol_destruir(un_arbol);
	pa2m_afirmar(true, "Puedo destruir un arbol Vacio");
	
	un_arbol = arbol_crear(abb_comparar_enteros, abb_liberar_entero);
    int elementos[MAX_ELEMENTOS] = {5,2,8,1,3,0,4,9,6,7};
	for(int i=0; i<10 ;i++)
		arbol_insertar(un_arbol, elementos+i);

	arbol_destruir(un_arbol);
	pa2m_afirmar(true, "Puedo destruir un arbol no vacio");
}



//Pre: La funcion de recorrido debe ser una de 3 validas (arbol_recorrido_inorden/arbol_recorrido_preorden/arbol_recorrido_postorden).
//Post: Se realizan las pruebas correspondientes a los distintos recorridos que pueden hacerse en un arbol.
void probar_recorrido(size_t (*arbol_recorrido)(abb_t* , void** , size_t ), int elementos_esperados_totales[], int elementos_esperados_parciales[]){
	
	size_t tamanio_array = 30;
	void* array_1[tamanio_array];
	abb_t* un_arbol = arbol_crear(abb_comparar_enteros, abb_liberar_entero);
	
	pa2m_afirmar((arbol_recorrido(NULL, array_1, tamanio_array)==0), "Intentar recorrer un arbol Nulo devuelve 0");
	pa2m_afirmar((arbol_recorrido(un_arbol, array_1, 0)==0), "Intentar recorrer un arbol Vacio devuelve 0");
	pa2m_afirmar((arbol_recorrido(un_arbol, NULL, tamanio_array)==0), "Intentar llenar un array Nulo devuelve 0");
	pa2m_afirmar((arbol_recorrido(un_arbol, array_1, 0)==0), "Intentar llenar un array de tamaño 0 devuelve 0");

    int elementos[MAX_ELEMENTOS] = {5,2,8,1,3,0,4,9,6,7};
	for(int i=0; i<10 ;i++)
		arbol_insertar(un_arbol, elementos+i);
	
	pa2m_afirmar(((arbol_recorrido(un_arbol, array_1, tamanio_array)) == CANT_ELEMENTOS_ARBOL) && son_elementos_esperados(elementos_esperados_totales, array_1, CANT_ELEMENTOS_ARBOL) && mostrar_elementos_array(array_1, CANT_ELEMENTOS_ARBOL), "Puedo recorrer un arbol con elementos y guardar todos su elementos, siendo la cantidad de elementos guaradados los que estaban en el arbol");

	void* array_2[MAX_ARRAY];
	pa2m_afirmar(((arbol_recorrido(un_arbol, array_2, MAX_ARRAY)) == MAX_ARRAY) && son_elementos_esperados(elementos_esperados_parciales, array_2, MAX_ARRAY) && mostrar_elementos_array(array_2, MAX_ARRAY), "Puedo recorrer un arbol con elementos y llenar el array (de 5 elementos), quedando elementos del arbol sin guardar");

	arbol_destruir(un_arbol);
}


//Pre: 
//Post: Prueba el correcto funcionamiento de los 3 recorridos posibles (inorden, preorden y postorden).
void probar_recorridos(){


	int elementos_inorden_totales[] = {0,1,2,3,4,5,6,7,8,9};
	int elementos_inorden_parciales[] = {0,1,2,3,4};

	int elementos_preorden_totales[] = {5,2,1,0,3,4,8,6,7,9};
	int elementos_preorden_parciales[] = {5,2,1,0,3};

	int elementos_postorden_totales[] = {0,1,4,3,2,7,6,9,8,5};
	int elementos_postorden_parciales[] = {0,1,4,3,2};

	pa2m_nuevo_grupo("-)INORDEN");
	probar_recorrido(arbol_recorrido_inorden, elementos_inorden_totales, elementos_inorden_parciales);

	pa2m_nuevo_grupo("-)PREORDEN");
	probar_recorrido(arbol_recorrido_preorden, elementos_preorden_totales, elementos_preorden_parciales);

	pa2m_nuevo_grupo("-)POSTORDEN");
	probar_recorrido(arbol_recorrido_postorden, elementos_postorden_totales, elementos_postorden_parciales);

}


//Pre: El elemento debe ser un entero.
//Post: Si no se pasa un tope simplemente imprime el entero por pantalla cada vez que se llama y devuelve false. Si le pasan un tope primero verifica si el elemento que le pasan no es el tope, si lo es ademas de imprimirlo devuelve true.
bool imprimir_enteros(void* elemento, void* tope){
	if(!tope){
		printf("%i ", *(int*)elemento);
		return false;
	}

	printf("%i ", *(int*)elemento);

	if((*(int*)elemento) == (*(int*)tope))
		return true;

	return false;
}


//Pre: El recorrido pasado debe ser uno de los 3 validos.
//Post: Establece cuantos elementos deberian ser recorridos hasta llegar al elemento tope deseado según el recorrido que va a realizarse.
void determinar_cant_recorridos_esperados(int* cant_recorridos_1, int* cant_recorridos_2, int* cant_recorridos_3, int recorrido){
	if(recorrido==ABB_RECORRER_INORDEN){
		(*cant_recorridos_1) = 9;
		(*cant_recorridos_2) = 4;
		(*cant_recorridos_3) = 1;
	}
	if(recorrido==ABB_RECORRER_PREORDEN){		//Se establecen la cantidad de elementos que deberian ser iterados en cada recorrido. Por ej) No se itera la misma cantidad de
		(*cant_recorridos_1) = 7;				//elementos hasta llegar al 3 si se recorre el arbol inorden (4 iteraciones) o postorden (9 iteraciones). 
		(*cant_recorridos_2) = 5;
		(*cant_recorridos_3) = 4;
	}
	if(recorrido==ABB_RECORRER_POSTORDEN){
		(*cant_recorridos_1) = 9;
		(*cant_recorridos_2) = 4;
		(*cant_recorridos_3) = 1;
	}
}



//Pre: El recorrido pasado debe ser uno de los 3 validos.
//Post: Se realizan las pruebas correspondientes al iterador con los distintos recorridos que pueden usarse.
void probar_iterador_con_recorrido(int recorrido){
	abb_t* un_arbol = arbol_crear(abb_comparar_enteros, abb_liberar_entero);
	
	pa2m_afirmar(abb_con_cada_elemento(NULL, recorrido, imprimir_enteros, NULL)== 0, "El iterador recorre 0 elementos cuando se le pasa un Arbol Nulo");
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, recorrido, imprimir_enteros, NULL)== 0, "El iterador recorre 0 elementos cuando se le pasa un Arbol Vacio");

	int elementos[MAX_ELEMENTOS] = {5,2,8,1,3,0,4,9,6,7};
	for(int i=0; i<10 ;i++)
		arbol_insertar(un_arbol, elementos+i);

	pa2m_afirmar(abb_con_cada_elemento(un_arbol, recorrido, NULL, NULL)== 0, "El iterador recorre 0 elementos cuando no se le pasa una funcion");
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, ABB_RECORRER_INVALIDO, imprimir_enteros, NULL)== 0, "El iterador recorre 0 elementos cuando no se le pasa un recorrido valido");

	int cant_recorridos_1, cant_recorridos_2, cant_recorridos_3;
	determinar_cant_recorridos_esperados(&cant_recorridos_1, &cant_recorridos_2, &cant_recorridos_3, recorrido);
	
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, recorrido, imprimir_enteros, NULL)== 10, "El iterador puede recorrer el arbol hasta que no haya mas elementos, aplicando la funcion en cada elemento");
	
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, recorrido, imprimir_enteros, elementos+2)== cant_recorridos_1, "El iterador puede recorrer el arbol hasta que la funcion pasada le indique detenerse (se cuenta la iteracionn en la que la funcion devuelve true), aplicando la funcion en cada elemento (hasta encontrar el 8)");
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, recorrido, imprimir_enteros, elementos+4)== cant_recorridos_2, "El iterador puede recorrer el arbol hasta que la funcion pasada le indique detenerse (se cuenta la iteracionn en la que la funcion devuelve true), aplicando la funcion en cada elemento (hasta encontrar el 3)");
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, recorrido, imprimir_enteros, elementos+5)== cant_recorridos_3, "El iterador puede recorrer el arbol hasta que la funcion pasada le indique detenerse (se cuenta la iteracionn en la que la funcion devuelve true), aplicando la funcion en cada elemento (hasta encontrar el 0)");

	arbol_destruir(un_arbol);
}


//Pre: 
//Post: Prueba el iterador interno de las 3 formas posibles (inorden, preorden y postorden).
void probar_iterador(){

	pa2m_nuevo_grupo("-)INORDEN");
	probar_iterador_con_recorrido(ABB_RECORRER_INORDEN);

	pa2m_nuevo_grupo("-)PREORDEN");
	probar_iterador_con_recorrido(ABB_RECORRER_PREORDEN);

	pa2m_nuevo_grupo("-)POSTORDEN");
	probar_iterador_con_recorrido(ABB_RECORRER_POSTORDEN);	
}


//Pre: 
//Post: Se realzan las pruebas necesarias para detetrminar el correcto funcionamiento de la funcion arbol_raiz.
void probar_obtener_elemento_raiz(){
	
	pa2m_afirmar((arbol_raiz(NULL)) == NULL, "Intentar obtener el elemento en la raiz de un arbol Nulo devuelve NULL");
	
	abb_t* un_arbol = arbol_crear(abb_comparar_enteros, abb_liberar_entero);

	pa2m_afirmar((arbol_raiz(un_arbol)) == NULL, "Intentar obtener el elemento en la raiz de un arbol Vacio devuelve NULL");

    int elementos[MAX_ELEMENTOS] = {5,2,8,1,3,0,4,9,6,7};
	arbol_insertar(un_arbol, elementos+0);

	pa2m_afirmar(*(int*)(arbol_raiz(un_arbol)) == elementos[0], "Puedo obtener el elemento en la raiz de un arbol no vacio y el elemento obtenido es el correcto");
	free(un_arbol->nodo_raiz);
    free(un_arbol);
}


//Pre: 
//Post: Se realzan las pruebas necesarias para detetrminar el correcto funcionamiento de la funcion arbol_vacio.
void probar_arbol_vacio(){
	pa2m_afirmar(arbol_vacio(NULL), "Un arbol Nulo esta Vacio");
	abb_t* un_arbol = arbol_crear(abb_comparar_enteros, abb_liberar_entero);
	pa2m_afirmar(arbol_vacio(un_arbol), "Un arbol Vacio esta Vacio");
    int elementos[MAX_ELEMENTOS] = {5,2,8,1,3,0,4,9,6,7};
	arbol_insertar(un_arbol, elementos+0);
	pa2m_afirmar(!arbol_vacio(un_arbol), "Un arbol con un elemento no esta Vacio");
	free(un_arbol->nodo_raiz);
    free(un_arbol);
}

//Pre: El arbol debe ser válido.
//Post: Se itera la totalidad del arbol con los 3 recorridos posibles, impriendo los elementos del arbol por pantalla.
void iterar_elementos_por_recorrido(abb_t* un_arbol, size_t cant_elementos){
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, ABB_RECORRER_INORDEN, imprimir_enteros, NULL) == cant_elementos, "<- Elementos del arbol inorden");
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, ABB_RECORRER_PREORDEN, imprimir_enteros, NULL) == cant_elementos, "<- Elementos del arbol preorden");
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, ABB_RECORRER_POSTORDEN, imprimir_enteros, NULL) == cant_elementos, "<- Elementos del arbol postorden");
}

//Pre: El arbol y los arrays deben ser válidos.
//Post: Se recorre el arbol con los 3 recorrdios posibles, llenando los arrays e impriendo los elementos del arbol por pantalla en cada recorrido.
void guardar_elementos_en_arrays(abb_t* un_arbol, void** array_inorden, void** array_preorden,  void** array_postorden, size_t tope){
	pa2m_afirmar((arbol_recorrido_inorden(un_arbol, array_inorden, tope) == tope) && mostrar_elementos_array(array_inorden, tope), "<- Elementos del array de 5 elementos obtenidos con recorrido inorden");
	pa2m_afirmar((arbol_recorrido_preorden(un_arbol, array_preorden, tope) == tope) && mostrar_elementos_array(array_preorden, tope), "<- Elementos del array de 5 elementos obtenidos con recorrido preorden");
	pa2m_afirmar((arbol_recorrido_postorden(un_arbol, array_postorden, tope) == tope) && mostrar_elementos_array(array_postorden, tope), "<- Elementos del array de 5 elementos obtenidos con recorrido postorden");
}

//Pre: 
//Post: Se realizan distintas operaciones genericas par corroborar el correcto funcionamiento del TDA.
void probar_distintas_operaciones(){
	abb_t* un_arbol = arbol_crear(abb_comparar_enteros, abb_liberar_entero);
	void* array_inorden[MAX_ARRAY];
	void* array_preorden[MAX_ARRAY];
	void* array_postorden[MAX_ARRAY];

    int elementos[MAX_ELEMENTOS] = {5,2,8,1,3,0,4,9,6,7};
	bool pude_insertar_todo = true;
	for(int i=0; i<MAX_ELEMENTOS ;i++){
		if(arbol_insertar(un_arbol, elementos+i)==-1)
			pude_insertar_todo = false;
	}

	pa2m_afirmar(pude_insertar_todo, "Creo un arbol y le inserto 10 elementos");
	iterar_elementos_por_recorrido(un_arbol, MAX_ELEMENTOS);
	pa2m_afirmar(arbol_raiz(un_arbol) == elementos+0, "La raiz del arbol es la esperada (5)");
	pa2m_afirmar(arbol_borrar(un_arbol, elementos+9) == 0, "Borro una hoja del arbol (7)");
	iterar_elementos_por_recorrido(un_arbol, MAX_ELEMENTOS-1);
	pa2m_afirmar(arbol_buscar(un_arbol, elementos+9) == NULL, "Ya no puedo encontrar el elemnto borrado en el arbol");
	pa2m_afirmar(arbol_borrar(un_arbol, arbol_raiz(un_arbol)) == 0, "Borro la raiz del arbol (5)");
	iterar_elementos_por_recorrido(un_arbol, MAX_ELEMENTOS-2);
	pa2m_afirmar(arbol_raiz(un_arbol) == elementos+6, "La raiz del arbol cambió y es la esperada (4)");
	pa2m_afirmar(arbol_insertar(un_arbol, elementos+8)==0, "Inserto la raiz borrada previamente");
	iterar_elementos_por_recorrido(un_arbol, MAX_ELEMENTOS-1);
	pa2m_afirmar((arbol_buscar(un_arbol, elementos+8) != NULL) && (arbol_raiz(un_arbol) == elementos+6), "El elemento es insertado correctamente y la raiz sigue siendo la misma (4)");
	guardar_elementos_en_arrays(un_arbol, array_inorden, array_preorden, array_postorden, MAX_ARRAY);

	arbol_destruir(un_arbol);
}



int main(){

	
    pa2m_nuevo_grupo("+)PRUEBAS DE CREACION");
    probar_creacion_arbol();
    
	pa2m_nuevo_grupo("+)PRUEBAS DE INSERCION");
    probar_insercion();
	
	pa2m_nuevo_grupo("+)PRUEBAS DE BORRADO");
    probar_borrado();
    probar_destruccion();
    
    pa2m_nuevo_grupo("+)PRUEBAS DE RECORRIDO");
    probar_recorridos();
    
    
    pa2m_nuevo_grupo("+)PRUEBAS DE ITERADOR");
    probar_iterador();
    
    pa2m_nuevo_grupo("+)PRUEBAS VARIAS");
    probar_obtener_elemento_raiz();
    probar_arbol_vacio();
    probar_distintas_operaciones();
   
    pa2m_mostrar_reporte();
    return 0;
}