typedef struct integrante
{
    char nombre[100];
    int tiempoEnPasar;
}integrante;

typedef struct estructuraGrupo
{
    int cantidadIntegrantes;
    integrante * integrantes;
    int tiempoLimite;
}estructuraGrupo;

typedef struct estado
{
    int antorcha;
    int id;
    int idAnterior;
    int tiempoTotal;
    char transicion[200];
    estructuraGrupo grupoIsla;
    estructuraGrupo grupoCiudad;
}estado;