#ifndef LISTAPRODUCTO_H_INCLUDED
#define LISTAPRODUCTO_H_INCLUDED

#include "arbolProducto.h"

typedef struct _nodo
{
    stProducto datoProducto;
    struct _nodo *siguiente;

}nodoProducto;

nodoProducto* inicListaProducto();
nodoProducto* creaNodoProducto(stProducto datoProducto);
nodoProducto* agregarPrincipioListaProducto(nodoProducto* lista,nodoProducto * nodoNuevo);
nodoProducto* agregoFinalListaProducto(nodoProducto* lista, nodoProducto* nuevoNodo);
nodoProducto* agregarEnOrdenListaXNombreProducto(nodoProducto* lista, nodoProducto* nuevoNodo);///borrar
nodoProducto* buscaUltimoNodoProducto(nodoProducto* lista);
void muestraListaProducto(nodoProducto* lista);
void muestraUnNodoProducto(nodoProducto * nodoProducto);


nodoProducto* borrarNodoIdProducto(nodoProducto* lista, int id);
nodoProducto* borraListaProducto(nodoProducto* lista);
nodoProducto* eliminaUltimoNodoProducto(nodoProducto* lista);
nodoProducto* eliminaPrimerNodoProducto(nodoProducto* lista);
nodoProducto* desvinculaNodoProducto(nodoProducto** pLista);
nodoProducto* buscarNodoProducto(nodoProducto* lista, int id);
nodoProducto* crearListaOrdenadaXNombreProducto(nodoProducto* lista);///elimar

void guardaDetalleToArchivo(nodoProducto * lista, char nombreArchivo[], int  idCliente, int idPedido);



#endif // LISTAPRODUCTO_H_INCLUDED
