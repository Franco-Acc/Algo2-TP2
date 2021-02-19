
#include "gimnasio.h"
#include "batallas.h"
#include "menus.h"
#include "interfaz.h"

//Determina que funcion de batalla se empleará a partir del valor recibido (se supone que el valor es el que esta en el archivo de gimnasio)
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

//Lee la primera linea del archivo de gimnasio y carga los datos al gimnasio pasado que ya esta en memoria.
//Si la lectura es correcta devuelve true y si no lee la cantidad de parametros esperados devuelve false.
bool leer_linea_gimnasio(FILE* archivo_gimnasio, gimnasio_t* un_gimnasio, int cant_items_esperados){
	if(!archivo_gimnasio || !un_gimnasio || cant_items_esperados<1){
		printf(ROJO"Error en los parametros a la hora de leerla primera linea del archivo del gimnasio\n");
		printf(NORMAL"");
		return false;
	}
    size_t reglas;
    int leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_GIMNASIO, un_gimnasio->nombre, &(un_gimnasio->dificultad), &reglas);
    un_gimnasio->reglas_de_batalla = determinar_funcion(reglas);
    if(leidos != cant_items_esperados){
        printf(ROJO"La cantidad de elementos leidos en la primera linea del archivo gimnasio no es la esperada\n");
        printf(NORMAL"");
        return false;
    }
    return true;
}


//Agrega un nuevo entrenador al gimnasio dado.
//Si el gimnasio no tenia ningun entrenador crea la pila de entrenadores necesaria, de existir solo se apila.
bool agregar_nuevo_entrenador(gimnasio_t* gimnasio, char nombre_entrenador[]){
	if(!gimnasio){
		printf(ROJO"El gimnasio no existe!! No se le puede agregar un entrenador\n");
		printf(NORMAL"");
		return false;
	}

    entrenador_t* nuevo_entrenador = calloc(1, sizeof(entrenador_t));
    if(!nuevo_entrenador){
        return false;
    }
    
    strcpy(nuevo_entrenador->nombre, nombre_entrenador);
    
    if(!gimnasio->entrenadores){
        gimnasio->entrenadores = lista_crear();
    }

    if(lista_apilar(gimnasio->entrenadores, nuevo_entrenador)==ERROR){
    	printf(ROJO"Error al intentar apilar un nuevo entrenador al gimnasio\n");
    	printf(NORMAL"");
        return false;
    }

    return true;
}


//Lee la linea de entrenador del archivo de gimnasio y carga los datos al gimnasio pasado que ya esta en memoria.
//Si la lectura es correcta devuelve true y si no lee la cantidad de parametros esperados devuelve false.
bool leer_linea_entrenador(FILE* archivo_gimnasio, gimnasio_t* un_gimnasio, int cant_items_esperados){
	if(!archivo_gimnasio || !un_gimnasio || cant_items_esperados<1){
		printf(ROJO"Error en los parametros a la hora de leer una linea del archivo del gimnasio\n");
		printf(NORMAL"");
		return false;
	}
    char nombre_entrenador[MAX_NOMBRE];
    int leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_ENTRENADOR, nombre_entrenador);
    if(leidos != cant_items_esperados)
        return false;
    return agregar_nuevo_entrenador(un_gimnasio, nombre_entrenador);
}


//Agrega un nuevo pokemon al entrenador dado, devuelve true si pudo hacerlo o false en caso de error.
//Si el entrenador no tenia ningun pokemon crea la lista necesaria para el equipo, de existir solo se encola.
bool agregar_nuevo_pokemon(entrenador_t* entrenador, pokemon_t* pokemon){
    if(!entrenador || !pokemon){
    	printf(ROJO"No se puede agregar un nuevo pokemon al entrenador porque este y/o el pokemon no existen\n");
    	printf(NORMAL"");
        free(pokemon);
        return false;
    }

    if(!entrenador->equipo){
        entrenador->equipo = lista_crear();
    }

    if(!entrenador->equipo){
    	printf(ROJO"Error al crear la lista para el equipo del entrenador sin pokemones\n");
    	printf(NORMAL"");
        free(pokemon);
        return false;
    }

    if(lista_elementos(entrenador->equipo)>=MAX_EQUIPO){
    	printf(ROJO"No se le pueden colocar mas pokemones a este entrenador, su equipo esta lleno!!!\n Se intentará seguir con la carga saltando este pokemon\n");
    	printf(NORMAL"");
        free(pokemon);
        return true;
    }

    if(lista_elementos(entrenador->equipo)<MAX_EQUIPO){
        if(lista_encolar(entrenador->equipo, pokemon)==ERROR){
        	printf(ROJO"Error al tratar de insertar el nuevo pokemon al equipo del entrenador\n");
    		printf(NORMAL"");
            free(pokemon);
            return false;
        }
    }
    return true;
}


//Lee la linea de pokemon del archivo de gimnasio y carga los datos al gimnasio pasado que ya esta en memoria.
//Si la lectura es correcta devuelve true y si no lee la cantidad de parametros esperados devuelve false.
bool leer_linea_pokemon(FILE* archivo_gimnasio, gimnasio_t* un_gimnasio, int cant_items_esperados){
	if(!archivo_gimnasio || !un_gimnasio || cant_items_esperados<1){
		printf(ROJO"Error en los parametros a la hora de leer una linea del archivo del gimnasio\n");
		printf(NORMAL"");
		return false;
	}
    pokemon_t* nuevo_pkm = calloc(1, sizeof(pokemon_t));
    int leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_POKEMON, nuevo_pkm->nombre, nuevo_pkm->tipo, &(nuevo_pkm->velocidad), &(nuevo_pkm->ataque), &(nuevo_pkm->defensa));
    if(leidos != cant_items_esperados){
        if(!feof(archivo_gimnasio)){
            printf(ROJO"La cantidad de elementos leidos en la linea de pokemon del archivo gimnasio no es la esperada\n");
            printf(NORMAL"");
        }
        free(nuevo_pkm);
        return false;
    }
    return agregar_nuevo_pokemon(lista_tope(un_gimnasio->entrenadores), nuevo_pkm);
}


//Carga la informacion del archivo gimnasio a un gimnasio en el heap (reserva la memoria necesario para ello)
//Devuelve el puntero al gimnasio en memoria o NULL en caso de Error la reservar la memoria.
//En caso de Error en la lectura del archivo se devolvera el gimnasio con la informacion cargada hasta donde se haya podido leer.
gimnasio_t* leer_archivo_gimnasio(FILE* archivo_gimnasio){

    gimnasio_t* un_gimnasio = calloc(1, sizeof(gimnasio_t));
    if(!un_gimnasio){
        printf(ROJO"Error al reservar memoria para el gimnasio\n");
        printf(NORMAL"");
        return NULL;
    }

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

/*
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
*/


//Carga la informacion del archivo gimnasio pasado a un gimnasio en el heap y lo inserta en el heap pasado.
//En caso de Error en la lectura del archivo se insertará en el heap gimnasio con la informacion cargada hasta donde se haya podido leer.
void cargar_gimnasio(heap_t* heap, char* direccion_gimasio){
    if(!heap ||!direccion_gimasio)
        return;

    FILE* archivo_gimnasio = fopen(direccion_gimasio, "r");
    if(!archivo_gimnasio){
        printf("Error al abrir el archivo de gimnasio seleccionado\n");
        return;
    }

    gimnasio_t* nuevo_gimnasio = leer_archivo_gimnasio(archivo_gimnasio);
    fclose(archivo_gimnasio);

    if(!nuevo_gimnasio){
        printf("Error al reservar memoria para el gimnasio\n");
        return;
    }

    if(heap_insertar(heap, nuevo_gimnasio)==ERROR){
        destructor_gimnasios(nuevo_gimnasio);
        printf("Error al insertar el gimnasio en el HEAP\n");
        return;
    }
    
    return;
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


//Aumneta en uno el bonus del pokemon pasado, siempre y cuando no supere el maximo establecido.
void actualizar_estadisticas_pokemon(pokemon_t* pokemon){
	if(!pokemon){
		printf(ROJO"NO existe el pokemon!! No se pueden actualizar sus estadísticas!!!\n");
		printf(NORMAL"");
		return;
	}
    if(pokemon->bonus < MAX_BONUS){
       pokemon->bonus++;
    }
}


//Enfrenta al jugador con el entrenador y devuelve le resultado del encuentro.
//Solo muestra salidas por pantalla si no es una simulacion.
int duelo_pokemon(lista_t* equipo_jugador, lista_t* equipo_entrenador, funcion_batalla reglas_de_batalla, bool es_simulacion){
    if(!equipo_jugador || !equipo_entrenador || !reglas_de_batalla){
    	printf(ROJO"Error en los parametros a la hora de enfrentarse a un entrenador\n");
		printf(NORMAL"");
        return ERROR;
    }

    lista_iterador_t* iterador_equipo_jugador = lista_iterador_crear(equipo_jugador);
    lista_iterador_t* iterador_equipo_entrenador = lista_iterador_crear(equipo_entrenador);

    int resultado_combate = 0;
    int resultado_duelo = 0;

    while(lista_iterador_tiene_siguiente(iterador_equipo_jugador) && lista_iterador_tiene_siguiente(iterador_equipo_entrenador) && resultado_combate!=ERROR){
        
        resultado_combate = reglas_de_batalla(lista_iterador_elemento_actual(iterador_equipo_jugador), lista_iterador_elemento_actual(iterador_equipo_entrenador));
        if(!es_simulacion)
            menu_combate(lista_iterador_elemento_actual(iterador_equipo_jugador), lista_iterador_elemento_actual(iterador_equipo_entrenador), resultado_combate);
        
        if(resultado_combate==GANO_PRIMERO){
            actualizar_estadisticas_pokemon(lista_iterador_elemento_actual(iterador_equipo_jugador));
            lista_iterador_avanzar(iterador_equipo_entrenador);
        }else if(resultado_combate==GANO_SEGUNDO){
            lista_iterador_avanzar(iterador_equipo_jugador);
        }
    }

    if(lista_iterador_tiene_siguiente(iterador_equipo_jugador)){
        resultado_duelo = VICTORIA;
    }else{
        resultado_duelo = DERROTA;
    }
    
    lista_iterador_destruir(iterador_equipo_jugador);
    lista_iterador_destruir(iterador_equipo_entrenador);
    
    if(resultado_combate==ERROR)
    	return ERROR;
    return resultado_duelo;
}


//
bool eliminar_entrenador_tope(lista_t* entrenadores){
	if(lista_elementos(entrenadores)>1){
	    liberar_entrenador(lista_tope(entrenadores));
	    lista_desapilar(entrenadores);
	    return false;
	}
	return true;
}

int enfrentar_gimnasio(personaje_t* jugador, gimnasio_t* gimnasio, bool es_simulacion){
    if(!jugador || !gimnasio){
    	printf(ROJO"Error en los parametros a la hora de enfrentarse a un gimnasio\n");
		printf(NORMAL"");
        return ERROR;
    }
    if(!(gimnasio->entrenadores)){
    	printf(ROJO"Error al enfrentarse a un gimnasio, NO TIENE PILA DE ENTRENADORES\n");
		printf(NORMAL"");
        return ERROR;
    }
    if(lista_vacia(gimnasio->entrenadores)){
    	printf(ROJO"Error al enfrentarse a un gimnasio, LA PILA DE ENTRENADORES ESTA VACIA\n");
		printf(NORMAL"");
        return ERROR;
    }

    bool fue_derrotado = false;
    bool vencio_al_lider = false;
    int resultado_duelo = 0;
    entrenador_t* entrenador_actual = NULL;

    while(!vencio_al_lider && !fue_derrotado){
        
        entrenador_actual = lista_tope(gimnasio->entrenadores);
        
        if(!es_simulacion){
            menu_gimnasio(jugador, gimnasio);
            printf(NORMAL"\nAhora te enfrentarás con %s\n", entrenador_actual->nombre);
        }
        
        resultado_duelo = duelo_pokemon(jugador->equipo, entrenador_actual->equipo, gimnasio->reglas_de_batalla, es_simulacion);

        if(resultado_duelo==VICTORIA){
            if(!es_simulacion){
                printf(VERDE"Venciste a %s\n", entrenador_actual->nombre);
            }
            vencio_al_lider = eliminar_entrenador_tope(gimnasio->entrenadores);
        }else if(resultado_duelo==DERROTA){
            printf(ROJO"Fuiste derrotado por %s\n", entrenador_actual->nombre);
            fue_derrotado = true;
        }else{
        	printf(ROJO"Ha ocurrido un error durante uno de los combates, el duelo queda suspendido.\n");
        	printf(NORMAL"");
        	return ERROR;
        }
        printf(NORMAL"");
    }


    if(vencio_al_lider && !es_simulacion){
        menu_victoria(jugador, lista_tope(gimnasio->entrenadores), false);
    }


    if(fue_derrotado && !es_simulacion){
        if(menu_derrota(jugador)==REINTENTAR)
            return enfrentar_gimnasio(jugador, gimnasio, es_simulacion);
    }
    

    if(fue_derrotado){
        return DERROTA;
    }
    return VICTORIA;
}
