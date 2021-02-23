
#include "personaje.h"

//Lee la primera linea del archivo de personaje y carga los datos al personaje pasado que ya esta en memoria.
//Si la lectura es correcta devuelve true y si no lee la cantidad de parametros esperados devuelve false.
bool leer_linea_personaje(FILE* archivo_personaje, personaje_t* personaje, int cant_items_esperados){
    if(!archivo_personaje || !personaje || cant_items_esperados<1){
        imp_err_falta_argumento_en_leer_linea_personaje();
        return false;
    }
    char nombre_personaje[MAX_NOMBRE];
    char ciudad_natal_personaje[MAX_NOMBRE];
    int leidos = fscanf(archivo_personaje, FORMATO_LECTURA_PERSONAJE, nombre_personaje, ciudad_natal_personaje);
    if(leidos != cant_items_esperados){
        imp_err_cant_items_lectura_primera_linea_personaje();
        return false;
    }
    strcpy(personaje->nombre, nombre_personaje);
    strcpy(personaje->ciudad_natal, ciudad_natal_personaje);
    return true;
}


//Agrega un nuevo pokemon al personaje dado, devuelve true si pudo hacerlo o false en caso de error.
//Si el personaje no tenia ningun pokemon crea la lista necesaria para el equipo, de existir solo se encola.
//Si el equipo del personaje esta lleno se hace lo mismo pero con capturados (caja).
bool agregar_nuevo_pokemon_personaje(personaje_t* personaje, pokemon_t* pokemon){
    if(!personaje || !pokemon){
        imp_err_falta_argumento_en_agregar_pokemon()
        free(pokemon);
        return false;
    }

    if(!personaje->equipo){
        personaje->equipo = lista_crear();
    }

    if(!personaje->equipo){
        imp_err_crear_lista();
        free(pokemon);
        return false;
    }


    if(!personaje->capturados){
        personaje->capturados = lista_crear();
    }

    if(!personaje->capturados){
        imp_err_crear_lista();
        free(pokemon);
        lista_destruir(personaje->equipo);
        return false;
    }

    if(lista_elementos(personaje->equipo)<MAX_EQUIPO){
        if(lista_encolar(personaje->equipo, pokemon)==ERROR){
            imp_err_insertar_pkmn();
            free(pokemon);
            return false;
        }
    }else{
        if(lista_encolar(personaje->capturados, pokemon)==ERROR){
            imp_err_insertar_pkmn();
            free(pokemon);
            return false;
        }
    }
    return true;
}

//Lee la linea de pokemon del archivo de personaje y carga los datos al personaje pasado que ya esta en memoria.
//Si la lectura es correcta devuelve true y si no lee la cantidad de parametros esperados devuelve false.
bool leer_linea_pokemon_personaje(FILE* archivo_personaje, personaje_t* personaje, int cant_items_esperados){
    if(!archivo_personaje || !personaje || cant_items_esperados<1){
        imp_err_falta_argumento_en_leer_linea_personaje()
        return false;
    }
    pokemon_t* nuevo_pkm = calloc(1, sizeof(pokemon_t));
    int leidos = fscanf(archivo_personaje, FORMATO_LECTURA_POKEMON, nuevo_pkm->nombre, nuevo_pkm->tipo, &(nuevo_pkm->velocidad), &(nuevo_pkm->ataque), &(nuevo_pkm->defensa));
    if(leidos != cant_items_esperados){
        if(!feof(archivo_personaje)){
            imp_err_cant_items_lectura_linea_pokemon_personaje();
        }
        free(nuevo_pkm);
        return false;
    }
    return agregar_nuevo_pokemon_personaje(personaje, nuevo_pkm);
}


//Carga la informacion del archivo personaje a un personaje en el heap (reserva la memoria necesario para ello).
//Devuelve el puntero al persoanje en memoria o NULL en caso de Error la reservar la memoria.
//En caso de Error en la lectura del archivo se devolvera el puntero al personaje con la informacion cargada hasta donde se haya podido leer.
personaje_t* leer_archivo_personaje(FILE* archivo_personaje){

    personaje_t* personaje = calloc(1, sizeof(personaje_t));
    if(!personaje){
        imp_err_reserva_de_memoria_personaje();
        return NULL;
    }

    bool todo_ok = true;
    char tipo_linea = ENTRENADOR;

    leer_primera_letra_de_linea(archivo_personaje, &tipo_linea);
    todo_ok = leer_linea_personaje(archivo_personaje, personaje, CANT_ITEMS_PERSONAJE);  //la primera linea siempre debe ser la del personaje
    
    while(todo_ok){
        leer_primera_letra_de_linea(archivo_personaje, &tipo_linea);

        if(tipo_linea == POKEMON){
            todo_ok = leer_linea_pokemon_personaje(archivo_personaje, personaje, CANT_ITEMS_POKEMON);
        }else{
            todo_ok = false;
        }
    }
    return personaje;
}


void cargar_personaje(personaje_t** jugador){

    imp_msj_intro_carga_personaje();  
    char direccion_personaje[MAX_DIRECCION];
    pedir_direccion(direccion_personaje);


    FILE* archivo_personaje = fopen(direccion_personaje, "r");
    if(!archivo_personaje){
        imp_err_abrir_archivo();
        return;
    }

    if(*jugador){
        liberar_jugador(*jugador);
    }

    (*jugador) = leer_archivo_personaje(archivo_personaje);

    fclose(archivo_personaje);
    return;
}