
#include "personaje.h"

//Lee la primera linea del archivo de personaje y carga los datos al personaje pasado que ya esta en memoria.
//Si la lectura es correcta devuelve true y si no lee la cantidad de parametros esperados devuelve false.
bool leer_linea_personaje(FILE* archivo_personaje, personaje_t* personaje, int cant_items_esperados){
    if(!archivo_personaje || !personaje || cant_items_esperados<1){
        printf(ROJO"Error en los parametros a la hora de leer la primera linea del archivo del personaje\n");
        printf(NORMAL"");
        return false;
    }
    char nombre_personaje[MAX_NOMBRE];
    char ciudad_natal_personaje[MAX_NOMBRE];
    int leidos = fscanf(archivo_personaje, FORMATO_LECTURA_PERSONAJE, nombre_personaje, ciudad_natal_personaje);
    if(leidos != cant_items_esperados){
        printf(ROJO"La cantidad de elementos leidos en la primera linea del archivo personaje no es la esperada\n");
        printf(NORMAL"");
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
        printf(ROJO"No se puede agregar un nuevo pokemon al jugador porque este y/o el pokemon no existen\n");
        printf(NORMAL"");
        free(pokemon);
        return false;
    }

    if(!personaje->equipo){
        personaje->equipo = lista_crear();
    }

    if(!personaje->equipo){
        printf(ROJO"Error al crear la lista para el equipo del jugador sin pokemones\n");
        printf(NORMAL"");
        free(pokemon);
        return false;
    }


    if(!personaje->capturados){
        personaje->capturados = lista_crear();
    }

    if(!personaje->capturados){
        printf(ROJO"Error al crear la lista para los capturados del jugador\n");
        printf(NORMAL"");
        free(pokemon);
        lista_destruir(personaje->equipo);
        return false;
    }

    if(lista_elementos(personaje->equipo)<MAX_EQUIPO){
        if(lista_encolar(personaje->equipo, pokemon)==ERROR){
            printf(ROJO"Error al tratar de insertar el nuevo pokemon al equipo del jugador\n");
            printf(NORMAL"");
            free(pokemon);
            return false;
        }
    }else{
        if(lista_encolar(personaje->capturados, pokemon)==ERROR){
            printf(ROJO"Error al tratar de insertar el nuevo pokemon en la caja del jugador\n");
            printf(NORMAL"");
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
        printf(ROJO"Error en los parametros a la hora de leer una linea del archivo del personaje\n");
        printf(NORMAL"");
        return false;
    }
    pokemon_t* nuevo_pkm = calloc(1, sizeof(pokemon_t));
    int leidos = fscanf(archivo_personaje, FORMATO_LECTURA_POKEMON, nuevo_pkm->nombre, nuevo_pkm->tipo, &(nuevo_pkm->velocidad), &(nuevo_pkm->ataque), &(nuevo_pkm->defensa));
    if(leidos != cant_items_esperados){
        if(!feof(archivo_personaje)){
            printf(ROJO"La cantidad de elementos leidos en la linea de pokemon del archivo personaje no es la esperada\n");
            printf(NORMAL"");
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
        printf(ROJO"Error al reservar memoria para el personaje principal\n");
        printf(NORMAL"");
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

    printf("Para ingreasar ingresar al personaje jugable indique la direccion del archivo, por ejemplo Personajes/Kanto/Ash.txt\n");
    printf("En caso de ocurrir algun error, se cargará la informacion del personaje que se pueda\n");

    char direccion_personaje[MAX_DIRECCION];
    pedir_direccion(direccion_personaje);


    FILE* archivo_personaje = fopen(direccion_personaje, "r");
    if(!archivo_personaje){
        printf("Error al abrir el archivo de personaje seleccionado\n");
        return;
    }

    if(*jugador){
        liberar_jugador(*jugador);
    }

    (*jugador) = leer_archivo_personaje(archivo_personaje);

    fclose(archivo_personaje);
    return;
}