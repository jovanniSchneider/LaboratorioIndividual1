#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
int main()
{
    int numero = pedirNumero("Por favor ingrese un numero entre 1 y 3:",1,3);
    return 0;
}
