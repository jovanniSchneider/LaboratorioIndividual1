//Probando limpiar la pantalla 

#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
//Entrada: No recibe
//Salida: No retorna
//Función: Detecta el sistema operativo en uso y limpia la consola
void limpiarConsola(){
    #if defined(_WIN32)
    #include <windows.h>
    #define LIMPIAR 0
    #define CANTIDAD 3
    #endif
    #if defined(__linux__)
    #include <unistd.h>
    #define LIMPIAR 1
    #define CANTIDAD 5
    #endif
    #if defined(__MACH__)
    #include <unistd.h>
    #define LIMPIAR 1
    #define CANTIDAD 5
    #endif
    char string[CANTIDAD];
    char paraWin[3] = "cls";
    char paraLinuxYMac[5] = "clear";
    switch (LIMPIAR)
    {
    case 0:
        strcpy(string,paraWin);
        break;
    case 1:
        strcpy(string,paraLinuxYMac);
        break;
    }
    system(string);
}

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
int main()
{ 
    char nombre[100];
    printf("Escriba el nombre del archivo de prueba: ");
    fflush(stdin);
    scanf("%s",&nombre);
    int existencia = verificarArchivo(nombre);
    getchar();
    limpiarConsola();
    return 0;
}