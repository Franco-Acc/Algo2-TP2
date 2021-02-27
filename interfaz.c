#include "interfaz.h"



//Mensaje de error al intentar añadir medalla.
void imp_err_aniadir_medalla(){
	printf(ROJO"No existe el jugador, no se puede aniadir medalla!!\n");
    printf(NORMAL"");
}

//Mensaje de error al intentar abrir el archivo.
void imp_err_abrir_archivo(){
     printf(ROJO"Error al abrir el archivo seleccionado\n");
     printf(NORMAL"");
}

//Mensaje de error al reservar memoria para las estructuras del programa.
void imp_err_crear_estructuras(){
	printf(ROJO"Error en la reserva de memoria para el heap de gimnasios\n");
    printf(NORMAL"");
}

//Mensaje de error al fallar la creacion de una lista.
void imp_err_crear_lista(){
    printf(ROJO"Error al crear la lista\n");
    printf(NORMAL"");
}

//Mensaje de error al fallar la creacion de un iterador externo de lista.
void imp_err_crear_iterador_lista(){
    printf(ROJO"Error al crear Iterador Externo de lista\n");
    printf(NORMAL"");
}





//Mensaje de error al faltar uno de los argumentos necesarios para enfrentar un gimnasio.
void imp_err_falta_argumento_en_enfrentar_gimnasio(){
    printf(ROJO"Error en los parametros a la hora de enfrentarse a un gimnasio\n");
    printf(NORMAL"");
}

//Mensaje de error al faltar uno de los argumentos necesarios para la batalla entre pokemnones.
void imp_err_falta_argumento_en_enfrentamiento(){
    printf(ROJO"Falta uno de los pokemones para el enfrentamiento\n");
    printf(NORMAL"");
}

//Mensaje de error al faltar uno de los argumentos necesarios para el duelo entre entrenadores pokemon.
void imp_err_falta_argumento_en_duelo(){
    printf(ROJO"Falta/n argumnetos para el duelo pokemon\n");
    printf(NORMAL"");
}

//Mensaje de error al faltar uno de los argumentos necesarios para aniadir un pokemon al equipo.
void imp_err_falta_argumento_en_aniadir_pkm(){
    printf(ROJO"Falta el jugador y/o el pokemon del lider\n");
    printf(NORMAL"");
}

//Mensaje de error al faltar uno de los argumentos necesarios para leer una linea de pokemon del archivo.
void imp_err_falta_argumento_en_leer_linea_pkm(){
    printf(ROJO"Error en los parametros a la hora de leer una linea de pokemon del archivo\n");
    printf(NORMAL"");
}

//Mensaje de error al faltar uno de los argumentos necesarios para leer una linea de entrenador del archivo.
void imp_err_falta_argumento_en_leer_linea_entrenador(){
    printf(ROJO"Error en los parametros a la hora de leer una linea de entrenador del archivo\n");
    printf(NORMAL"");
}

//Mensaje de error al faltar uno de los argumentos necesarios para leer una linea del archivo del personaje.
void imp_err_falta_argumento_en_leer_linea_personaje(){
    printf(ROJO"Error en los parametros a la hora de leer una linea del archivo del personaje\n");
    printf(NORMAL"");
}

//Mensaje de error al faltar uno de los argumentos necesarios para leer una linea del archivo del gimnasio.
void imp_err_falta_argumento_en_leer_linea_gimnasio(){
    printf(ROJO"Error en los parametros a la hora de leer una linea del archivo del gimnasio\n");
    printf(NORMAL"");
}

//Mensaje de error al faltar uno de los argumentos necesarios para agregar un nuevo pokemon al personaje.
void imp_err_falta_argumento_en_agregar_pokemon(){
    printf(ROJO"No se puede agregar un nuevo pokemon al jugador/entrenador porque este y/o el pokemon no existen\n");
    printf(NORMAL"");
}

//Mensaje de error al faltar uno de los argumentos necesarios para jugar.
void imp_err_falta_argumento_en_jugar(){
    printf(ROJO"Error en los parametros a la hora de intentar jugar\n");
    printf(NORMAL"");
}



//Mensaje de error al fallar la reserva de memoria para un nuevo pokemon.
void imp_err_reserva_de_memoria_pkmn(){
    printf(ROJO"Error al reservar memoria para el nuevo pokemon\n");
    printf(NORMAL"");
}

//Mensaje de error al fallar la reserva de memoria para un nuevo entrenador.
void imp_err_reserva_de_memoria_entrenador(){
    printf(ROJO"Error al reservar memoria para el nuevo entrenador\n");
    printf(NORMAL"");
}

//Mensaje de error al fallar la reserva de memoria para el personaje principal.
void imp_err_reserva_de_memoria_personaje(){
    printf(ROJO"Error al reservar memoria para el personaje principal\n");
    printf(NORMAL"");
}

//Mensaje de error al fallar la reserva de memoria para el gimnasio.
void imp_err_reserva_de_memoria_gimnasio(){
    printf(ROJO"Error al reservar memoria para el gimnasio\n");
    printf(NORMAL"");
}






//Mensaje de error al fallar la insercion del entrenador a la pila.
void imp_err_insertar_gimnasio(){
    printf(ROJO"Error al intentar insertar un nuevo gimnasio en el HEAP\n");
    printf(NORMAL"");
}

//Mensaje de error al fallar la insercion del entrenador al gimnasio.
void imp_err_insertar_entrenador(){
    printf(ROJO"Error al intentar apilar un nuevo entrenador al gimnasio\n");
    printf(NORMAL"");
}

//Mensaje de error al fallar la insercion de el pokemon a una lista.
void imp_err_insertar_pkmn(){
    printf(ROJO"Error al insertar el pokemon a la lista\n");
    printf(NORMAL"");
}

//Mensaje de error al fallar la extraccion del pokemon de la lista.
void imp_err_extraer_pkmn(){
    printf(ROJO"Error al sacar el pokemon de la lista\n");
    printf(NORMAL"");
}

//Mensaje de error al fallar el traslado del pokemon en el equipo a capturados.
void imp_err_trasladar_pkmn(){
     printf(ROJO"Error al mover el pokemon del equipo a capturados\n");
     printf(NORMAL"");
}

//Mensaje de error al fallar la insercion del pokemon porque el equipo del entrenador estaba lleno.
void imp_err_equipo_lleno(){
    printf(ROJO"No se le pueden colocar mas pokemones a este entrenador, su equipo esta lleno!!!\n Se intentará seguir con la carga saltando este pokemon\n");
    printf(NORMAL"");
}







//Mensaje de error cuando no hay pokemon
void imp_err_falta_pokemon(){
    printf(ROJO"No hay pokemon\n");
    printf(NORMAL"");
}

//Mensaje de error cuando no hay jugador
void imp_err_falta_jugador(){
    printf(ROJO"No hay jugador\n");
    printf(NORMAL"");
}

//Mensaje de error cuando no hay gimnasios
void imp_err_falta_gimnasio(){
    printf(ROJO"No hay gimnasio/s\n");
    printf(NORMAL"");
}

//Mensaje de error cuando no se han cargados los datos necesarios para jugar el juego y tratan de iniciarse.
void imp_err_faltan_elementos_para_iniciar(){
    printf(ROJO"Debe cargarse necesariamente el personaje principal y al menos un gimnasio para jugar\n");
    printf(NORMAL"");
}





//Mensaje de error cuando la cantidad de elementos leidos en la linea con los datos del jugador del archivo de personaje no es la esperada.
void imp_err_cant_items_lectura_linea_personaje(){
    printf(ROJO"La cantidad de elementos leidos en la linea con la informacion del personaje no es la esperada\n");
    printf(NORMAL"");
}
//Mensaje de error cuando la cantidad de elementos leidos en la inea con los datos del gimnasio del archivo de gimnasio no es la esperada.
void imp_err_cant_items_lectura_linea_gimnasio(){
    printf(ROJO"La cantidad de elementos leidos en la linea con la informacion del gimnasio no es la esperada\n");
    printf(NORMAL"");
}
//Mensaje de error cuando la cantidad de elementos leidos en la linea de un entrenador del archivo no es la esperada.
void imp_err_cant_items_lectura_linea_entrenador(){
    printf(ROJO"La cantidad de elementos leidos en la linea de un entrenador del archivo no es la esperada\n");
    printf(NORMAL"");
}
//Mensaje de error cuando la cantidad de elementos leidos en la linea de un pokemon del archivo de gimnasio no es la esperada.
void imp_err_cant_items_lectura_linea_pokemon(){
    printf(ROJO"La cantidad de elementos leidos en la linea de un pokemon del archivo no es la esperada\n");
    printf(NORMAL"");
}
//Mensaje de error cuando falla en algun punto la lectura del archivo personaje.
void imp_err_lectura_archivo_personaje(){
    printf(ROJO"Error en los parametros a la hora de leer una linea del archivo del personaje\n");
    printf(NORMAL"");
}
//Mensaje de error cuando falla en algun punto la lectura del archivo gimnasio.
void imp_err_lectura_archivo_gimnasio(){
    printf(ROJO"Error en los parametros a la hora de leer una linea del archivo del gimnasio\n");
    printf(NORMAL"");
}












//Mensaje de bienvenida al iniciar la estructura
void imp_msj_bienvenida(){
	printf(NORMAL"Bienvenidos a la gran aventura pokemon!!\n");
}

//Mensaje de siguiente gimnasio con el que se tendrá que enfrentar el jugador.
void imp_msj_sig_gim_a_enfrentar(char* nombre, bool es_simulacion){
	if(!es_simulacion){
		system("clear");
		printf(NORMAL"\nAhora te enfrentaras al %s\n", nombre);
	}
}

//Mensaje de siguiente entrenador con el que se tendrá que enfrentar el jugador.
void imp_sig_entrenador_a_enfrentar(char* nombre, bool es_simulacion){
    if(!es_simulacion){
        printf(NORMAL"\nAhora te enfrentaras con %s\n", nombre);
    }
}

//Mensaje de se ha ganado una nueva medalla
void imp_msj_medalla_obtenida(char* nombre, bool es_simulacion){
	if(!es_simulacion){
		printf(VERDE"\nHas obtenido la medalla de %s\n", nombre);
        printf(NORMAL"");
    }
}

//Mensaje de se ha ganado una nueva medalla
void imp_entrenador_vencido(char* nombre, bool es_simulacion){
    if(!es_simulacion){
        printf(VERDE"Venciste a %s\n", nombre);
        printf(NORMAL"");
    }
}

//Mensaje de se ha perdido contra un entrenador
void imp_entrenador_me_vencio(char* nombre){
    printf(ROJO"Fuiste derrotado por %s\n", nombre);
    printf(NORMAL"");
}

//Mensaje de ha ocurrido un error durante el duelo contra otro entrenador
void imp_error_en_duelo(){
    printf(ROJO"Ha ocurrido un error durante uno de los combates, el duelo queda suspendido.\n");
    printf(NORMAL"");
}

//Mensaje de rendicion y final del juego.
void imp_msj_finalizacion_por_rendicion(char* nombre){
	printf(AMARILLO"\nHas sucumbido a la dificultad del gimnasio %s, mejor suerte la proxima\n", nombre);
    printf(NORMAL"");
}

//Mensaje de final del juego debido a un error.
void imp_msj_finalizacion_por_error(){
	printf(ROJO"Debido al error tu aventura tendrá que posponerse...\n");
    printf(NORMAL"");
}

//Mensaje de Victoria al ganar todos los gimnasios y terminar el juego
void imp_msj_finalizacion_por_victoria(size_t medallas_ganadas){
	printf(VERDE"Felicidades, has recolectado las %u medallas de gimnasio y ganado la Liga Pokemon!!\n", medallas_ganadas);
    printf(NORMAL"");
}

//Mensaje que indica quien es el dueño del equipo que se muestra a continuacion
void imp_msj_muestro_duenio_equipo(char* nombre){
    system("clear");
    printf(NORMAL"A continuacion se muestra el equipo de %s\n", nombre);
}

//Mensaje que indica que los pokemones que aparecen a continuacion son los capturados del jugador.
void imp_msj_muestro_capturados(){
    system("clear");
    printf(NORMAL"A continuacion se muestran tus pokemones capturados\n");
}

//Mensaje que indica al usario como ingresar la posicion que desee reemplazar
void imp_msj_ingresar_posicion(){
    printf(NORMAL"Ingrese la posicion del pokemon que desea reemplazar (la primera posicion es la 0) o -1 si se arrepiente\n");
}

//Mensaje que indica que lo que se muestra a continuacion es el pokemon seleccionado
void imp_msj_pkm_seleccionado(){
    printf(NORMAL"Pokemon seleccionado:\n");
}

//Mensaje de transferencia realizada con exito.
void imp_msj_transferencia_exitosa(){
    printf(VERDE"Transfrencia realizada con exito!!\n");
    printf(NORMAL"");
}

//Mensaje de introduccion a la carga del personaje
void imp_msj_intro_carga_personaje(){
    printf(NORMAL"Para ingreasar ingresar al personaje jugable indique la direccion del archivo, por ejemplo Personajes/Kanto/Ash.txt\n");
    printf("En caso de ocurrir algun error, se cargará la informacion del personaje que se pueda\n");
}

//Mensaje de introduccion a la carga del gimnasio
void imp_msj_intro_carga_gimnasio(){
    printf(NORMAL"Para ingreasar ingresar un gimnasio indique la direccion del archivo, por ejemplo Gimnasios/Kanto/Misty.txt\n");
    printf("En caso de ocurrir algun error, este se indicará.\n");
}









//Pide al usuario que ingrese una direccion de archivo.
void pedir_direccion(char* direccion){
    if(!direccion)
        return;
    printf(NORMAL"\n Ingrese la direccion del archivo: ");
    scanf("%199s", direccion);
}

//Pide al usuario que ingrese una letra cualquira para continuar la ejecucion del programa.
//La ejecucion del programa se detiene hasta que el ususrio ingrese dicho caracter.
void pedir_letra_para_continuar(){
    printf(NORMAL"Presiona cualquier letra para continuar\n");
    getchar();
}


//Imprime un pokemon por pantalla, mostrando toda su info.
void imprimir_pokemon(pokemon_t* pokemon){
    if(!pokemon){
        printf(NORMAL"No se selecciono un pokemon\n");      //CRea que puede sacarse
        return;
    }
    printf(AMARILLO"%-50s\n", pokemon->nombre);
    printf(NORMAL"Tipo: %-20s\n", pokemon->tipo);
    printf("V: %u + %u\n", pokemon->velocidad, pokemon->bonus);
    printf("A: %u + %u\n", pokemon->ataque, pokemon->bonus);
    printf("D: %u + %u\n\n", pokemon->defensa, pokemon->bonus);
}


//Muestra toda la informacion de los pokemones que se estan enfrentando en combate en simultaneo con el resutado del combate.
//Se debe llamar una vez hecho el chequeo de sus parametros, deben ser validos.
void mostrar_combate_pokemon(pokemon_t* pokemon_jugador, pokemon_t* pokemon_entrenador, int resultado_combate){
    printf(AMARILLO"\t\tCombate Pokemon!!\n");
    printf(NORMAL"Tu pokemon \t\t\t Pokemon del rival \n");
    printf("%-32s %-32s\n", pokemon_jugador->nombre, pokemon_entrenador->nombre);
    printf("Tipo: %-26s Tipo: %-26s\n", pokemon_jugador->tipo, pokemon_entrenador->tipo);
    printf("V: %u + %u \t\t\t V: %u \n", pokemon_jugador->velocidad, pokemon_jugador->bonus, pokemon_entrenador->velocidad);
    printf("A: %u + %u \t\t\t A: %u \n", pokemon_jugador->ataque, pokemon_jugador->bonus, pokemon_entrenador->ataque);
    printf("D: %u + %u \t\t\t D: %u \n\n", pokemon_jugador->defensa, pokemon_jugador->bonus, pokemon_entrenador->defensa);
    if(resultado_combate==GANO_PRIMERO){
        printf(VERDE"TU POKEMON GANA!!\n\n");
    }else{
        printf(ROJO"TU POKEMON PIERDE!!\n\n");
    }
    printf(NORMAL"");
}


//Muestra por pantalla todos los pokemones que esten en el equipo dado en sucesion.
void mostrar_equipo(lista_t* equipo){
    lista_iterador_t* iterador_equipo = lista_iterador_crear(equipo);
    while(lista_iterador_tiene_siguiente(iterador_equipo)){
        pokemon_t* pokemon_actual = lista_iterador_elemento_actual(iterador_equipo);
        imprimir_pokemon(pokemon_actual);
        lista_iterador_avanzar(iterador_equipo);
    }
    lista_iterador_destruir(iterador_equipo);
}

//Muestra por pantalla toda la informacion del personaje controlado por el usuario.
void mostrar_jugador(personaje_t* jugador){
    printf(NORMAL"Nombre del jugador: %s\n", jugador->nombre);
    printf("Ciudad de origen: %s\n", jugador->ciudad_natal);
    printf("Medallas ganadas: %u\n", jugador->medallas_ganadas);
    printf(VERDE"Equipo Pokemon:\n");
    mostrar_equipo(jugador->equipo);
    printf(VERDE"Pokemones Capturados:\n");
    mostrar_equipo(jugador->capturados);
}

//Muestra por pantalla toda la informacion del entrenador.
void imprimir_entrenador(entrenador_t* entrenador){
    printf(NORMAL"%s\n", entrenador->nombre);
    mostrar_equipo(entrenador->equipo);
}


//Muestra por pantalla la informacion de todos los entrenadores que se encuentran en la lista en sucesion..
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

//Muestra por pantalla la informacion del gimnasio dado.
void mostrar_gimnasio(gimnasio_t* gimnasio){
    printf(AMARILLO"\n%s\n", gimnasio->nombre);
    printf("Dificultad del Gimnasio: %u\n", gimnasio->dificultad);
    printf("Entrenadores totales: %u\n", lista_elementos(gimnasio->entrenadores));
    printf(NORMAL"");
    imprimir_entrenadores(gimnasio->entrenadores);
}

//Muestra por pantalla la informacion de todos los gimnasios cargados en el HEAP en sucesion.
void mostrar_gimnasios(heap_t* gimnasios){
    if(!gimnasios){
            printf(ROJO"No hay un HEAP!!!!\n");
            printf(NORMAL"");
        return;
    }

    gimnasio_t* gimnasio = heap_extraer_minimal(gimnasios);

    while(gimnasio){
        mostrar_gimnasio(gimnasio);
        printf("\n\n\n");
        gimnasio = heap_extraer_minimal(gimnasios);
    }
    printf(NORMAL"Ya no hay más gimnasios para mostrar\n");
}


//Muestra por pantalla las opciones que tiene disponible el usuario en el menu victoria.
//En caso de ya haber usado la opcion de tomar uno de los pokemones del lider vencido, esta opcion ya no se mostrará.
void mostrar_opciones_menu_victoria(bool ya_robo){
    printf(NORMAL"Seleccione una de las siguientes opciones a continuacion y recuerde solo ingresar la letra correspondiente en mayuscula:\n");
    if(!ya_robo){
        printf(" %c --> Elegir uno de los pokemones del equipo del lider derrotado para añadirlo a tu equipo\n", TOMAR_PRESTADO);
    }
    printf(" %c --> Cambiar los pokemones en tu equipo con aquellos que hayas capturado\n", CAMBIAR_EQUIPO);
    printf(" %c --> Siguiente gimnaio\n", PROXIMO);
}

//Pide al usuario que ingrerse uno de los comandos que tiene disponible en el menu victoria.
//En caso de ya haber usado la opcion de tomar uno de los pokemones del lider vencido, este comando ya no será valido para el mismo lider.
//En caso de ingresar un comando no valido se aclara que el comando ingresado no es valido y se vulve a pedir otro.
char pedir_instruccion_victoria(bool ya_robo){
    printf(NORMAL"Ingrese uno de los comandos de arriva...\n");
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

//Pide al usuario que ingrerse la posicion del pokemon que desea seleccionar.
//Se supone que se usa en conjunto con alguna funcion que muestra una lista de pokemones.
//En caso de ingresar un posicion invalida se aclara que la posicion ingresada no es valida y se vulve a pedir otra.
int pedir_posicion_pokemon(size_t tope_equipo){
    int posicion;
    scanf("%i", &posicion);
    while(getchar()!='\n'){}
    if(posicion >= (int)tope_equipo){
        printf("Debes elegir una posicion válida\n");
        return pedir_posicion_pokemon(tope_equipo);
    }
    return posicion;
}

//Devuelve el pokemon que este en la posicion dada en la lista recibida.
pokemon_t* obtener_pokemon_en_posicion(lista_t* equipo, int posicion){
    if(posicion<0){
        printf("No se seleccionó ningun pokemon\n");
        return NULL;
    }
    return lista_elemento_en_posicion(equipo, (size_t)posicion);
}

//Pide al usuario que confirme alguna opción/comando elegido con anterioridad.
//En caso de ingresar una respuesta no valido se aclara que no es valida y se vulve a pedir otra.
//SE devuelve true si el usuario confirma su eleccion o false si se arrepiente.
bool pedir_confirmacion(){
    printf("Es esto correcto? Y/N: ");
    char respuesta;
    scanf(" %c", &respuesta);
    while(getchar()!='\n'){}

    if((respuesta!=SI) && (respuesta!=NO)){
        printf("\nSolo se acepta Y o N (mayúscula)\n");
        return pedir_confirmacion();
    }

    if(respuesta==SI)
        return true;
    else
        return false;
}


//Pregunta al usuario si quiere seguir cargando archivos de gimnasio.
//En caso de ingresar una respuesta no valido se aclara que no es valida y se vulve a pedir otra.
//Se devuelve true si el usuario quiere seguir cargando o false si no.
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

//Muestra por pantalla las opciones que tiene disponible el usuario en el menu derrota.
void mostrar_opciones_menu_derrota(){
    printf("Seleccione una de las siguientes opciones a continuacion y recuerde solo ingresar la letra correspondiente en mayuscula:\n");
    printf(" %c --> Cambiar los pokemones en tu equipo con aquellos que hayas capturado\n", CAMBIAR_EQUIPO);
    printf(" %c --> Reintentar gimnaio\n", REINTENTAR);
    printf(" %c --> REndirse\n", RENDIRSE);
}

//Pide al usuario que ingrerse uno de los comandos que tiene disponible en el menu derrota.
//En caso de ingresar un comando no valido se aclara que el comando ingresado no es valido y se vulve a pedir otro.
char pedir_instruccion_derrota(){
    printf("Ingrese uno de los comandos de arriva...\n");
    char letra;
    scanf(" %c", &letra);
    while(getchar()!='\n'){}
    if(letra!=REINTENTAR && letra!=CAMBIAR_EQUIPO && letra!=RENDIRSE){
        printf("El comando ingresado no es valido\n");
        return pedir_instruccion_derrota();
    }
    return letra;
}


//Muestra por pantalla las opciones que tiene disponible el usuario en el menu inicial.
void mostrar_opciones_menu_inicial(){
    printf("Seleccione una de las siguientes opciones a continuacion y recuerde solo ingresar la letra correspondiente en mayuscula:\n");
    printf(" %c --> Ingreasar archivo del personaje principal\n", INGRESAR_JUGADOR);
    printf(" %c --> Ingreasar archivos de gimnasios\n", INGRESAR_GIMNASIO);
    printf(" %c --> Jugar una partida con los datos cargados\n", JUGAR);
    printf(" %c --> simular una partida con los datos cargados\n", SIMULAR);
}

//Pide al usuario que ingrerse uno de los comandos que tiene disponible en el menu inicial.
//En caso de ingresar un comando no valido se aclara que el comando ingresado no es valido y se vulve a pedir otro.
char pedir_instruccion_inicial(){
    printf("Ingrese uno de los comandos de arriva...\n");
    char letra;
    scanf(" %c", &letra);
    while(getchar()!='\n'){}
    if(letra!=INGRESAR_JUGADOR && letra!=INGRESAR_GIMNASIO && letra!=JUGAR && letra!=SIMULAR){
        printf("El comando ingresado no es valido\n");
        return pedir_instruccion_inicial();
    }
    return letra;
}


//Muestra por pantalla las opciones que tiene disponible el usuario en el menu gimnasio.
void mostrar_opciones_menu_gimnasio(){
    printf("Seleccione una de las siguientes opciones a continuacion y recuerde solo ingresar la letra correspondiente en mayuscula:\n");
    printf(" %c --> Mostrar al entrenador actual con su equipo\n", MOSTRAR_JUGADOR);
    printf(" %c --> Mostrar el gimnasio octual\n", MOSTRAR_GIMNASIO);
    printf(" %c --> Cambiar los pokemones en tu equipo con aquellos que hayas capturado\n", CAMBIAR_EQUIPO);
    printf(" %c --> Avanzar al siguiente combate\n", BATALLA);
}

//Pide al usuario que ingrerse uno de los comandos que tiene disponible en el menu gimnasio.
//En caso de ingresar un comando no valido se aclara que el comando ingresado no es valido y se vulve a pedir otro.
char pedir_instruccion_gimnasio(){
    printf("Ingrese uno de los comandos de arriva...\n");
    char letra;
    scanf(" %c", &letra);
    while(getchar()!='\n'){}
    if(letra!=MOSTRAR_JUGADOR && letra!=MOSTRAR_GIMNASIO && letra!=CAMBIAR_EQUIPO && letra!=BATALLA){
        printf("El comando ingresado no es valido\n");
        return pedir_instruccion_gimnasio();
    }
    return letra;
}
