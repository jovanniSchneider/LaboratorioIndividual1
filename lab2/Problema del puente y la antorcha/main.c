/*
ASIGNATURA: MÉTODOS DE PROGRAMACIÓN
SECCIÓN DE LABORATORIO: 0-L-7
SECCION DE CÁTEDRA: A-1
PROFESOR DE LABORATORIO: LUIS CELEDÓN
PROFESOR DE CÁTEDRA: ALEJANDRO CISTERNA
FECHA: 11/01/2021

AUTOR:
-JOVANNI SCHNEIDER
-20.278.543-3
-INGENIERÍA CIVIL EN INFORMATICA


*/

//--------------Importación de librerias y headers-------------
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "funciones.h"

//-----------------Declaración de funciones-----------------
int menuPrincipal();
int main();


//-----------------Definicion de funciones-------------------

int main()
{
    return menuPrincipal(1); //Se le da el valor de entrada 1 para tener por predeterminado el algoritmo de anchura
}

//-----------------------------------

//Entrada: Un entero que representa el tipo de algoritmo de busqueda a utilizar
//Salida: Un entero que siempre será un 0, para que el main finalice
//Funcion: Ejecuta todo el programa llamandose a si misma de manera recursiva para cada ejecución de este.
int menuPrincipal(int algoritmoDeBusqueda){
    limpiarConsola();

    //Se solicita si correr el programa o salir de el
    printf("1.Ingresar la informacion del grupo para cruzar\n");
    printf("2.Salir\n");
    int decision = pedirNumero("Ingrese su eleccion aca (1 o 2):",1,2);

    //Se define lo necesario para utilizar el programa ya que dentro del switch no se puede
    limpiarConsola();   
    int correlativoId = 0;
    int cantidadAbiertos = 0;
    int cantidadCerrados = 0;
    int cantidadStringsFinal = 0;
    estructuraGrupo grupo;
    estado actual,siguiente;
    estado * abiertos = (estado *)malloc(sizeof(estado)*cantidadAbiertos);
    estado * cerrados = (estado *)malloc(sizeof(estado)*cantidadCerrados);
    int posiciones[2];
    switch (decision)
    {
    //Caso en que el usuario quiere usar el programa
    case 1:
        grupo.cantidadIntegrantes = 4;
        
        //Se pregunta si se quiere cambiar los nombres predeterminados
        int cambiarNombres = pedirNumero("¿Desea cambiar los nombres por defecto de los integrantes? 1.Sí/2.No:",1,2);
        pedirDatos(&grupo,cambiarNombres);
        limpiarConsola();

        //Se pregunta si se desea cambiar el algoritmo de busqueda y se cambia si se elige que sí
        printf("¿Desea cambiar el algoritmo de busqueda?\nAlgoritmo actual: ");
        switch (algoritmoDeBusqueda)
        {
        case 1:
            printf("Anchura iterativo\n");
            break;
        
        case 2:
            printf("Profundidad iterativo\n");
            break;
        }
        int cambiarAlgoritmo = pedirNumero("Ingrese aca su eleccion (1.Sí/2.No): ",1,2);
        switch (cambiarAlgoritmo)
        {
        case 1:
            printf("1.Anchura iterativo\n");
            printf("2.Profundidad iterativo\n");
            algoritmoDeBusqueda = pedirNumero("Ingrese aca el indice de su opcion:",1,2);
            break;
        }
        limpiarConsola();

        //Se imprimen los datos de los integrantes del grupo
        printf("------Integrantes------\n");
        for (int i = 0; i < grupo.cantidadIntegrantes; i++)
        {
            printf("Nombre: %s, Tiempo en que cruza: %d minutos\n",grupo.integrantes[i].nombre,grupo.integrantes[i].tiempoEnPasar);
        }
        printf("Tiempo limite: %d minutos\n",grupo.tiempoLimite);
        
        //Se agrega el estado inicial al array abiertos
        abiertos = agregarEstadoAnchura(abiertos,&cantidadAbiertos,crearEstadoInicial(&correlativoId,grupo));
        
        //Se inicia el ciclo principal de BEE hasta que hayan estados abiertos o se encuentre el estado final
        while (cantidadAbiertos > 0)
        {   
            //Se toma el primer estado de abiertos y se traspasa a cerrados
            actual = abiertos[0];
            abiertos = eliminarEstado(abiertos,&cantidadAbiertos);
            cerrados = agregarEstadoAnchura(cerrados,&cantidadCerrados,actual);

            //Si es el estado final se finaliza la busqueda y se muestra la solución para volver al menu inicial
            if (esFinal(actual)==1){
                printf("--------Busqueda finalizada--------\n");
                printf("Tiempo total: %d minutos\n",actual.tiempoTotal);
                char ** stringsFinal = (char**)malloc(sizeof(char*)*cantidadStringsFinal);
                mostrarSolucion(cerrados,actual,cantidadCerrados,stringsFinal,&cantidadStringsFinal);
                presioneEnter();
                return menuPrincipal(algoritmoDeBusqueda);

            //Si no es el estado final se comienzan las transiciones siempre y cuando el estado no haya pasado el tiempo limite
            }else if(actual.tiempoTotal < grupo.tiempoLimite)
            {
                //Depende la posición de la linterna es la transición que se realiza
                switch (actual.linterna)
                {
            
                //Cuando la linterna está en 1 quiere decir que está en la isla, asi que se realizan los cruces de las parejas posibles
                case 1:
                    if (actual.grupoIsla.cantidadIntegrantes >1)
                    {
                        //Se recorre la lista de integrantes del grupo de la isla
                        for (int i = 0; i < actual.grupoIsla.cantidadIntegrantes; i++)
                        {
                            //Se hacen las parejas de manera que se considera que 'a y b' es igual a 'b y a'
                            if (i+1 < actual.grupoIsla.cantidadIntegrantes)
                            {
                                for (int j = i+1; j < actual.grupoIsla.cantidadIntegrantes; j++)
                                {
                                    posiciones[0] = i;
                                    posiciones[1] = j;
                                    
                                    //Se realiza la transición de cruzar para la pareja actual
                                    siguiente = cruzarPuente(actual,posiciones,2,&correlativoId);

                                    //Se verifica que el estado que se acaba de crear no esté ya abierto o cerrado
                                    if (verificarExistencia(abiertos,cantidadAbiertos,siguiente)==0 && verificarExistencia(cerrados,cantidadCerrados,siguiente)==0)
                                    {
                                        //Depende del algoritmo de busqueda se agrega el estado al inicio o al final de abiertos para anchura y profundidad respectivamente
                                        switch (algoritmoDeBusqueda)
                                        {
                                        case 1:
                                            abiertos = agregarEstadoAnchura(abiertos,&cantidadAbiertos,siguiente);
                                            break;
                                        
                                        case 2:
                                            abiertos = agregarEstadoProfundidad(abiertos,&cantidadAbiertos,siguiente);
                                            break;
                                        }
                                        
                                    }
                                    
                                }
                            }
                        }
                    }
                    break;
                
                //En el caso de que la linterna tenga el valor 2 significa que se encuentra en la ciudad, por lo que alguien se debe devolver
                case 2:

                        //Se recorren los integrantes que estén en la ciudad para devolver a cada uno de ellos en un distinto estado
                        for (int i = 0; i < actual.grupoCiudad.cantidadIntegrantes; i++)
                        {
                            posiciones[0] = i;

                            //Se crea un estado al aplicar la transicion de devolverse con la linterna a la isla
                            siguiente = devolverse(actual,posiciones,&correlativoId);

                            //Se verifica que el estado que se acaba de crear no esté ya abierto o cerrado
                            if (verificarExistencia(abiertos,cantidadAbiertos,siguiente)==0 && verificarExistencia(cerrados,cantidadCerrados,siguiente)==0)
                            {

                                //Depende del algoritmo de busqueda se agrega el estado al inicio o al final de abiertos para anchura y profundidad respectivamente
                                switch (algoritmoDeBusqueda)
                                    {
                                    case 1:
                                        abiertos = agregarEstadoAnchura(abiertos,&cantidadAbiertos,siguiente);
                                        break;
                                    
                                    case 2:
                                        abiertos = agregarEstadoProfundidad(abiertos,&cantidadAbiertos,siguiente);
                                        break;
                                    }
                            }
                        }
                    
                    break;
            }
        }
        }

        //Acá solo se llega si no se encuentra solución, por lo que el grupo no logra pasa y se le notifica al usuario.
        printf("-----Busqueda finalizada------\n");
        printf("El grupo no logra pasar en el tiempo limite\n");
        presioneEnter();
        free(abiertos);
        free(cerrados);
        return menuPrincipal(algoritmoDeBusqueda);
        break;

    //Este es el caso donde el usuario decide salir, por lo que se le da la despedida y se retorna 0 para que el main retorne 0 igual y finalice el programa
    case 2:
        printf("-----------\nHasta luego\n-----------\n");
        presioneEnter();
        limpiarConsola();
        return 0;
        break;
    }
}