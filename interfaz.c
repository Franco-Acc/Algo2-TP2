#include "interfaz.h"


void imprimir_pokemon(pokemon_t* pokemon){
    if(!pokemon){
        printf("No se selecciono un pokemon\n");
        return;
    }
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
    lista_iterador_destruir(iterador_equipo);
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
    lista_iterador_destruir(iterador_entrenadores);
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
    printf("Ya no hay más gimnasios para mostrar\n");
}



void mostrar_opciones_menu_victoria(bool ya_robo){
    printf("Seleccione una de las siguientes opciones a continuacion y recuerde solo ingresar la letra correspondiente en mayuscula:\n");
    if(!ya_robo)
        printf(" %c --> Elegir uno de los pokemones del equipo del lider derrotado para añadirlo a tu equipo\n", TOMAR_PRESTADO);
    printf(" %c --> Cambiar los pokemones en tu equipo con aquellos que hayas capturado\n", CAMBIAR_EQUIPO);
    printf(" %c --> Siguiente gimnaio\n", PROXIMO);
}

char pedir_instruccion_victoria(bool ya_robo){
    printf("Ingrese uno de los comandos de arriva...\n");
    char letra = (char)getchar();
    if(letra!=TOMAR_PRESTADO && letra!=CAMBIAR_EQUIPO && letra!=PROXIMO){
        printf("El comando ingresado no es valido\n");
        return pedir_instruccion_victoria(ya_robo);
    }
    if((letra==TOMAR_PRESTADO) && ya_robo){
        printf("Solo pudes tomar prestado un poquemon del lider y ya lo hiciste\n");
        return pedir_instruccion_victoria(ya_robo);
    }
    return letra;
}


int pedir_posicion_pokemon(size_t tope_equipo){
    int posicion;
    scanf("%i", &posicion);
    if(posicion>=tope_equipo)
        return pedir_posicion_pokemon(tope_equipo);
    return posicion;
}

pokemon_t* obtener_pokemon_en_posicion(lista_t* equipo, int posicion){
    if(posicion<0){
        printf("No se seleccionó ningun pokemon\n");
        return NULL;
    }
    return lista_elemento_en_posicion(equipo, (size_t)posicion);
}


bool pedir_confirmacion(){
    printf("Es esto correcto? Y/N: ");
    char respuesta;
    scanf(" %c", &respuesta);

    if((respuesta!=SI) && (respuesta!=NO)){
        printf("\nSolo se acepta Y o N (mayúscula)\n");
        return pedir_confirmacion();
    }

    if(respuesta==SI)
        return true;
    else
        return false;
}





void mostrar_opciones_menu_derrota(){
    printf("Seleccione una de las siguientes opciones a continuacion y recuerde solo ingresar la letra correspondiente en mayuscula:\n");
    printf(" %c --> Cambiar los pokemones en tu equipo con aquellos que hayas capturado\n", CAMBIAR_EQUIPO);
    printf(" %c --> Reintentar gimnaio\n", REINTENTAR);
    printf(" %c --> REndirse\n", RENDIRSE);
}

char pedir_instruccion_derrota(){
    printf("Ingrese uno de los comandos de arriva...\n");
    char letra;
    scanf(" %c", &letra);
    if(letra!=REINTENTAR && letra!=CAMBIAR_EQUIPO && letra!=RENDIRSE){
        printf("El comando ingresado no es valido\n");
        return pedir_instruccion_derrota();
    }
    return letra;
}






/*

int cargar_estructuras(personaje_t* jugador, heap_t* gimnasios){
    
    heap_t* gimnasios = heap_crear(comparador_gimnasios, destructor_gimnasios);
    if(!gimnasios)
        return ERROR_FATAL;

    cargar_gimnasios(gimnasios);

    cargar_personaje(jugador);
    
    return OK;
}

*/


void mostrar_opciones_menu_inicial(){
    printf("Seleccione una de las siguientes opciones a continuacion y recuerde solo ingresar la letra correspondiente en mayuscula:\n");
    printf(" %c --> Ingreasar archivo del personaje principal\n", INGRESAR_JUGADOR);
    printf(" %c --> Ingreasar archivos de gimnasios\n", INGRESAR_GIMNASIO);
    printf(" %c --> Jugar una partida con los datos cargados\n", JUGAR);
    printf(" %c --> simular una partida con los datos cargados\n", SIMULAR);
}

char pedir_instruccion_inicial(){
    printf("Ingrese uno de los comandos de arriva...\n");
    char letra;
    scanf(" %c", &letra);
    if(letra!=INGRESAR_JUGADOR && letra!=INGRESAR_GIMNASIO && letra!=JUGAR && letra!=SIMULAR){
        printf("El comando ingresado no es valido\n");
        return pedir_instruccion_inicial();
    }
    return letra;
}