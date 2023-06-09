#include "utilidades.h"

///funcion que pasa de el archivo de cabecera de pedido y lo enlaza con los clientes correspondientes
void archivoCabeceraPedido2ListaPedido(nodoCliente* listaCliente, char nombreArch[])
{
    stCabeceraPedido c; ///dato que lee de la cabecera del pedido

    FILE* arch = fopen(nombreArch, "rb");

    if(arch)
    {
        while(fread(&c, sizeof(stCabeceraPedido), 1, arch) > 0)
        {
            altaPedido(listaCliente, c);
        }
        fclose(arch);
    }
}

/**
ESTA FUNCION SOLO SIRVE PARA EL MOMENTO EN EL QUE SE BAJAN LOS DATOS DEL ARCHIVO A LAS LISTAS
CUANDO SE INCICIALIZA EL SISTEMA
NO ES PARA CUANDO EL USUARIO CREE UN NUEVO PEDIDO/PRODUCTO
*/
void altaPedido(nodoCliente* listaCliente, stCabeceraPedido cabecera)
{

    nodoCliente* auxCliente = buscarNodoIdCliente(listaCliente, cabecera.idCliente);

    if(auxCliente)
    {
        auxCliente->listaPedidos = agregoFinalListaPedido(auxCliente->listaPedidos, creaNodoPedido(cabecera));
        auxCliente->listaPedidos->costoPedido = 0;///sumaCostoPedido(auxCliente->listaPedidos->listaProducto);
    }

}



///funcion que pasa del archivo de detalle de pedido a la lista de pedidos

void archivoDetalleProducto2ListaProductos(nodoCliente* listaCliente, arbolProducto* productos, char nombreArch[])
{

    stDetallePedidos d;///funcion que almaceno lo que resivo del archivo de detalle
    nodoCliente* auxCliente = NULL;

    FILE* arch = fopen(nombreArch, "rb");

    if(arch)
    {
        while(fread(&d, sizeof(stDetallePedidos), 1, arch) > 0)
        {
            /// obtengo el cliente en base al id q tiene el detalle
            auxCliente = buscarNodoIdCliente(listaCliente, d.idCliente);

            if(auxCliente)
            {
                altaProducto(auxCliente, d, productos);
                ///auxCliente->listaPedidos->costoPedido = sumaCostoPedido(auxCliente->listaPedidos->listaProducto);
            }
        }
        fclose(arch);
    }
}

/**
ESTA FUNCION SOLO SIRVE PARA EL MOMENTO EN EL QUE SE BAJAN LOS DATOS DEL ARCHIVO A LAS LISTAS
CUANDO SE INCICIALIZA EL SISTEMA
NO ES PARA CUANDO EL ADMINISTRADOR CREA EL PRODUCTO
*/
void altaProducto(nodoCliente* cliente, stDetallePedidos detalleProducto, arbolProducto* productos)
{
    nodoPedido* auxPedido = buscarNodoIdPedido(cliente->listaPedidos, detalleProducto.idPedido);

    stProducto auxProducto = buscarArbolIdDevuelveProducto(productos, detalleProducto.idProducto);

    ///agregar a la lista de pedidos el detalle corespondeinte
    auxPedido->listaProducto = agregoFinalListaProducto(auxPedido->listaProducto, creaNodoProducto(auxProducto));


}

/**
FUNCION QUE INVOCA A LAS FUNCIONES QUE CARGAN SUS LISTAS DE MANERAS INDEPENDIENTES
RECIBE LA LISTA PRINCIPAL DE CLIENTES Y LOS NOMBRES DE SUS ARCHIVOS DE CABECERA Y DETALLE DE PRODUCTO
*/

nodoCliente* subProgramaCargaSistema(nodoCliente* listaCliente, arbolProducto* productos, char archCliente[], char archCabeceraPedido[], char archDetalleProducto[])
{
    ///funcion que me devuelve la lista de cliente completa con las listas de pedidos inicializadas
    listaCliente = archivoCliente2ListaClientes(listaCliente, archCliente);
    ///funcion que me devuelve la lista de pedidos completa con las listas de productos inicializadas
    archivoCabeceraPedido2ListaPedido(listaCliente, archCabeceraPedido);
    ///funcion que me devuelve la lista de productos completa
    archivoDetalleProducto2ListaProductos(listaCliente, productos, archDetalleProducto);

    listaCliente = sumaCostos(listaCliente);

    return listaCliente;
}

/**
FUNCION QUE CREA LOS DATOS DE LA CABECERA E INVOCA A LA FUNCION EN LA QUE EL USUARIO
CREA SU PEDIDO
*/
int cargaPedidoCliente(nodoCliente* cliente, arbolProducto* productos)
{
    stCabeceraPedido c;
    int flag = 0;

    int idCabecera = buscaUltimoIdCabeceraPedido(ARCHIVO_CABECERA_PEDIDO);
    idCabecera++;

    c.idCabeceraPedido = idCabecera;
    c = fechaActual(c);
    c.idCliente = cliente->datoCliente.idCliente;

    cliente->listaPedidos = agregarPrincipioListaPedido(cliente->listaPedidos, creaNodoPedido(c));
    flag = cargaProductosAPedido(cliente->listaPedidos, productos);

    if(flag == 0)
    {
        cliente->costoTotalPedidos = sumaPedidos(cliente->listaPedidos);
        guardaCabecera(cliente->listaPedidos, c.idCabeceraPedido, ARCHIVO_CABECERA_PEDIDO);
    }


    return flag;
}
/**
FUNCION QUE MUESTRA LOS PRODUCTOS AL CLIENTE Y ATRAVES DEL ID DEL PRODUCTO ELIJE CUAL DESEA
CARGANDOSE A SU RESPECTIVO PEDIDO
*/
int cargaProductosAPedido(nodoPedido* pedido, arbolProducto* productos)
{
    char opcion = 0;
    int id = 0;///aca se almacena el id del producto a seleccionar
    stProducto auxProdcuto; ///aca se almacena el dato que el cliente elije para su pedido
    arbolProducto* aux = NULL; ///utilizo un aux para ver si el dato que me retorno en buscarArbolIdDevuelveProducto no es basura en caso que no este en el arbol
    int flag = 0;

    while(opcion != ESC)
    {
        verProductoPorEstilo(productos);

        printf("\n\nIngrese el ID del producto que desea: ");
        scanf("%d", &id);

        auxProdcuto = buscarArbolIdDevuelveProducto(productos, id);

        aux = buscarArbolId(productos,auxProdcuto.idProducto); //ES UNA PEDORRADA PERO NO ME QUEDO OTRA


        if(aux!=NULL)
        {
            if(auxProdcuto.stock > 50)
            {
                pedido->listaProducto = agregarPrincipioListaProducto(pedido->listaProducto, creaNodoProducto(auxProdcuto));
                pedido->costoPedido += auxProdcuto.precio;
                productos = subProgramaDisminuyeStock(productos, ARCHIVO_PRODUCTO, id);

            }
            else
            {
                printf("\n<<<<STOCK INSUFICIENTE>>>>");
                flag = 1;
            }
            printf("\nESC para salir OTRO para continuar\n");
            opcion = getch();

        }
        else
        {
            printf("\n<<<<EL PRODUCTO NO EXISTE>>>>");
            flag = 1;
            getch();
        }
    }

    return flag; ///retorna si se realizo el pedido con exito o no para ver si se persisten los datos 1 no hay pedido 0 hay pedido
}
/**
MENU QUE MUESTRA QUE ESTILO DE SERVESA DESEA ELEJIR EL CLIENTE Y LE MUESTRA LOS QUE SELECCIONE
*/
void verProductoPorEstilo(arbolProducto* productos)
{
    int opcion = 0;

    titulo();
    gotoxy(10,10);
    printf("1.Rubia");
    gotoxy(10,11);
    printf("2.Roja");
    gotoxy(10,12);
    printf("3.Lupulada");
    gotoxy(10,13);
    printf("4.Negra");

    opcion = leerOpcion();

    switch(opcion)
    {

    case 1:
        system("cls");
        gotoxy(5, 2);
        printf("<<<PRODUCTOS ESTILO RUBIA>>>");
        lineaRecta(6);
        muestraProductosPorEstilo(productos, "Rubia");
        break;

    case 2:
        system("cls");
        gotoxy(5, 2);
        printf("<<<PRODUCTOS ESTILO ROJA>>>");
        lineaRecta(6);
        muestraProductosPorEstilo(productos, "Roja");
        break;

    case 3:
        system("cls");
        gotoxy(5, 2);
        printf("<<<PRODUCTOS ESTILO LUPULADA>>>");
        lineaRecta(6);
        muestraProductosPorEstilo(productos, "Lupulada");
        break;

    case 4:
        system("cls");
        gotoxy(5, 2);
        printf("<<<PRODUCTOS ESTILO NEGRA>>>");
        lineaRecta(6);
        muestraProductosPorEstilo(productos, "Negra");
        break;
    }

}


/**
FUNCION QUE VALIDA CONTRASEÑA PARA EL MOMENTO DE LOGEARSE
RECIBE EL CLIENTE Y SE FIJA QUE CONTENGAN LAS MISMAS CONTRASEÑAS
*/
int validaPasswordCliente(nodoCliente* cliente, char passWord[])
{
    int flag = 0;

    if(strcmp(cliente->datoCliente.password, passWord) == 0)
    {
        flag = 1;
    }

    return flag;
}

/**
FUNCION QUE VALIDA USERNAME PARA EL MOMENTO DE LOGEARSE
RECIBE LA LISTA Y BUSCA QUE SE ENCUENTRE ESE USUARII
*/
int validaUserNameCliente(nodoCliente* listaCliente, char userName[])
{
    int flag = 0;
    nodoCliente* auxCliente = listaCliente;

    while(auxCliente)
    {
        if(strcmp(auxCliente->datoCliente.userName, userName) == 0)
        {
            flag = 1;
        }
        auxCliente = auxCliente->siguiente;
    }

    return flag;
}

/**
ESTA FUNCION A MEDIDA QUE SE HACE UN PEDIDO LLAMA A LA FUNCION "modificarProductoEnArbol" Y
"modificarProductoEnArchivo" ASI LE DESCUENTA EL STOCK DEL ARBOL Y DEL ARCHIVO DE A 50 LITROS
QUE CORRESPONDE A UN BARRIL
*/
arbolProducto* subProgramaDisminuyeStock(arbolProducto* productosArbol, char nombreArch[], int idProducto)
{
    arbolProducto* auxProductos = productosArbol;
    auxProductos = modificarProductoEnArbol(auxProductos, idProducto);
    modificarProductoEnArchivo(nombreArch, idProducto);

    return productosArbol;
}

/**
FUNCION QUE PERSISTE TODOS LOS DATOS EN LAS CABECERAS Y DETALLES DE PEDIDO
INVOCA A LAS FUNCIONES DEL ARCHIVO
*/
void persistirDatosCabeceraYDetalle (nodoCliente * listaCliente, char archivoCabecera[], char archivoDetalle[])
{

    limpiarArchivoCabecera(archivoCabecera);
    limpiarArchivoDetalle(archivoDetalle);
    int idCabecera =1;

    nodoCliente * auxCliente = listaCliente;

    while(auxCliente)
    {
        nodoPedido * auxPedido = auxCliente->listaPedidos;

        while(auxPedido)
        {
            guardaCabecera(auxPedido,idCabecera, archivoCabecera);
            guardaDetalleToArchivo(auxPedido->listaProducto,archivoDetalle, auxCliente->datoCliente.idCliente, idCabecera);
            auxPedido=auxPedido->siguiente;
            idCabecera++;
        }
        auxCliente=auxCliente->siguiente;
    }

}

///Funcion para borrar todos los clientes con todos sus pedidos.
nodoCliente * liberarSistema(nodoCliente * lista)
{

    nodoCliente * auxCliente = lista;

    while(auxCliente)
    {
        nodoPedido * auxPedido = auxCliente->listaPedidos;

        while(auxPedido)
        {
            nodoProducto * auxProducto = auxPedido->listaProducto;
            auxProducto = borraListaProducto(auxProducto);
            auxPedido = auxPedido->siguiente;
        }
        auxCliente->listaPedidos = borraListaPedido(auxCliente->listaPedidos);
        auxCliente = auxCliente->siguiente;
    }
    lista = borraListaCliente(lista);

    return lista;
}

/**
FUNCION PARA NO REPERTIR MUCHAS VECES EL MISMO CODIGO EN LOS MENUS
*/
int ingresaIdCliente()
{
    int id = 0;
    gotoxy(9,23);
    printf("Ingrese ID del cliente: ");
    fflush(stdin);
    scanf("%d", &id);

    return id;
}

/**
FUNCION PARA NO REPERTIR MUCHAS VECES EL MISMO CODIGO EN LOS MENUS
*/
int ingresaIdProducto()
{
    int id = 0;
    gotoxy(9,23);
    printf("Ingrese ID del producto: ");
    fflush(stdin);
    scanf("%d", &id);

    return id;
}
/**
FUNCION PARA NO REPERTIR MUCHAS VECES EL MISMO CODIGO EN LOS MENUS
*/
int ingresaIdPedido()
{
    int id = 0;
    printf("\nIngrese ID del pedido: ");
    fflush(stdin);
    scanf("%d", &id);

    return id;
}

/**
FUNCION QUE DA DE BAJA UN CLIENE OSEA LE CAMBIA EL ESTADO A INACTIVO
DE LA LASTIA COMO DEL ARCHIVO
*/
nodoCliente* subProgramaBajaCliente(char nombreArch[], nodoCliente* listaCliente, int id)
{
    nodoCliente* auxCliente = listaCliente;

    bajaCliente(nombreArch, id);

    listaCliente = liberarClienteConDatoS(listaCliente, id);

    return listaCliente;
}

/**
FUNCION QUE DA DE ALTA UN CLIENE OSEA LE CAMBIA EL ESTADO A ACTIVO
DE LA LASTIA COMO DEL ARCHIVO
*/
nodoCliente* subProgramaActivaCliente(nodoCliente* listaCliente, char nombreArch[], int id, arbolProducto* productosArbol)
{
    stCliente cliente = activaCliente(nombreArch, id);

    nodoCliente* auxCliente = creaNodoCliente(cliente);

    archivoCabeceraPedido2ListaPedido(auxCliente, ARCHIVO_CABECERA_PEDIDO);
    archivoDetalleProducto2ListaProductos(auxCliente, productosArbol, ARCHIVO_DETALLE_PRODUCTO);
    auxCliente = sumaCostos(auxCliente);

    listaCliente = agregarEnOrdenListaXIdCliente(listaCliente, auxCliente);

    return listaCliente;
}

/**
BUSCA UN PEDIDO EN PARTICULAR EN EL SISTEMA Y LO RETORNA
*/
nodoPedido* subProgramaBuscaPedido(nodoCliente* listaCliente, int idPedido)
{
    nodoCliente* auxCliente = listaCliente;
    nodoPedido* aBuscar=NULL;
    int flag = 0;

    while(auxCliente && flag ==0)
    {
        nodoPedido* auxPedido = auxCliente->listaPedidos;
        while(auxPedido && flag ==0)
        {
            aBuscar = buscarNodoIdPedido(auxPedido, idPedido);
            if(aBuscar)
            {
                flag = 1;
            }
            auxPedido = auxPedido->siguiente;
        }
        auxCliente = auxCliente->siguiente;
    }
    return aBuscar;
}


/**
MUESTRA TODOS LOS PEDIDOS DEL SISTEMA
*/
void muestraPedidosSistema(nodoCliente* listaCliente)
{
    nodoCliente* auxListaCliente = listaCliente;

    while(auxListaCliente)
    {
        muestraListaPedido(auxListaCliente->listaPedidos);
        auxListaCliente = auxListaCliente->siguiente;
    }
}
/**
MUESTRA LOS PEDIDOS DE UN CLIENTE EN PARTOCULAR RESIVIDO POR PARAMETRO
*/
void muestraPedidosSistemaUnCliente(nodoCliente* listaCliente)
{
    nodoCliente* auxListaCliente = listaCliente;

    if(auxListaCliente)
    {
        muestraListaPedido(auxListaCliente->listaPedidos);
    }
}

int eliminaPedido(nodoCliente* listaCliente, int idPedido)
{
    nodoCliente* auxListaCliente = listaCliente;
    int flag = 0;

    while(auxListaCliente && flag == 0)
    {
        flag = borraPedidoYproductosCliente(auxListaCliente->listaPedidos, idPedido);
        if(flag == 1)
        {
            auxListaCliente->listaPedidos = borrarNodoIdPedido(auxListaCliente->listaPedidos, idPedido);
        }
        auxListaCliente = auxListaCliente->siguiente;
    }
    return flag;
}

/**
BORRA LOS PRODUCTOS DE UN PEDIDO EN PARTICULAR
*/
int borraPedidoYproductosCliente(nodoPedido* pedidos, int idPedido)
{
    int flag = 0;

    nodoPedido* pedidoABorrar = buscarNodoIdPedido(pedidos, idPedido);

    if(pedidoABorrar)
    {
        pedidoABorrar->listaProducto = borraListaProducto(pedidoABorrar->listaProducto);
        flag = 1;
    }

    return flag;
}


arbolProducto* subProgramaBajaProducto(arbolProducto* productos, int id)
{
    bajaProducto(ARCHIVO_PRODUCTO, id);
    productos = borrarNodoArbolPorIdProducto(productos, id);

    return productos;
}










