#include "pa2mm.h"
#include "gimnasio.h"
#include "estructuras.h"


void probar_creacion_heap(){
    pa2m_afirmar(heap_crear(NULL, destructor_gimnasios)==NULL, "No puedo crear un heap sin comparador.");

    heap_t* heap_1 = heap_crear(comparador_gimnasios, NULL);
    pa2m_afirmar(heap_1, "Puedo crear un heap con comparador y sin destructor.");
    
    heap_t* heap_2 = heap_crear(comparador_gimnasios, destructor_gimnasios);
    pa2m_afirmar(heap_2, "Puedo crear un heap con comparador y con destructor.");

    pa2m_afirmar(heap_2->comparador && heap_2->destructor, "El heap con todo posee el comparador y el destructor dados.");
    pa2m_afirmar(heap_vacio(heap_2), "El heap se crea vacio.");
    heap_destruir(heap_1);
    heap_destruir(heap_2);
}

void probar_insercion_gimnasios(){
    heap_t* heap = heap_crear(comparador_gimnasios, destructor_gimnasios);

    cargar_gimnasio(heap, "Gimnasios/Kanto/Misty.txt");
    cargar_gimnasio(heap, "Gimnasios/Kanto/Brock.txt");
    
    pa2m_afirmar(!heap_vacio(heap), "Al insertar gimnasios (2) el heap deja de estar vacio.");
    gimnasio_t* gimnasio_1 = NULL;
    gimnasio_t* gimnasio_2 = NULL;
    
    gimnasio_1 = heap_extraer_minimal(heap);
    pa2m_afirmar(gimnasio_1, "Puedo extraer un gimnasio insertado.");
    pa2m_afirmar(!heap_vacio(heap), "El heap no queda vacio, todavia queda un gimnasio.");

    gimnasio_2 = heap_extraer_minimal(heap);
    pa2m_afirmar(gimnasio_2, "Puedo extraer el gimnasio restante del heap.");
    pa2m_afirmar(heap_vacio(heap), "El heap ahora esta vacio.");
    pa2m_afirmar(heap_extraer_minimal(heap)==NULL, "Intentar extraer mas elementos del heap vacio solo devuelve NULL.");


    pa2m_afirmar(gimnasio_1->dificultad <= gimnasio_2->dificultad, "Se extrajeron los gimnasios con dificultad creciente.");

    printf("Cantidad de entrenadores en el gimnasio: %i  ", lista_elementos(gimnasio_2->entrenadores));
    pa2m_afirmar(lista_elementos(gimnasio_2->entrenadores) == 3, "La cantidad de entrenadores del gimnasio es la esperada.");

    printf("%s  ", ((entrenador_t*)lista_primero(gimnasio_2->entrenadores))->nombre);
    pa2m_afirmar(strcmp(((entrenador_t*)lista_primero(gimnasio_2->entrenadores))->nombre, "Misty")==0, "El lider del gimnasio es el esperado.");


    int pokemones_esperados[3] = {2,1,2};
    char* nombres_entrenadores[3];
    nombres_entrenadores[2] = "Nadador Luis";
    nombres_entrenadores[1] = "Dominguera Diana";
    nombres_entrenadores[0] = "Misty";
    bool son_valores_esperados = true;

    for(size_t i=0; i<3 ;i++){
    	if(lista_elementos(((entrenador_t*)lista_elemento_en_posicion(gimnasio_2->entrenadores, i))->equipo) != pokemones_esperados[i]){
    		printf("%i) Los que tiene:%i != Esperados%i\n", i, lista_elementos(((entrenador_t*)lista_elemento_en_posicion(gimnasio_2->entrenadores, i))->equipo), pokemones_esperados[i]);
    		son_valores_esperados = false;
    	}

    	if(strcmp(((entrenador_t*)lista_elemento_en_posicion(gimnasio_2->entrenadores, i))->nombre, nombres_entrenadores[i])!=0){
    		printf("%i) Nombre:%s != Esperado:%s\n", i, ((entrenador_t*)lista_elemento_en_posicion(gimnasio_2->entrenadores, i))->nombre, nombres_entrenadores[i]);
    		son_valores_esperados = false;
    	}
    }

    pa2m_afirmar(son_valores_esperados, "Los entrenadores del gimnasio tienen sus nombres y cantidad de pokemones esperados.");

    
    destructor_gimnasios(gimnasio_1);
    destructor_gimnasios(gimnasio_2);
    heap_destruir(heap);
}

int main(){
    
	pa2m_nuevo_grupo("PRUEBAS DE HEAP");
	pa2m_nuevo_grupo("+)PRUEBAS DE CREACION");
    probar_creacion_heap();
	pa2m_nuevo_grupo("+)PRUEBAS DE GIMNASIO");
    probar_insercion_gimnasios();

    pa2m_mostrar_reporte();
    return 0;
}