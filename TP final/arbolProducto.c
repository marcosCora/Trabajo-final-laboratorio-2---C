#include "arbolProducto.h"

arbolProducto * inicArbol ()
{
    return NULL;
}

arbolProducto * crearNodoArbol (stProducto dato)
{
    arbolProducto * arbol = (arbolProducto *)malloc(sizeof(arbolProducto)); /// creo el nodo
    arbol->datoProducto = dato;       /// igualo la variable datos a la que recibo
    arbol->der=NULL;               /// inicializo dereca en NULL
    arbol->izq=NULL;                /// inicializo izquierda en NULL

    return arbol;   /// retorno el arbol
}

void muestraUnNodoArbol (arbolProducto * arbol)
{
    muestraUnProducto(arbol->datoProducto);
}


void preorder (arbolProducto * arbol)
{

    if(arbol)
    {
        muestraUnNodoArbol(arbol);
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

void inorder (arbolProducto * arbol)
{
    if(arbol)
    {
        inorder(arbol->izq);
        muestraUnNodoArbol(arbol);
        inorder(arbol->der);
    }
}

void posorder(arbolProducto * arbol)
{
    if(arbol)
    {
        posorder(arbol->izq);
        posorder(arbol->der);
        muestraUnNodoArbol(arbol);

    }

}

arbolProducto * insertarArbolId (arbolProducto * arbol, arbolProducto * nuevo)
{
    if(!arbol)
    {
        arbol = nuevo;
    }
    else
    {
        if(nuevo->datoProducto.idProducto > arbol->datoProducto.idProducto)
        {
            arbol->der = insertarArbolId(arbol->der, nuevo);
        }
        else
        {
            arbol->izq = insertarArbolId(arbol->izq, nuevo);
        }
    }
    return arbol;
}

///funcion que pasa del archivo de productos a un arbol balanceado
arbolProducto * subprogramaArchivo2ArbolBalanceado (char nombreArchivo[], arbolProducto * arbol)
{
    int dimension = cuentaCantProductosActivos(ARCHIVO_PRODUCTO);///la funcion que se invoca devuelve la cantidad de productos activos en el sistema
    stProducto* p = (stProducto*) malloc(sizeof(stProducto)* dimension);///creo un arreglo del tamaño justo
    int validos = 0;


    validos = archivo2ArrayProducto(p, dimension, validos, nombreArchivo);

    arbol = array2Arbol(p, 0, validos-1);

    return arbol;  /// retorno el arbol
}

arbolProducto * buscarArbolId (arbolProducto * arbol, int id)
{

    arbolProducto * aux = NULL;

    if(arbol)
    {
        if(arbol->datoProducto.idProducto == id)
        {
            aux = arbol;
        }
        else
        {
            if(id > arbol->datoProducto.idProducto)
            {
                aux = buscarArbolId(arbol->der, id);
            }
            else
            {
                aux=buscarArbolId(arbol->izq, id);
            }
        }

    }
    return aux;
}



///FUNCION PARA LA AGREGAR EN UN ARBOL DESDE UN ARRAY Y QUE ESTE EQUILIBRADO
arbolProducto* array2Arbol(stProducto p[], int i, int v) ///LE PASO EL INICIO DEL ARRAY Y LOS VALIDOS
{
    int medio;
    arbolProducto* arbol = NULL;

    if(!(i>v))
    {
        medio = (i+v)/2;
        arbol = crearNodoArbol(p[medio]);
        arbol->izq = array2Arbol(p, i, medio-1);
        arbol->der = array2Arbol(p, medio+1,v);
    }
    return arbol;
}

///funcion que busca arbol nodo mas derecho

arbolProducto* buscaNodoMasDerecho(arbolProducto* arbol)
{

    arbolProducto* rta;

    if(arbol)
    {

        if(arbol->der)
        {
            rta = buscaNodoMasDerecho(arbol->der);
        }
        else
        {

            rta = arbol;
        }

    }

    return rta;
}

///funcion que busca arbol nodo mas izquierdo

arbolProducto* buscaNodoMasIzquierdo(arbolProducto* arbol)
{

    arbolProducto* rta;

    if(arbol)
    {

        if(arbol->izq)
        {

            rta = buscaNodoMasIzquierdo(arbol->izq);
        }
        else
        {

            rta = arbol;
        }

    }

    return rta;
}

arbolProducto* borrarNodoArbolPorIdProducto(arbolProducto* arbol, int id)
{

    if(arbol)
    {

        if(id == arbol->datoProducto.idProducto)
        {
            if(arbol->izq)
            {
                arbolProducto* masDerecho = buscaNodoMasDerecho(arbol->izq);
                arbol->datoProducto = masDerecho->datoProducto;
                arbol->izq = borrarNodoArbolPorIdProducto(arbol->izq, masDerecho->datoProducto.idProducto);
            }
            else if(arbol->der)
            {
                arbolProducto* masIzquierda = buscaNodoMasIzquierdo(arbol->der);
                arbol->datoProducto = masIzquierda->datoProducto;
                arbol->der = borrarNodoArbolPorIdProducto(arbol->der, masIzquierda->datoProducto.idProducto);
            }
            else
            {
                free(arbol);
                arbol = NULL;
            }

        }
        else if(arbol->datoProducto.idProducto > id)///busco por izquierda
        {
            arbol->izq = borrarNodoArbolPorIdProducto(arbol->izq, id);
        }

        else ///busco por derecha
        {
            arbol->der = borrarNodoArbolPorIdProducto(arbol->der, id);
        }
    }


    return arbol;
}


arbolProducto * modificarProductoEnArbol(arbolProducto * arbol, int idProducto)
{

    arbolProducto * aux = buscarArbolId(arbol, idProducto);

    if(aux)
    {
        aux->datoProducto.stock = aux->datoProducto.stock - 50;
    }

    return arbol;
}

///FUNCION PARA BUSCAR EL PRODUCTO EN EL ARBOL Y MOSTRARLO CON UN FILTRO (ESTILO)

void  muestraProductosPorEstilo(arbolProducto* arbol, char estilo[])
{
    if(arbol)
    {
        if(strcmp(arbol->datoProducto.estilo, estilo)==0)

        {
            muestraUnNodoArbol(arbol);
        }
        muestraProductosPorEstilo(arbol->izq, estilo);
        muestraProductosPorEstilo(arbol->der, estilo);

    }

}

stProducto buscarArbolIdDevuelveProducto (arbolProducto * arbol, int id)
{
    stProducto p;///donde se almacena el producto que se va a devolver

    if(arbol)
    {
        if(arbol->datoProducto.idProducto == id)
        {
            p = arbol->datoProducto;
        }
        else
        {
            if(id > arbol->datoProducto.idProducto)
            {
                p = buscarArbolIdDevuelveProducto(arbol->der, id);
            }
            else
            {
                p = buscarArbolIdDevuelveProducto(arbol->izq, id);
            }
        }

    }
    return p;
}

//FUNCION PARA MODIFICAR UN PRODUCTO DESDE ADMINISTRADOR

arbolProducto* modificaProductoAdmin(arbolProducto* arbol)
{
    int id;
    int guardaStock;
    float guardaPrecio;
    char guardaString[30];
    int opcion;

    gotoxy(9, 23);
    printf("Ingrese ID del producto a modificar: ");
    fflush(stdin);
    scanf("%d", &id);

    arbolProducto* aux = buscarArbolId(arbol, id);

    if(aux)
    {
        do
        {
            titulo();
            gotoxy(10,10);
            printf("1.Nombre");
            gotoxy(10,11);
            printf("2.Marca");
            gotoxy(10,12);
            printf("3.Estilo");
            gotoxy(10,13);
            printf("4.Precio");
            gotoxy(10,14);
            printf("5.Stock");
            gotoxy(10,15);
            printf("0.Salir");

            opcion = leerOpcion();

            switch(opcion)
            {

            case 1:
                titulo();
                gotoxy(10,10);
                printf("Ingrese nuevo Nombre: ");
                fflush(stdin);
                gets(guardaString);
                strcpy(aux->datoProducto.nombre, guardaString);
                gotoxy(9, 23);
                printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
                getch();
                break;

            case 2:
                titulo();
                gotoxy(10,10);
                printf("Ingrese nueva marca: ");
                fflush(stdin);
                gets(guardaString);
                strcpy(aux->datoProducto.marca, guardaString);
                gotoxy(9, 23);
                printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
                getch();
                break;

            case 3:
                titulo();
                gotoxy(10,10);
                printf("Ingrese nuevo estilo: ");
                fflush(stdin);
                gets(guardaString);
                strcpy(aux->datoProducto.estilo, guardaString);
                gotoxy(9, 23);
                printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
                getch();
                break;

            case 4:
                titulo();
                gotoxy(10,10);
                printf("Ingrese nuevo precio: ");
                fflush(stdin);
                scanf("%f", &guardaPrecio);
                aux->datoProducto.precio = guardaPrecio;
                gotoxy(9, 23);
                printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
                getch();
                break;

            case 5:
                titulo();
                gotoxy(10,10);
                printf("Ingrese nuevo stock: ");
                fflush(stdin);
                scanf("%d", &guardaStock);
                aux->datoProducto.stock = guardaStock;
                gotoxy(9, 23);
                printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
                getch();
                break;

            case 0:
                break;

            }

        }
        while(opcion != 0);
    }
    return arbol;

}








