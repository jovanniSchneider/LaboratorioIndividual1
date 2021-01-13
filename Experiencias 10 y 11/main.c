#include "funciones.h"
#include <locale.h>


int main(){
    setlocale(LC_ALL, "");
    trios * conjuntoDetrios = generarConjuntoDeTrios();
    int cantidadMatrices = 0;
    int *** matrices = crearMatrizPorSumasHorizontales(conjuntoDetrios,&cantidadMatrices);
    for (int i = 0; i < cantidadMatrices; i++)
    {  
        if (verificarSumasVerticales(matrices[i]) == 0){
            matrices = eliminarSolucion(matrices,&cantidadMatrices,i);
            i--;
        }
    }
    for (int i = 0; i < cantidadMatrices; i++)
    {
         if (verificarSumasDiagonales(matrices[i]) == 0){
            matrices = eliminarSolucion(matrices,&cantidadMatrices,i);
            i--;
        }
    }
    printf("----------Busqueda Finalizada-----------\n");
    printf("Cantidad de soluciones: %d\n\n",cantidadMatrices);
    for (int i = 0; i < cantidadMatrices; i++)
    {

        imprimirMatriz(matrices[i],i+1);
    }
    free (matrices);
    free (conjuntoDetrios);
    return 0;
}