/*
ASIGNATURA: MÉTODOS DE PROGRAMACIÓN
SECCIÓN DE LABORATORIO: 0-L-7
SECCION DE CÁTEDRA: A-1
PROFESOR DE LABORATORIO: LUIS CELEDON
PROFESOR DE CÁTEDRA: ALEJANDRO CISTERNA
FECHA: 20/12/2020

AUTOR:
-JOVANNI SCHNEIDER
-20.278.543-3
-INGENIERÍA CIVIL EN INFORMATICA

VERSIÓN DEL CODIGO: 2.2

EXPLICACIÓN:
TODOS LOS PROCESOS DEL PROGRAMA OCURREN DENTRO DE LA FUNCIÓN LLAMADA menuPrincipal, LA CUAL TRABAJA DE MANERA RECURSIVA MIENTRAS EL USUARIO QUIERA SEGUIR USANDO EL PROGRAMA.
LO PRIMERO QUE SE HACE ES SOLICITAR AL USUARIO EL NOMBRE DEL ARCHIVO DE ENTRADA PARA LUEGO VERIFICAR QUE EL ARCHIVO EXISTA, LA PRIMERA LINEA CONTENGA UN NUMERO POTENCIA DE 2 Y QUE SU CONTENIDO SOLO SEAN 'X' Y '_'.
ESTAS VERIFICACIONES LAS HACE UTILIZANDO LAS FUNCIONES verificarArchivo(), verificarPrimeraLinea(), verificarPotenciaDos(),leerLineas(), verificarMatriz(),verificarCaracteres() Y verificarIgualdad()
SI ALGUNA DE ESTAS VERIFICACIONES FALLA (EL RESULTADO NO ES EL ESPERADO), ENTONCES SE LE DICE AL USUARIO QUE NO CUMPLE CON LOS REQUISITOS Y SE LE DA LA POSIBILIDAD DE VOLVER A USAR EL PROGRAMA.
SI TODAS LAS VERIFICACIONES SALEN POSITIVAS, ENTONCES SE LE SOLICITA AL USUSARIO CUANTAS GENERACIONES DESEA PROCESAR Y SI DESEA VER POR PANTALLA CADA GENERACION, LUEGO SE PROCEDE A PROCESAR EL PASO DE GENERACIONES CON LA FUNCION pasoDeGeneraciones(),
LA CUAL USA LAS FUNCIONES divisionVertical() Y divisionHorizontal() PARA REDUCIR LOS DATOS Y ASI TRABAJAR LOS CASOS ESPECIFICOS, TENIENDO CADA CASO ESPECIFICO SE UTILIZA LA FUNCION calcularEstado() PARA SABER SI LA CELDA VIVE O NO Y SE GRABA EN UN ARCHIVO Y SE MUESTRA(SOLO SI CORRESPONDE)POR PANTALLA SU AVANCE.
*/


//-------------Importación de librerias-------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


//-------------Definicion de estructuras------------


//-------------Declaración de funciones--------------
int detectarSO();
void limpiarConsola();
int verificarArchivo();
int verificarPrimeraLinea();
int verificarPotenciaDos();
void leerLineas();
int verificarMatriz();
int verificarCaracteres();
int verificarIgualdad();
void divisionVertical();
void divisionHorizontal();
void calcularEstado();
void pasoDeGeneraciones();
int pedirNumero();
int menuPrincipal();

//-------------Definición de funciones declaradas------------

//Entrada: No recibe
//Salida: Un entero, 0 para windows, 1 Para Linux o MAC
//Función: Detecta el sistema operativo en el que se está trabajando

int detectarSO(){
    #if defined(_WIN32)
    #define SISTEMA 0
    #else
    #define SISTEMA 1
    #endif
    return SISTEMA;
}

//------------------------------------------------------

//Entrada: No recibe
//Salida: No retorna
//Función: Detecta el sistema operativo en uso y limpia la consola
void limpiarConsola(){
    int sistema = detectarSO();
    switch (sistema)
    {
    case 0:
        system("cls");
        break;
    case 1:
        system("clear");
        break;
    }
}

//--------------------------------------------------------

void presioneEnter(){
    printf("Presione enter para continuar...\n");
    getchar();
}

//--------------------------------------------------------

//Entrada: El nombre del archivo de prueba
//Salida: Un 1 si el archivo de prueba existe en la carpeta de ejecución del codigo y 0 en caso contrario
//Función: Verifica si el archivo de prueba existe en la carpeta de ejecución del codigo

int verificarArchivo(char* nombre){
    FILE * archivo;
    archivo = fopen(nombre,"r");
    if (archivo == NULL){
        return 0;
    }else
    {
        fclose(archivo);
        return 1;
    }
}

//--------------------------------------------------------

//Entrada: Un "string", el cual representa el nombre del archivo de prueba y la cantidad de caracteres a leer
//Salida: Un entero, la primera linea del archivo si esta es un numero entero y si es potencia de 2 y un 0 en caso contrario
//Función: Comprobar que la primera linea de un archivo es un numero entero potencia de 2

int verificarPrimeraLinea(char * nombre,int cantidadCaracteres){
    FILE * archivo;
    char primeraLinea[cantidadCaracteres];
    archivo = fopen(nombre,"r");
    fscanf(archivo,"%s",primeraLinea);
    fclose(archivo);
    int verificador = 1;
    for(int i = 0; i<cantidadCaracteres;i++){
        if (isdigit(primeraLinea[0]) == 0)
            verificador = 0;
    }
    if(verificador == 1){
        int numero = atoi(primeraLinea);
        if(numero < 2){
            return 0;
        }else
            switch (verificarPotenciaDos(numero))
            {
            case 1:
                return numero;
                break;
            
            default:
                return 0;
                break;
            }
    }else
        return 0;
    
} 

//--------------------------------------------------------

//Entrada: Un numero
//Salida: Un entero, un 1 si es potencia de 2 y un 0 en caso contrario
//Función: Comprobar si un numero entero potencia de 2

int verificarPotenciaDos(int numero){
    if (numero == 1){
        return 1;
    }else{
        if(numero%2 == 0){
            return verificarPotenciaDos(numero/2);
        }else
            return 0;
    }
}

//----------------------------------------------------------

//Entrada: Un numero que representa el ancho y largo de un archivo y un puntero a archivo
//Salida: Un array de "strings", la cual tiene como elementos las lineas del archivo
//Función: Guarda las lineas de un archivo de texto en un array

void leerLineas(FILE * archivo,int ancho,char matriz[ancho][ancho]){
    char temporal[ancho];
    char residuo[ancho];
    for (int i = 0; i < ancho;i++){
        fgets(residuo,ancho,archivo);
        fgets(temporal,ancho,archivo); 
        strcpy(matriz[i],temporal);
    }
}

//----------------------------------------------------------

//Entrada: Un entero y una "matriz", el entero representa el tamaño de la matriz cuadrada.
//Salida: Un entero, un 1 si es verdadero y un 0 si es falso
//Función: Verifica si todas las filas de una matriz poseen solo X y _

int verificarMatriz(int tamano, char matriz[tamano][tamano]){
    int verificacion = 0;
    for (int i = 0; i < tamano-1;i++){
        char * array = (char *)malloc(sizeof(char)*tamano);
        for (int j = 0; j < tamano;j++){
            array[j] = matriz[i][j];
        }
        verificacion += verificarCaracteres(tamano-1,array,tamano-1);
        free(array);
    }
    if (verificacion == tamano-1){
        return 1;
    }else{
        return 0;
    }
}

//----------------------------------------------------------

//Entrada: Un "string", que representa una de las lineas de la matriz principal
//Salida: Un entero, un 1 en caso de ser verdadero y un 0 en caso de ser falso
//Funcion: Verifica si en un "string" hay solo X y _, si encuentra otro caracter es falso

int verificarCaracteres(int tamano,char * array,int tamanoInicial){
    char * arrayAux;
    if (strlen(array) > tamano){
        char * arrayAux = (char *)calloc(tamano,sizeof(char));
        for(int i = 0;i<tamano;i++){
            arrayAux[i]=array[i];
        }
        array = arrayAux;
    }
    if (tamano == 1){
        return verificarIgualdad(array);
    }else{
        int sizeIzquierda = tamano/2;
        int sizeDerecha = tamano - sizeIzquierda;
        char * strIzquierda = (char *)malloc(sizeof(char)*(sizeIzquierda));
        char * strDerecha = (char *)malloc(sizeof(char)*(sizeDerecha));
        for (int i = 0;i < sizeIzquierda;i++){
            strIzquierda[i]=array[i];
        }
        for (int i = 0;i<sizeDerecha;i++){
            strDerecha[i]=array[i+sizeIzquierda];
        }
        if (tamanoInicial != tamano){
            free(array);
        }
        if (verificarCaracteres(sizeIzquierda,strIzquierda,tamanoInicial) == 1 && verificarCaracteres(sizeDerecha,strDerecha,tamanoInicial) == 1){
            return 1;
        }    
        else{
            return 0;
        }
    }
}

//----------------------------------------------------------

//Entrada:Un array de un caracter que representa un caracter del array de la función verificarCaracteres
//Salida: Un entero, un 1 en caso de ser verdadero y un 0 en caso de ser falso
//Funcion: Verifica que el caracter del array sea igual a X o a _, si no es ninguno es falso

int verificarIgualdad(char array[1]){
    if (strcmp(array,"X") == 0 || strcmp(array,"_") == 0 )
    {
        return 1;
    }else{
        return 0;
    }
    
    
}
//----------------------------------------------------------

//Entrada: 4 enteros los cuales representan el tamaño vertical y horizontal de la matriz, el ciclo recursivo, y la desicion de ver el estado por pantalla, una matriz de char de 2 dimensiones y un archivo, que es en el cual se escribirá el nuevo estado
//Salida: no retorna
//Función: Genera la división vertical de los datos, para solo trabajar con 2(inicio y final) o 3 filas a la vez

void divisionVertical(int tamanoVertical,int tamanoHorizontal,char matriz[tamanoVertical][tamanoHorizontal+1], int ciclo,FILE * archivo,int verEstado){
    int inicio = 0;
    int medio = 1;
    if (tamanoVertical == 2 && ciclo != 1){
        char ** newMatriz = (char **)malloc(sizeof(char*)*2);
        for (int i = 0; i < 2; i++)
        {
            newMatriz[i] = (char *)malloc(sizeof(char)*tamanoHorizontal);
            strcpy(newMatriz[i],matriz[i]);
        }
        divisionHorizontal(2,tamanoHorizontal,newMatriz,medio,archivo,1,verEstado);
        free(newMatriz);
    }
    else{
        int sizeArriba;
        int sizeAbajo;
        if (ciclo == 1){
            sizeArriba = 2;
        }else
            sizeArriba = 3;
        sizeAbajo = tamanoVertical-sizeArriba+2;
        char ** matrizArriba = (char **)malloc(sizeof(char*)*sizeArriba);
        for (int i = 0; i < sizeArriba;i++){
            matrizArriba[i] = (char *)malloc(sizeof(char)*tamanoHorizontal+1);
        }
        char matrizAbajo[sizeAbajo][tamanoHorizontal+1];
        for (int i = 0;i < sizeArriba;i++){
            strcpy(matrizArriba[i],matriz[i]);
        }
        for (int i = 0;i < sizeAbajo;i++){
            strcpy(matrizAbajo[i],matriz[sizeArriba+i-2]);
        }
        if (sizeArriba == 2){
            divisionHorizontal(2,tamanoHorizontal,matrizArriba,inicio,archivo,1,verEstado);
            if(ciclo !=1){
                free(matriz);
            }
        }else{
            divisionHorizontal(3,tamanoHorizontal,matrizArriba,medio,archivo,1,verEstado);
        }
        divisionVertical(sizeAbajo,tamanoHorizontal,matrizAbajo,ciclo+1,archivo,verEstado);
    }
    
}
//----------------------------------------------------------

//Entrada: 5 enteros los cuales representan el tamaño vertical y horizontal de la matriz, el ciclo recursivo, la desicion de ver el estado por pantalla y la fila que se va a analizar, una matriz de char de 2 dimensiones y un archivo, que es en el cual se escribirá el nuevo estado
//Salida: No entrega
//Función: Genera la división horizontal de los datos, para solo trabajar con 2(inicio y final) o 3 columnas a la vez
void divisionHorizontal(int tamanoVertical,int tamanoHorizontal,char** matriz,int filaAnalisis,FILE * archivo,int ciclo,int verEstado){
    int inicio = 0;
    int medio = 1;
    if (tamanoHorizontal == 2 && ciclo != 1){
        calcularEstado(tamanoVertical,tamanoHorizontal,matriz,filaAnalisis,medio,archivo,verEstado);
        fputc('\n',archivo);
        if (verEstado == 1)
        {
            printf("\n");
        }
    }
    else{
        int sizeIzquierda;
        int sizeDerecha;
        if (ciclo == 1){
            sizeIzquierda = 2;
        }else
        sizeIzquierda = 3;
        sizeDerecha = tamanoHorizontal-sizeIzquierda+2;
        char ** matrizIzquierda = (char **)calloc(tamanoVertical,sizeof(char*));
        for(int i = 0; i < tamanoVertical;i++){
            matrizIzquierda[i] = (char*)calloc(sizeIzquierda,sizeof(char));
        }
        
        char ** matrizDerecha = (char **)calloc(tamanoVertical,sizeof(char*));
        for(int i = 0; i < tamanoVertical;i++){
            matrizDerecha[i] = (char*)calloc(sizeDerecha,sizeof(char));
        }
        for (int i = 0;i < tamanoVertical;i++){
            for(int j = 0;j < sizeIzquierda;j++){
                matrizIzquierda[i][j] = matriz[i][j];
            }
            for(int j = 0;j < sizeDerecha;j++){
                matrizDerecha[i][j] = matriz[i][j+sizeIzquierda-2];
            }
        }
        if(ciclo !=1){
            free(matriz);
        }
        if (sizeIzquierda == 2){
            calcularEstado(tamanoVertical,2,matrizIzquierda,filaAnalisis,inicio,archivo,verEstado);
        }else
            calcularEstado(tamanoVertical,3,matrizIzquierda,filaAnalisis,medio,archivo,verEstado);
        divisionHorizontal(tamanoVertical,sizeDerecha,matrizDerecha,filaAnalisis,archivo,ciclo+1,verEstado);
    }
    
}
//----------------------------------------------------------

//Entrada: 5 enteros los cuales representan el tamaño vertical y horizontal de la matriz, la columna que se va a analizar, la desicion de ver el estado por pantalla y la fila que se va a analizar, una matriz de char de 2 dimensiones y un archivo, que es en el cual se escribirá el nuevo estado
//Salida: Un caracter adicional al archivo
//Función: Calcula si una celda debe nacer,morir o seguir viva; agregando su nuevo estado al archivo

void calcularEstado(int tamanoVertical,int tamanoHorizontal,char ** matriz,int fila, int columna,FILE * archivo,int verEstado){
    int vecinasVivas = 0;
    int estado; //1 para viva, 0 para muerta
    for (int i = 0;i<tamanoVertical;i++){
        for (int j = 0; j < tamanoHorizontal; j++){

            if (!(i == fila && j == columna)){
                if(matriz[i][j] == 'X'){
                    vecinasVivas++;
                }
            }
        }
    }
    if(matriz[fila][columna] == 'X'){
        if(vecinasVivas < 2)
            estado = 0;
        else if(vecinasVivas > 3){
            estado = 0;
        }else if (vecinasVivas == 3 || vecinasVivas ==2)
        {
            estado = 1;
        }
        
    }else{
        if(vecinasVivas == 3){
            estado = 1;
        }else
            estado = 0;
    }
    if(estado == 1){
        fputc('X',archivo);
        if (verEstado == 1)
        {
            printf("X");
        }
    }else{
        fputc('_',archivo);
        if (verEstado == 1)
        {
            printf("_");
        }
    }

}

//-------------------------------------------------------------

//Entrada: un "string" que representa el nombre del archivo que contiene la matriz, una matriz de char de 2 dimensiones, 5 enteros, que representan el tamaño vertical y horizontal de la matriz, la generacion en la que se encuentra, la cantidad de generaciones a calcular y la desicion de ver el estado por pantalla 
//Salida: No genera
//Función: Genera el archivo de salida y utiliza la funcion division vertical para calcular la siguiente generación, esto lo hace de manera recursiva, hasta que la generacion sea igual a la cantidad que se desea

void pasoDeGeneraciones(char * nombreArchivoOriginal,int sizeV,int sizeH,int generacionActual,int generaciones,char matriz[sizeV][sizeH+1],int verEstado){
    struct stat st = {0};
    if (stat(nombreArchivoOriginal,&st) == -1){
        #if defined(_WIN32)
        mkdir(nombreArchivoOriginal);
        #else
        mkdir(nombreArchivoOriginal,0700);
        #endif
    }
    if (verEstado == 1)
    {
        presioneEnter();
        limpiarConsola();
    }
    char generacion[50]="";
    strcat(generacion,nombreArchivoOriginal);
    char salida[12]="/Salida_gen";
    strcat(generacion,salida);
    char * extension = ".in";
    char generacionActualChar[7];
    char sizeChar[3];
    sprintf(generacionActualChar,"%u",generacionActual);
    strcat(generacion,generacionActualChar);
    strcat(generacion,extension);
    sprintf(sizeChar,"%u",sizeV);
    FILE * archivo = fopen(generacion,"w");
    fputs(sizeChar,archivo);
    fputc('\n',archivo);
    divisionVertical(sizeV,sizeH,matriz,1,archivo,verEstado);
    fclose(archivo);
    if (generacionActual >= generaciones || generaciones <= 1)
    {
        printf("Paso de generaciones finalizado\n");
    }else
    {
        FILE * archivo = fopen(generacion,"r");
        char newMatriz[sizeV][sizeH+2];
        leerLineas(archivo,sizeV+1,newMatriz);
        fclose(archivo);
        pasoDeGeneraciones(nombreArchivoOriginal,sizeV,sizeH,generacionActual+1,generaciones,newMatriz,verEstado);
        if (!(generaciones == generacionActual)){
            remove(generacion);
        }
    }

}

//-----------------------------------------------------------------------

//Entrada: un "string" que se utilizará para decirle al usuario que debe ingresar y 2 enteros, que representan el numero minimo y maximo respectivamente que el usuario puede ingresar
//Salida: un entero, que es el numero ingresado por el usuario
//Funcion: Pide un entero hasta que se ingrese un numero y que esté dentro del rango esperado

int pedirNumero(char* string,int cotaInferior,int cotaSuperior){
    printf("%s ",string);
    char numero[5];
    fgets(numero,5,stdin);
    int longitud = strlen(numero);
    if(numero[longitud-1] == '\n'){
        numero[longitud-1] = '\0';
    }
    for (int i = 0; i < longitud-1; i++)
    {
        if (!(isdigit(numero[i])))
        {   
            printf("Ingrese un numero correcto, por favor vuelva a intentarlo\n");
            return pedirNumero(string,cotaInferior,cotaSuperior);
        }
    }
    int numeroFinal = atoi(numero);
    if (numeroFinal < cotaInferior || numeroFinal > cotaSuperior){
        printf("Ingrese un numero correcto, por favor vuelva a intentarlo\n");
        return pedirNumero(string,cotaInferior,cotaSuperior);
    }
    return numeroFinal;
}

//-----------------------------------------------------------------------

//Entrada: un entero, que representa la decisión de ejecutar el menu principal
//Salida: no entrega
//Funcion: Utiliza todas las funciones y representa visualmente el menu del usuario

int menuPrincipal(int seguir){
    if (seguir == 1)
    {
        char nombre[100];
        char nombreSinExtension[100]="";
        printf("Escriba el nombre del archivo de prueba sin extension: ");
        fflush(stdin);
        fgets(nombre,100,stdin);
        int longitud = strlen(nombre);
        if(nombre[longitud-1] == '\n'){
            nombre[longitud-1] = '\0';
        }
        strcat(nombreSinExtension,nombre);
        strcat(nombre,".in");
        int existencia = verificarArchivo(nombre);
        if (existencia == 0)
        {
            printf("El documento no existe\n");
        }else
        {
            int numero = verificarPrimeraLinea(nombre,4);
            if (numero == 0)
            {
                printf("El archivo no cumple con los requisitos\n");
            }else
            {
                printf("Archivo: %s\n",nombre);
                printf("------------Estado inicial-------------\n");
                char matriz[numero+1][numero+1];
                FILE * archivo;
                archivo = fopen(nombre,"r");
                leerLineas(archivo,numero+1,matriz);
                fclose(archivo);
                for (int i = 0; i < numero;i++){
                    printf("%s\n",matriz[i]);
                }
                if (verificarMatriz(numero+1,matriz) == 0){
                    printf("El archivo no cumple con los requisitos\n");
                    return 0;
                }else
                {
                    printf("El archivo cumple con los requisitos\n");
                    int generaciones = pedirNumero("¿Cuantas generaciones desea?(Max 500):",1,500);
                    int verEstado = pedirNumero("¿Desea ver el cambio de estado en pantalla?\nSí (1)\nNo (2)\nIngrese el numero de su opcion aquí:",1,2);
                    fflush(stdin);
                    limpiarConsola();
                    pasoDeGeneraciones(nombreSinExtension,numero,numero,2,generaciones,matriz,verEstado);
                }
            }
        }
        seguir = pedirNumero("¿Desea seguir utilizando el programa?\nSí (1)\nNo (2)\nIngrese el numero de su opcion aquí:",1,2);
        return menuPrincipal(seguir);
    }else
    {
        printf("--------------------Hasta luego---------------\n");
        return 0;
    }
}

//--------------Función/Bloque principal-----------------------
int main()
{ 
    menuPrincipal(1);
    return 0;
}