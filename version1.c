/*
ASIGNATURA: MÉTODOS DE PROGRAMACIÓN
SECCIÓN DE LABORATORIO: 0-L-7
SECCION DE CÁTEDRA: A-1
PROFESOR DE LABORATORIO: LUIS CELEDON
PROFESOR DE CÁTEDRA: ALEJANDRO CISTERNA

AUTOR:
-JOVANNI SCHNEIDER
-20.278.543-3
-INGENIERÍA CIVIL EN INFORMATICA

VERSIÓN DEL CODIGO: 1.0
*/


//-------------Importación de librerias-------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//-------------Declaración de funciones--------------
int detectarSO();
void limpiarConsola();
int verificarArchivo();
int verificarPrimeraLinea();
int verificarPotenciaDos();
void leerLineas();

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
    fscanf(archivo,"%s",&primeraLinea);
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
            verificarPotenciaDos(numero/2);
        }else
            return 0;
    }
}

//----------------------------------------------------------

//Entrada: Un numero que representa el ancho y largo de un archivo y un puntero a archivo
//Salida: Un array de "strings", la cual tiene como elementos las lineas del archivo
//Función: Guarda las lineas de un archivo de texto en un array

void leerLineas(FILE * archivo,int ancho,char matriz[ancho][ancho+2]){
    char residuo[ancho + 2];
    //fscanf(archivo,"%s",primeraLinea);
    fgets(residuo,ancho + 2,archivo);
    printf("Aqui voy\n");
    for (int i = 0; i < ancho;i++){
        fgets(matriz[i],ancho+2,archivo);
        fgets(residuo,ancho+2,archivo);
    }
}


//--------------Función/Bloque principal-----------------------
int main()
{ 
    presioneEnter();
    char nombre[100];
    printf("Escriba el nombre del archivo de prueba: ");
    gets(nombre);
    int existencia = verificarArchivo(nombre);
    if (existencia == 0)
    {
        printf("El documento no existe\n");
    }else
    {
        int numero = verificarPrimeraLinea(nombre,4);
        if (numero == 0)
        {
            printf("El archivo no cumple con los requisitos");
        }else
        {
            printf("El documento cumple con los requisitos\n");
            char matriz[numero+1][numero+2];
            FILE * archivo;
            archivo = fopen(nombre,"r");
            leerLineas(archivo,numero,matriz);
            fclose(archivo);   
            for (int i = 0; i < numero;i++){
                printf("%s\n",matriz[i]);
            }
        }
    }
    return 0;
}