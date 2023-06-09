#include "cabeceraPedido.h"

int ultimoIdPedido(char nombreArchivo[])
{
    int id = 0;
    stCabeceraPedido c;

    FILE* archi = fopen(nombreArchivo, "rb");

    if(archi)
    {
        fseek(archi, -1*(sizeof(stCabeceraPedido)), SEEK_END);
        if(fread(&c, sizeof(stCabeceraPedido), 1, archi)>0)
        {
            id = c.idCabeceraPedido;
        }
        fclose(archi);
    }
    return id;
}


void muestraUnaCabeceraPedido(stCabeceraPedido p)
{
    printf("ID PEDIDO.........: %d\n", p.idCabeceraPedido);
    printf("FECHA.............: %s\n", p.fechaPedido);
    printf("CLIENTE...........: %d\n", p.idCliente);
    printf("--------------------------------\n");

}

stCabeceraPedido fechaActual(stCabeceraPedido c)
{
    /// Tiempo actual
    time_t t = time(NULL);

    struct tm tiempoLocal = *localtime(&t);

    /// El lugar en donde se pondrá la fecha y hora formateadas
    char fechaHora[20];

    /// El formato. Mira más en https://en.cppreference.com/w/c/chrono/strftime
    char *formato = "%d/%m/%Y %H:%M:%S";

    /// Intentar formatear
    int bytesEscritos = strftime(fechaHora, sizeof (fechaHora), formato, &tiempoLocal);


    if(bytesEscritos != 0)
    {
        strcpy(c.fechaPedido, fechaHora);
    }

    return c;
}

int buscaUltimoIdCabeceraPedido(char nombreArchivo [])
{

    FILE * archi = fopen(nombreArchivo, "rb");
    int ultimoId;
    stCabeceraPedido c;

    if(archi)
    {
        fseek(archi, -1 * sizeof(stCabeceraPedido), SEEK_END);
        fread(&c, sizeof(stCabeceraPedido), 1, archi);
        ultimoId = c.idCabeceraPedido;

        fclose(archi);
    }

    return ultimoId;
}

void limpiarArchivoCabecera(char nombreArchivo[])
{

    FILE * archi = fopen(nombreArchivo, "wb");
    if(archi)
    {
        fclose(archi);
    }
}

void mostrarArchivoCabecera(char nombreArchivo[]){
    FILE* archi = fopen(nombreArchivo, "rb");
    stCabeceraPedido c;
    if(archi){
        while(fread(&c, sizeof(stCabeceraPedido), 1, archi)>0){
            muestraUnaCabeceraPedido(c);
        }
        fclose(archi);
    }
}






