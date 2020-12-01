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
int verificarPrimerCaracter();

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
        printf("\n\nEl archivo no existe\n");
        return 0;
    }else
    {
        fclose(archivo);
        printf("\n\nEl archivo existe\n\n");
        return 1;
    }
}

//--------------------------------------------------------

//Entrada: Un "string", el cual representa el nombre del archivo de prueba
//Salida: Un entero, un 1 si el primer caracter del archivo es un numero entero potencia de 2 y un 0 en caso contrario
//Función: Comprobar que el primer caracter de un archivo es un numero entero potencia de 2

int verificarPrimerCaracter(char * nombre){
    FILE * archivo;
    char primerCaracter[4];
    int cantidadCaracteres = 4;
    int numeroPrimerCaracter;
    archivo = fopen(nombre,"r");
    fgets(primerCaracter,cantidadCaracteres,archivo);
    printf("%c\n",primerCaracter);
    fclose(archivo);
    return 1;
} 

//--------------Función/Bloque principal-----------------------
int main()
{ 
    presioneEnter();
    char nombre[100];
    printf("Escriba el nombre del archivo de prueba: ");
    gets(nombre);
    int existencia = verificarArchivo(nombre);
    presioneEnter();
    verificarPrimerCaracter(nombre);
    return 0;
}