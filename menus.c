#include "menus.h"
#include "interfaz.h"
#include "personaje.h"
#include "gimnasio.h"



void menu_combate(pokemon_t* pokemon_jugador, pokemon_t* pokemon_entrenador, int resultado_combate){
    printf("Combate Pokemon!!\n");
    printf("Tu pokemon \t\t\t Pokemon del rival \n\n");
    printf("\t%s \t\t %s\n", pokemon_jugador->nombre, pokemon_entrenador->nombre);
    printf("Tipo: %s \t\t\t Tipo: %s\n", pokemon_jugador->tipo, pokemon_entrenador->tipo);
    printf("V: %u \t\t\t V: %u \n", pokemon_jugador->velocidad, pokemon_entrenador->velocidad);
    printf("A: %u \t\t\t A: %u \n", pokemon_jugador->ataque, pokemon_entrenador->ataque);
    printf("D: %u \t\t\t D: %u \n", pokemon_jugador->defensa, pokemon_entrenador->defensa);
    if(resultado_combate==GANO_PRIMERO)
        printf("TU POKEMON GANA!!\n");
    else 
        printf("TU POKEMON PIERDE!!\n");
    printf("Presiona cualquier letra para continuar\n");
    getchar();
}




void aniadir_pokemon_al_equipo(personaje_t* jugador, pokemon_t* pokemon_lider, size_t posicion_a_ocupar){
    
    pokemon_t* nuevo_pkm = calloc(1, sizeof(pokemon_t));
    if(!nuevo_pkm){
        printf("Error al reservar memoria para el nuevo pokemon del equipo\n");
        return;
    }

    (*nuevo_pkm) = (*pokemon_lider);

    if(lista_elementos(jugador->equipo)<MAX_EQUIPO){
        if(lista_encolar(jugador->equipo, nuevo_pkm)==ERROR){
            printf("Error al insertar el pokemon del entrenador al equipo\n");
            free(nuevo_pkm);
            return;
        }
        return;
    }


    if(lista_encolar(jugador->capturados, lista_elemento_en_posicion(jugador->equipo, posicion_a_ocupar))==ERROR){
        printf("Error al mover el pokemon del equipo a capturados\n");
            free(nuevo_pkm);
            return;
        }

    if(lista_borrar_de_posicion(jugador->equipo, posicion_a_ocupar)==ERROR){
        printf("Error al sacar el pokemon del equipo\n");
        free(nuevo_pkm);
        return;
    }

    if(lista_insertar_en_posicion(jugador->equipo, nuevo_pkm, posicion_a_ocupar)==ERROR){
        printf("Error al insertar el pokemon del entrenador al equipo\n");
        free(nuevo_pkm);
        return;
    }
}

void tomar_prestado(personaje_t* jugador, entrenador_t* lider){
    bool es_lo_esperado = false;
    int posicion = -1;
    pokemon_t* pokemon_lider = NULL;
    while(!es_lo_esperado){
        printf("A continuacion se muestra el equipo del lider de gimnasio %s\n", lider->nombre);
        mostrar_equipo(lider->equipo);
        printf("Ingrese la posicion del pokemon que desea tomar o -1 si no deseea ninguno\n");
        posicion = pedir_posicion_pokemon(lista_elementos(lider->equipo));
        pokemon_lider = obtener_pokemon_en_posicion(lider->equipo, posicion);
        printf("Pokemon seleccionado:\n");
        imprimir_pokemon(pokemon_lider);
        es_lo_esperado = pedir_confirmacion();
    }

    if(posicion>=0){
        es_lo_esperado = false;
        while(!es_lo_esperado){
            printf("A continuacion se muestra tu equipo, %s de %s\n", jugador->nombre, jugador->ciudad_natal);
            mostrar_equipo(jugador->equipo);
            printf("Ingrese la posicion del pokemon que desea reemplazar o -1 si se arrepiente\n");
            posicion = pedir_posicion_pokemon(lista_elementos(jugador->equipo));
            pokemon_t* pokemon_jugador = obtener_pokemon_en_posicion(jugador->equipo, posicion);
            printf("Pokemon seleccionado:\n");
            imprimir_pokemon(pokemon_jugador);
            es_lo_esperado = pedir_confirmacion();
        }
    }

    if(posicion>=0)
        aniadir_pokemon_al_equipo(jugador, pokemon_lider, (size_t)posicion);
}

void eliminar_pokemon_en_posicion(lista_t* pokemones, size_t posicion){
     liberar_pokemon(lista_elemento_en_posicion(pokemones, posicion));
     lista_borrar_de_posicion(pokemones, posicion);
}

void cambiar_equipo(personaje_t* jugador){
    bool es_lo_esperado = false;
    int posicion = -1;
    pokemon_t* pokemon_capturado;
    while(!es_lo_esperado){
        printf("A continuacion se muestra tu equipo, %s de %s\n", jugador->nombre, jugador->ciudad_natal);
        mostrar_equipo(jugador->equipo);
        printf("Ingrese la posicion del pokemon que desea reemplazar o -1 si se arrepiente\n");
        posicion = pedir_posicion_pokemon(lista_elementos(jugador->equipo));
        pokemon_t* pokemon_equipo = obtener_pokemon_en_posicion(jugador->equipo, posicion);
        printf("Pokemon seleccionado:\n");
        imprimir_pokemon(pokemon_equipo);
        es_lo_esperado = pedir_confirmacion();
    }

    if(posicion>=0){
        es_lo_esperado = false;
        while(!es_lo_esperado){
            printf("A continuacion se muestran tus pokemones capturados\n");
            mostrar_equipo(jugador->capturados);
            printf("Ingrese la posicion del pokemon desee para reemplazar al seleccionado del equipo o -1 si se arrepiente\n");
            posicion = pedir_posicion_pokemon(lista_elementos(jugador->equipo));
            pokemon_capturado = obtener_pokemon_en_posicion(jugador->equipo, posicion);
            printf("Pokemon seleccionado:\n");
            imprimir_pokemon(pokemon_capturado);
            es_lo_esperado = pedir_confirmacion();
        }
    }

    if(posicion>=0){
        aniadir_pokemon_al_equipo(jugador, pokemon_capturado, (size_t)posicion);
        eliminar_pokemon_en_posicion(jugador->capturados, (size_t)posicion);
    }
}


void ejecutar_instruccion_menu_victoria(char letra, personaje_t* jugador, entrenador_t* lider, bool* ya_robo){
    if(letra==TOMAR_PRESTADO)
        tomar_prestado(jugador, lider);
    if(letra==CAMBIAR_EQUIPO)
        cambiar_equipo(jugador);
}


void menu_victoria(personaje_t* jugador, entrenador_t* lider){
    system("clear");
    bool ya_robo = false;
    mostrar_opciones_menu_victoria(ya_robo);
    char letra = pedir_instruccion_victoria(ya_robo);
    ejecutar_instruccion_menu_victoria(letra, jugador, lider, &ya_robo);
    if(letra!=PROXIMO)
        return menu_victoria(jugador, lider);
}


void ejecutar_instruccion_menu_derrota(char letra, personaje_t* jugador){
    if(letra==CAMBIAR_EQUIPO)
        cambiar_equipo(jugador);
}

char menu_derrota(personaje_t* jugador){
    system("clear");
    mostrar_opciones_menu_derrota();
    char letra = pedir_instruccion_derrota();
    ejecutar_instruccion_menu_derrota(letra, jugador);
    if(letra==CAMBIAR_EQUIPO)
        return menu_derrota(jugador);
    return letra;
}


void ejecutar_instruccion_menu_inicial(char letra, personaje_t** jugador, heap_t* gimnasios){
    if(letra == INGRESAR_JUGADOR)
        cargar_personaje(jugador); 

    if(letra == INGRESAR_GIMNASIO)
        cargar_gimnasios(gimnasios);
}

char menu_inicial(personaje_t** jugador, heap_t* gimnasios){
    system("clear");

    mostrar_opciones_menu_inicial();
    char letra = pedir_instruccion_inicial();
    ejecutar_instruccion_menu_inicial(letra, jugador, gimnasios);
    while(letra!=JUGAR && letra!=SIMULAR){
        mostrar_opciones_menu_inicial();
        letra = pedir_instruccion_inicial();
        ejecutar_instruccion_menu_inicial(letra, jugador, gimnasios);
    }

    if(!jugador)
        printf("No hay jugador\n");
    if(heap_vacio(gimnasios))
        printf("No hay gimnaios\n");

    if(!jugador || heap_vacio(gimnasios)){
        printf("Debe cargarse necesariamente el personaje principla y al menos un gimnasio para jugar\n");
        return menu_inicial(jugador, gimnasios);
    }
    return letra;
}

