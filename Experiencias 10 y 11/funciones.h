#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trios
{
    int id;
    int **trios;
} trios;

trios generarTrios(int numeroInicial)
{
    trios estructuraDeTrios;
    estructuraDeTrios.id = numeroInicial;
    int **conjuntoDeTrios = (int **)malloc(sizeof(int *) * 56); //56 son la cantidad de trios posibles con un mismo numero inicial y los otros 2 variando de 1 a 9 sin que se repitan
    int segundoNumero;
    int tercerNumero;
    int i = 0;
    while (i < 56)
    {
        for (segundoNumero = 1; segundoNumero <= 9; segundoNumero++)
        {
            for (tercerNumero = 1; tercerNumero <= 9; tercerNumero++)
            {
                if (segundoNumero != tercerNumero && segundoNumero != numeroInicial && tercerNumero != numeroInicial)
                {
                    conjuntoDeTrios[i] = (int *)malloc(sizeof(int) * 3);
                    conjuntoDeTrios[i][0] = numeroInicial;
                    conjuntoDeTrios[i][1] = segundoNumero;
                    conjuntoDeTrios[i][2] = tercerNumero;
                    i++;
                }
            }
        }
    }
    estructuraDeTrios.trios = conjuntoDeTrios;
    return estructuraDeTrios;
}

trios *generarConjuntoDeTrios()
{
    trios *conjunto = (trios *)malloc(sizeof(trios) * 9);
    for (int i = 0; i < 9; i++)
    {
        conjunto[i] = generarTrios(i + 1);
    }
    return conjunto;
}

int **crearMatrizTresPorTres(int *fila1, int *fila2, int *fila3)
{
    int **matriz = (int **)malloc(sizeof(int *) * 3);
    matriz[0] = fila1;
    matriz[1] = fila2;
    matriz[2] = fila3;
    return matriz;
}
int verificarRepeticion(int *fila1, int *fila2)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (fila1[i] == fila2[j])
            {
                return 1;
            }
        }
    }
    return 0;
}

void imprimirMatriz(int **matriz,int numeroMatriz)
{
    printf("----------Solucion numero %d-----------\n",numeroMatriz);
    for (int i = 0; i < 3; i++)
    {
        printf("|");
        for (int j = 0; j < 3; j++)
        {
            switch (j)
            {
            case 2:
                printf("%d", matriz[i][j]);
                break;
            
            default:
                printf("%d ", matriz[i][j]);
                break;
            }
        }
        printf("|\n");
    }
}

int ***agregarSolucion(int ***matrices, int *cantidad, int **solucion)
{
    int ***nuevoConjunto = (int ***)malloc(sizeof(int **) * (*cantidad + 1));
    for (int i = 0; i < *cantidad + 1; ++i)
    {
        nuevoConjunto[i] = (int **)malloc(sizeof(int *) * 3);
        for (int j = 0; j < 3; ++j)
        {
            nuevoConjunto[i][j] = (int *)malloc(sizeof(int) * 3);
        }
    }

    for (int numSolucion = 0; numSolucion < *cantidad; ++numSolucion)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; ++j)
            {
                nuevoConjunto[numSolucion][i][j] = matrices[numSolucion][i][j];
            }
        }
    }
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            nuevoConjunto[*cantidad][i][j] = solucion[i][j];
        }
    }
    *cantidad = *cantidad + 1;
    free(matrices);
    return nuevoConjunto;
}

int ***crearMatrizPorSumasHorizontales(trios *conjunto, int *cantidadMatrices)
{
    int ***matrices = (int ***)malloc(sizeof(int **) * (*cantidadMatrices));
    int *fila1;
    int *fila2;
    int *fila3;
    int **matriz;
    int sumaFila1;
    int sumaFila2;
    int sumaFila3;
    for (int numeroConjunto = 0; numeroConjunto < 9; numeroConjunto++)
    {
        for (int numeroTrio = 0; numeroTrio < 56; numeroTrio++)
        {
            fila1 = conjunto[numeroConjunto].trios[numeroTrio];
            sumaFila1 = fila1[0] + fila1[1] + fila1[2];
            for (int i = 0; i < 9; i++)
            {
                if (i + 1 != fila1[0] && i + 1 != fila1[1] && i + 1 != fila1[2])
                {
                    for (int j = 0; j < 56; j++)
                    {
                        fila2 = conjunto[i].trios[j];
                        sumaFila2 = fila2[0] + fila2[1] + fila2[2];
                        if (sumaFila2 == sumaFila1)
                        {
                            if (verificarRepeticion(fila1, fila2) == 0)
                            {
                                for (int k = 0; k < 9; k++)
                                {
                                    if (k + 1 != fila1[0] && k + 1 != fila1[1] && k + 1 != fila1[2])
                                    {
                                        for (int l = 0; l < 56; l++)
                                        {
                                            fila3 = conjunto[k].trios[l];
                                            sumaFila3 = fila3[0] + fila3[1] + fila3[2];
                                            if (sumaFila3 == sumaFila2)
                                            {
                                                if (verificarRepeticion(fila1, fila3) == 0 && verificarRepeticion(fila2, fila3) == 0)
                                                {
                                                    matriz = crearMatrizTresPorTres(fila1, fila2, fila3);
                                                    matrices = agregarSolucion(matrices, cantidadMatrices, matriz);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return matrices;
}

int verificarSumasVerticales(int ** matriz){
    int suma1 = matriz[0][0]+matriz[1][0]+matriz[2][0];
    int suma2 = matriz[0][1]+matriz[1][1]+matriz[2][1];
    int suma3 = matriz[0][2]+matriz[1][2]+matriz[2][2];
    if (suma1 == suma2 && suma2 == suma3)
    {
        //imprimirMatriz(matriz);
        return 1;
    }
    return 0;
}

int verificarSumasDiagonales (int ** matriz){
    int sumaVertical = matriz[0][0]+matriz[1][0]+matriz[2][0];;
    int diagonalPrincipal = matriz[0][0]+matriz[1][1]+matriz[2][2];
    int diagonalSecundaria = matriz[2][0]+matriz[1][1]+matriz[0][2];

    if (sumaVertical == diagonalPrincipal && diagonalPrincipal == diagonalSecundaria)
    {
        return 1;
    }
    return 0;
}

int *** eliminarSolucion(int *** conjunto, int * cantElementos, int posSolEliminar){
	//Se crea el nuevo conjunto de soluciones
	int*** conjuntoNuevo = (int ***)malloc(sizeof(int**)*(*cantElementos-1));
	for (int i = 0; i < *cantElementos-1; ++i){
		conjuntoNuevo[i] = (int **)malloc(sizeof(int *)*3);
		for (int j = 0; j < 3; ++j){
			conjuntoNuevo[i][j] = (int *)malloc(sizeof(int)*3);
		}
	}
	//Se copian las soluciones existentes, excepto aquel que hay que eliminar
	int contNuevaLista = 0;//Este contador corresponde a la lista nueva
	int contAntiguaLista = 0;
	while(contAntiguaLista < *cantElementos){
		//printf("\tComparando: %d con %d\n", contAntiguaLista, posSolEliminar);
		//Acá se verifica que no sea la solución a eliminar
		if(posSolEliminar != contAntiguaLista){
			//printf("\t\tDistintos, se mantiene\n");
			for(int ejeX = 0; ejeX < 3; ejeX ++){
				for (int ejeY = 0; ejeY < 3; ++ejeY){
					conjuntoNuevo[contNuevaLista][ejeX][ejeY] = conjunto[contAntiguaLista][ejeX][ejeY];
				}
			}//Si se agrega, se aumenta el contador de la nueva lista
			contNuevaLista++;
		}
		else{
			//printf("\t\tcontAntiguaLista eliminado\n");
		}//Siempre se debe avanzar el contador de la lista antigua
		contAntiguaLista++;
	}
	*cantElementos = *cantElementos-1;//Se actualiza la cantidad de elementos
	free(conjunto);//Se libera memoria del conjunto de soluciones que ya no se utilizará
	return conjuntoNuevo;
}