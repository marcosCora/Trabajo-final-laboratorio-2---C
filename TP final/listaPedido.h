#ifndef LISTAPEDIDO_H_INCLUDED
#define LISTAPEDIDO_H_INCLUDED

#include "cabeceraPedido.h"
#include "listaProducto.h" ///lista de productos


typedef struct _nodoPedido
{
    stCabeceraPedido datoPedido;
    float costoPedido;

    struct _nodoPedido* siguiente;
    nodoProducto* listaProducto;

}nodoPedido;

nodoPedido* inicListaPedido();
nodoPedido* creaNodoPedido();
nodoPedido* agregarPrincipioListaPedido(nodoPedido* lista,nodoPedido * nodoNuevo);
nodoPedido* agregoFinalListaPedido(nodoPedido* lista, nodoPedido* nuevoNodo);
nodoPedido* buscaUltimoNodoPedido(nodoPedido* lista);

void muestraUnNodoPedido(nodoPedido* pedido);
void muestraListaPedido(nodoPedido* lista);

nodoPedido* borraListaPedido(nodoPedido* lista);
nodoPedido* eliminaUltimoNodoPedido(nodoPedido* lista);
nodoPedido* eliminaPrimerNodoPedido(nodoPedido* lista);
nodoPedido* buscarNodoIdPedido(nodoPedido* lista, int id);
nodoPedido* borrarNodoIdPedido(nodoPedido* lista, int id);
nodoPedido* desvinculaNodoPedido(nodoPedido** pLista);

/// manejo de archivos
void guardaCabecera(nodoPedido * pedido, int idCabecera, char archivoCabecera[]);
void listaPedido2CabeceraPedido(nodoPedido* listaPedido, char nombreArch[]);
float sumaCostoProducto(nodoProducto* listaProducto);



#endif // LISTAPEDIDO_H_INCLUDED
