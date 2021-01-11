#include "aventura.h"
#include "gimnasio.h"
#include "personaje.h"
#include "menus.h"


void destructor_gimnasios(void* gimnasio){
    liberar_entrenadores(((gimnasio_t*)gimnasio)->entrenadores);
    free(gimnasio);
}

int comparador_gimnasios (void* gimnasio_1, void* gimnasio_2){
    if(((gimnasio_t*)gimnasio_1)->dificultad < ((gimnasio_t*)gimnasio_2)->dificultad)
        return -1;
    else
        return 1;
}

void aniadir_medalla(personaje_t* jugador){
    jugador->medallas_ganadas++;
}

void jugar(personaje_t* jugador, heap_t* gimnasios){
    bool se_rinde = false;
    int resultado;
    gimnasio_t* gimnasio_actual = heap_extraer_minimal(gimnasios);

    while(gimnasio_actual && (!se_rinde)){
        printf("Ahora te enfrentaras al %s\n", gimnasio_actual->nombre);
        resultado = enfrentar_gimnasio(jugador, gimnasio_actual, false);
        if(resultado==VICTORIA){
            printf("Has obtenido la medalla de %s\n", gimnasio_actual->nombre);
            aniadir_medalla(jugador);
            destructor_gimnasios((void*)gimnasio_actual);
            gimnasio_actual = heap_extraer_minimal(gimnasios);
        }else if(resultado==DERROTA){
            printf("Has sucumbido a la dificultad del gimnasio %s, mejor suerte la proxima\n", gimnasio_actual->nombre);
            se_rinde = true;
        }else{
            printf("Falta el jugador y/o gimnasio\n");
            se_rinde = true;
        }
    }

    if(!se_rinde)
        printf("Felicidades, has recolectado las %u medallas de gimnasio y ganada la LIga Pokemon!!\n", jugador->medallas_ganadas);
}

void simular(personaje_t* jugador, heap_t* gimnasios){
    int resultado = VICTORIA;
    gimnasio_t* gimnasio_actual = heap_extraer_minimal(gimnasios);

    while(gimnasio_actual && resultado==VICTORIA){
        resultado = enfrentar_gimnasio(jugador, gimnasio_actual, false);
        if(resultado==VICTORIA){
            aniadir_medalla(jugador);
            destructor_gimnasios((void*)gimnasio_actual);
            gimnasio_actual = heap_extraer_minimal(gimnasios);
        }else if(resultado==DERROTA){
            printf("Has sucumbido a la dificultad del gimnasio %s, mejor suerte la proxima\n", gimnasio_actual->nombre);
        }else{
            printf("Falta el jugador y/o gimnasio\n");
        }
    }
}

int crear_estructuras(heap_t** gimnasios, personaje_t** jugador){
	*gimnasios = heap_crear(comparador_gimnasios, destructor_gimnasios);
	if(!gimnasios){
		printf("Error en la reserva de memeoria para el heap de gimnasios\n");
		return ERROR;
	}
	*jugador = NULL;
	return OK;
}


int main(){

	heap_t* gimnasios;
	personaje_t* jugador;

	if(crear_estructuras(&gimnasios, &jugador)==ERROR)
		return 0;

	printf("Bienvenidos a la gran aventura pokemon!!\n");
	
	char instruccion = menu_inicial(&jugador, gimnasios);

	if(instruccion == JUGAR)
		jugar(jugador, gimnasios);
	else
		simular(jugador, gimnasios);
	return 0;
}


