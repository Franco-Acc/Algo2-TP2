#ifndef __INTERFAZ_H__
#define __INTERFAZ_H__

#include "estructuras.h"

//Mensaje de error al intentar añadir medalla.
void imp_err_aniadir_medalla();
//Mensaje de error al intentar abrir el archivo.
void imp_err_abrir_archivo();
//Mensaje de error al reservar memoria para las estructuras del programa.
void imp_err_crear_estructuras();
//Mensaje de error al fallar la creacion de una lista.
void imp_err_crear_lista();
//Mensaje de error al fallar la creacion de un iterador externo de lista.
void imp_err_crear_iterador_lista();
//Mensaje de error al fallar la reserva de memoria para un nuevo pokemon.
void imp_err_reserva_de_memoria_pkmn();
//Mensaje de error al fallar la reserva de memoria para un nuevo entrenador.
void imp_err_reserva_de_memoria_entrenador();
//Mensaje de error al fallar la reserva de memoria para el personaje principal.
void imp_err_reserva_de_memoria_personaje();
//Mensaje de error al fallar la reserva de memoria para el gimnasio.
void imp_err_reserva_de_memoria_gimnasio();



//Mensaje de error al faltar uno de los argumentos necesarios para enfrentar un gimnasio.
void imp_err_falta_argumento_en_enfrentar_gimnasio();
//Mensaje de error al faltar uno de los argumentos necesarios para la batalla entre pokemnones.
void imp_err_falta_argumento_en_enfrentamiento();
//Mensaje de error al faltar uno de los argumentos necesarios para el duelo entre entrenadores pokemon.
void imp_err_falta_argumento_en_duelo();
//Mensaje de error al faltar uno de los argumentos necesarios para aniadir un pokemon al equipo.
void imp_err_falta_argumento_en_aniadir_pkm();
//Mensaje de error al faltar uno de los argumentos necesarios para leer una linea de pokemon del archivo.
void imp_err_falta_argumento_en_leer_linea_pkm();
//Mensaje de error al faltar uno de los argumentos necesarios para leer una linea de entrenador del archivo.
void imp_err_falta_argumento_en_leer_linea_entrenador();
//Mensaje de error al faltar uno de los argumentos necesarios para leer una linea del archivo del personaje.
void imp_err_falta_argumento_en_leer_linea_personaje();
//Mensaje de error al faltar uno de los argumentos necesarios para leer una linea del archivo del gimnasio.
void imp_err_falta_argumento_en_leer_linea_gimnasio();
//Mensaje de error al faltar uno de los argumentos necesarios para agregar un nuevo pokemon al personaje.
void imp_err_falta_argumento_en_agregar_pokemon();



//Mensaje de error al fallar la insercion del entrenador a la pila.
void imp_err_insertar_gimnasio();
//Mensaje de error al fallar la insercion del entrenador a la pila.
void imp_err_insertar_entrenador();
//Mensaje de error al fallar la insercion del pokemon al equipo.
void imp_err_insertar_pkmn();
//Mensaje de error al fallar la extraccion del pokemon del equipo.
void imp_err_extraer_pkmn();
//Mensaje de error al fallar el traslado del pokemon en el equipo a capturados.
void imp_err_trasladar_pkmn();
//Mensaje de error al fallar la insercion del pokemon porque el equipo del entrenador estaba lleno.
void imp_err_equipo_lleno();




//Mensaje de error cuando no hay pokemon
void imp_err_falta_pokemon();
//Mensaje de error cuando no hay jugador
void imp_err_falta_jugador();
//Mensaje de error cuando no hay gimnasios
void imp_err_falta_gimnasio();
//Mensaje de error cuando no se han cargados los datos necesarios para jugar el juego y tratan de iniciarse.
void imp_err_faltan_elementos_para_iniciar();


//Mensaje de error cuando la cantidad de elementos leidos en la linea con los datos del jugador del archivo de personaje no es la esperada.
void imp_err_cant_items_lectura_linea_personaje();
//Mensaje de error cuando la cantidad de elementos leidos en la inea con los datos del gimnasio del archivo de gimnasio no es la esperada.
void imp_err_cant_items_lectura_linea_gimnasio();
//Mensaje de error cuando la cantidad de elementos leidos en la linea de un entrenador del archivo no es la esperada.
void imp_err_cant_items_lectura_linea_entrenador();
//Mensaje de error cuando la cantidad de elementos leidos en la linea de un pokemon del archivo de gimnasio no es la esperada.
void imp_err_cant_items_lectura_linea_pokemon();
//Mensaje de error cuando falla en algun punto la lectura del archivo personaje.
void imp_err_lectura_archivo_personaje();
//Mensaje de error cuando falla en algun punto la lectura del archivo gimnasio.
void imp_err_lectura_archivo_gimnasio();









//Mensaje de bienvenida al iniciar la estructura
void imp_msj_bienvenida();
//Mensaje de siguiente gimnasio con el que se tendrá que enfrentar el jugador.
void imp_sig_gim_a_enfrentar(char* nombre, bool es_simulacion);
//Mensaje de siguiente entrenador con el que se tendrá que enfrentar el jugador.
void imp_sig_entrenador_a_enfrentar(char* nombre, bool es_simulacion);
//Mensaje de se ha ganado una nueva medalla
void imp_medalla_obtenida(char* nombre, bool es_simulacion);
//Mensaje de se ha ganado contra un entrenador
void imp_entrenador_vencido(char* nombre, bool es_simulacion);
//Mensaje de se ha perdido contra un entrenador
void imp_entrenador_me_vencio(char* nombre);
//Mensaje de ha ocurrido un error durante el duelo contra otro entrenador
void imp_error_en_duelo();

//Mensaje de rendicion y final del juego.
void imp_msj_finalizacion_por_rendicion(char* nombre);
//Mensaje de final del juego debido a un error.
void imp_msj_finalizacion_por_error()
//Mensaje de Victoria al ganar todos los gimnasios y terminar el juego
void imp_msj_finalizacion_por_victoria(size_t medallas_ganadas);
//Mensaje que indica que lo que se muestra a continuacion es el equipo del lider de gimnasio
void imp_msj_muestro_duenio_equipo(char* nombre);
//Mensaje que indica que los pokemones que aparecen a continuacion son los capturados del jugador.
void imp_msj_muestro_capturados();
//Mensaje que indica al usario como ingresar la posicion que desee reemplazar
void imp_msj_ingresar_posicion();
//Mensaje que indica que lo que se muestra a continuacion es el pokemon seleccionado
void imp_msj_pkm_seleccionado();
//Mensaje de transferencia realizada con exito.
void imp_msj_transferencia_exitosa();
//Mensaje de introduccion a la carga del personaje
void imp_msj_intro_carga_personaje();
//Mensaje de introduccion a la carga del gimnasio
void imp_msj_intro_carga_gimnasio();











//Pide al usuario la direccion de un archivo y la almacena en la variable pasada.
void pedir_direccion(char* direccion);

//Pide al usuario que presione alguna letra para continuar y detiene la ejecucion del programa hasta que lo haga.
void pedir_letra_para_continuar();



//Muestra los comandos disponibles para el usuario en el menu de gimnasios.
void mostrar_opciones_menu_gimnasio();

//Pide el comando del usuario, aceptando como valido solo los comandos para el gimnasio.
char pedir_instruccion_gimnasio();


//Muestra los comandos disponibles para el usuario en el menu inicial.
void mostrar_opciones_menu_inicial();

//Pide el comando del usuario, aceptando como valido solo los comandos para el inicio.
char pedir_instruccion_inicial();


//Muestra los comandos disponibles para el usuario en el menu de victoria.
void mostrar_opciones_menu_victoria(bool ya_robo);

//Pide el comando del usuario, aceptando como valido solo los comandos para la victoria.
char pedir_instruccion_victoria(bool ya_robo);


//Muestra los comandos disponibles para el usuario en el menu de derrota.
void mostrar_opciones_menu_derrota();

//Pide el comando del usuario, aceptando como valido solo los comandos para la derrota.
char pedir_instruccion_derrota();


//Muestra toda la informacion del pokemon pasado por pantalla.
void imprimir_pokemon(pokemon_t* pokemon);

//Muestra toda la informacion de los pokemones que se estan enfrentando en combate.
void mostrar_combate_pokemon(pokemon_t* pokemon_jugador, pokemon_t* pokemon_entrenador, int resultado_combate);

//Muestra todos los pokemones del equipo pasado por pantalla.
void mostrar_equipo(lista_t* equipo);

//Muestra toda la informacion del gimnasio por pantalla, incluyendo los entrenadores que contiene con sus respectivos equipos.
void mostrar_gimnasio(gimnasio_t* gimnasio);

//Muestra toda la informacion de los gimnasios de la partida por pantalla.
void mostrar_gimnasios(heap_t* gimnasios);

//Muestra toda la informacion del personaje principal por pantalla, incluyendo pokemones del equipo y capturados.
void mostrar_jugador(personaje_t* jugador);

//Pide al usuario ingresar SI o NO para confirmar algo.
bool pedir_confirmacion();

//Pregunta al usuario si quiere ingresar otro gimnasio.
bool quiere_seguir_cargando();

//Pide al usuario ingrsar la posicion en la lista de un pokemon, siendo inválida cualquier posicion mayor al tope recibido.
int pedir_posicion_pokemon(size_t tope_equipo);

//Devuelve el puntero al pokemon que se encuentra en la posicion dada del equipo recibido.
pokemon_t* obtener_pokemon_en_posicion(lista_t* equipo, int posicion);

#endif /* __INTERFAZ_H__ */