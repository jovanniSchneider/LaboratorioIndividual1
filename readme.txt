Se sugiere seguir las siguientes instrucciones para un correcto funcionamiento del programa
1) Compilar el archivo de extensión .c llamada main con gcc
2) El ejecutable de salida post compilación debe encontrarse en la misma carpeta donde están todos los archivos de texto plano de extensión .in
3) Al ejecutar el programa se le solicitará en primera instancia el nombre del archivo de texto plano, el cual debe ser ingresado sin extensión y respetando mayusculas
4) Luego de ingresar el nombre el programa corroborará si el archivo existe, si es así mostrará por pantalla su contenido y dirá que el archivo cumple con los requisitos, los cuales deben ser:
    a)El archivo debe tener como primera linea un numero potencia de 2
    b)El archivo debe tener la cantidad de lineas siguientes equivalentes al numero indicado en la primera linea
    c)El archivo debe solo contener los caracteres 'X' y '_' luego de la primera linea
5) Si el archivo no cumple con los requisitos se le notificará por pantalla, a lo cual se le pedirá si quiere seguir usando el programa o finalizar
6) Para la entrada de la opcion anterior se le solicitará una entrada numerica la cual puede ser un 1 o un 2, si ingresa otra cosa se le volverá a pedir su elección
7) Si el archivo de entrada existe y cumple con los requisitos entonces se le solicitará que ingrese de manera numerica cuantas generaciones desea procesar
8) Una vez ingresada la cantidad de generaciones se le dará la opcion de ver el paso de generación en generación por pantalla, lo cual será mediante consola.
9) Independiente de su elección se procederá a procesar cada generación siempre y cuando la cantidad de generaciones deseadas sea mayor a 1
10) Para el paso de generación en generación primero se creará (solo si no existe) una carpeta dentro de la carpeta de ejecucion del programa, la cual tendrá por nombre el mismo nombre del archivo de entrada sin extensión
11) En la carpeta se guardará la generación X ingresada por usuario de la matriz contenida en el archivo de entrada, la cual tendrá como nombre Salida_genX.in , donde X es el numero de la generación solicitada
12) Cuando el paso de generaciones finalice se notificará de manera escrita por la consola que el paso de generaciones a finalizado
13) Se le pedirá que decida si quiere seguir utilizando el programa, para lo cual se le solicita una entrada numerica con opciones 1 y 2 (si y no respectivamente).

Jovanni Schneider
Ingeniería Civil Informática