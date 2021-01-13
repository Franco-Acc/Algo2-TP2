
#include "gimnasio.h"
#include "menus.h"


funcion_batalla determinar_funcion(size_t n){
    if(n==1)
        return funcion_batalla_1;
    if(n==2)
        return funcion_batalla_2;
    if(n==3)
        return funcion_batalla_3;
    if(n==4)
        return funcion_batalla_4;
    else
        return funcion_batalla_5;
}

bool leer_linea_gimnasio(FILE* archivo_gimnasio, gimnasio_t* un_gimnasio, int cant_items_esperados){
    size_t reglas;
    int leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_GIMNASIO, un_gimnasio->nombre, &(un_gimnasio->dificultad), &reglas);
    un_gimnasio->reglas_de_batalla = determinar_funcion(reglas);
    if(leidos != cant_items_esperados)
        return false;
    return true;
}

bool agregar_nuevo_entrenador(gimnasio_t* gimnasio, char nombre_entrenador[]){
    entrenador_t* nuevo_entrenador = calloc(1, sizeof(entrenador_t));
    if(!nuevo_entrenador)
        return false;
    
    strcpy(nuevo_entrenador->nombre, nombre_entrenador);
    
    if(!gimnasio->entrenadores)
        gimnasio->entrenadores = lista_crear();

    if(lista_apilar(gimnasio->entrenadores, nuevo_entrenador)==ERROR)
        return false;

    return true;
}


bool leer_linea_entrenador(FILE* archivo_gimnasio, gimnasio_t* un_gimnasio, int cant_items_esperados){
    char nombre_entrenador[MAX_NOMBRE];
    int leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_ENTRENADOR, nombre_entrenador);
    if(leidos != cant_items_esperados)
        return false;
    return agregar_nuevo_entrenador(un_gimnasio, nombre_entrenador);
}

bool agregar_nuevo_pokemon(entrenador_t* entrenador, pokemon_t* pokemon){
    if(!entrenador){
        free(pokemon);
        return false;
    }

    if(!entrenador->equipo)
        entrenador->equipo = lista_crear();

    if(!entrenador->equipo){
        free(pokemon);
        return false;
    }

    if(lista_elementos(entrenador->equipo)<MAX_EQUIPO){
        if(lista_encolar(entrenador->equipo, pokemon)==ERROR){
            free(pokemon);
            return false;
        }
    }
    return true;
}



bool leer_linea_pokemon(FILE* archivo_gimnasio, gimnasio_t* un_gimnasio, int cant_items_esperados){
    pokemon_t* nuevo_pkm = calloc(1, sizeof(pokemon_t));
    int leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_POKEMON, nuevo_pkm->nombre, nuevo_pkm->tipo, &(nuevo_pkm->velocidad), &(nuevo_pkm->ataque), &(nuevo_pkm->defensa));
    if(leidos != cant_items_esperados){
        free(nuevo_pkm);
        return false;
    }
    return agregar_nuevo_pokemon(lista_tope(un_gimnasio->entrenadores), nuevo_pkm);
}



gimnasio_t* leer_archivo_gimnasio(FILE* archivo_gimnasio){

    gimnasio_t* un_gimnasio = calloc(1, sizeof(gimnasio_t));
    if(!un_gimnasio)
        return NULL;

    bool todo_ok = true;
    char tipo_linea = GIMNASIO;

    leer_primera_letra_de_linea(archivo_gimnasio, &tipo_linea);
    todo_ok = leer_linea_gimnasio(archivo_gimnasio, un_gimnasio, CANT_ITEMS_GIMNASIO);  //la primera linea siempre debe ser la del gimnasio
    
    while(todo_ok){
        leer_primera_letra_de_linea(archivo_gimnasio, &tipo_linea);

        if((tipo_linea == ENTRENADOR) || (tipo_linea == LIDER)){
            todo_ok = leer_linea_entrenador(archivo_gimnasio, un_gimnasio, CANT_ITEMS_ENTRENADOR);
        }else if(tipo_linea == POKEMON){
            todo_ok = leer_linea_pokemon(archivo_gimnasio, un_gimnasio, CANT_ITEMS_POKEMON);
        }else{
            todo_ok = false;
        }
    }
    return un_gimnasio;
}


void liberar_gimnasio(gimnasio_t* gimnasio){
    if(!gimnasio)
        return;
    if(gimnasio->entrenadores){
        while(!lista_vacia(gimnasio->entrenadores)){
            entrenador_t* un_entrenador = lista_tope(gimnasio->entrenadores);
            if(un_entrenador->equipo){
                while(!lista_vacia(un_entrenador->equipo)){
                    free(lista_primero(un_entrenador->equipo));
                    lista_desencolar(un_entrenador->equipo);
                }
                lista_destruir(un_entrenador->equipo);
            }
            free(un_entrenador);
            lista_desapilar(gimnasio->entrenadores);
        }
        lista_destruir(gimnasio->entrenadores);
    }
    free(gimnasio);
}

void cargar_gimnasio(heap_t* heap, char* direccion_gimasio){
    if(!heap ||!direccion_gimasio)
        return;

    FILE* archivo_gimnasio = fopen(direccion_gimasio, "r");
    if(!archivo_gimnasio){
        printf("Error al abrir el archivo de gimnasio seleccionado\n");
        return;
    }

    gimnasio_t* nuevo_gimnasio = leer_archivo_gimnasio(archivo_gimnasio);

    if(!nuevo_gimnasio){
        printf("Error al reservar memoria para el gimnasio\n");
        fclose(archivo_gimnasio);
        return;
    }

    if(heap_insertar(heap, nuevo_gimnasio)==ERROR){
        liberar_gimnasio(nuevo_gimnasio);
        fclose(archivo_gimnasio);
        printf("Error al insertar el gimnasio en el HEAP\n");
        return;
    }
    fclose(archivo_gimnasio);
    return;
}

bool quiere_seguir_cargando(){
    char respuesta;
    printf("Quiere cargar otro gimnasio??\n Y/N : ");
    scanf(" %c", &respuesta);
    if(respuesta==SI)
        return true;
    if(respuesta==NO)
        return false;
    printf("Recurde solo ingresar uno de los carcateres indicados, en mayuscula\n");
    return quiere_seguir_cargando();
}

void cargar_gimnasios(heap_t* gimnasios){
    
    char direccion_gimasio[MAX_DIRECCION];

    printf("Para ingreasar ingresar un gimnasio indique la direccion del archivo, por ejemplo Gimnasios/Kanto/Misty.txt\n");
    printf("En caso de ocurrir algun error, este se indicará.\n");
    pedir_direccion(direccion_gimasio);
    cargar_gimnasio(gimnasios, direccion_gimasio);

    while(quiere_seguir_cargando()){
        pedir_direccion(direccion_gimasio);
        cargar_gimnasio(gimnasios, direccion_gimasio);
    }
}


void trasladar_primer_pokemon(lista_t* lista_original, lista_t* lista_nueva){
    lista_encolar(lista_nueva, lista_primero(lista_original));
    lista_desencolar(lista_original);
}


void restaurar_equipos(lista_t* lista_aux, lista_t* equipo){
    while(!lista_vacia(lista_aux))
        trasladar_primer_pokemon(lista_aux, equipo);
}

void actualizar_estadisticas_pokemon(pokemon_t* pokemon){
    if(pokemon->bonus < MAX_BONUS){
       pokemon->bonus++;
    }
}

int duelo_pokemon(lista_t* equipo_jugador, lista_t* equipo_entrenador, funcion_batalla reglas_de_batalla, bool es_simulacion){
    if(!equipo_jugador || !equipo_entrenador || !reglas_de_batalla)
        return ERROR;

    lista_t* lista_aux_jugador = lista_crear();
    lista_t* lista_aux_entrenador = lista_crear();
    int resultado_combate = 0;
    int resultado_duelo = 0;

    while(!lista_vacia(equipo_jugador) && !lista_vacia(equipo_entrenador)){
        
        resultado_combate = reglas_de_batalla(lista_primero(equipo_jugador), lista_primero(equipo_entrenador));
        if(!es_simulacion)
            menu_combate(lista_primero(equipo_jugador), lista_primero(equipo_entrenador), resultado_combate);
        
        if(resultado_combate==GANO_PRIMERO){
            actualizar_estadisticas_pokemon(lista_primero(equipo_jugador));
            trasladar_primer_pokemon(equipo_entrenador, lista_aux_entrenador);
        }else{
            trasladar_primer_pokemon(equipo_jugador, lista_aux_jugador);
        }
    }

    if(lista_vacia(equipo_entrenador)){
        resultado_duelo = VICTORIA;
    }else{
        resultado_duelo = DERROTA;
    }

    restaurar_equipos(equipo_jugador, lista_aux_jugador); // ESTO ES PARA MANTENER EL ORDEN ORIGINAL
    restaurar_equipos(lista_aux_jugador, equipo_jugador);

    restaurar_equipos(equipo_entrenador, lista_aux_entrenador); // ESTO ES PARA MANTENER EL ORDEN ORIGINAL
    restaurar_equipos(lista_aux_entrenador, equipo_entrenador);

    lista_destruir(lista_aux_jugador);
    lista_destruir(lista_aux_entrenador);
    return resultado_duelo;
}


void trasladar_ultimo_entrenador(lista_t* pila_original, lista_t* pila_nueva){
    lista_apilar(pila_nueva, lista_tope(pila_original));
    lista_desapilar(pila_original);
}


void restaurar_gimnasio(lista_t* pila_aux, lista_t* entrenadores){
    while(!lista_vacia(pila_aux))
        trasladar_ultimo_entrenador(pila_aux, entrenadores);
}




int enfrentar_gimnasio(personaje_t* jugador, gimnasio_t* gimnasio, bool es_simulacion){
    if(!jugador || !gimnasio){
        return ERROR;
    }

    lista_t* pila_aux_entrenadores = lista_crear();
    bool fue_derrotado = false;
    int resultado_duelo = 0;
    entrenador_t* entrenador_actual = NULL;

    while(!lista_vacia(gimnasio->entrenadores) && !fue_derrotado){
        
        entrenador_actual = lista_tope(gimnasio->entrenadores);
        
        if(!es_simulacion){
            menu_gimnasio(jugador, gimnasio);
            printf(NORMAL"\nAhora te enfrentarás con %s\n", entrenador_actual->nombre);
        }
        
        resultado_duelo = duelo_pokemon(jugador->equipo, entrenador_actual->equipo, gimnasio->reglas_de_batalla, es_simulacion);

        if(resultado_duelo==VICTORIA){
            if(!es_simulacion)
                printf(VERDE"Venciste a %s\n", entrenador_actual->nombre);
            trasladar_ultimo_entrenador(gimnasio->entrenadores, pila_aux_entrenadores);
        }else{
            printf(ROJO"Fuiste derrotado por %s\n", entrenador_actual->nombre);
            fue_derrotado = true;
        }
        printf(NORMAL"");
    }

    if(!fue_derrotado && !es_simulacion)
        menu_victoria(jugador, lista_tope(pila_aux_entrenadores), false);

    restaurar_gimnasio(pila_aux_entrenadores, gimnasio->entrenadores);
    lista_destruir(pila_aux_entrenadores);

    if(fue_derrotado && !es_simulacion){
        if(menu_derrota(jugador)==REINTENTAR)
            return enfrentar_gimnasio(jugador, gimnasio, es_simulacion);
    }
    

    if(fue_derrotado)
        return DERROTA;
    return VICTORIA;
}
