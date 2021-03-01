
#include "gimnasio.h"
#include "batallas.h"
#include "menus.h"
#include "interfaz.h"

//Determina que funcion de batalla se empleará a partir del valor recibido (se supone que el valor es el que esta en el archivo de gimnasio)
funcion_batalla determinar_funcion(size_t n){
    if(n==1){
        return funcion_batalla_1;
    }else if(n==2){
        return funcion_batalla_2;
    }else if(n==3){
        return funcion_batalla_3;
    }else if(n==4){
        return funcion_batalla_4;
    }else{
        return funcion_batalla_5;
    }
}


//Lee la primera letra de una linea de un archivo de texto y la almacena en la varaibel pasada por referencia.
bool leer_primera_letra_de_linea_gimnasio(FILE* archivo, char* letra){
    if(!archivo || !letra)
        return false;
   int leidos = fscanf(archivo, FORMATO_LECTURA_PRIMERA_LETRA, letra);
   if(leidos!=1 || leidos==EOF){
        return false;
   }
   return true;
}


//Lee la primera linea del archivo de gimnasio y carga los datos al gimnasio pasado que ya esta en memoria.
//Si la lectura es correcta devuelve true y si no lee la cantidad de parametros esperados devuelve false.
bool leer_linea_gimnasio(FILE* archivo_gimnasio, gimnasio_t* un_gimnasio, int cant_items_esperados){
	if(!archivo_gimnasio || !un_gimnasio || cant_items_esperados<1){
		imp_err_falta_argumento_en_leer_linea_gimnasio();
		return false;
	}
    size_t reglas;
    int leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_GIMNASIO, un_gimnasio->nombre, &(un_gimnasio->dificultad), &reglas);
    un_gimnasio->reglas_de_batalla = determinar_funcion(reglas);
    if(leidos != cant_items_esperados){
        imp_err_cant_items_lectura_linea_gimnasio();
        return false;
    }
    return true;
}


//Agrega un nuevo entrenador al gimnasio dado.
//Si algo falla devuelve false, si todo sale bien devuelve true.
bool agregar_nuevo_entrenador(gimnasio_t* gimnasio, char nombre_entrenador[]){
	if(!gimnasio){
		imp_err_falta_gimnasio();
		return false;
	}

    entrenador_t* nuevo_entrenador = calloc(1, sizeof(entrenador_t));
    if(!nuevo_entrenador){
        imp_err_reserva_de_memoria_entrenador();
        return false;
    }

    nuevo_entrenador->equipo = lista_crear();
    if(!nuevo_entrenador->equipo){
        imp_err_crear_lista();
        free(nuevo_entrenador);
        return false;
    }
    
    strcpy(nuevo_entrenador->nombre, nombre_entrenador);
 
    if(lista_apilar(gimnasio->entrenadores, nuevo_entrenador)==ERROR){
    	imp_err_insertar_entrenador();
        liberar_entrenador(nuevo_entrenador);
        return false;
    }

    return true;
}


//Lee la linea de entrenador del archivo de gimnasio y carga los datos al gimnasio pasado que ya esta en memoria.
//Si la lectura es correcta devuelve true y si no lee la cantidad de parametros esperados devuelve false.
bool leer_linea_entrenador(FILE* archivo_gimnasio, gimnasio_t* un_gimnasio, int cant_items_esperados){
	if(!archivo_gimnasio || !un_gimnasio || cant_items_esperados<1){
		imp_err_falta_argumento_en_leer_linea_gimnasio();
		return false;
	}
    char nombre_entrenador[MAX_NOMBRE];
    int leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_ENTRENADOR, nombre_entrenador);
    if(leidos != cant_items_esperados){
        imp_err_cant_items_lectura_linea_entrenador();
        return false;
    }
    return agregar_nuevo_entrenador(un_gimnasio, nombre_entrenador);
}


//Agrega un nuevo pokemon al entrenador dado, devuelve true si pudo hacerlo o false en caso de error.
bool agregar_nuevo_pokemon_entrenador(entrenador_t* entrenador, pokemon_t* pokemon){
    if(!entrenador || !pokemon){
    	imp_err_falta_argumento_en_agregar_pokemon();
        free(pokemon);
        return false;
    }

    if(lista_elementos(entrenador->equipo)>=MAX_EQUIPO){
    	imp_err_equipo_lleno(pokemon->nombre, entrenador->nombre);
        free(pokemon);
        return true;
    }

    if(lista_elementos(entrenador->equipo)<MAX_EQUIPO){
        if(lista_encolar(entrenador->equipo, pokemon)==ERROR){
        	imp_err_insertar_pkmn();
            free(pokemon);
            return false;
        }
    }
    return true;
}


//Lee la linea de pokemon del archivo de gimnasio y carga los datos al gimnasio pasado que ya esta en memoria.
//Si la lectura es correcta devuelve true y si no lee la cantidad de parametros esperados devuelve false.
bool leer_linea_pokemon_gimnasio(FILE* archivo_gimnasio, gimnasio_t* un_gimnasio, int cant_items_esperados){
	if(!archivo_gimnasio || !un_gimnasio || cant_items_esperados<1){
		imp_err_falta_argumento_en_leer_linea_pkm();
		return false;
	}
    
    pokemon_t* nuevo_pkm = calloc(1, sizeof(pokemon_t));
    if(!nuevo_pkm){
        imp_err_reserva_de_memoria_pkmn();
        return false;
    }

    int leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_POKEMON, nuevo_pkm->nombre, nuevo_pkm->tipo, &(nuevo_pkm->velocidad), &(nuevo_pkm->ataque), &(nuevo_pkm->defensa));
    if(leidos != cant_items_esperados){
        if(!feof(archivo_gimnasio)){
            imp_err_cant_items_lectura_linea_pokemon();
        }
        free(nuevo_pkm);
        return false;
    }

    if(!es_pkm_valido(nuevo_pkm)){
        imp_err_pkm_tipo_invalido(nuevo_pkm);
        strcpy(nuevo_pkm->tipo, AGUA);          //Con esto en caso de haber ingresado un pokemon de tipo invalido se cambiara su tipo a uno por defecto, agua. De esta forma evito tirar todo el pokemon a la basura solo porque el tipo es incorrecto.
    }

    return agregar_nuevo_pokemon_entrenador(lista_tope(un_gimnasio->entrenadores), nuevo_pkm);
}


//Carga la informacion del archivo gimnasio a un gimnasio en el heap (reserva la memoria necesario para ello)
//Devuelve el puntero al gimnasio en memoria o NULL en caso de Error en la reservar la memoria.
//En caso de Error en la lectura del archivo se devolvera el gimnasio con la informacion cargada hasta donde se haya podido leer.
gimnasio_t* leer_archivo_gimnasio(FILE* archivo_gimnasio){
    if(!archivo_gimnasio){
        return NULL;
    }

    gimnasio_t* un_gimnasio = calloc(1, sizeof(gimnasio_t));
    if(!un_gimnasio){
        imp_err_reserva_de_memoria_gimnasio();
        return NULL;
    }

    un_gimnasio->entrenadores = lista_crear();
    if(!un_gimnasio->entrenadores){
        imp_err_crear_lista();
        free(un_gimnasio);
        return NULL;
    }

    bool todo_ok = true;
    char tipo_linea = GIMNASIO; //La primera linea siempre deberia ser la del gimnasio
    

    todo_ok = leer_primera_letra_de_linea_gimnasio(archivo_gimnasio, &tipo_linea);
    
    while(todo_ok){
        if(tipo_linea == GIMNASIO){
            todo_ok = leer_linea_gimnasio(archivo_gimnasio, un_gimnasio, CANT_ITEMS_GIMNASIO);  
        }else if((tipo_linea == ENTRENADOR) || (tipo_linea == LIDER)){
            todo_ok = leer_linea_entrenador(archivo_gimnasio, un_gimnasio, CANT_ITEMS_ENTRENADOR);
        }else if(tipo_linea == POKEMON){
            todo_ok = leer_linea_pokemon_gimnasio(archivo_gimnasio, un_gimnasio, CANT_ITEMS_POKEMON);
        }else{
            todo_ok = false;
        }

        if(todo_ok){
            todo_ok = leer_primera_letra_de_linea_gimnasio(archivo_gimnasio, &tipo_linea);
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
        return imp_err_abrir_archivo();
    }

    gimnasio_t* nuevo_gimnasio = leer_archivo_gimnasio(archivo_gimnasio);
    fclose(archivo_gimnasio);

    if(!nuevo_gimnasio){
        return;
    }

    if(heap_insertar(heap, nuevo_gimnasio)==ERROR){
        destructor_gimnasios(nuevo_gimnasio);
        return imp_err_insertar_gimnasio();
    }
    
    return imp_msj_carga_exitosa();
}


//Pide al ususario la direccion de los archivos de gimnasio que quiera cargar al programa, y carga dichos archivos.
void cargar_gimnasios(heap_t* gimnasios){
    
    char direccion_gimasio[MAX_DIRECCION];

    imp_msj_intro_carga_gimnasio();
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
		imp_err_falta_pokemon();
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
    	imp_err_falta_argumento_en_duelo();
        return ERROR;
    }

    lista_iterador_t* iterador_equipo_jugador = lista_iterador_crear(equipo_jugador);
    lista_iterador_t* iterador_equipo_entrenador = lista_iterador_crear(equipo_entrenador);

    if(!iterador_equipo_jugador || !iterador_equipo_entrenador){
        lista_iterador_destruir(iterador_equipo_jugador);
        lista_iterador_destruir(iterador_equipo_entrenador);
        imp_err_crear_iterador_lista();
        return ERROR;
    }

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
        }else{
            imp_err_falta_pokemon();
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


//Elimina el ultimo entrenador de la lista, liberando la memeoria reservada. y devulviendo false (indica que  no se acabaron los entreandores de la lista dada).
//En el momento en que no haya mas entrenadores que eliminar devuelve true, indicando que se acabaron los entrenadores de la lista pasada.
bool eliminar_entrenador_tope(lista_t* entrenadores){
	if(lista_elementos(entrenadores)>1){
	    liberar_entrenador(lista_tope(entrenadores));
	    lista_desapilar(entrenadores);
	    return false;
	}
	return true;
}


//Enfrenta al personaje del usuario con todos los entrenadores del gimnasio pasado hasta que los haya vencido a todos o se haya rendido.
//Si no es una simulacion, irá mostrando los menus y salidas por panatallas correspondientes.
//Si es una simulacion, solo mostrará por pantalla el mensaje de derrota tras haber perdido ante unn entrenador.
int enfrentar_gimnasio(personaje_t* jugador, gimnasio_t* gimnasio, bool es_simulacion){
    if(!jugador || !gimnasio){
    	imp_err_falta_argumento_en_enfrentar_gimnasio();
        return ERROR;
    }

    bool fue_derrotado = false;
    bool vencio_al_lider = lista_vacia(gimnasio->entrenadores);
    int resultado_duelo = 0;
    entrenador_t* entrenador_actual = NULL;

    while(!vencio_al_lider && !fue_derrotado){
        
        entrenador_actual = lista_tope(gimnasio->entrenadores);
        
        if(!es_simulacion){
            menu_gimnasio(jugador, gimnasio);
            imp_sig_entrenador_a_enfrentar(entrenador_actual->nombre, es_simulacion);
        }
        
        resultado_duelo = duelo_pokemon(jugador->equipo, entrenador_actual->equipo, gimnasio->reglas_de_batalla, es_simulacion);

        if(resultado_duelo==VICTORIA){
            imp_entrenador_vencido(entrenador_actual->nombre, es_simulacion);
            vencio_al_lider = eliminar_entrenador_tope(gimnasio->entrenadores);
        }else if(resultado_duelo==DERROTA){
            imp_entrenador_me_vencio(entrenador_actual->nombre);
            fue_derrotado = true;
        }else{
        	imp_error_en_duelo();
        	return ERROR;
        }
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
