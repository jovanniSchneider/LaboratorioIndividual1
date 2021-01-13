La carpeta donde se presenta este archivo posee 3 otros 3 archivos los cuales deben estar en el mismo directorio al momento de compilar y ejecutar el programa.
Estos archivos son: 
'estructuras.h' : este archivo es un header donde se definen las estructuras necesarias a utilizar en el programa.
'funciones.h' : este archivo es un header donde se definen las funciones necesarias para el programa y utiliza el header 'estructuras.h' .
'main.c' : este archivo es el codigo base donde se encuentra el main y el menu principal del programa, en donde se utilizan las funciones definidas en el archivo 'funciones.h' .
Se separa el programa en estos 3 archivos para facilitar la lectura del programa a la hora de revisar la forma en que está estructurado y poseer un mayor orden.

El programa utiliza por defecto el algoritmo de busqueda anchura iterativo, debido a que logra encontrar la secuencia de pasos que tomen menor tiempo con la introducción de los datos de cierta forma, cosa que con profundidad no se logra.
Sin embargo el programa da la posibilidad de cambiar el algoritmo de busqueda a profundidad iterativo, para poder ver la diferencia que se produce en la solución con este.

Se considera para un estado los siguientes atributos:
-Linterna: Un valor numerico, 1 para cuando esté en la isla y 2 para cuando esté en la ciudad
-Id: Identificador unico del estado, valor numerico mayor a 0.
-Id anterior: Identificador unico del estado anterior para poder devolverse al momentode encontrar la solución
-Tiempo total: Tiempo que se ha empleado en las transiciones hasta el estado actual, valor numerico mayor o igual a 0
-Transición: Un string que representa la transición que se empleó para llegar al estado actual
-Grupo isla: Una estructura del tipo estructuraGrupo que representa al grupo que aún está en la isla
-Grupo ciudad: Una estructura del tipo estructuraGrupo que representa al grupo que está en la ciudad

Para las transiciones se consideran 2 generales que luego de manera automatica el programa decide quien debe aplicarlas.
Estas transiciones son:
-Cruzar el puente: Esta transición se aplica para cuando la linterna se encuentra en la isla, es aplicable solo a parejas de integrantes y estas se calculan automaticamente mediante todas las combinaciones posibles de 2 integrantes del grupo Isla.
-Devolverse a la isla: Esta transición se aplica para cuando la linterna se encuentra en la ciudad, es aplicable a solo un integrante del grupo ciudad, se aplica a todos los integrantes del grupo ciudad creano cada uno un estado distinto.

El estado final se considera cuando no quedan integrantes en el Grupo isla y el Tiempo total del estado es menor o igual a la restricción de tiempo.

El programa se ejecuta mediante entrada y salida estandar e inicia con un menú que da la posibilidad de ejecutar el programa o salir de este mediante una entrada numerica con los valores posibles 1 y 2.
Si se elige la opcion de ejecutar (1) se pregunta si se desea cambiar los nombres por defecto, lo cual se solicita como entrada numerica con valores posibles 1 y 2.

Luego se solicita los datos de cada integrante, nombre y tiempo que demora en cruzar en caso de haber querido cambiar los datos (1) y solo el tiempo que demora cada uno en cruzar en caso de no querer cambiar los nombres (2).
Luego de ingresar los datos de los integrantes se solicita el tiempo limite que estos disponen para cruzar.

Para todas las entradas de tiempo se solicita un numero entero mayor a 0.

Posteriormente se solicita mediante una entrada numerica(1 o 2) si se desea cambiar el algoritmo de busqueda.
Si se elige cambiar (1) se le solicita otra entrada numerica (1 o 2) para que elija si quiere anchura iterativo o profundidad iterativo.

Despues se procede a ejecutar el algoritmo de busqueda de la solución y si se encuentra se muestra la secuencia de pasos para poder cruzar el puente de manera que todos logren cruzar en el tiempo indicado.
Si no se encuentra solución se le da a conocer al usuario.
Luego de manera recursiva se vuelve al inicio donde se pregunta de nuevo si quiere utilizar el programa o salir.