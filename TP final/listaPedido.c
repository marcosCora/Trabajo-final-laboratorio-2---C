#include "listaPedido.h"

nodoPedido* inicListaPedido()
{
    return NULL;
}

///funcion que crea un nuevo nodoPedido

nodoPedido* creaNodoPedido(stCabeceraPedido dato)
{
    nodoPedido* nodoNuevo = (nodoPedido*) malloc(sizeof(nodoPedido));
    nodoNuevo->datoPedido = dato;
    nodoNuevo->listaProducto = inicListaProducto();
    nodoNuevo->siguiente = NULL;

    return nodoNuevo;
}

///Funcion que agrega datos a la lista desde el principio

nodoPedido* agregarPrincipioListaPedido(nodoPedido* lista, nodoPedido * nodoNuevo)
{
    ///si la lista no tiene nodos asgina el nuevoNodo como primer elemento de la lista
    if(lista == NULL)
    {
        lista = nodoNuevo;
    }
    else
    {
        ///si no al nuevo nodoPedido le carga la direccion de memoria del primer nodoPedido de la lista
        nodoNuevo->siguiente = lista;

        ///piso lo que almacena lista con el nodoNuevo ya que este contiene las direcciones de los siguientes nodoPedido al
        ///almacenarse en el principio de la lista
        lista = nodoNuevo;
    }

    return lista;
}

///agrego el final de la lista

nodoPedido* agregoFinalListaPedido(nodoPedido* lista, nodoPedido* nuevoNodo)
{
    nodoPedido* ultimo;

    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        ultimo = buscaUltimoNodoPedido(lista);///almaceno el ultimo nodoPedido en la variable ultimo
        ultimo->siguiente = nuevoNodo;///le asigno el nuevo nodoPedido al siguiente de ultimo
    }

    return lista;
}

///busca ultimo nodo

nodoPedido* buscaUltimoNodoPedido(nodoPedido* lista)
{
    nodoPedido* aux = lista; ///creo una variable auxilar

    if(aux != NULL)
    {
        while(aux->siguiente != NULL) ///recorrre la lista hasta que el siguiente sea NULL
        {
            aux = aux->siguiente;
        }
    }

    return aux;///retorno el ultimo
}


///muestra un nodo

void muestraUnNodoPedido(nodoPedido* pedido)
{
    printf("\n--------------------------------------------------\n");
    muestraUnaCabeceraPedido(pedido->datoPedido);
    printf("COSTO PEDIDO......: %.2f\n", pedido->costoPedido);
    printf("\n--------------------------------------------------\n");
}


///muestra lista
void muestraListaPedido(nodoPedido* lista)
{
    nodoPedido* aux = lista;

    while(aux != NULL)
    {
        muestraUnNodoPedido(aux);
        aux = aux->siguiente;
    }

}


///borrar lista

nodoPedido* borraListaPedido(nodoPedido* lista)
{
    nodoPedido* aux;///creo una variable para ir liberando esa parte de memoria

    while(lista != NULL)
    {
        aux = lista;///le asigno a aux la lista
        lista = lista->siguiente;///lista se asigna el siguiente y pierdo el primer valor
        free(aux);///borro el nodo con la informacion de aux
    }

    return lista;
}

///funcion que elimina el ultimo nodo de una lista
nodoPedido* eliminaUltimoNodoPedido(nodoPedido* lista)
{
    nodoPedido* aux = lista;///creo una variable auxiliar
    nodoPedido* ante;///anterior

    if(lista != NULL)
    {
        while(aux->siguiente != NULL)///recorro hasta el ultimo nodo de la lista
        {
            ante = aux;///le asigno a ante lo que se almacena en aux antes de correr hacia adelante
            aux = aux->siguiente;///me corro de la lista
        }
    }
    ante->siguiente = NULL;
    free(aux);


    return lista;
}


nodoPedido* eliminaPrimerNodoPedido(nodoPedido* lista)
{
    nodoPedido* aux = lista;///creo una lista auxilliar y el asigno la lista recibida

    if(lista != NULL)
    {
        lista = lista->siguiente;///le asgino a lista el siguiente nodo que sera el primero
        free(aux);///elimino el primer nodo
    }

    return lista;///retorno la lista
}

///busca un nodo por numero de id
///retorna el nodo si se encuentra y si no retorna null

nodoPedido* buscarNodoIdPedido(nodoPedido* lista, int id)
{
    nodoPedido* aux = lista;///creo una variable seguidora

    while((aux != NULL) && (aux->datoPedido.idCabeceraPedido != id))///recorro la lista mientras no finalize o no se encuentre el nodo
    {
        aux = aux->siguiente;
    }

    return aux;///retorno el nodo donde del que se busco o NULL si no se encuentra
}


nodoPedido* borrarNodoIdPedido(nodoPedido* lista, int id)
{
    ///creo dos listas que sirven para recorrer la lista sin perder datos
    nodoPedido* seg;
    nodoPedido* ante;

    if(lista != NULL && lista->datoPedido.idCabeceraPedido == id)///si la lista no esta vacia y el primer nodoPedido es el buscado se elimina
    {
        lista = eliminaPrimerNodoPedido(lista);
    }
    else
    {
        seg = lista;///le asgino la lista a siguiente
        while((seg != NULL) && seg->datoPedido.idCabeceraPedido != id)///recorre la lista mientras no sea NULL y no se encuentre el dato
        {
            ante = seg;
            seg = seg->siguiente;
        }
        if(seg != NULL)///si seg no es NULL significa que el dato se encontr
        {
            ante->siguiente = seg->siguiente;///redirreciono los nodos
            free(seg);///elimino el nodoPedido
        }
    }

    return lista;
}

///funcion que devincula un nodo de la lista recibida y lo retorna solo

nodoPedido* desvinculaNodoPedido(nodoPedido** pLista)///recibe un puntero doble a la lista
{
    nodoPedido* aux;///crea un axuliar

    if((*pLista))///mientras a lo que apunta lista tenga datos
    {
        aux  = (*pLista);///le asigno el primer nodo a auxiliar
        (*pLista) = (*pLista)->siguiente;///hago que el primer dato de la lista sea el siguiente del primero recibido
        aux->siguiente = NULL;///el siguiente del primero lo convierto en NULL desvinculando de la lista
    }
    return aux;///retorno el nodo desvinculado
}



void listaPedido2CabeceraPedido(nodoPedido* listaPedido, char nombreArch[])///carga archivo de cabecera
{

    FILE* arch = fopen(nombreArch, "ab");
    int id = ultimoIdPedido(nombreArch);

    nodoPedido* aux = listaPedido;

    stCabeceraPedido c;

    if(arch)
    {
        while(aux)
        {
            c.idCabeceraPedido += id;
            strcpy(c.fechaPedido, aux->datoPedido.fechaPedido);

            c.idCabeceraPedido = aux->datoPedido.idCabeceraPedido;

            c.descuento = -1;

            fwrite(&c, sizeof(stCabeceraPedido), 1, arch);
            aux = aux->siguiente;
        }
        fclose(arch);
    }

}

void guardaCabecera(nodoPedido * pedido, int idCabecera, char archivoCabecera[])
{

    stCabeceraPedido p;
    FILE * archi = fopen(archivoCabecera, "ab");
    if(archi)
    {
        p = pedido->datoPedido;
        p.idCabeceraPedido=idCabecera;
        fwrite(&p, sizeof(stCabeceraPedido), 1, archi);

        fclose(archi);
    }
}

float sumaCostoProducto(nodoProducto* listaProducto)
{
    nodoProducto* auxProducto = listaProducto;
    float sumaCosto = 0;

    while(auxProducto)
    {
        sumaCosto += auxProducto->datoProducto.precio;
        auxProducto = auxProducto->siguiente;
    }
    return sumaCosto;
}















