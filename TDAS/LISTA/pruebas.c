#include "lista.h"
#include "pa2mm.h"
#define MUCHOS_ELEMENTOS 10000


//Pre: Los punteros deben apuntar enteros
//Post: Muestra por pantalla el elemento recibido y devuelve true salvo en el caso de que el eelemento sea el tope buscado.
bool mostrar_elementos_por_pantalla(void* elemento, void* elemento_tope){
	printf("%i ", *(int*)elemento);
	if((*(int*)elemento) == (*(int*)elemento_tope))
		return false;
	return true;
}

//Pre: 
//Post: Prueba los casos normales y bordes de crear una lista.
void probar_creacion_lista(){
	pa2m_nuevo_grupo("-)CREACION LISTA");
    lista_t* una_lista = NULL;

    pa2m_afirmar((una_lista=lista_crear()) != NULL, "Puedo crear una lista");
    pa2m_afirmar(((una_lista->nodo_inicio == NULL) && (una_lista->nodo_fin == NULL)), "Una lista se crea con punteros nulos");
    pa2m_afirmar(una_lista->nodo_fin == NULL, "Una lista se crea con 0 elementos");

    lista_destruir(una_lista);
}

//Pre: 
//Post: Prueba los casos normales y bordes de crear un iterador externo.
void probar_creacion_iterador_externo(){
	pa2m_nuevo_grupo("-)CREACION ITERADOR EXTERNO");

	lista_iterador_t* un_iterador = lista_iterador_crear(NULL);
	pa2m_afirmar(un_iterador==NULL, "No puedo crear un iterador externo de una lista nula");

	lista_t* una_lista = lista_crear();
	un_iterador = lista_iterador_crear(una_lista);
	pa2m_afirmar(un_iterador!=NULL, "Puedo crear un iterador externo de una lista vacia");
	lista_iterador_destruir(un_iterador);

	int elementos[] = {0,1,2,3,4,5,6,7,8,9};
	for(int i=0; i<10 ;i++)
		lista_insertar(una_lista, elementos+i);

	un_iterador = lista_iterador_crear(una_lista);

	pa2m_afirmar(un_iterador!=NULL, "Puedo crar un iterador de una lista");
	pa2m_afirmar((un_iterador->lista)==una_lista, "El iterador itera en su lista asignada");
	pa2m_afirmar((un_iterador->corriente)==(una_lista->nodo_inicio), "El iterador creado apunta al primer nodo de la lista asignada");

	lista_iterador_destruir(un_iterador);
	lista_destruir(una_lista);
}

//Pre: 
//Post: Prueba los casos normales y bordes de usar un iterador externo.
void probar_iterador_externo(){
	pa2m_nuevo_grupo("-)ITERADOR EXTERNO");
	
	lista_t* una_lista = lista_crear();
	
	

	int elementos[] = {0,1,2,3,4,5,6,7,8,9};
	for(int i=0; i<10 ;i++)
		lista_insertar(una_lista, elementos+i);

	
	lista_iterador_t* un_iterador = lista_iterador_crear(una_lista);


	bool itera_bien = true;
	int i=0;

	while(lista_iterador_tiene_siguiente(un_iterador)){
		if(lista_iterador_elemento_actual(un_iterador)!=elementos+i){
			itera_bien = false;
		}
		printf("%i ", *(int*)lista_iterador_elemento_actual(un_iterador));
		i++;
		lista_iterador_avanzar(un_iterador);
	}

	/*
	if(lista_iterador_elemento_actual(un_iterador)!=elementos+i){
			itera_bien = false;
		}
		printf("%i ", *(int*)lista_iterador_elemento_actual(un_iterador));
		i++;
	*/


	pa2m_afirmar(itera_bien, "Itera correctamente a lo largo de la lista y se detiene al llegar al final de la misma");
	pa2m_afirmar(!lista_iterador_tiene_siguiente(un_iterador), "El iterador indica que no puede seguir iterando cuando llega al final de la lista");
	pa2m_afirmar(!lista_iterador_avanzar(un_iterador), "El iterador siguió iterando y se salio de la lista");

	pa2m_afirmar(lista_iterador_elemento_actual(un_iterador)==NULL, "Al pedir el elemento del iterador que se salio de la lista devuelve NULL");
	pa2m_afirmar(lista_iterador_elemento_actual(un_iterador)==NULL, "El insistir con la iteracion sin sentido no genera efecto alguno y el iterador sigue apuntando a NULL");

	lista_iterador_destruir(un_iterador);
	lista_destruir(una_lista);
}

//Pre: 
//Post: Prueba los casos normales y bordes de crear y usar un iterador interno.
void probar_iterador_interno(){
	pa2m_nuevo_grupo("-)ITERADOR INTERNO");
	
	lista_t* una_lista = lista_crear();
	
	pa2m_afirmar(lista_con_cada_elemento(NULL, mostrar_elementos_por_pantalla, NULL) == 0, "No recorre nada cuando se le pasa una lista nula");
	pa2m_afirmar(lista_con_cada_elemento(una_lista, mostrar_elementos_por_pantalla, NULL) == 0, "No recorre nada cuando se le pasa una lista vacia");

	int elementos[] = {0,1,2,3,4,5,6,7,8,9};
	int elemento_fuera = 10;
	for(int i=0; i<10 ;i++)
		lista_insertar(una_lista, elementos+i);
	
	pa2m_afirmar(lista_con_cada_elemento(una_lista, NULL, elementos+9) == 0, "No recorre la lista cuando no se le pasa una funcion");
	pa2m_afirmar(lista_con_cada_elemento(una_lista, mostrar_elementos_por_pantalla, elementos+9) == 10, "Recorre correctamente la lista y aplica la funcion dada (hasta el tope dado como contexto)");
	pa2m_afirmar(lista_con_cada_elemento(una_lista, mostrar_elementos_por_pantalla, &elemento_fuera) == 10, "Recorre correctamente la lista y aplica la funcion dada hasta el final cuando la condicion de corte de la funcion no se cumple nunca");

	lista_destruir(una_lista);
}


//Pre: 
//Post: Prueba los casos normales y bordes de insertar un elemento al final de una lista.
void probar_insercion_normal_lista(){
	pa2m_nuevo_grupo("-)INSERCION NORMAL");
    lista_t* una_lista = lista_crear();
    int un_elemento=1, otro_elemento=10, otro_mas=100;

    pa2m_afirmar(lista_insertar(una_lista,&un_elemento)==0, "Puedo insertar un elemento al final de una lista vacia");
    pa2m_afirmar((una_lista->cantidad==1),"La lista tiene un elemento");
    pa2m_afirmar((una_lista->nodo_inicio != NULL),"El nodo inicial ya no es NULL");
    pa2m_afirmar((una_lista->nodo_fin != NULL),"El nodo final ya no es NULL");
    pa2m_afirmar((una_lista->nodo_inicio == una_lista->nodo_fin),"El nodo inicial es el mismo que el final");

    pa2m_afirmar(lista_insertar(una_lista,&otro_elemento)==0, "Puedo insertar un elemento en una lista no vacia");
    pa2m_afirmar((una_lista->cantidad==2),"La lista tiene 2 elementos");
    pa2m_afirmar((una_lista->nodo_inicio != una_lista->nodo_fin), "El nodo final es uno distinto al inicial");
    pa2m_afirmar(((una_lista->cantidad==2) && (una_lista->nodo_inicio != NULL) && (una_lista->nodo_fin != NULL) && (una_lista->nodo_inicio != una_lista->nodo_fin)), "Puede inseratar correctamente un elemento al finaL de una lista no vacia");
 	
 	pa2m_afirmar(lista_insertar(una_lista,&otro_mas)==0, "Puedo insertar otro elemento a la lista");
    pa2m_afirmar((una_lista->cantidad==3),"La lista tiene  ahora 3 elementos");
    pa2m_afirmar((una_lista->nodo_inicio != una_lista->nodo_fin),"El nodo final sigue siendo distinto al inicial");
    
    lista_iterador_t* un_iterador = lista_iterador_crear(una_lista);

    pa2m_afirmar((*(int*)lista_iterador_elemento_actual(un_iterador))==un_elemento,"El primer elemento es el correcto");
    lista_iterador_avanzar(un_iterador);
    pa2m_afirmar((*(int*)lista_iterador_elemento_actual(un_iterador))==otro_elemento,"El segundo elemento tambien es el correcto");
    lista_iterador_avanzar(un_iterador);
    pa2m_afirmar((*(int*)lista_iterador_elemento_actual(un_iterador))==otro_mas,"El tercer elemento tambien es el correcto");
    
    lista_iterador_destruir(un_iterador);
    lista_destruir(una_lista);
}

//Pre: 
//Post: Prueba los casos normales y bordes de insertar un elemento en cualquier posicion de una lista.
void probar_insercion_posicion_lista(){
	pa2m_nuevo_grupo("-)INSERCION EN POSICION");

	pa2m_afirmar(lista_insertar_en_posicion(NULL, NULL, 0)==-1, "Intentar insertar algo en una lista NULL no hace nada, pero tampoco rompe nada ;)");
	
	lista_t* una_lista = lista_crear();
	int primer_elemento = 99;

	pa2m_afirmar(lista_insertar_en_posicion(una_lista, &primer_elemento, 0)==0, "Puedo insertar un elemento en la 'posicion inicial' de una lista vacia");
	pa2m_afirmar(una_lista->nodo_fin->elemento == &primer_elemento, "El valor es el esperado");
	pa2m_afirmar(lista_elementos(una_lista)==1, "La cantidad de elementos en la lista se actualiza correctamente");

	lista_borrar(una_lista);

	pa2m_afirmar(lista_insertar_en_posicion(una_lista, &primer_elemento, 10)==0, "Puedo insertar un elemento en la 'posicion final' de una lista vacia");
	pa2m_afirmar(una_lista->nodo_fin->elemento == &primer_elemento, "El valor es el esperado");
	pa2m_afirmar(lista_elementos(una_lista)==1, "La cantidad de elementos en la lista se actualiza correctamente");

	lista_borrar(una_lista);

	int elementos[] = {0,1,2,3,4,5,6,7,8,9};
	for(int i=0; i<10 ;i++)
		lista_insertar(una_lista, elementos+i);

	int nuevo_elemento_1 = 10;
	pa2m_afirmar(lista_insertar_en_posicion(una_lista, &nuevo_elemento_1, 10)==0, "Puedo insertar un elemento en la posicion final de una lista no vacia");
	pa2m_afirmar(una_lista->nodo_fin->elemento == &nuevo_elemento_1, "El valor es el esperado");
	pa2m_afirmar(lista_elementos(una_lista)==11, "La cantidad de elementos en la lista se actualiza correctamente");

	pa2m_afirmar(lista_insertar_en_posicion(una_lista, &nuevo_elemento_1, 0)==0, "Puedo insertar un elemento en la posicion inicial de una lista no vacia");
		pa2m_afirmar(una_lista->nodo_inicio->elemento == &nuevo_elemento_1, "El valor es el esperado");
	pa2m_afirmar(lista_elementos(una_lista)==12, "La cantidad de elementos en la lista se actualiza correctamente");

	pa2m_afirmar(lista_insertar_en_posicion(una_lista, &nuevo_elemento_1, 5)==0, "Puedo insertar un elemento en una posicion cualquiera de una lista no vacia");
	pa2m_afirmar(lista_elementos(una_lista)==13, "La cantidad de elementos en la lista se actualiza correctamente");
	lista_destruir(una_lista);
}

//Pre: 
//Post: Prueba los casos normales y bordes de borrar un elemento al final de una lista.
void probar_borrado_normal_lista(){
	pa2m_nuevo_grupo("-)BORRADO NORMAL");
	lista_t* una_lista = lista_crear();
	pa2m_afirmar(lista_borrar(una_lista)==-1, "No puede borrar un elemento de una lista vacia");

	int elementos[] = {0,1,2,3,4,5,6,7,8,9};
	for(int i=0; i<10 ;i++)
		lista_insertar(una_lista, elementos+i);

	pa2m_afirmar(lista_borrar(una_lista)==0,"Puedo eliminar un elemento de una lista normalmente");
	pa2m_afirmar(lista_elementos(una_lista)==9,"La cantidad de elementos de la lista se reduce en uno");
	pa2m_afirmar(una_lista->nodo_fin->elemento == (elementos+8),"El ultimo elemento luego del borrado es el correcto");
	

	bool puedo_borrar = true;
	for(int i=0; i<5 ;i++){
		if(lista_borrar(una_lista)==-1)
			puedo_borrar = false;
	}

	pa2m_afirmar(puedo_borrar,"Puedo eliminar 5 elementos de una lista normalmente");
	pa2m_afirmar(lista_elementos(una_lista)==4,"La cantidad de elementos de la lista se reduce en 5");
	pa2m_afirmar(una_lista->nodo_fin->elemento == (elementos+3),"El ultimo elemento luego del borrado es el correcto");

	for(int i=0; i<4 ;i++)
		lista_borrar(una_lista);

	pa2m_afirmar(lista_borrar(una_lista)==-1,"Puedo eliminar todos los elementos de una lista normalmente");
	pa2m_afirmar(lista_elementos(una_lista)==0,"La cantidad de elementos de la lista se reduce a 0");

	lista_destruir(una_lista);
}


//Pre: 
//Post: Prueba los casos normales y bordes de borrar un elemento en cualquier posicion de una lista.
void probar_borrado_posicion_lista(){
	pa2m_nuevo_grupo("-)BORRADO POSICION");
	lista_t* una_lista = lista_crear();
	pa2m_afirmar(lista_borrar_de_posicion(una_lista, 0)==-1, "No puede borrar un elemento en la posicion inicial de una lista vacia");
	pa2m_afirmar(lista_borrar_de_posicion(una_lista, 100)==-1, "No puede borrar un elemento en una posicion generica de una lista vacia");
	
	int elementos[] = {0,1,2,3,4,5,6,7,8,9};
	for(int i=0; i<10 ;i++)
		lista_insertar(una_lista, elementos+i);

	pa2m_afirmar(lista_borrar_de_posicion(una_lista, 100)==0,"Intentar eliminar una el elemento en una posicion mayor al tamaño de la lista resulta en el borrado del ultimo elemento");
	pa2m_afirmar(lista_elementos(una_lista)==9,"La cantidad de elementos de la lista se reduce en uno");
	pa2m_afirmar(una_lista->nodo_fin->elemento == (elementos+8),"El ultimo elemento luego del borrado es el correcto");
	
	pa2m_afirmar(lista_borrar_de_posicion(una_lista, 8)==0,"Puedo eliminar el ultimo elemento de la lista normalmente");
	pa2m_afirmar(lista_elementos(una_lista)==8,"La cantidad de elementos de la lista se reduce en uno");
	pa2m_afirmar(una_lista->nodo_fin->elemento == (elementos+7),"El ultimo elemento luego del borrado es el correcto");
	
	pa2m_afirmar(lista_borrar_de_posicion(una_lista, 0)==0,"Puedo eliminar el primer elemento de la lista normalmente");
	pa2m_afirmar(lista_elementos(una_lista)==7,"La cantidad de elementos de la lista se reduce en uno");
	pa2m_afirmar(una_lista->nodo_inicio->elemento == (elementos+1),"El primer elemento luego del borrado es el correcto");
	
	pa2m_afirmar(lista_borrar_de_posicion(una_lista, 3)==0,"Puedo eliminar un elemento en el medio de la lista normalmente");
	pa2m_afirmar(lista_elementos(una_lista)==6,"La cantidad de elementos de la lista se reduce en uno");
	pa2m_afirmar(una_lista->nodo_inicio->siguiente->siguiente->siguiente->elemento == (elementos+5),"El primer elemento luego del borrado es el correcto");
	
	for(int i=0; i<6 ;i++)
		lista_borrar_de_posicion(una_lista, 0);

	pa2m_afirmar(lista_borrar_de_posicion(una_lista, 0)==-1,"Puedo eliminar todos los elementos de una lista con borrado por posicion");
	pa2m_afirmar(lista_elementos(una_lista)==0,"La cantidad de elementos de la lista se reduce a 0");
	
	lista_destruir(una_lista);
}


//Pre: 
//Post: Prueba los casos normales y bordes de apilar elementos en una pila.
void probar_apilado(){
	pa2m_nuevo_grupo("-)APILADO");

	lista_t* una_lista = lista_crear();
	int elementos[] = {0,1,2,3,4,5,6,7,8,9};

	pa2m_afirmar(lista_apilar(NULL, NULL)==-1, "No puedo apilar un elemento en una pila nula");
	pa2m_afirmar(lista_tope(una_lista) == NULL, "Pedir el tope de una pila vacia devuelve NULL");
	pa2m_afirmar(lista_apilar(una_lista, elementos+0)==0, "Puedo apilar un elemento en una pila vacia");
	pa2m_afirmar((*(int*)lista_tope(una_lista)) == elementos[0], "El elemento apilado es el correcto y es el nuevo tope de la pila");
	
	pa2m_afirmar(lista_apilar(una_lista, elementos+1)==0, "Puedo apilar un nuevo elemento en una pila no vacia");
	pa2m_afirmar((*(int*)lista_tope(una_lista)) == elementos[1], "El elemento apilado es el correcto y es el nuevo tope de la pila");

	bool puedo_apilar = true;
	for(int i=2; i<10 ;i++){
		if(lista_apilar(una_lista, elementos+i)==-1)
			puedo_apilar = false;
	}
	pa2m_afirmar(puedo_apilar, "Puedo apilar 8 elementoa en una pila");
	pa2m_afirmar((*(int*)lista_tope(una_lista)) == elementos[9], "El nuevo tope de la pila es el ultimo elemento apilado");

	lista_destruir(una_lista);
}

//Pre: 
//Post: Prueba los casos normales y bordes de desapilar elementos en una pila.
void probar_desapilado(){
	pa2m_nuevo_grupo("-)DESAPILADO");

	lista_t* una_lista = lista_crear();
	int elementos[] = {0,1,2,3,4,5,6,7,8,9};

	pa2m_afirmar(lista_desapilar(NULL)==-1, "No puedo desapilar un elemento de una pila nula");
	pa2m_afirmar(lista_desapilar(una_lista)==-1, "No puedo desapilar un elemento en una pila vacia");

	for(int i=0; i<10 ;i++)
		lista_apilar(una_lista, elementos+i);
	
	pa2m_afirmar(lista_desapilar(una_lista)==0, "Puedo desapilar un elemento de una pila");
	pa2m_afirmar((*(int*)lista_tope(una_lista)) == elementos[8], "El elemento quitado es el ultimo insertado y el nuevo tope de la pila es el correcto");

	for(int i=9; i!=0 ;i--)
		lista_desapilar(una_lista);

	pa2m_afirmar(lista_tope(una_lista) == NULL, "Puedo desapilar totalmente una pila y dejarla vacia");


	for(int i=0; i<5 ;i++)
		lista_apilar(una_lista, elementos+i);

	for(int i=2; i>0 ;i--)
		lista_desapilar(una_lista);

	pa2m_afirmar((*(int*)lista_tope(una_lista)) == elementos[2], "Puedo apilar y luego apilar sin problemas y el tope es el esperado");

	lista_destruir(una_lista);
}


//Pre: 
//Post: Prueba los casos normales y bordes de encolar elementos en una cola.
void probar_encolado(){
	pa2m_nuevo_grupo("-)ENCOLADO");

	lista_t* una_lista = lista_crear();
	int elementos[] = {0,1,2,3,4,5,6,7,8,9};

	pa2m_afirmar(lista_encolar(NULL, NULL)==-1, "No puedo encolar un elemento en una cola nula");
	pa2m_afirmar(lista_tope(una_lista) == NULL, "Pedir el tope de una cola vacia devuelve NULL");
	pa2m_afirmar(lista_encolar(una_lista, elementos+0)==0, "Puedo encolar un elemento en una cola vacia");
	pa2m_afirmar((*(int*)lista_primero(una_lista)) == elementos[0], "El elemento encolado es el correcto y es la nueva cabeza de la pila");
	
	pa2m_afirmar(lista_encolar(una_lista, elementos+1)==0, "Puedo encolar un nuevo elemento en una cola no vacia");
	pa2m_afirmar((*(int*)lista_tope(una_lista)) == elementos[1], "El elemento encolado es el correcto y es ahora el ultimo de la cola");
	pa2m_afirmar((*(int*)lista_primero(una_lista)) == elementos[0], "El primer elemento sigue siendo el mismo");

	bool puedo_encolar = true;
	for(int i=2; i<10 ;i++){
		if(lista_encolar(una_lista, elementos+i)==-1)
			puedo_encolar = false;
	}
	pa2m_afirmar(puedo_encolar, "Puedo encolar 8 elementoa en una cola");
	pa2m_afirmar((*(int*)lista_tope(una_lista)) == elementos[9], "El ultimo de la cola es el ultimo en ser encolado");
	pa2m_afirmar((*(int*)lista_primero(una_lista)) == elementos[0], "El primer elemento sigue siendo el mismo");

	lista_destruir(una_lista);
}

//Pre: 
//Post: Prueba los casos normales y bordes de desencolar elementos en una cola.
void probar_desencolado(){
	pa2m_nuevo_grupo("-)DESENCOLADO");

	lista_t* una_lista = lista_crear();
	int elementos[] = {0,1,2,3,4,5,6,7,8,9};

	pa2m_afirmar(lista_desencolar(NULL)==-1, "No puedo desencolar un elemento de una cola nula");
	pa2m_afirmar(lista_desencolar(una_lista)==-1, "No puedo desencolar un elemento en una cola vacia");

	for(int i=0; i<10 ;i++)
		lista_encolar(una_lista, elementos+i);
	
	pa2m_afirmar(lista_desencolar(una_lista)==0, "Puedo desencolar un elemento de una cola");
	pa2m_afirmar((*(int*)lista_primero(una_lista)) == elementos[1], "El elemento quitado es el primero insertado y el nuevo primero de la cola es el correcto");
	pa2m_afirmar((*(int*)lista_tope(una_lista)) == elementos[9], "El ultimo de la cola sigue siendo el mismo");

	for(int i=9; i!=0 ;i--)
		lista_desencolar(una_lista);

	pa2m_afirmar((lista_tope(una_lista) == NULL) && (lista_primero(una_lista) == NULL), "Puedo desencolar totalmente una cola y dejarla vacia");


	for(int i=0; i<5 ;i++)
		lista_encolar(una_lista, elementos+i);

	for(int i=2; i>0 ;i--)
		lista_desencolar(una_lista);

	pa2m_afirmar((*(int*)lista_primero(una_lista)) == elementos[2], "Puedo encolar y luego desencolar sin problemas y el primero es el esperado");
	pa2m_afirmar((*(int*)lista_tope(una_lista)) == elementos[4], "Puedo encolar y luego desencolar sin problemas y el ultimo es el esperado");

	lista_destruir(una_lista);
}

//Pre: 
//Post: Prueba el correcto funcionamiento de la lista con grandes volumenes de elementos.
void probar_insertar_muchos(){
	lista_t* una_lista = lista_crear();

	for(int i=0; i<10000 ;i++)
		lista_insertar(una_lista, NULL);
	pa2m_afirmar(lista_elementos(una_lista) == 10000, "Puedo insertar 10000 elementos al final de una lista normalmente");
	
	for(int i=0; i<10000 ;i++)
		lista_insertar_en_posicion(una_lista, NULL, 5000);
	pa2m_afirmar(lista_elementos(una_lista) == 20000, "Puedo insertar 10000 elementos en medio de una lista normalmente");

	for(int i=0; i<10000 ;i++)
		lista_insertar_en_posicion(una_lista, NULL, 0);
	pa2m_afirmar(lista_elementos(una_lista) == 30000, "Puedo insertar 10000 elementos al principio de una lista normalmente");

	for(int i=0; i<10000 ;i++)
		lista_borrar_de_posicion(una_lista, 0);
	pa2m_afirmar((una_lista->nodo_inicio != NULL) && (una_lista->nodo_fin != NULL) && (lista_elementos(una_lista) == 20000), "Puedo borrar los primeros 10000 elementos en una lista");
	
	for(int i=0; i<10000 ;i++)
		lista_borrar_de_posicion(una_lista, 10000);
	pa2m_afirmar((una_lista->nodo_inicio != NULL) && (una_lista->nodo_fin != NULL) && (lista_elementos(una_lista) == 10000), "Puedo borrar 10000 elementos del medio de una lista");
	
	for(int i=0; i<10000 ;i++)
		lista_borrar(una_lista);
	pa2m_afirmar((una_lista->nodo_inicio == NULL) && (una_lista->nodo_fin == NULL) && (lista_elementos(una_lista) == 0), "Puedo borrar los ultimos 10000 elementos restantes de la lista normalmente y esta queda vacia");

	lista_destruir(una_lista);
}

//Pre: 
//Post: Prueba el correcto funcionamiento de la pila con grandes volumenes de elementos.
void probar_apilar_muchos(){
	lista_t* una_pila = lista_crear();

	for(int i=0; i<10000 ;i++)
		lista_apilar(una_pila, NULL);
	pa2m_afirmar(lista_elementos(una_pila) == 10000, "Puedo apilar 10000 de elementos en una pila normalmente");

	for(int i=0; i<10000 ;i++)
		lista_desapilar(una_pila);

	pa2m_afirmar((una_pila->nodo_inicio == NULL) && (una_pila->nodo_fin == NULL) && (lista_elementos(una_pila) == 0), "Puedo desapilar 10000 de elementos en una pila y esta queda vacia");

	lista_destruir(una_pila);
}

//Pre: 
//Post: Prueba el correcto funcionamiento de la cola con grandes volumenes de elementos.
void probar_encolar_muchos(){
	lista_t* una_cola = lista_crear();

	for(int i=0; i<10000 ;i++)
		lista_encolar(una_cola, NULL);

	pa2m_afirmar(lista_elementos(una_cola) == 10000, "Puedo encolar 10000 de elementos en una cola normalmente");

	for(int i=0; i<10000 ;i++)
		lista_desencolar(una_cola);

	pa2m_afirmar((una_cola->nodo_inicio == NULL) && (una_cola->nodo_fin == NULL) && (lista_elementos(una_cola) == 0), "Puedo desencolar 10000 de elementos en una cola y esta queda vacia");

	lista_destruir(una_cola);
}


int main(){
    pa2m_nuevo_grupo("+)PRUEBAS DE CREACION");
    probar_creacion_lista();
    probar_creacion_iterador_externo();

    pa2m_nuevo_grupo("+)PRUEBAS DE ITERADOR");
    probar_iterador_externo();
    probar_iterador_interno();
	
	pa2m_nuevo_grupo("+)PRUEBAS DE INSERCION");
    probar_insercion_normal_lista();
    probar_insercion_posicion_lista();
	
	pa2m_nuevo_grupo("+)PRUEBAS DE BORRADO");
    probar_borrado_normal_lista();
    probar_borrado_posicion_lista();
	
	pa2m_nuevo_grupo("+)PRUEBAS DE PILA");
    probar_apilado();
    probar_desapilado();

    pa2m_nuevo_grupo("+)PRUEBAS DE COLA");
    probar_encolado();
    probar_desencolado();

    pa2m_nuevo_grupo("+)PRUEBAS DE VOLUMEN");
    probar_insertar_muchos();
    probar_apilar_muchos();
    probar_encolar_muchos();

    pa2m_mostrar_reporte();
    return 0;
}