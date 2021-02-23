#include "menus.h"
#include "interfaz.h"
#include "personaje.h"
#include "gimnasio.h"



void menu_combate(pokemon_t* pokemon_jugador, pokemon_t* pokemon_entrenador, int resultado_combate){
    if(!pokemon_jugador || !pokemon_entrenador){
        return imp_err_falta_argumento_en_enfrentamiento();
    }
    mostrar_combate_pokemon(pokemon_jugador,pokemon_entrenador,resultado_combate);
    pedir_letra_para_continuar();
}



/*Añade el pokemon dado al equipo.
 *Si no hay espacio en el equipo se le pedira al usuario por qué pokemon presente desea reemplazarlo, enviendo al reemplazado a la lista de capturados.
 *Si hay espacio en el equipo, el pokemon es agregado al final de la lista. 
*/
void aniadir_pokemon_al_equipo(personaje_t* jugador, pokemon_t* pokemon_lider, size_t posicion_a_ocupar){
    if(!jugador || !pokemon_lider){
        return imp_err_falta_argumento_en_aniadir_pkm();
    }

    pokemon_t* nuevo_pkm = calloc(1, sizeof(pokemon_t));
    if(!nuevo_pkm){
        return imp_err_reserva_de_memoria_pkmn();
    }

    (*nuevo_pkm) = (*pokemon_lider);

    if(lista_elementos(jugador->equipo)<MAX_EQUIPO){
        if(lista_encolar(jugador->equipo, nuevo_pkm)==ERROR){
            imp_err_insertar_pkmn();
            free(nuevo_pkm);
            return;
        }
        return;
    }


    if(lista_encolar(jugador->capturados, lista_elemento_en_posicion(jugador->equipo, posicion_a_ocupar))==ERROR){
            imp_err_trasladar_pkmn();
            free(nuevo_pkm);
            return;
        }

    if(lista_borrar_de_posicion(jugador->equipo, posicion_a_ocupar)==ERROR){
        imp_err_extraer_pkmn();
        free(nuevo_pkm);
        return;
    }

    if(lista_insertar_en_posicion(jugador->equipo, nuevo_pkm, posicion_a_ocupar)==ERROR){
        imp_err_insertar_pkmn();
        free(nuevo_pkm);
        return;
    }
}


/*Copia un pokemon del lider y lo agrega al equipo.
 *Si no hay espacio en el equipo se le pedira al usuario por qué pokemon presente desea reemplazarlo, enviendo al reemplazado a la lista de capturados.
 *Si hay espacio en el equipo, el pokemon es agregado al final de la lista. 
*/
void tomar_prestado(personaje_t* jugador, entrenador_t* lider, bool* ya_robo){
    bool es_lo_esperado = false;
    int posicion = -1;
    pokemon_t* pokemon_lider = NULL;
    while(!es_lo_esperado){
        imp_msj_muestro_duenio_equipo(lider->nombre);
        mostrar_equipo(lider->equipo);
        imp_msj_ingresar_posicion();
        posicion = pedir_posicion_pokemon(lista_elementos(lider->equipo));
        pokemon_lider = obtener_pokemon_en_posicion(lider->equipo, posicion);
        imp_msj_pkm_seleccionado();
        imprimir_pokemon(pokemon_lider);
        es_lo_esperado = pedir_confirmacion();
    }

    if(posicion>=0){
        es_lo_esperado = false;
        while(!es_lo_esperado){
            imp_msj_muestro_duenio_equipo(jugador->nombre);
            mostrar_equipo(jugador->equipo);
            imp_msj_ingresar_posicion();
            posicion = pedir_posicion_pokemon(lista_elementos(jugador->equipo));
            pokemon_t* pokemon_jugador = obtener_pokemon_en_posicion(jugador->equipo, posicion);
            imp_msj_pkm_seleccionado();
            imprimir_pokemon(pokemon_jugador);
            es_lo_esperado = pedir_confirmacion();
        }
    }

    if(posicion>=0){
        aniadir_pokemon_al_equipo(jugador, pokemon_lider, (size_t)posicion);
        *ya_robo = true;
        imp_msj_transferencia_exitosa();
    }
}

//Elimina el pokemon en la posicion dada de la lista, liberando la memoria reservada para el mismo.
void eliminar_pokemon_en_posicion(lista_t* pokemones, size_t posicion){
     liberar_pokemon(lista_elemento_en_posicion(pokemones, posicion));
     lista_borrar_de_posicion(pokemones, posicion);
}


/*Permite intercambiar un pokemon del equipo por uno en la caja (capturados).
 *Si el usuario se rrepinte del cambio en durante la operacion puede cancelarla
 */
void cambiar_equipo(personaje_t* jugador){
    bool es_lo_esperado = false;
    int posicion = -1;
    pokemon_t* pokemon_capturado;
    while(!es_lo_esperado){
        imp_msj_muestro_duenio_equipo(jugador->nombre);
        mostrar_equipo(jugador->equipo);
        imp_msj_ingresar_posicion();
        posicion = pedir_posicion_pokemon(lista_elementos(jugador->equipo));
        pokemon_t* pokemon_equipo = obtener_pokemon_en_posicion(jugador->equipo, posicion);
        imp_msj_pkm_seleccionado();
        imprimir_pokemon(pokemon_equipo);
        es_lo_esperado = pedir_confirmacion();
    }

    if(posicion>=0){
        es_lo_esperado = false;
        while(!es_lo_esperado){
           imp_msj_muestro_capturados()
            mostrar_equipo(jugador->capturados);
            imp_msj_ingresar_posicion();
            posicion = pedir_posicion_pokemon(lista_elementos(jugador->capturados));
            pokemon_capturado = obtener_pokemon_en_posicion(jugador->capturados, posicion);
            imp_msj_pkm_seleccionado();
            imprimir_pokemon(pokemon_capturado);
            es_lo_esperado = pedir_confirmacion();
        }
    }

    if(posicion>=0){
        aniadir_pokemon_al_equipo(jugador, pokemon_capturado, (size_t)posicion);
        eliminar_pokemon_en_posicion(jugador->capturados, (size_t)posicion);
        imp_msj_transferencia_exitosa();
    }
}


void ejecutar_instruccion_menu_victoria(char letra, personaje_t* jugador, entrenador_t* lider, bool* ya_robo){
    if(letra==TOMAR_PRESTADO)
        tomar_prestado(jugador, lider, ya_robo);
    if(letra==CAMBIAR_EQUIPO)
        cambiar_equipo(jugador);
}


void menu_victoria(personaje_t* jugador, entrenador_t* lider, bool ya_robo){
    mostrar_opciones_menu_victoria(ya_robo);
    char letra = pedir_instruccion_victoria(ya_robo);
    ejecutar_instruccion_menu_victoria(letra, jugador, lider, &ya_robo);
    if(letra!=PROXIMO)
        return menu_victoria(jugador, lider, ya_robo);
}


void ejecutar_instruccion_menu_derrota(char letra, personaje_t* jugador){
    if(letra==CAMBIAR_EQUIPO)
        cambiar_equipo(jugador);
}

char menu_derrota(personaje_t* jugador){
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
    mostrar_opciones_menu_inicial();
    char letra = pedir_instruccion_inicial();
    ejecutar_instruccion_menu_inicial(letra, jugador, gimnasios);
    while(letra!=JUGAR && letra!=SIMULAR){
        mostrar_opciones_menu_inicial();
        letra = pedir_instruccion_inicial();
        ejecutar_instruccion_menu_inicial(letra, jugador, gimnasios);
    }

    if(!jugador || heap_vacio(gimnasios)){
        imp_err_faltan_elementos_para_iniciar();

        if(!(*jugador)){
            imp_err_falta_jugador();
        }

        if(heap_vacio(gimnasios)){
            imp_err_falta_jugador()
        }
        return menu_inicial(jugador, gimnasios);
    }
    return letra;
}


void ejecutar_instruccion_menu_gimnasio(char letra, personaje_t* jugador, gimnasio_t* gimnasio){
    if(letra==MOSTRAR_JUGADOR)
        mostrar_jugador(jugador);
    if(letra==MOSTRAR_GIMNASIO)
        mostrar_gimnasio(gimnasio);
    if(letra==CAMBIAR_EQUIPO)
        cambiar_equipo(jugador);
}


void menu_gimnasio(personaje_t* jugador, gimnasio_t* gimnasio){
    mostrar_opciones_menu_gimnasio();
    char letra = pedir_instruccion_gimnasio();
    ejecutar_instruccion_menu_gimnasio(letra, jugador, gimnasio);
    if(letra!=BATALLA)
        return menu_gimnasio(jugador, gimnasio);
}


