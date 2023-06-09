#ifndef DETALLEPEDIDO_H_INCLUDED
#define DETALLEPEDIDO_H_INCLUDED

#include "producto.h"

#define ARCHIVO_DETALLE_PRODUCTO "detalleProducto.dat"


typedef struct
{
    int idPedido;///este id proviene de la lista de pedidos(pedido 1, pedido 2...)
    int idDetallePedido;///autoicrementeal que se agrega en el archivo
    int idProducto;/// viene del arbol
    int idCliente;///de la lista de cliente

}stDetallePedidos;

void muestraUnDetallePedido(stDetallePedidos d);
void mostrarArchivoDetallePedido(char nombreArchivo[]);
int buscaUltimoIdDetallePedido(char nombreArchivo []);

void limpiarArchivoDetalle(char nombreArchivo[]);


#endif // DETALLEPEDIDO_H_INCLUDED
