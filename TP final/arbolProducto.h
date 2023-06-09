#ifndef ARBOLPRODUCTO_H_INCLUDED
#define ARBOLPRODUCTO_H_INCLUDED

#include "producto.h"

typedef struct _arbol
{
    stProducto datoProducto;
    struct _arbol* izq;
    struct _arbol* der;
}arbolProducto;

arbolProducto * inicArbol ();
arbolProducto * crearNodoArbol (stProducto dato);

void muestraUnNodoArbol (arbolProducto * arbol);
void preorder (arbolProducto * arbol);
void inorder (arbolProducto * arbol);
void posorder(arbolProducto * arbol);

arbolProducto * insertarArbolId (arbolProducto * arbol, arbolProducto * nuevo);
arbolProducto * buscarArbolId (arbolProducto * arbol, int id);
arbolProducto * subprogramaArchivo2ArbolBalanceado(char nombreArchivo[], arbolProducto * arbol);
arbolProducto* buscaNodoMasDerecho(arbolProducto* arbol);
arbolProducto* buscaNodoMasIzquierdo(arbolProducto* arbol);
arbolProducto* borrarNodoArbolPorIdProducto(arbolProducto* arbol, int id);

///FUNCION PARA LA AGREGAR EN UN ARBOL DESDE UN ARRAY Y QUE ESTE EQUILIBRADO
arbolProducto* array2Arbol(stProducto p[], int i, int v);
arbolProducto * modificarProductoEnArbol(arbolProducto * arbol, int idProducto);
void  muestraProductosPorEstilo(arbolProducto* arbol, char estilo[]);
stProducto buscarArbolIdDevuelveProducto (arbolProducto * arbol, int id);
arbolProducto* modificaProductoAdmin(arbolProducto* arbol);

#endif // ARBOLPRODUCTO_H_INCLUDED
