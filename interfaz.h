#ifndef __INTERFAZ_H__
#define __INTERFAZ_H__

#include "estructuras.h"

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