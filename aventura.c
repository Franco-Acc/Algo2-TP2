#include "aventura.h"
#include "gimnasio.h"
#include "personaje.h"
#include "menus.h"
#include "interfaz.h"

//Añade una medalla al personaje principal.
void aniadir_medalla(personaje_t* jugador){
    if(!jugador){
        return imp_err_aniadir_medalla();
    }
    jugador->medallas_ganadas++;
}


//Funcion principal del programa hace que el usuario se enfrente a los gimnasios cargados hasta superarlos a todos o hasta que se rinde. Muestra el resultado final de la aventura por pantalla.
void jugar(personaje_t* jugador, heap_t* gimnasios, bool es_simulacion){
	if(!jugador || !gimnasios){
        imp_err_falta_argumento_en_jugar();
		return;
    }

    bool se_rinde = false;
    int resultado;
    gimnasio_t* gimnasio_actual = heap_extraer_minimal(gimnasios);

    while(gimnasio_actual && (!se_rinde)){

    	imp_sig_gim_a_enfrentar(gimnasio_actual->nombre, es_simulacion);
        resultado = enfrentar_gimnasio(jugador, gimnasio_actual, es_simulacion);

        if(resultado==VICTORIA){
        	imp_medalla_obtenida(gimnasio_actual->nombre, es_simulacion);
            aniadir_medalla(jugador);
            destructor_gimnasios((void*)gimnasio_actual);
            gimnasio_actual = heap_extraer_minimal(gimnasios);
        }else if(resultado==DERROTA){
        	imp_msj_finalizacion_por_rendicion(gimnasio_actual->nombre);
            destructor_gimnasios((void*)gimnasio_actual);
            se_rinde = true;
        }else{
        	imp_msj_finalizacion_por_error();
            destructor_gimnasios((void*)gimnasio_actual);
            se_rinde = true;
        }
        printf(NORMAL"");
    }

    if(!se_rinde)
    	imp_msj_finalizacion_por_victoria(jugador->medallas_ganadas);
}


//Reserva la memoria necesaria para el heap de gimnasios e inicializa el personaje jugable en NULL.
int crear_estructuras(heap_t** gimnasios, personaje_t** jugador){
	*gimnasios = heap_crear(comparador_gimnasios, destructor_gimnasios);
	if(!gimnasios){
		imp_err_crear_estructuras();
		return ERROR;
	}
	*jugador = NULL;
	return OK;
}


int main(){

	heap_t* gimnasios;
	personaje_t* jugador;

	if(crear_estructuras(&gimnasios, &jugador)==ERROR){
		return 0;
    }

	imp_msj_bienvenida();
	
	char instruccion = menu_inicial(&jugador, gimnasios);
	bool es_simulacion = true;

	if(instruccion == JUGAR){
		es_simulacion = false;
    }
		
	jugar(jugador, gimnasios, es_simulacion);

    liberar_jugador(jugador);
    liberar_gimnasios(gimnasios);

	return 0;
}


