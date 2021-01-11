#include "estructuras.h"

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
//Salida: No retorSin costo hasta los 30 años:na
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

//------------------------------------------------------

//Entrada: un "string" que se utilizará para decirle al usuario que debe ingresar y 2 enteros, que representan el numero minimo y maximo respectivamente que el usuario puede ingresar
//Salida: un entero, que es el numero ingresado por el usuario
//Funcion: Pide un entero hasta que se ingrese un numero y que esté dentro del rango esperado

int pedirNumero(char* string,int cotaInferior,int cotaSuperior){
    printf("%s ",string);
    char numero[5];
    fflush(stdin);
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


//--------------------------------------------------------

//Entrada: No recibe
//Salida: No entrega
//Función: Detiene el flujo del programa hasta que se presione enter

void presioneEnter(){
    printf("Presione enter para continuar...\n");
    getchar();
}

//------------------------------------------------------

//Entrada: Un puntero a estructuraGrupo
//Salida: No retorna
//Funcion: Pide y guarda el nombre y tiempo de cruce de cada integrante, ademas de pedir el tiempo limite para cruzar

void pedirDatos(estructuraGrupo * grupo){
    integrante * integrantes = (integrante *)malloc(sizeof(integrante)*grupo->cantidadIntegrantes);
    char nombre[100];
    for (int i = 0; i < grupo->cantidadIntegrantes; i++)
    {
        printf("Ingrese el nombre del integrante: ");
        fgets(nombre,100,stdin);
        int longitud = strlen(nombre);
        if(nombre[longitud-1] == '\n'){
            nombre[longitud-1] = '\0';
        }
        strcpy(integrantes[i].nombre,nombre);
        integrantes[i].tiempoEnPasar = pedirNumero("Ingrese el tiempo que demora en cruzar (minutos):",1,1000);
    }
    grupo->integrantes = integrantes;
    grupo->tiempoLimite = pedirNumero("Ingrese el tiempo limite que se dispone para cruzar",1,1000);
}

//------------------------------------------------------

//Entrada: un puntero a entero que representa el id correlativo pasado por referencia, un entero que representa el id del estado anterior, un entero que representa el tiempo total que ha transcurrido hasta antes de la transicion, un entero que representa el tiempo empleado en la transicion, 2 estructuras del tipo estructuraGrupo que representan el grupo que está en la isla y el grupo que está en la ciudad, un entero que representa la posición de la linterna.
//Salida: una estructura del tipo estado, que representa el nuevo estado que se creó
//Funcion: Crea un nuevo estado

estado crearEstado(int * id,int idAnterior,int tiempoTotal,int tiempoTransicion,estructuraGrupo grupoIsla, estructuraGrupo grupoCiudad,int posicionAntorcha){
    *id = *id+1;
    estado nuevoEstado;
    nuevoEstado.linterna = posicionAntorcha;
    nuevoEstado.id = *id;
    nuevoEstado.idAnterior = idAnterior;
    nuevoEstado.tiempoTotal = tiempoTotal + tiempoTransicion;
    nuevoEstado.grupoIsla = grupoIsla;
    nuevoEstado.grupoCiudad = grupoCiudad;
    return nuevoEstado;
}

//------------------------------------------------------

//Entrada: un puntero a entero que representa el id correlativo pasado por referencia,
//Salida: una estructura del tipo estado
//Funcion: un estado inicial

estado crearEstadoInicial(int * id, estructuraGrupo grupoIsla){
    *id = *id+1;
    estado nuevoEstado;
    nuevoEstado.linterna = 1;
    nuevoEstado.id = *id;
    nuevoEstado.idAnterior = 0;
    nuevoEstado.tiempoTotal = 0;
    nuevoEstado.grupoIsla = grupoIsla;
    estructuraGrupo grupoCiudad;
    grupoCiudad.cantidadIntegrantes = 0;
    grupoCiudad.tiempoLimite = grupoIsla.tiempoLimite;
    grupoCiudad.integrantes = (integrante *)malloc(sizeof(integrante)*grupoCiudad.cantidadIntegrantes);
    nuevoEstado.grupoCiudad = grupoCiudad;
    return nuevoEstado;
}

//------------------------------------------------------

//Entrada: un array de estructuras del tipo estado, un puntero a entero que es la cantidad de elementos que tiene la lista pasado por referencia, y una estructura del tipo estado que será la que se agregue.
//Salida: un array de estructuras del tipo estado con un elemento mas que el ingresado
//Funcion: agrega un elemento a un array de estructuras

estado * agregarEstadoAnchura(estado * lista,int * cantEstados,estado nuevoEstado){
    estado * nuevaLista = (estado *)malloc(sizeof(estado)*(*cantEstados+1));
    for (int i = 0; i < *cantEstados; i++)
    {
        nuevaLista[i] = lista[i];
    }
    nuevaLista[*cantEstados] = nuevoEstado;
    *cantEstados = *cantEstados+1;
    free(lista);
    return nuevaLista;
}

//------------------------------------------------------

//Entrada: un array de estructuras del tipo estado, un puntero a entero que es la cantidad de elementos que tiene la lista pasado por referencia, y una estructura del tipo estado que será la que se agregue.
//Salida: un array de estructuras del tipo estado con un elemento mas que el ingresado
//Funcion: agrega un elemento a un array de estructuras

estado * agregarEstadoProfundidad(estado * lista,int * cantEstados,estado nuevoEstado){
    estado * nuevaLista = (estado *)malloc(sizeof(estado)*(*cantEstados+1));
    nuevaLista[0] = nuevoEstado;
    for (int i = 1; i < *cantEstados+1; i++)
    {
        nuevaLista[i] = lista[i-1];
    }
    *cantEstados = *cantEstados+1;
    free(lista);
    return nuevaLista;
}

//------------------------------------------------------

//Entrada: un array de estructuras del tipo estado, un puntero a entero que es la cantidad de elementos que tiene la lista pasado por referencia
//Salida: un array de estructuras del tipo estado con un elemento menos que el ingresado
//Funcion: Elimina el primer elemento de una lista de estados

estado * eliminarEstado(estado * lista,int * cantEstados){
    estado * nuevaLista = (estado *)malloc(sizeof(estado)*(*cantEstados-1));
    for (int i = 1; i < *cantEstados; i++)
    {
        nuevaLista[i-1] = lista[i];
    }
    *cantEstados = *cantEstados-1;
    free(lista);
    return nuevaLista;
}

//------------------------------------------------------

//Entrada: un array de estructuras del tipo integrante, un puntero a entero que es la cantidad de elementos que tiene la lista pasado por referencia, un entero que representa la cantidad de elementos a sacar y un array de enteros con las posiciones de los elementos a sacar.
//Salida: un array de estructuras del tipo integrante con 1 o 2 elementos menos que el ingresado
//Funcion: Saca 2 o 1 elementos de un array de integrantes

integrante * sacarIntegrantes(integrante * integrantesActuales,int * cantIntegrantes,int cantASacar,int * posiciones){
    integrante * nuevosIntegrantes = (integrante *)malloc(sizeof(integrante)*(*cantIntegrantes-cantASacar));
    switch (cantASacar)
    {
    case 1:
        for (int i = 0, j = 0; i < *cantIntegrantes,j<*cantIntegrantes-cantASacar; i++,j++)
        {
            if (i != posiciones[0]){
                nuevosIntegrantes[j] = integrantesActuales[i];
            }else
            {
                j--;
            }
        }
        break;
    
    case 2:
        for (int i = 0, j = 0; i < *cantIntegrantes,j<*cantIntegrantes-cantASacar; i++,j++)
        {
            if (i != posiciones[0] && i !=posiciones[1]){
                nuevosIntegrantes[j] = integrantesActuales[i];
            }else
            {
                j--;
            }
        }
        break;
    }
    *cantIntegrantes = *cantIntegrantes-cantASacar;
    return nuevosIntegrantes;
}

//------------------------------------------------------

//Entrada: un array de estructuras del tipo integrante, un puntero a entero que es la cantidad de elementos que tiene la lista pasado por referencia y una estructura del tipo integrante que será la que se agregue
//Salida: un array de estructuras del tipo integrante con un elemento mas que el ingresado
//Funcion: agrega un elemento al array de integrantes

integrante * agregarIntegrantes(integrante * lista,int * cantidadIntegrantes,integrante nuevoIntegrante){
    integrante * nuevaLista = (integrante *)malloc(sizeof(integrante)*(*cantidadIntegrantes+1));
    
    for (int i = 0; i < *cantidadIntegrantes; i++)
    {
        nuevaLista[i]=lista[i];
    }
    nuevaLista[*cantidadIntegrantes]=nuevoIntegrante;
    *cantidadIntegrantes = *cantidadIntegrantes+1;
    return nuevaLista;
}

//------------------------------------------------------

//Entrada: una estructura del tipo estado, un array de enteros que representa las posiciones de los integrantes del grupo isla que cruzarán, un entero que representa la cantidad de integrantes que cruzarán, y un puntero a entero que representa el id actual pasado por referencia.
//Salida: un nuevo estado con la transición de cruzar puente realizada
//Funcion: Pasa 2 elementos del grupo isla al grupo ciudad calculando su tiempo de cruce y creando un nuevo estado

estado cruzarPuente(estado estadoActual,int * posiciones,int cantPosiciones,int * id){
    estructuraGrupo grupoIsla = estadoActual.grupoIsla;
    estructuraGrupo grupoCiudad = estadoActual.grupoCiudad;
    int tiempoTransicion = grupoIsla.integrantes[posiciones[0]].tiempoEnPasar;
    for (int i = 0;i <cantPosiciones;i++){
        grupoCiudad.integrantes = agregarIntegrantes(grupoCiudad.integrantes,&grupoCiudad.cantidadIntegrantes,grupoIsla.integrantes[posiciones[i]]);
        if (grupoIsla.integrantes[posiciones[i]].tiempoEnPasar > tiempoTransicion)
        tiempoTransicion = grupoIsla.integrantes[posiciones[i]].tiempoEnPasar;
    }
    grupoIsla.integrantes = sacarIntegrantes(grupoIsla.integrantes,&grupoIsla.cantidadIntegrantes,cantPosiciones,posiciones);
    estado nuevoEstado;
    nuevoEstado = crearEstado(id,estadoActual.id,estadoActual.tiempoTotal,tiempoTransicion,grupoIsla,grupoCiudad,2);
    char * temporal = "Cruza ";
    strcpy(nuevoEstado.transicion,temporal);
    if (cantPosiciones == 2){
        strcat(nuevoEstado.transicion,estadoActual.grupoIsla.integrantes[posiciones[0]].nombre);
        strcat(nuevoEstado.transicion," y ");
        strcat(nuevoEstado.transicion,estadoActual.grupoIsla.integrantes[posiciones[1]].nombre);
    }else
        strcat(nuevoEstado.transicion,estadoActual.grupoIsla.integrantes[posiciones[0]].nombre);
    strcat(nuevoEstado.transicion," de la isla a la ciudad demorando ");
    char minutosTransicion[4];
    sprintf(minutosTransicion,"%d",tiempoTransicion);
    strcat(nuevoEstado.transicion,minutosTransicion);
    strcat(nuevoEstado.transicion,", se tiene un total de ");
    char minutosTotales[4];
    sprintf(minutosTotales,"%d",nuevoEstado.tiempoTotal);
    strcat(nuevoEstado.transicion,minutosTotales);
    strcat(nuevoEstado.transicion," minutos\n");
    return nuevoEstado;
}

//------------------------------------------------------

//Entrada: una estructura del tipo estado, un array de enteros que representala posición del integrante del grupo ciudad que cruzará y un puntero a entero que representa el id actual pasado por referencia.
//Salida: un nuevo estado con la transición devolverse realizada
//Funcion: Pasa un elemento del grupo ciudad al grupo isla agregando su tiempo de cruce y creando un nuevo estado

estado devolverse(estado estadoActual,int * posicion,int * id){
    estructuraGrupo grupoIsla = estadoActual.grupoIsla;
    estructuraGrupo grupoCiudad = estadoActual.grupoCiudad;
    int tiempoTransicion = grupoCiudad.integrantes[posicion[0]].tiempoEnPasar;
    grupoIsla.integrantes = agregarIntegrantes(grupoIsla.integrantes,&grupoIsla.cantidadIntegrantes,grupoCiudad.integrantes[posicion[0]]);
    grupoCiudad.integrantes = sacarIntegrantes(grupoCiudad.integrantes,&grupoCiudad.cantidadIntegrantes,1,posicion);
    estado nuevoEstado;
    nuevoEstado = crearEstado(id,estadoActual.id,estadoActual.tiempoTotal,tiempoTransicion,grupoIsla,grupoCiudad,1);
    char * temporal = "Cruza ";
    strcpy(nuevoEstado.transicion,temporal);
    strcat(nuevoEstado.transicion,estadoActual.grupoCiudad.integrantes[posicion[0]].nombre);
    strcat(nuevoEstado.transicion," de la ciudad a la isla demorando ");
    char minutosTransicion[4];
    sprintf(minutosTransicion,"%d",tiempoTransicion);
    strcat(nuevoEstado.transicion,minutosTransicion);
    strcat(nuevoEstado.transicion,", se tiene un total de ");
    char minutosTotales[4];
    sprintf(minutosTotales,"%d",nuevoEstado.tiempoTotal);
    strcat(nuevoEstado.transicion,minutosTotales);
    strcat(nuevoEstado.transicion," minutos\n");
    return nuevoEstado;
}

//------------------------------------------------------

//Entrada: una estructura del tipo estado
//Salida: un entero, un 1 si es el estado final y un 0 en caso contrario
//Funcion: verifica si un estado es el estado final

int esFinal(estado estadoActual){
    if (estadoActual.grupoIsla.cantidadIntegrantes == 0 && estadoActual.tiempoTotal <= estadoActual.grupoIsla.tiempoLimite){
        return 1;
    }
    return 0;
}

//------------------------------------------------------

//Entrada: un array de estructuras del tipo estado, un entero que representa la cantidad de elementos que contiene el array y una estructura del tipo estado que representa el estado a verificar
//Salida: un entero, un 1 si el estado está en el array y un 0 en caso contrario
//Funcion: verifica si una estructura del tipo estado está en un array

int verificarExistencia(estado * lista,int cantEstados,estado estadoABuscar){
    int contador;
    for (int i = 0; i < cantEstados; i++)
    {
        contador = 0;
        for (int j = 0; j < estadoABuscar.grupoIsla.cantidadIntegrantes; j++)
        {
            for (int k = 0; k < lista[i].grupoIsla.cantidadIntegrantes; k++)
            {
                if (strcmp(estadoABuscar.grupoIsla.integrantes[j].nombre,lista[i].grupoIsla.integrantes[k].nombre)==0)
                {
                    contador++;
                }
                
            }
        }
        if (contador == estadoABuscar.grupoIsla.cantidadIntegrantes && contador == lista[i].grupoIsla.cantidadIntegrantes)
        {
            if(lista[i].tiempoTotal == estadoABuscar.tiempoTotal){
                return 1;
            }
        }
    }
    return 0;
}

//------------------------------------------------------

//Entrada: un array de estructuras del tipo estado, una estructura del tipo estado que representa el estado final, un entero que representa la cantidad de estados, un array de string y un entero que representa la cantidad de string presentes en el arreglo
//Salida: no entrega
//Funcion: Muestra la solución del problema devolviendose desde el estado final al inicial anotando todas las transiciones realizadas

void mostrarSolucion(estado * listaEstados, estado estadoFinal,int cantidadEstados,char ** stringsFinal, int * cantidadString){
    char ** nuevaLista = (char**)malloc(sizeof(char*)*(*cantidadString+1));
    for (int i = 0; i < *cantidadString; i++)
    {
        nuevaLista[i+1] = stringsFinal[i];
    }
    nuevaLista[0] = estadoFinal.transicion;
    *cantidadString = *cantidadString+1;
    if (estadoFinal.idAnterior == 0)
    {
        printf("----Solucion----\n");
        for (int i = 0; i < *cantidadString-1; i++)
        {
            printf("%s",stringsFinal[i]);
        }
    }else{
        for (int i = 0; i < cantidadEstados; i++)
        {
            if(listaEstados[i].id == estadoFinal.idAnterior){
                mostrarSolucion(listaEstados,listaEstados[i],cantidadEstados,nuevaLista,cantidadString);
                free(nuevaLista);
            }
        }
    }
}