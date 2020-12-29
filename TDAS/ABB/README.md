# #Algo2 - TDA ABB - 2°cuatrimestre 2020 - Franco Leonardo Acciardi 106272



	Resumen:
		El trabajo entregado es la implementacion del Tipo de dato abstracto Árbol Binario de Búsqueda. Ademas del TDA principal de ABB se mplmentó un iterador interno para la el arbol.
		A su vez tambien se crearon y corrieron una serie de pruebas sobre todos el TDA. Las mismas se hicieron utilizando el archivo pa2mm.h brindado por la catedra y estan disponibles en pruebas.c . 


	Compilacion:
		Comando)	gcc -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 abb.c pruebas.c -o abb
		Makefile)	make compilar	


	Ejecucion:
		Comando)	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb
		Makefile)	make valgrind


	Composicion del TP:
		El TP consta de 2 archivos .c y 2 archivo .h
			-En abb.c esta la implementacion de las funciones cuyas firmas fueron dadas en abb.h.
			-En pruebas.c se encuentra el main del programa y es donde se corren las distintas pruebas que verfifican el correcto funcionamiento del TDA.
		*El usuario final no debiera tener acceso a los .c y solo podria ver las primitivas a su disposicion en el .h sin conocer como estan implementadas las mismas.





	Funcionamiento de pruebas.c:

		+)Las pruebas se encuentran agrupadas en categorias segun lo que prueban.

		+)Dentro de los grupos hay otros subgrupos que se encargan de agrupar las pruebas sobre un elemento y hacer el seguimineto de las pruebas mas sencillo.

		+)Se prueba tanto el correcto funcionamiento del árbol como del iterador interno.

		+)Cada subgrupo de pruebas funciona de manera independiente, por lo que pueden quitarse y agregarse grupos de pruebas sin afectar al resto. 

		+)Para la implemantacion de las pruebas se utiliza el archivo pa2mm.h el cual permite mostrar por pantalla si una prueba tuvo exito o no.
			-)A la funcion pam_afirmar se le pasan 2 parametros:
				1)Una condicion a ser evaludada como verdadera o falsa, la cual determina si el resultado de la prueba es el esperado o no.
				2)Una linea de texto que es la que sera impresa por pantalla junto con una tilde verde en caso de que la condicion pasada sea verdadera (se paso la     
					prueba correctamente) o una cruz roja en caso de que sea falsa (no se completo la prueba correctamente).




	Comentarios sobre la implemantacion de las funciones de abb.h:

		+) A la hora de determinar si un arbol dado es válido o no se analizan todos los casos posibles en las que el arbol puede venir 'rota', esto es:
			-)Que el árbol sea nulo (NULL).
			-)Que no tenga un comparador.

		+)La funcion 'arbol_destruir' solo se hará responsable de detruir aquellos árboles creados y modificados con las primitivas provistas, lo cual garantiza su
			validez. En caso de modificar el arbol  manualmente accediendo a la estructura y haciéndolo inválido esta funicon no destruira dicho árbol (no hará nada).

		+) 'arbol_vacio' devolverá true solo cuando el arbol no tenga raiz, ya que en ese caso no tiene ningun elemento. Si se da el caso de que el arbol a evaluar es
			inválido, la funcion devolverá true como si estuviera vacío.

		+) La funcion 'arbol_destruir' simplemento llama a arbol_borrar, pasandole el elemento del nodo raiz para que la raiz sea borrada. Esto se repite hasta que ya no haya raiz, con lo cual el arbol queda vacío. Finalemente se procede a liberar el árbol en sí.

		+) La funcion 'arbol_borrar' al tener que borrar un nodo con 2 hijos buscará el predecesor inorden.

		+)El iterador interno no iterará los lementos del arbol si no se le pass una funcion que haga algo con ellos, pues no tiene sentido simplemente reccorer los lementos hasta el final del árbol sin hacer nada con ellos. Tampoco iterará si detecta que el árbol pasado no es válido.

--------------------------------------------------------------------------------------------------------------------------------------------------------------


1)	

	Un Árbol Binario es una estructura de datos donde los datos estan organizados de manera binaria. Se define como:
		a) Vacío (esto es en esta implementacion un puntero a NULL).
		b) Un nodo al cual llamamos raiz junto con un AB a su izquierda y otro a su derecha (En nuestra implementacion esto es un nodo con 2 punteros; Uno a un
		   nodo_izquierdo y otro a un nodo_dercho, cumpliendo los mismos con esta misma definición [a) o b)]).

	El AB nos permite dicernir las direcciones 'izquierda' y 'derecha' lo cual nos permite realizar en el mismo distintos recorridos para pasar por todos sus nodos. Los recorridos más utilizados son NID (preorden) - IND (inorden) - IDN (postorden).

	Si a esta definicion tambien le agregamos las siguientes características:

		-) Tener una relacion de orden entre sus elementos, lo cual permite saber que los elementos contenidos en el sub-arbol izquierdo de un nodo (si existe)
		   tienen claves menores al nodo actual, mientras que los elementos contenidos en el sub-arbol derecho de un nodo (si existe) tienen claves mayores al nodo actual.
		
		-) Tanto el sub-arbol izquierdo como el derecho cumplen tambien con la característica anterior.

	Entonces obtenemos un Árbol Binario de Búsqueda.
	

	En el ABB cuando nos paramos en una raíz tenemos en el sub-arbol izquierdo todos los nodos con elmentos 'menores' al de la raíz y en el sub-arbol derecho los nodos con los elementos 'mayores' al de la raiz. 

	A diferencia del AB común que solo nos brinda una forma de guardar elementos, el ABB aprovecha la relacion de orden entre sus elementos y el hecho de ser binario para facilitar la busqueda e inserción de elementos entre otras cosas. Se caracteriza por tener funciones con complejidad menor a la del AB común y lista (Ver punto 3). Además de esto el ABB nos brinda la posibilidad de recorrer el arbol con distintos recorridos. (por ejemplo pudiendo obtener los elementos del arbol de menor a mayor recorriéndolo inorden).


2)	
	
	El tener un destructor incluido en el TDA permite liberar al usuario de la tarea de liberar los elementos almacenados en el ABB. Con solo pasar una funcion que destruya lo que se guarde en el arbol (El destructor se pasa en la creacion del mismo) ya no debe preocuparse de destruir el elemento cada vez que se borra un nodo.

	El TDA al contar con el destructor en todo momento puede hacer uso del mismo en las primitivas como arbol_borrar o arbol_destruir sin que el usario haga nada extra. Si el destructor no estuviera incluido en el TDA el usuario debería pasarlo a las primitivas mencionadas anteriormente por separado cada vez que las use.


3)	

	Complejidad en las distintas operaciones del ABB:
	
		+) Complejidad de la búsqueda de un elemento O(log(n)).
	
		+) Complejidad de la inserción de un elemento O(log(n)).
	
		+) Complejidad de la eliminación de un elemento O(n*log(n)).
	
		+) Complejidad de recorrer la totalidad del arbol O(n).


	*) Valga aclarar que si bien estas complejidades tienen en cuenta el peor escenario, esto es solo cuando el ABB está balanceado. En caso de no estarlo decimos que 
		degenerá en una lista, perdiendo sus ventajas e incrementando la complejidad de las operaciones. (Por ejemplo insertar y buscar tendrían complejidad O(n))
	
	**) Un ABB puede estar balanceado en peso o en altura:
		En Peso: En cada nodo, la cantidad de nodos de sus sub-arboles difiere a lo summo en 1.
		Altura: En cada nodo, las alturas de los sub-arboles derecho e izquierdo difieren a lo sumo en 1.
	
	***) Definimos la altura de un nodo/sub-arbol como la cantidad de sub-arboles entre el mismo y la hoja mas lejana (contando la hoja).
