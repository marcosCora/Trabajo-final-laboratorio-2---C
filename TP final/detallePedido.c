#include "detallePedido.h"

void muestraUnDetallePedido(stDetallePedidos d)
{
    printf("ID PEDIDO.............: %d\n", d.idPedido);
    printf("ID DETALLE PEDIDO.....: %d\n", d.idDetallePedido);
    printf("ID PRODUCTO...........: %d\n", d.idProducto);
    printf("ID CLIENTE............: %d\n", d.idCliente);
    printf("-----------------------------\n");


}

void mostrarArchivoDetallePedido(char nombreArchivo[])
{
    FILE* archi = fopen(nombreArchivo, "rb");
    stDetallePedidos d;
    if(archi)
    {
        while(fread(&d, sizeof(stDetallePedidos), 1, archi)>0)
        {
            muestraUnDetallePedido(d);
        }
        fclose(archi);
    }
}



int buscaUltimoIdDetallePedido(char nombreArchivo [])
{

    FILE * archi = fopen(nombreArchivo, "rb");
    int ultimoId=0;
    stDetallePedidos det;

    if(archi)
    {
        fseek(archi, -1 * sizeof(stDetallePedidos), SEEK_END);
        if(fread(&det, sizeof(stDetallePedidos), 1, archi)>0)
        {
            ultimoId = det.idDetallePedido;
        }



        fclose(archi);
    }
    return ultimoId;
}


void limpiarArchivoDetalle(char nombreArchivo[])
{

    FILE * archi = fopen(nombreArchivo, "wb");
    if(archi)
    {
        fclose(archi);
    }
}
