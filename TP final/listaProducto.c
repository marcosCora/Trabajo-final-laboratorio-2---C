#include "listaProducto.h"

nodoProducto* inicListaProducto()
{
    return NULL;
}

///funcion que crea un nuevo nodoProducto

nodoProducto* creaNodoProducto(stProducto dato)
{
    ///creo en espacio de memoria un lugar para almacenar mi nuevo nodoProducto
    nodoProducto* nodoNuevo = (nodoProducto*) malloc(sizeof(nodoProducto));

    ///le asigno el dato a el nodoProducto nuevo
    nodoNuevo->datoProducto = dato;

    ///marco el siguiente nodoProducto como NULL
    nodoNuevo->siguiente = NULL;


    return nodoNuevo;
}

///Funcion que agrega datos a la lista desde el principio

nodoProducto* agregarPrincipioListaProducto(nodoProducto* lista,nodoProducto * nodoNuevo)
{
    ///si la lista no tiene nodos asgina el nuevoNodo como primer elemento de la lista
    if(lista == NULL)
    {
        lista = nodoNuevo;
    }
    else
    {
        ///si no al nuevo nodoProducto le carga la direccion de memoria del primer nodoProducto de la lista
        nodoNuevo->siguiente = lista;

        ///piso lo que almacena lista con el nodoNuevo ya que este contiene las direcciones de los siguientes nodoProducto al
        ///almacenarse en el principio de la lista
        lista = nodoNuevo;
    }

    return lista;
}

///agrego el final de la lista

nodoProducto* agregoFinalListaProducto(nodoProducto* lista, nodoProducto* nuevoNodo)
{
    nodoProducto* ultimo;

    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        ultimo = buscaUltimoNodoProducto(lista);///almaceno el ultimo nodoProducto en la variable ultimo
        ultimo->siguiente = nuevoNodo;///le asigno el nuevo nodoProducto al siguiente de ultimo
    }

    return lista;
}

///busca ultimo nodo

nodoProducto* buscaUltimoNodoProducto(nodoProducto* lista)
{
    nodoProducto* aux = lista; ///creo una variable auxilar

    if(aux != NULL)
    {
        while(aux->siguiente != NULL) ///recorrre la lista hasta que el siguiente sea NULL
        {
            aux = aux->siguiente;
        }
    }

    return aux;///retorno el ultimo
}

///funcion que agrega en orden a una lista ya ordenada

nodoProducto* agregarEnOrdenListaXNombreProducto(nodoProducto* lista, nodoProducto* nuevoNodo)
{
    nodoProducto* seg = lista;
    nodoProducto* ante;

    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        ///si el nuevo nodo debe colocarse al principio se llama a la funcion de agregar el principio
        if((seg != NULL) && (strcmpi(seg->datoProducto.nombre , nuevoNodo->datoProducto.nombre) > 0))
        {
            lista = agregarPrincipioListaProducto(lista, nuevoNodo);
        }
        else///si no recorre la lista y busca el hueco donde ubicarlo
        {
            while((seg != NULL) && (strcmpi(seg->datoProducto.nombre, nuevoNodo->datoProducto.nombre) < 0))
            {
                ante = seg;
                seg = seg->siguiente;

            }
            ante->siguiente = nuevoNodo;
            nuevoNodo->siguiente = seg;
        }
    }

    return lista;
}

///muestra un nodo

void muestraUnNodoProducto(nodoProducto* listaProducto)
{
    muestraUnProducto(listaProducto->datoProducto);
}


///muestra lista

void muestraListaProducto(nodoProducto* lista)
{
    nodoProducto* aux = lista;

    while(aux != NULL)
    {
        muestraUnNodoProducto(aux);
        aux = aux->siguiente;
    }

}


///borrar lista

nodoProducto* borraListaProducto(nodoProducto* lista)
{
    nodoProducto* aux;///creo una variable para ir liberando esa parte de memoria

    while(lista != NULL)
    {
        aux = lista;///le asigno a aux la lista
        lista = lista->siguiente;///lista se asigna el siguiente y pierdo el primer valor
        free(aux);///borro el nodo con la informacion de aux
    }

    return lista;
}

///funcion que elimina el ultimo nodo de una lista
nodoProducto* eliminaUltimoNodoProducto(nodoProducto* lista)
{
    nodoProducto* aux = lista;///creo una variable auxiliar
    nodoProducto* ante;///anterior

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


nodoProducto* eliminaPrimerNodoProducto(nodoProducto* lista)
{
    nodoProducto* aux = lista;///creo una lista auxilliar y el asigno la lista recibida

    if(lista != NULL)
    {
        lista = lista->siguiente;///le asgino a lista el siguiente nodo que sera el primero
        free(aux);///elimino el primer nodo
    }

    return lista;///retorno la lista
}

///busca un nodo por numero de id
///retorna el nodo si se encuentra y si no retorna null
nodoProducto* buscarNodoIdProducto(nodoProducto* lista, int id)
{
    nodoProducto* aux = lista;///creo una variable seguidora

    while((aux != NULL) && (aux->datoProducto.idProducto != id))///recorro la lista mientras no finalize o no se encuentre el nodo
    {
        aux = aux->siguiente;
    }

    return aux;///retorno el nodo donde del que se busco o NULL si no se encuentra
}

nodoProducto* borrarNodoIdProducto(nodoProducto* lista, int id)
{
    ///creo dos listas que sirven para recorrer la lista sin perder datos
    nodoProducto* seg;
    nodoProducto* ante;

    if(lista != NULL && lista->datoProducto.idProducto == id)///si la lista no esta vacia y el primer nodoProducto es el buscado se elimina
    {
        lista = eliminaPrimerNodoProducto(lista);
    }
    else
    {
        seg = lista;///le asgino la lista a siguiente
        while((seg != NULL) && seg->datoProducto.idProducto != id)///recorre la lista mientras no sea NULL y no se encuentre el dato
        {
            ante = seg;
            seg = seg->siguiente;
        }
        if(seg != NULL)///si seg no es NULL significa que el dato se encontr
        {
            ante->siguiente = seg->siguiente;///redirreciono los nodos
            free(seg);///elimino el nodoProducto
        }
    }

    return lista;
}


///funcion que va creando una lista ordenada a medida que es cargada
nodoProducto* crearListaOrdenadaXNombreProducto(nodoProducto* lista)
{
    char opcion;

    while(opcion != ESC)
    {
        lista = agregarEnOrdenListaXNombreProducto(lista, creaNodoProducto(cargaUnProducto()));

        printf("\nESC para salir/otro para continuar\n\n");
        opcion = getch();
    }

    return lista;
}



///funcion que devincula un nodo de la lista recibida y lo retorna solo

nodoProducto* desvinculaNodoProducto(nodoProducto** pLista)///recibe un puntero doble a la lista
{
    nodoProducto* aux;///crea un axuliar

    if((*pLista))///mientras a lo que apunta lista tenga datos
    {
        aux  = (*pLista);///le asigno el primer nodo a auxiliar
        (*pLista) = (*pLista)->siguiente;///hago que el primer dato de la lista sea el siguiente del primero recibido
        aux->siguiente = NULL;///el siguiente del primero lo convierto en NULL desvinculando de la lista
    }
    return aux;///retorno el nodo desvinculado
}

void guardaDetalleToArchivo(nodoProducto * lista, char nombreArchivo[], int  idCliente, int idPedido)
{
    nodoProducto * aux = lista;
    stDetallePedidos d;
    int idDet;
    FILE * archi = fopen(nombreArchivo, "ab");
    idDet = buscaUltimoIdDetallePedido(nombreArchivo);
    if(archi)
    {
        while(aux)
        {
            idDet++;
            d.idProducto = aux->datoProducto.idProducto;
            d.idCliente = idCliente;
            d.idDetallePedido = idDet;
            d.idPedido = idPedido;


            fwrite(&d, sizeof(stDetallePedidos), 1, archi);

            aux=aux->siguiente;
        }
        fclose(archi);
    }

}
















