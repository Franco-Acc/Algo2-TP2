# Franco Acciardi - 106272 - Algo2 - TP2 - 2° cuatrimestre - 2020


+)Las particularidades de la lecura y consiguiente armado de los archivos de gimnasio y personaje han sido explicadas en sus respectivos archivos README.txt


+)Para este TP fueron utilizados 2 TDA´s implementados anteriormente, estos son:


		1)	El TDA HEAP: Utilizado para almacenar los gimnasios a los que tiene que enfrentarse el jugador durante la partida.


			-)Se escogió este TDA ya que lo que se necesitaba era almacenar los gimnasios e ir extrayendo aquel de menor dificultad. De esta forma se va progresando a gimnasios cada vez
			  mas difíciles.
			

			-)Se utilizó un HEAP Minimal, el cual asegura que siempre se extrae el elemento con la menor clave, en este caso la clave era la dificultad del gimnasio.






		2)El TDA LISTA: Utilizado para distintas cosas las cuales se mencionan a continuacion:


			-)  Equipos de pokemon : Se utilizó una lista ya que se necesitaba tener acceso a todos los elementos del mismo. Para esto se utilizó en conjunto un Iterador Externo de lista 
				para poder ir recorriendo todos los elementos de manera controlada.

				Cabe destacar que en la gran mayoria del tiempo las listas de equipos pokemon se utilizan como colas, puesto que la carga de los pokemones en el equipo se da en el mismo orden en el que están en el archivo, desde el primer pokemon de la lista hasta el ultimo.

				Sin embargo no se optó por usar una cola "pura" ya que era necesario tener acceso a todos los items almacenados y no solamente al primero y al ultimo.
				Por ejemplo cuando se enfrentan dos entrenadores y uno de sus pokemones gana una pelea el que perdio debe enviar a su siguiente pokemon en la lista. Esto en una cola en la que solo se tiene acceso al primer y ultimo pokemon implicaría el uso de otra cola auxiliar para ir guaradando los pokemones derrotados de ambos bandos y al terminar la pelea devolverlos a todos a sus listas originales en el mismo orden.

				Si bien esto se puede implmentar de esa forma, el uso de listas auxiliares y traslados de datos hacen mas costoso en terminos de espacio y complejidad el programa inecesariamente, por lo que se optó por una lista con iterdor externo, la cual puede usarse a efectos practicos como una cola de ser necesario (y es lo que se hace en
				el programa).



			-) Capturados del ususario (caja) : Se aplica lo mismo que para los equipos, solo que a esta lista nunca se le establece un maximo de items que pueden tener como si ocurre con
			   el equipo.

			   Aqui vale la pena remarcar que al ser cosas conceptualmente distintas (por un lado los pokemones que se usan para pelear y por otro aquellos 'descansando en casa') los pokemones que se encuentran en una de las listas no pueden estar en la otra.




			-) Entrenadores en gimnasio : Se utilizó la lista por un motivo similar al de los equipos, se necesitaba pooder iterar por los distintos entrenadores para, por ejemplo, poder
			   mostrar a todos los entrenadores de un gimnasio. Si bien se usa una lista es importante mencionar que la mayor parte del tiempo esta lista se utiliza como una pila.

			   En este caso se podría haberse optado por utilizar una pila "pura" ya que por la forma en la que estan diseñados los archivos de gimnasio y las lecturas de los mismos los primeros entrenadores que aparecen en el archivo (lider de gimnasio incluido) son los últimos que se enfrentan. Esto sumado al hecho de que se puede ir 'desapilando' los entrenadores a los que se van venciendo daria a entender que no se necesita nada mas que el acceso al ultimo entrenador incertado y por consiguiente podria usarse una pila.

			   El problema surge a la hora de querer mostrar todos los entrenadores que tiene un gimnasio, la pila solo nos da acceso al entrenador en el tope de la misma y no estaría conceptualmente bien usar un iterador de lista en una pila (ya que en teoria son TDA´s distintos). Si se hubiera elegido usar una pila (cosa perfectamente posible) se habrían tenido que usar pilas auxiliares para guardar temporalmente los entrenadores a medida que se van sacando para mostrar al siguiente para despues devolverlos todos a
			   su pila original, manteniendo asi el orden previo. Todo esto implicaría un uso extra de memoria y complejidad a la hora de mostrar todos los entrenadores. Se optó finalmente con usar una lista con iterador externo ya que es más versatil, no se necesitan elementos auxiliares, y puede usarse a efectos practicos como una pila (y es lo 
			   que se usó).



+)Funcinamiento general del programa:

	-)LISTA.C/H : TDA lista
	-)HEAP.C/H : TDA heap
	-)PRUEBAS.C/ pa2mm.H :	Una pequeña cantidad de pruebas generales para ver a grandes rasgos el correcto funcionamiento del heap y la lectura de archivos.



	-) AVENTURA.C/H : 
		El archivo princial es el de aventura.c, que es donde se encuentra el main del programa. Aqui se crea el heap de gimnasios y se llama al menu inicial para que el usario pueda
	 	ingresar los archivos que desee e inciar su aventura (o simularla). Para esto se llama a la funcion jugar con el heap de gimnasios y el puntero al personaje cargados junto con un
	 	booleano que indica si es una simulacion o no. De ser una simulacio no se mostrará ninguna salida o menu por pantalla hasta que se termine el juego ya sea porque venció todos los
	 	gimnasios o perdió ante algun entrenador. Una vez finalizada la partida se llama a las funciones correspondiente que liberan toda la memeoria reservada para el personaje y para el HEAP.

	-) BATALLAS.C/H :
		Aqui están implementadas las funciones de batalla, a continuacion se resumen los criterios para que el pokemon del usuario gane con cada una (de no cumplir con lo dicho su pokemon perderá), se nombrarán de acuerdo al id que le corresponde a cada una en los archivos de gimnasios:

			1) Gana cuando es su pokemon es del mismo tipo o del 'ventajoso' respecto a su oponente. Es decir que gana siempre y cuando su pokemon no sea del tipo que es vencido por el tipo de su oponente.
									A saber: AGUA    le gana a  FUEGO
											 FUEGO   le gana a  TIERRA
											 TIERRA  le gana a  AIRE
											 AIRE    le gana a  AGUA

			2) Gana cuando su velocidad es igual o superior a la del oponente.

			3) Lo mismo que 2 pero con la defensa. 									(pelea de metapods!!!)

			4) Lo mismo que 2 pero con el ataque.

			5) Gana cuando su nombre es igual o mas largo que el de su oponente 				(xd)


	-) GIMNASIO.C/H :
		Toda la implementacion de la lectura de los archivos de gimnasio, la carga de los datos a las estructuras de programa y la mecanica de enfrentarse a un gimnasio se encuentra en este archivo. Esto ultimo incluye las mecanicas de enfrentamiento con los entrenadores y entre pokemones.
	
	-) PERSONAJE.C/H :
		Toda la implementacion de la lectura y carga de los archivos de personaje se encuentra en este archivo.

	-) MENUS.C/H :
		Aqui se encuentra toda la implementacion de los distintos menus del juego, asi como todas funcionalidades que brindan los mismos (Esto es por ejemplo tomar prestado un pokemon o mostarar todos los entrenadores de un gimnasio, etc). Nota: Las funciones que no estan aqui son las que solo implican mostrar algo por pantalla, ellas estan en el siguiente archivo:

	-) INTERFAZ.C/H:
		Aqui se encuentran implementadas todas las funciones que implican mostrarle algo por pantalla al ususario, desde un mensaje de error hasta mostrar todos los pokemones de su jugador. 

	-) ESTRUCTURAS.C/H :
		Aqui se encuentran todas las estructuras , formatos de lectura y constantes del programa asi como todo la funcionalidad de la liberacion de memoria. Tambien posee el coomparador de gimnasios.



+)Compilacion y ejecucion:

	-)Para esto se provee un MAKEFILE con todos los comandos.

	-)Para compilar el programa ----------------------------> make compile_aventura
	-)Para correr el programa ------------------------------> make aventura
	-)Para correr el programa con Valgrind -----------------> make check_aventura

	-)Para compilar las pruebas ----------------------------> make compile_pruebas
	-)Para correr las pruebas con Valgrind -----------------> make check_pruebas


+)Organizacion:

	-)Todos los archivos .c y .h deben estar sueltos en la carpeta principal.

	-)Los archivos de texto como los de personaje o gimnasio pueden estar en subcarpetas o no (Por defectos vienen en subcarpetas).