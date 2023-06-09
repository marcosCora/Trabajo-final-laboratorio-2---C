#include "menu.h"

void cleanAndSetScreen()
{
    system("cls");
    titulo();
    gotoxy(10,10);
}

void titulo()
{
    system("cls");
    marco();
    gotoxy(30,5);
    printf("TecBeer");
}

int leerOpcion()
{
    int opcion;
    gotoxy(10, 20);
    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

void lineaRecta(int x)
{
    for(; 9<x; x--)
    {
        printf("%c", 205);
    }
}

void lineaRectavertical(int x,int y)
{
    for(; 3<y; y--)
    {
        gotoxy(x,y);
        printf("%c",186);
    }
}



void marco()
{
    gotoxy(8,3);
    printf("%c", 201);
    lineaRecta(58);
    gotoxy(8,22);
    printf("%c", 200);
    lineaRecta(58);
    gotoxy(58,22);
    printf("%c", 188);
    gotoxy(58,3);
    printf("%c", 187);
    lineaRectavertical(58, 21);
    lineaRectavertical(8, 21);


}

void menuPrincipal()
{

    int opcion;

    arbolProducto* productosArbol = inicArbol();
    productosArbol = subprogramaArchivo2ArbolBalanceado(ARCHIVO_PRODUCTO, productosArbol);

    nodoCliente* listaCliente = inicListaCliente();
    listaCliente = subProgramaCargaSistema(listaCliente, productosArbol, ARCHIVO_CLIENTE, ARCHIVO_CABECERA_PEDIDO, ARCHIVO_DETALLE_PRODUCTO);

    do
    {
        titulo();
        gotoxy(10,10);
        printf("1. Loguearse");
        gotoxy(10,11);
        printf("2. Registrarse");
        gotoxy(10,12);
        printf("0. Salir");

        opcion = leerOpcion();

        switch(opcion)
        {

        case 1:
            SubProgramaLogIn(listaCliente, productosArbol);
            break;

        case 2:
            registrarse(listaCliente);
            break;

        case 0:
            break;
        }

    }
    while(opcion != 0);
}

void logIn(nodoCliente* listaCliente, int *guardaRol, int *idCliente)
{
    nodoCliente* auxCliente = NULL;
    int flagPasword = 0;///aca se almacena lo que devuelve la validacion de la contraseña
    int flagUserName = 0;///aca se almacena lo que devuelve la validacion del usuario


    char guardaUsuario[20];
    char guardaPassword[20];

    titulo();
    cleanAndSetScreen();

    printf(" Ingrese UserName: ");
    fflush(stdin);
    scanf("%s", guardaUsuario);

    flagUserName = validaUserNameCliente(listaCliente, guardaUsuario);

    if(flagUserName == 1)
    {
        do
        {
            system("cls");
            titulo();
            gotoxy(10,12);
            printf(" Ingrese Password: ");

            char pass[20];
            char caracter;

            int i=0;
            while(caracter = getch())
            {
                if(caracter == 13)
                {
                    pass[i]='\0';
                    break;
                }
                else if(caracter == 8)
                {
                    i--;
                    printf("\b \b");
                }
                else
                {
                    printf("*");
                    pass[i] = caracter;
                    i++;
                }
            }

            auxCliente = buscarNodoUserNameCliente(listaCliente, guardaUsuario);
            flagPasword = validaPasswordCliente(auxCliente, pass);
            if(flagPasword != 1)
            {
                gotoxy(9, 23);
                printf("<<<<CONTRASEÑA INCORRECTA>>>>");
                getch();

            }

        }



        while(flagPasword != 1);

        *guardaRol = buscaRolEnListaCliente(auxCliente, guardaUsuario);

        *idCliente = buscaIdListaClientePorUserName(auxCliente, guardaUsuario);
    }
    else
    {
        gotoxy(9, 23);
        printf("El usuario ingresado no se encuentra en el sistema...");
        getch();
    }
}


void SubProgramaLogIn(nodoCliente* listaCliente, arbolProducto* productosArbol)
{
    nodoCliente* auxCliente = listaCliente;

    int idCliente = 0;
    int guardaRol = 0;

    logIn(listaCliente, &guardaRol, &idCliente);

    if(idCliente != 0)
    {
        if(guardaRol == 1)
        {
            //MUESTRO MENU PARA EL ADMINISTRADOR
            subMenuAdmin(listaCliente, productosArbol);
        }
        else if(guardaRol == 0)
        {
            //MUESTRO MENU PARA EL USUARIO
            subMenuUsuario(listaCliente, productosArbol, idCliente);
        }
    }



}

void registrarse(nodoCliente* listaCliente)
{
    titulo();
    altaUnUsuariEnListaCliente(listaCliente);//EN ESTA PARTE SOLO CARGO UN CLIENTE YA QUE ENTRO COMO USUARIO
    gotoxy(9, 17);
    printf("<<REGISTRO EXITOSO>>");
    getch();
}


//SUB MENU PARA EL ADMINISTRADOR (EN ESTA SECCION SE PUEDE ELEGIR OPCIONES PARA CLIENTE, PEDIDO, PRODUCTO O LIBERAR TODO EL ESPACIO DEL SISTEMA)
void subMenuAdmin(nodoCliente* listaCliente, arbolProducto* productosArbol)
{
    int opcion;

    do
    {
        titulo();
        gotoxy(10,10);
        printf("1.Cliente");
        gotoxy(10,11);
        printf("2.Pedido");
        gotoxy(10,12);
        printf("3.Producto");
        gotoxy(10,13);
        printf("4.Liberar sistema");
        gotoxy(10,14);
        printf("5.Carga sistema");
        gotoxy(10,15);
        printf("6.Archivos");
        gotoxy(10,16);
        printf("0.Salir");

        opcion = leerOpcion();

        switch(opcion)
        {

        case 1:
            adminCliente(listaCliente, productosArbol);
            break;

        case 2:
            adminPedido(listaCliente);
            break;

        case 3:
            adminProducto(productosArbol);
            break;

        case 4:
            listaCliente = liberarSistema(listaCliente);
            gotoxy(9,23);
            printf("<<<<SE LIBERO TODO EL SISTEMA>>>>");
            getch();
            break;

        case 5:
            listaCliente = subProgramaCargaSistema(listaCliente, productosArbol, ARCHIVO_CLIENTE, ARCHIVO_CABECERA_PEDIDO, ARCHIVO_DETALLE_PRODUCTO);
            gotoxy(9,23);
            printf("<<<<SE CARGO EL SISTEMA NUEVAMENTE>>>>");
            getch();
            break;

        case 6:
            subMenuArchivos();
            break;

        case 0:

            break;

        }

    }
    while(opcion != 0);
}


//SUB MENU PARA EL USUARIO (EN ESTA SECCION PUEDE ELEGIR OPCIONES DE CLIENTE, PEDIDO O PRODUCTO)
void subMenuUsuario(nodoCliente* listaCliente, arbolProducto* productosArbol, int id)
{
    int opcion;

    do
    {
        titulo();
        gotoxy(10,10);
        printf("1.Cliente");
        gotoxy(10,11);
        printf("2.Pedido");
        gotoxy(10,12);
        printf("0.Salir");

        opcion = leerOpcion();

        switch(opcion)
        {

        case 1:
            usuarioCliente(listaCliente, id);
            break;

        case 2:
            usuarioPedido(listaCliente, id, productosArbol);
            break;


        case 0:
            break;

        }

    }
    while(opcion != 0);
}


//SUB MENU PARA EL ADMINISTRADOR EN LA SECCION CLIENTE(EN ESTA SECCION TENDRA DISPONIBLE TODAS LAS OPCIONES QUE COMPETEN AL CLIENTE)
void adminCliente(nodoCliente* listaCliente, arbolProducto* productos)
{
    int opcion;

    nodoCliente* aux = listaCliente;

    int guardaId;

    do
    {
        titulo();
        gotoxy(10,10);
        printf("1.Ver un cliente");
        gotoxy(10,11);
        printf("2.Ver todos los clientes");
        gotoxy(10,12);
        printf("3.Alta Cliente");
        gotoxy(10,13);
        printf("4.Alta Admin");
        gotoxy(10,14);
        printf("5.Baja");
        gotoxy(10,15);
        printf("6.Activar Cliente");
        gotoxy(10,16);
        printf("7.Modificar");
        gotoxy(10,17);
        printf("0.Salir");

        opcion = leerOpcion();

        switch(opcion)
        {

        case 1:
            gotoxy(10, 23);
            guardaId = ingresaIdCliente();
            aux = buscarNodoIdCliente(listaCliente, guardaId);
            gotoxy(11, 24);
            if(aux)
            {
                 muestraUnNodoClienteAdmin(aux);
            }
            else
            {
                gotoxy(9, 23);
                printf("<<<<EL CLIENTE NO EXISTE>>>>");
            }


            getch();
            break;

        case 2:
            gotoxy(11, 24);
            muestraListaClienteAdmin(listaCliente);//ACA SE MUESTRAN TODOS LOS CLIENTES ACTIVOS
            getch();
            break;

        case 3:
            listaCliente = altaUnUsuariEnListaCliente(listaCliente);

            break;

        case 4:
            listaCliente = altaUnAdminEnListaCliente(listaCliente);

            break;

        case 5:
            gotoxy(10, 23);
            guardaId = ingresaIdCliente();
            listaCliente = subProgramaBajaCliente(ARCHIVO_CLIENTE, listaCliente, guardaId);
            gotoxy(9,25);
            printf("<<<<<BAJA EXITOSA>>>>>");
            getch();
            break;

        case 6:
            gotoxy(10, 23);
            guardaId = ingresaIdCliente();
            listaCliente = subProgramaActivaCliente(listaCliente, ARCHIVO_CLIENTE, guardaId, productos);
            gotoxy(9,25);
            printf("<<<<<SE ACTIVO EL CLIENTE>>>>>");
            getch();
            break;

        case 7:
            gotoxy(9, 23);
            guardaId = ingresaIdCliente();

            aux = buscarNodoIdCliente(aux, guardaId);
            aux = modificaClienteAdmin(aux, guardaId);
            guardaClienteModificado(ARCHIVO_CLIENTE, guardaId, aux->datoCliente);

            break;
        case 0:

            break;

        }

    }
    while(opcion != 0);
}

void usuarioCliente(nodoCliente* listaCliente, int id)
{
    int opcion;

    nodoCliente* aux = listaCliente;

    do
    {
        titulo();
        gotoxy(10,10);
        printf("1.Ver mi usuario");
        gotoxy(10,11);
        printf("2.Baja");
        gotoxy(10,12);
        printf("3.Modificar");
        gotoxy(10,13);
        printf("0.Salir");

        opcion = leerOpcion();

        switch(opcion)
        {

        case 1:
            aux = buscarNodoIdCliente(listaCliente, id);
            gotoxy(11, 24);
            muestraUnNodoClienteUsuario(aux);
            getch();
            break;

        case 2:
            subProgramaBajaCliente(ARCHIVO_CLIENTE, listaCliente, id);
            gotoxy(9,25);
            printf("<<<<<BAJA EXITOSA>>>>>");
            getch();
            break;

        case 3:
            aux = buscarNodoIdCliente(listaCliente, id);
            aux = modificaClienteAdmin(aux, id);
            guardaClienteModificado(ARCHIVO_CLIENTE, id, aux->datoCliente);
            break;

        case 0:

            break;

        }

    }
    while(opcion != 0);
}



void adminPedido(nodoCliente* listaCliente)
{
    int opcion;
    int idABuscar = -1;
    int flag = 0;
    nodoCliente* auxListaCliente = listaCliente;
    nodoCliente* auxCliente = NULL;
    nodoPedido* auxPedido = NULL;

    do
    {
        titulo();
        gotoxy(10,10);
        printf("1.Ver pedidos");
        gotoxy(10,11);
        printf("2.Ver todos los pedidos de un cliente");
        gotoxy(10,12);
        printf("3.Eliminar pedido");
        gotoxy(10,13);
        printf("0.Salir");

        opcion = leerOpcion();

        switch(opcion)
        {

        case 1:

            gotoxy(15,23);
            printf("<<<<PEDIDOS>>>>");
            gotoxy(9,24);
            muestraPedidosSistema(listaCliente);

            idABuscar = ingresaIdPedido();
            auxPedido = subProgramaBuscaPedido(listaCliente, idABuscar);
            if(auxPedido)
            {
                muestraListaProducto(auxPedido->listaProducto);
            }
            else
            {
                printf("<<<<EL PEDIDO NO EXISTE>>>>");
            }

            getch();


            break;

        case 2:

            idABuscar = ingresaIdCliente();

            auxCliente = buscarNodoIdCliente(auxListaCliente, idABuscar);

            if(auxCliente)
            {
                if(auxCliente->listaPedidos)
                {
                    printf("\n\nEstos son los pedidos del usuario:\n\n");
                    muestraListaPedido(auxCliente->listaPedidos);

                    idABuscar = ingresaIdPedido();
                    auxPedido = subProgramaBuscaPedido(listaCliente, idABuscar);

                    if(auxPedido)
                    {
                        muestraListaProducto(auxPedido->listaProducto);
                    }
                }
                else
                {
                    gotoxy(9,26);
                    printf("<<<<ESTE USUARIO NO TIENE PEDIDOS>>>>");
                }
            }
            else
            {
                printf("El usuario no existe.\n");
            }
            opcion = getch();

            break;

        case 3:

            gotoxy(15,23);
            printf("<<<<PEDIDOS>>>>");
            gotoxy(9,24);
            muestraPedidosSistema(listaCliente);

            printf("Ingrese el ID del pedido que desea borrar: ");
            scanf("%d", &idABuscar);

            flag = eliminaPedido(listaCliente, idABuscar);

            if(flag == 1)
            {
                printf("<<<<Se ha eliminado el pedido con exito>>>>");
                persistirDatosCabeceraYDetalle(listaCliente, ARCHIVO_CABECERA_PEDIDO, ARCHIVO_DETALLE_PRODUCTO);

            }
            else
            {
                printf("<<<<El pedido no existe>>>>");
            }


            getch();
            break;


        case 0:

            break;

        }

    }
    while(opcion != 0);
}


void usuarioPedido(nodoCliente* listaCliente, int idCliente, arbolProducto* productosArbol)
{
    int opcion;
    nodoCliente* auxCliente = buscarNodoIdCliente(listaCliente, idCliente);
    nodoPedido* auxPedido = NULL;
    int idABuscar = -1;
    int flag = 0;

    do
    {
        titulo();
        gotoxy(10,10);
        printf("1.Ver pedido");
        gotoxy(10,11);
        printf("2.Hacer pedido");
        gotoxy(10,12);
        printf("3.Eliminar pedido");
        gotoxy(10,13);
        printf("4.Ver productos");
        gotoxy(10,14);
        printf("0.Salir");

        opcion = leerOpcion();

        switch(opcion)
        {

        case 1:
            gotoxy(9, 25);

            if(auxCliente->listaPedidos)
            {
                printf("<<<<PEDIDOS>>>>");
                muestraListaPedido(auxCliente->listaPedidos);
                idABuscar = ingresaIdPedido();
                auxPedido = buscarNodoIdPedido(auxCliente->listaPedidos, idABuscar);

                if(auxPedido)
                {
                    muestraListaProducto(auxPedido->listaProducto);
                }
                else
                {

                    printf("\n<<<<EL PRODUCTO NO EXISTE>>>>");
                }
            }
            else
            {
                printf("\n<<<<NO HAY PEDIDOS CARGADOS>>>>");
            }


            getch();
            break;
        case 2:

            flag = cargaPedidoCliente(auxCliente, productosArbol);

            if(flag == 0)
            {
                printf("\n <<<<PEDIDO CARGADO CON EXITO>>>>");
            }
            getch();

            break;

        case 3:
            gotoxy(15,23);

            gotoxy(9,24);

            if(auxCliente->listaPedidos)
            {
                printf("<<<<PEDIDOS>>>>");
                muestraListaPedido(auxCliente->listaPedidos);

                printf("Ingrese el ID del pedido que desea borrar: ");
                scanf("%d", &idABuscar);

                flag = borraPedidoYproductosCliente(auxCliente->listaPedidos, idABuscar);

                if(flag == 1)
                {
                    auxCliente->listaPedidos = borrarNodoIdPedido(auxCliente->listaPedidos, idABuscar);
                    printf("<<<<Se ha eliminado el pedido con exito>>>>");
                    persistirDatosCabeceraYDetalle(listaCliente, ARCHIVO_CABECERA_PEDIDO, ARCHIVO_DETALLE_PRODUCTO);
                }
                else
                {
                    printf("<<<<El pedido no existe>>>>");
                }
            }
            else
            {
                printf("No hay pedidos cargados...");
            }




            getch();
            break;

        case 4:
            verProductoPorEstiloMenu(productosArbol);
            break;

        case 0:
            break;

        }

    }
    while(opcion != 0);
}

void adminProducto(arbolProducto* productosArbol)
{
    int opcion;
    int guardaId;
    arbolProducto* aux;


    do
    {
        titulo();
        gotoxy(10,10);
        printf("1.Alta");
        gotoxy(10,11);
        printf("2.Baja");
        gotoxy(10,12);
        printf("3.Modificar");
        gotoxy(10,13);
        printf("4.Activar producto");
        gotoxy(10,14);
        printf("5.Ver todos los productos");
        gotoxy(10,15);
        printf("0.Salir");

        opcion = leerOpcion();

        switch(opcion)
        {

        case 1:
            cargaArchivoProducto(ARCHIVO_PRODUCTO);
            gotoxy(9,23);
            printf("<<<<ES NECESARIO REINICIAR EL SISTEMA PARA QUE SE CARGUEN LOS DATOS>>>>");
            getch();

            break;

        case 2:
            ///BAJA PRODUCTO EN ARBOL Y ARCHIVO
            gotoxy(9, 23);
            printf("Ingrese ID del producto: ");
            fflush(stdin);
            scanf("%d", &guardaId);

            productosArbol = subProgramaBajaProducto(productosArbol, guardaId);
            getch();

            break;

        case 3:

            productosArbol = modificaProductoAdmin(productosArbol);
            break;

        case 4:
            gotoxy(9, 23);
            printf("Ingrese ID del producto: ");
            fflush(stdin);
            scanf("%d", &guardaId);

            activaProductoEnArchivo(ARCHIVO_PRODUCTO, guardaId);
            gotoxy(9,25);
            printf("<<<<ES NECESARIO REINICIAR EL SISTEMA PARA QUE SE CARGUEN LOS DATOS>>>>");
            getch();


            break;

        case 5:
            verProductoPorEstiloMenu(productosArbol);
            getch();
            break;


        case 0:
            break;

        }

    }
    while(opcion != 0);
}



void verProductoPorEstiloMenu(arbolProducto* productosArbol)
{
    int opcion;

    do
    {
        titulo();
        gotoxy(10,10);
        printf("1.Rubia");
        gotoxy(10,11);
        printf("2.Roja");
        gotoxy(10,12);
        printf("3.Lupulada");
        gotoxy(10,13);
        printf("4.Negra");
        gotoxy(10,14),
               printf("0.Salir");

        opcion = leerOpcion();

        switch(opcion)
        {

        case 1:
            system("cls");
            gotoxy(5, 2);
            printf("<<<PRODUCTOS ESTILO RUBIA>>>");
            lineaRecta(6);
            muestraProductosPorEstilo(productosArbol, "Rubia");
            getch();
            break;

        case 2:
            system("cls");
            gotoxy(5, 2);
            printf("<<<PRODUCTOS ESTILO ROJA>>>");
            lineaRecta(6);
            muestraProductosPorEstilo(productosArbol, "Roja");
            getch();
            break;

        case 3:
            system("cls");
            gotoxy(5, 2);
            printf("<<<PRODUCTOS ESTILO LUPULADA>>>");
            lineaRecta(6);
            muestraProductosPorEstilo(productosArbol, "Lupulada");
            getch();
            break;

        case 4:
            system("cls");
            gotoxy(5, 2);
            printf("<<<PRODUCTOS ESTILO NEGRA>>>");
            lineaRecta(6);
            muestraProductosPorEstilo(productosArbol, "Negra");
            getch();
            break;

        case 0:
            break;

        }


    }
    while(opcion != 0);
}

void subMenuArchivos()
{
    int opcion;

    do
    {
        titulo();
        gotoxy(10,10);
        printf("1.Archivo clientes");
        gotoxy(10,11);
        printf("2.Archivo productos");
        gotoxy(10,12);
        printf("3.Archivo cabecera");
        gotoxy(10,13);
        printf("4.Archivo detalle");
        gotoxy(10,14),
               printf("0.Salir");

        opcion = leerOpcion();

        switch(opcion)
        {

        case 1:
            gotoxy(0,23);
            mostrarArchivoCliente(ARCHIVO_CLIENTE);
            getch();
            break;

        case 2:
            gotoxy(0,23);
            mostrarArchivoProducto(ARCHIVO_PRODUCTO);
            getch();
            break;

        case 3:
            gotoxy(0,23);
            mostrarArchivoCabecera(ARCHIVO_CABECERA_PEDIDO);
            getch();
            break;

        case 4:
            gotoxy(0,23);
            mostrarArchivoDetallePedido(ARCHIVO_DETALLE_PRODUCTO);
            getch();
            break;

        case 0:
            break;

        }


    }
    while(opcion != 0);
}







