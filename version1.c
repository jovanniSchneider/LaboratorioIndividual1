//Probando limpiar la pantalla 

#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
//Entrada: No recibe
//Salida: No retorna
//Función: Detecta el sistema operativo en uso y limpia la consola
void limpiarConsola(){
    #if defined(_WIN32)
    #define LIMPIAR 0
    #else
    #define LIMPIAR 1
    #endif
    switch (LIMPIAR)
    {
    case 0:
        system("cls");
        break;
    case 1:
        system("clear");
        break;
    }
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
    limpiarConsola();
    char nombre[100];
    printf("Escriba el nombre del archivo de prueba: ");
    fflush(stdin);
    scanf("%s",&nombre);
    int existencia = verificarArchivo(nombre);
    printf("Presione cualquier tecla para continuar...\n");
    fflush(stdin);
    getchar();
    return 0;
}