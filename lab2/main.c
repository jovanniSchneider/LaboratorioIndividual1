#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "funciones.h"

int main()
{
    estructuraGrupo grupo;
    printf("1.Ingresar la información del grupo para cruzar\n");
    printf("2.Salir\n");
    int decision = pedirNumero("Ingrese su elección acá (1 o 2):",1,2);
    int correlativoId = 0;
    int cantidadAbiertos = 0;
    int cantidadCerrados = 0;
    int cantidadStringsFinal = 0;
    estado actual,siguiente;
    estado * abiertos = (estado *)malloc(sizeof(estado)*cantidadAbiertos);
    estado * cerrados = (estado *)malloc(sizeof(estado)*cantidadCerrados);
    int posiciones[2];
    switch (decision)
    {
    case 1:
        grupo.cantidadIntegrantes = 4;
        pedirDatos(&grupo);
        abiertos = agregarEstado(abiertos,&cantidadAbiertos,crearEstadoInicial(&correlativoId,0,grupo));
        while (cantidadAbiertos > 0)
        {
            printf("%d\n",correlativoId);
            actual = abiertos[0];
            abiertos = eliminarEstado(abiertos,&cantidadAbiertos);
            cerrados = agregarEstado(cerrados,&cantidadCerrados,actual);
            if (esFinal(actual)==1){
                printf("--------Busqueda finalizada--------\n");
                printf("Tiempo total: %d minutos\n",actual.tiempoTotal);
                char ** stringsFinal = (char**)malloc(sizeof(char*)*cantidadStringsFinal);
                mostrarSolucion(cerrados,actual,cantidadCerrados,stringsFinal,&cantidadStringsFinal);
                main();
            }else
            {
                switch (actual.antorcha)
                {
                case 1:
                if (actual.grupoIsla.cantidadIntegrantes >1)
                {
                    for (int i = 0; i < actual.grupoIsla.cantidadIntegrantes; i++)
                    {
                        if (i+1 < actual.grupoIsla.cantidadIntegrantes)
                        {
                            for (int j = i+1; j < actual.grupoIsla.cantidadIntegrantes; j++)
                            {
                                posiciones[0] = i;
                                posiciones[1] = j;
                                siguiente = cruzarPuente(actual,posiciones,2,&correlativoId);
                                if (verificarExistencia(abiertos,cantidadAbiertos,siguiente)==0 && verificarExistencia(cerrados,cantidadCerrados,siguiente)==0)
                                {
                                    abiertos = agregarEstado(abiertos,&cantidadAbiertos,siguiente);
                                    printf("Cantidad abiertos = %d\n",cantidadAbiertos);
                                    printf("Cantidad cerrados = %d\n",cantidadCerrados);
                                }
                                
                            }
                        }
                    }
                }else
                {
                    if(actual.grupoIsla.cantidadIntegrantes == 1){
                        posiciones[0] = 0;
                        siguiente = cruzarPuente(actual,posiciones,1,&correlativoId);
                        if (verificarExistencia(abiertos,cantidadAbiertos,siguiente)==0 && verificarExistencia(cerrados,cantidadCerrados,siguiente)==0)
                        {
                            abiertos = agregarEstado(abiertos,&cantidadAbiertos,siguiente);
                        }
                    }
                }       
                    break;
                
                case 2:
                        for (int i = 0; i < actual.grupoCiudad.cantidadIntegrantes; i++)
                        {
                            posiciones[0] = i;
                            siguiente = devolverse(actual,posiciones,&correlativoId);
                            if (verificarExistencia(abiertos,cantidadAbiertos,siguiente)==0 && verificarExistencia(cerrados,cantidadCerrados,siguiente)==0)
                            {
                                abiertos = agregarEstado(abiertos,&cantidadAbiertos,siguiente);
                            }
                        }
                    break;
            }
        }
        }
        printf("-----Busqueda finalizada------\n");
        printf("El grupo no logra pasar en el tiempo limite");
        free(abiertos);
        free(cerrados);
        main();
        break;
    case 2:
        return 0;
        break;
    }
}