
#include "personaje.h"

bool leer_linea_personaje(FILE* archivo_personaje, personaje_t* personaje, int cant_items_esperados){
    char nombre_personaje[MAX_NOMBRE];
    char ciudad_natal_personaje[MAX_NOMBRE];
    int leidos = fscanf(archivo_personaje, FORMATO_LECTURA_PERSONAJE, nombre_personaje, ciudad_natal_personaje);
    if(leidos != cant_items_esperados){
        printf("La cantidad de elementos leidos en la primera linea del archivo personaje no es la esperada\n");
        return false;
    }
    strcpy(personaje->nombre, nombre_personaje);
    strcpy(personaje->ciudad_natal, ciudad_natal_personaje);
    return true;
}


bool agregar_nuevo_pokemon_personaje(personaje_t* personaje, pokemon_t* pokemon){
    if(!personaje){
        free(pokemon);
        return false;
    }

    if(!personaje->equipo)
        personaje->equipo = lista_crear();

    if(!personaje->equipo){
        free(pokemon);
        return false;
    }


    if(!personaje->capturados)
        personaje->capturados = lista_crear();

    if(!personaje->capturados){
        free(pokemon);
        lista_destruir(personaje->equipo);
        return false;
    }

    if(lista_elementos(personaje->equipo)<MAX_EQUIPO){
        if(lista_encolar(personaje->equipo, pokemon)==ERROR){
            free(pokemon);
            return false;
        }
    }else{
        if(lista_encolar(personaje->capturados, pokemon)==ERROR){
            free(pokemon);
            return false;
        }
    }
    return true;
}


bool leer_linea_pokemon_personaje(FILE* archivo_personaje, personaje_t* personaje, int cant_items_esperados){
    pokemon_t* nuevo_pkm = calloc(1, sizeof(pokemon_t));
    int leidos = fscanf(archivo_personaje, FORMATO_LECTURA_POKEMON, nuevo_pkm->nombre, nuevo_pkm->tipo, &(nuevo_pkm->velocidad), &(nuevo_pkm->ataque), &(nuevo_pkm->defensa));
    if(leidos != cant_items_esperados){
        free(nuevo_pkm);
        return false;
    }
    return agregar_nuevo_pokemon_personaje(personaje, nuevo_pkm);
}


personaje_t* leer_archivo_personaje(FILE* archivo_personaje){

    personaje_t* personaje = calloc(1, sizeof(personaje_t));
    if(!personaje){
        printf("Error al reservar memoria para el personaje principal\n");
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

    if(*jugador)
        liberar_jugador(*jugador);

    *jugador = leer_archivo_personaje(archivo_personaje);

    fclose(archivo_personaje);
    return;
}