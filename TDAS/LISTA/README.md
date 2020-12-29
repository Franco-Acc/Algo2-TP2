#Algo2 - TDA lista - 2°cuatrimestre 2020 - Franco Leonardo Acciardi 106272



	Resumen:
		El trabajo entregado es la implementacion del Tipo de dato abstracto lista. Ademas del TDA principal de lista tambien se implmentarojn los TDA pila y cola junto con iteradores interno y externo para la lista.
		A su vez tambien se crearon y corrieron una serie de pruebas sobre todos los TDAs. Las mismas se hicieron utilizando el archivo pa2mm.h brindado por la catedra y estan disponibles en pruebas.c . 


	Compilacion:
		Comando)	gcc -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 lista.c pruebas.c -o lista_se
		Makefile)	make compilar	


	Ejecucion:
		Comando)	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_se
		Makefile)	make valgrind


	Composicion del TP:
		El TP consta de 2 archivos .c y 2 archivo .h
			-En lista.c esta la implementacion de las funciones cuyas firmas fueron dadas en lista.h.
			-En pruebas.c se encuentra el main del programa y es donde se corren las distintas pruebas que verfifican el correcto funcionamiento del TDA.
		#El usuario final no debiera tener acceso a los .c y solo podria ver las primitivas a su disposicion en el .h sin conocer como estan implementadas las mismas.





	Funcionamiento de pruebas.c:

		+)Las pruebas se encuentran agrupadas en categorias segun lo que prueban.

		+)Dentro de los grupos hay otros subgrupos que se encargan de agrupar las pruebas sobre un elemento y hacer el seguimineto de las pruebas mas sencillo.

		+)Se prueba tanto el correcto funcionamiento de la lista como de la cola y la pila. Tambien se realizan pruebas sobre los iteradores tanto interno como externo.

		+)Cada subgrupo de pruebas funciona de manera independiente, por lo que pueden quitarse y agregarse grupos de pruebas sin afectar al resto. 

		+)Para la implemantacion de las pruebas se utiliza el archivo pa2mm.h el cual permite mostrar por pantalla si una prueba tuvo exito o no.
			-)A la funcion pam_afirmar se le pasan 2 parametros:
				1)Una condicion a ser evaludada como verdadera o falsa, la cual determina si el resultado de la prueba es el esperado o no.
				2)Una linea de texto que es la que sera impresa por pantalla junto con una tilde verde en caso de que la condicion pasada sea verdadera (se paso la     
					prueba correctamente) o una cruz roja en caso de que sea falsa (no se completo la prueba correctamente).






	Comentarios sobre la implemantacion de las funciones de lista.h:

		+) A la hora de determinar si una lista pasada es verdadera o falsa se analizan todos los casos posibles en las que la lista pueda venir 'rota', esto es:
			-)Que tenga el nodo inicial o final nulo y el otro no.
			-)Que tenga ambos nodos nulos cuando diga tener elementos guardados.
			-)Que alguno de los nodos (inicial o final) sea  no nulo cuando diga no tener ningun elñemento guardado. 

		+)El iterador externo solo dira que no puede seguir iterando cuando halla pasado al ultimo elemento de la lista y este apuntando a NULL, esto implica que la
			funcion 'iterador_tiene_siguiente' solo devolvera false una vez iterada completamente toda la lista (incluido el ultimo nodo) y se halla salido de la lista.

		+)La funcion 'lista_destruir' solo se hará responsable de detruir aquellas lista creadas y modificadas con las primitivas provistas, lo cual garantiza su
			validez. En caso de modificar la lista  manualmente accediendo a la estructura y haciendola inválida esta funicon no destruira dicha lista.

		+) 'lista_vacia' devolverá true solo cuando la lista este vacia (tenga 0 elementos) y ademas dicha lista vacia sea valida (tenga nodos inicial y final nulos). En caso de ser una lista inválida devolverá false como si estuviese llena pese a que la cantidad sea 0.

		+) Las funciones de pila y cola estan implementadas como casos particulares de lista.

		+)El iterador interno no iterará los lementos de la lista si no se le pas auna funcion que haga algo con ellos, pues no tiene sentido simplemente reccorer los lementos hasta el final de la lista sin hacer nada con ellos.




--------------------------------------------------------------------------------------------------------------------------------------------------------------





1)	

	Un Árbol Binario es una estructura de datos donde los datos estan organizados de manera binaria. Se define como:
		a) Vacío (esto es en esta implementacion un puntero a NULL).
		b) Un nodo al cual llamamos raiz junto con un AB a su izquierda y otro a su derecha (En nuestra implementacion esto es un nodo con 2 punteros; Uno a un
		   nodo_izquierdo y otro a un nodo_dercho, puediendo estar los mismos vacios o no [a) o b)]).

	Si a esta definicion tambien le agregamos la cararcterística de tener una relacion de orden entre sus elementos, entonces obtenemos un Árbol Binario de Búsqueda.
	En el ABB cuando nos paramos en una raíz tenemos en el sub-arbol izquierdo todos los nodos con elmentos 'menores' al de la raíz y en el sub-arbol derecho los nodos con los elementos 'mayores' al de la raiz. A diferencia del AB común que solo nos brinda una forma de guardar elementos, el ABB aprovecha la relacion de orden entre sus elementos y el hecho de ser binario y se caracteriza por tener funciones con complejidad menor a la del AB común y lista (Ver punto 3).


2)	
	
	El tener un destructor incluido en el TDA permite liberar al usuario de la tarea de liberar los elementos almacenados en el ABB. Con solo pasar una funcion que destruya lo que se guarde en el arbol (El destructor se pasa en la creacion del mismo) ya no debe preocuparse de destruir el elemento cada vez que se borra un nodo. El TDA al contar con el destructor en todo momento puede hacer uso del mismo en las primitivas como arbol_borrar o arbol_destruir sin que el usario haga nada extra. Si el destructor no estuviera incluido en el TDA el usuario debería pasarlo a las primitivas mencionadas anteriormente por separado cada vez que las use.




3)	

	Complejidad en las distintas operaciones del ABB:
	
		+) Complejidad de la búsqueda de un elemento O(log(n)).
	
		+) Complejidad de la inserción de un elemento O(log(n)).
	
		+) Complejidad de la eliminación de un elemento O(n*log(n)).
	
		+) La posibilidad de recorrer el arbol con distintos recorridos. (por ejemplo pudiendo obtener los elementos del arbol de menor a mayor recorriendolo inorden).

	*) Valga aclarar que si bien estas complejidades tienen en cuenta el peor escenario, esto es solo cuando el ABB está balanceado. En caso de no estarlo decimos que 
		degenerá en una lista, perdiendo sus ventajas e incrementando la complejidad de las operaciones. (Por ejemplo insertar y buscar tendrían complejidad O(n))
	
	**) Un ABB puede estar balanceado en peso o en altura:
		En Peso: En cada nodo, la cantidad de nodos de sus sub-arboles difiere a lo summo en 1.
		Altura: En cada nodo, las alturas de los sub-arboles derecho e izquierdo difieren a lo sumo en 1.
	
	***) Definimos la altura de un nodo/sub-arbol como la cantidad de sub-arboles entre el mismo y la hoja mas cercana. REVISAR
