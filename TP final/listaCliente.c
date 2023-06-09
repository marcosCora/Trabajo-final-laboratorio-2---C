#include "listaCliente.h"

nodoCliente* inicListaCliente()
{
    return NULL;
}

///funcion que crea un nuevo nodoCliente

nodoCliente* creaNodoCliente(stCliente dato)
{
    nodoCliente* nodoNuevo = (nodoCliente*) malloc(sizeof(nodoCliente));
    nodoNuevo->datoCliente = dato;
    nodoNuevo->listaPedidos = inicListaPedido();
    nodoNuevo->siguiente = NULL;

    return nodoNuevo;
}

//Funcion que agrega datos a la lista desde el principio

nodoCliente* agregarPrincipioListaCliente(nodoCliente* lista,nodoCliente * nodoNuevo)
{
    if(lista == NULL)
    {
        lista = nodoNuevo;
    }
    else
    {
        nodoNuevo->siguiente = lista;
        lista = nodoNuevo;
    }

    return lista;
}

///agrego el final de la lista

nodoCliente* agregoFinalListaCliente(nodoCliente* lista, nodoCliente* nuevoNodo)
{
    nodoCliente* ultimo;

    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        ultimo = buscaUltimoNodoCliente(lista);///almaceno el ultimo nodoCliente en la variable ultimo
        ultimo->siguiente = nuevoNodo;///le asigno el nuevo nodoCliente al siguiente de ultimo
    }

    return lista;
}

///busca ultimo nodo

nodoCliente* buscaUltimoNodoCliente(nodoCliente* lista)
{
    nodoCliente* aux = lista; ///creo una variable auxilar

    if(aux != NULL)
    {
        while(aux->siguiente != NULL) ///recorrre la lista hasta que el siguiente sea NULL
        {
            aux = aux->siguiente;
        }
    }

    return aux;///retorno el ultimo
}

nodoCliente* agregarEnOrdenListaXIdCliente(nodoCliente* lista, nodoCliente* nuevoNodo)
{
    nodoCliente* seg = lista;
    nodoCliente* ante;

    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        ///si el nuevo nodo debe colocarse al principio se llama a la funcion de agregar el principio
        if((seg != NULL) && seg->datoCliente.idCliente > nuevoNodo->datoCliente.idCliente)
        {
            lista = agregarPrincipioListaProducto(lista, nuevoNodo);
        }
        else///si no recorre la lista y busca el hueco donde ubicarlo
        {
            while((seg != NULL) && seg->datoCliente.idCliente < nuevoNodo->datoCliente.idCliente)
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

void muestraUnNodoClienteAdmin(nodoCliente* listaCliente)
{
    muestraUnClienteAdmin(listaCliente->datoCliente);
    printf("\n Total pedidos...: %.2f", listaCliente->costoTotalPedidos);
    printf("\n ------------------------\n");

}

void muestraUnNodoClienteUsuario(nodoCliente* listaCliente)
{
    muestraUnClienteUsuario(listaCliente->datoCliente);
    printf("\n Total pedidos...: %.2f", listaCliente->costoTotalPedidos);
    printf("\n ------------------------\n");

}



///muestra lista

void muestraListaClienteAdmin(nodoCliente* lista)
{
    nodoCliente* aux = lista;

    while(aux != NULL)
    {

        muestraUnNodoClienteAdmin(aux);
        aux = aux->siguiente;
    }

}

void muestraListaClienteUsuario(nodoCliente* lista)
{
    nodoCliente* aux = lista;

    while(aux != NULL)
    {

        muestraUnNodoClienteUsuario(aux);
        aux = aux->siguiente;
    }

}


///borrar lista

nodoCliente* borraListaCliente(nodoCliente* lista)
{
    nodoCliente* aux;///creo una variable para ir liberando esa parte de memoria

    while(lista != NULL)
    {
        aux = lista;///le asigno a aux la lista
        lista = lista->siguiente;///lista se asigna el siguiente y pierdo el primer valor
        free(aux);///borro el nodo con la informacion de aux
    }

    return lista;
}

///funcion que elimina el ultimo nodo de una lista
nodoCliente* eliminaUltimoNodoCliente(nodoCliente* lista)
{
    nodoCliente* aux = lista;///creo una variable auxiliar
    nodoCliente* ante;///anterior

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


nodoCliente* eliminaPrimerNodoCliente(nodoCliente* lista)
{
    nodoCliente* aux = lista;///creo una lista auxilliar y el asigno la lista recibida

    if(lista != NULL)
    {
        lista = lista->siguiente;///le asgino a lista el siguiente nodo que sera el primero
        free(aux);///elimino el primer nodo
    }

    return lista;///retorno la lista
}

///busca un nodo por numero de id
///retorna el nodo si se encuentra y si no retorna null
nodoCliente* buscarNodoIdCliente(nodoCliente* lista, int id)
{
    nodoCliente* aux = lista;///creo una variable seguidora

    while((aux != NULL) && (aux->datoCliente.idCliente != id))///recorro la lista mientras no finalize o no se encuentre el nodo
    {
        aux = aux->siguiente;
    }

    return aux;///retorno el nodo donde del que se busco o NULL si no se encuentra
}

nodoCliente* borrarNodoIdCliente(nodoCliente* lista, int id)
{
    ///creo dos listas que sirven para recorrer la lista sin perder datos
    nodoCliente* seg;
    nodoCliente* ante;

    if(lista != NULL && lista->datoCliente.idCliente == id)///si la lista no esta vacia y el primer nodoCliente es el buscado se elimina
    {
        lista = eliminaPrimerNodoCliente(lista);
    }
    else
    {
        seg = lista;///le asgino la lista a siguiente
        while((seg != NULL) && seg->datoCliente.idCliente != id)///recorre la lista mientras no sea NULL y no se encuentre el dato
        {
            ante = seg;
            seg = seg->siguiente;
        }
        if(seg != NULL)///si seg no es NULL significa que el dato se encontr
        {
            ante->siguiente = seg->siguiente;///redirreciono los nodos
            free(seg);///elimino el nodoCliente
        }
    }

    return lista;
}

///funcion que devincula un nodo de la lista recibida y lo retorna solo

nodoCliente* desvinculaNodoCliente(nodoCliente** pLista)///recibe un puntero doble a la lista
{
    nodoCliente* aux;///crea un axuliar

    if((*pLista))///mientras a lo que apunta lista tenga datos
    {
        aux  = (*pLista);///le asigno el primer nodo a auxiliar
        (*pLista) = (*pLista)->siguiente;///hago que el primer dato de la lista sea el siguiente del primero recibido
        aux->siguiente = NULL;///el siguiente del primero lo convierto en NULL desvinculando de la lista
    }
    return aux;///retorno el nodo desvinculado
}


int buscaRolEnListaCliente(nodoCliente* listaCliente, char userName[20])
{
    nodoCliente* aux = listaCliente;
    int flag = 0;
    int rta = 0;

    while(aux && flag == 0)
    {
        if(strcmp(userName, aux->datoCliente.userName)==0)
        {
            flag = 1;
            rta = aux->datoCliente.rol;
        }
        else
        {
            flag = 0;
        }
        aux = aux->siguiente;
    }
    return rta;
}

///funcion que pasa del archivo de clientes
///a una lista de clientes con toda su info
nodoCliente* archivoCliente2ListaClientes(nodoCliente* listaCliente, char nombreArch[])
{
    stCliente c;

    FILE* arch = fopen(nombreArch, "rb");

    if(arch)
    {
        while(fread(&c, sizeof(stCliente), 1, arch) > 0)
        {
            if(c.activo == 1)
            {
                listaCliente = agregoFinalListaCliente(listaCliente, creaNodoCliente(c));
                listaCliente->costoTotalPedidos = 0;
            }
        }
        fclose(arch);
    }

    return listaCliente;
}

/**
FUNCION QUE DA DE ALTA UN CLIENTE EN LA LISTA DE CLIENTE EN ROL 0 (USUARIO)
*/
nodoCliente* altaUnUsuariEnListaCliente(nodoCliente* listaCliente)
{
    stCliente c;
    c = cargaUnCliente();

    c.idCliente = ultimoIdCliente(ARCHIVO_CLIENTE);
    c.idCliente++;
    listaCliente = agregoFinalListaCliente(listaCliente, creaNodoCliente(c));
    guardaClienteCreado(ARCHIVO_CLIENTE, c);

    return listaCliente;
}


nodoCliente* modificaClienteUsuario(nodoCliente* listaCliente, char userName[20])
{
    nodoCliente* aux = listaCliente;
    aux = buscarNodoUserNameCliente(listaCliente, userName);
    char guardaString[40];
    char guardaChar;
    int opcion;
    do
    {
        titulo();
        gotoxy(10,10);
        printf("1.Nombre");
        gotoxy(10,11);
        printf("2.Apellido");
        gotoxy(10,12);
        printf("3.UserName");
        gotoxy(10,13);
        printf("4.Password");
        gotoxy(10,14);
        printf("5.Mail");
        gotoxy(10,15);
        printf("6.Genero");
        gotoxy(10,16);
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
            validacionGeneralNombre(guardaString);
            strcpy(aux->datoCliente.nombre, guardaString);
            gotoxy(10, 12);
            printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
            getch();
            break;

        case 2:
            titulo();
            gotoxy(10,10);
            printf("Ingrese nuevo Apellido: ");
            fflush(stdin);
            gets(guardaString);
            validacionGeneralNombre(guardaString);
            strcpy(aux->datoCliente.apellido, guardaString);
            gotoxy(10, 12);
            printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
            getch();
            break;

        case 3:
            titulo();
            gotoxy(10,10);
            printf("Ingrese nuevo UserName: ");//VALIDAR NUEVAMENTE
            fflush(stdin);
            gets(guardaString);
            existeUserNameEnArchivoGeneral(ARCHIVO_CLIENTE, guardaString);
            strcpy(aux->datoCliente.userName, guardaString);
            gotoxy(10, 12);
            printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
            getch();
            break;

        case 4:
            titulo();
            gotoxy(10,10);
            printf("Ingrese nueva Password: ");
            fflush(stdin);
            gets(guardaString);
            validacionGeneralPass(guardaString);
            strcpy(aux->datoCliente.password, guardaString);
            gotoxy(10, 12);
            printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
            getch();
            break;

        case 5:
            titulo();
            gotoxy(10,10);
            printf("Ingrese nuevo Mail: ");//VALIDAR NUEVAMENTE
            fflush(stdin);
            gets(guardaString);
            validacionGeneralEmail(guardaString);
            existeEmail(ARCHIVO_CLIENTE, guardaString);
            strcpy(aux->datoCliente.mail, guardaString);
            gotoxy(10, 12);
            printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
            getch();
            break;

        case 6:
            titulo();
            gotoxy(10,10);
            printf("Ingrese nuevo Genero: ");//VALIDAR NUEVAMENTE
            fflush(stdin);
            scanf("%c", &guardaChar);
            guardaChar=validacionGenero(toupper(guardaChar));
            aux->datoCliente.genero = guardaChar;
            gotoxy(10, 12);
            printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
            getch();
            break;

        case 0:
            break;

        }

    }
    while(opcion != 0);

    return aux;
}

nodoCliente* modificaClienteAdmin(nodoCliente* listaCliente, int id)
{
    nodoCliente* aux = listaCliente;
    aux = buscarNodoIdCliente(aux, id);
    char guardaString[40];
    char guardaChar;
    int opcion;
    do
    {
        titulo();
        gotoxy(10,10);
        printf("1.Nombre");
        gotoxy(10,11);
        printf("2.Apellido");
        gotoxy(10,12);
        printf("3.UserName");
        gotoxy(10,13);
        printf("4.Password");
        gotoxy(10,14);
        printf("5.Mail");
        gotoxy(10,15);
        printf("6.Genero");
        gotoxy(10,16);
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
            validacionGeneralNombre(guardaString);
            strcpy(aux->datoCliente.nombre, guardaString);
            gotoxy(10, 12);
            printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
            getch();
            break;

        case 2:
            titulo();
            gotoxy(10,10);
            printf("Ingrese nuevo Apellido: ");
            fflush(stdin);
            gets(guardaString);
            validacionGeneralNombre(guardaString);
            strcpy(aux->datoCliente.apellido, guardaString);
            gotoxy(10, 12);
            printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
            getch();
            break;

        case 3:
            titulo();
            gotoxy(10,10);
            printf("Ingrese nuevo UserName: ");//VALIDAR NUEVAMENTE
            fflush(stdin);
            gets(guardaString);
            existeUserNameEnArchivoGeneral(ARCHIVO_CLIENTE, guardaString);
            strcpy(aux->datoCliente.userName, guardaString);
            gotoxy(10, 12);
            printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
            getch();
            break;

        case 4:
            titulo();
            gotoxy(10,10);
            printf("Ingrese nueva Password: ");
            fflush(stdin);
            gets(guardaString);
            validacionGeneralPass(guardaString);
            strcpy(aux->datoCliente.password, guardaString);
            gotoxy(10, 12);
            printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
            getch();
            break;

        case 5:
            titulo();
            gotoxy(10,10);
            printf("Ingrese nuevo Mail: ");//VALIDAR NUEVAMENTE
            fflush(stdin);
            gets(guardaString);
            validacionGeneralEmail(guardaString);
            existeEmail(ARCHIVO_CLIENTE, guardaString);
            strcpy(aux->datoCliente.mail, guardaString);
            gotoxy(10, 12);
            printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
            getch();
            break;

        case 6:
            titulo();
            gotoxy(10,10);
            printf("Ingrese nuevo Genero: ");//VALIDAR NUEVAMENTE
            fflush(stdin);
            scanf("%c", &guardaChar);
            guardaChar=validacionGenero(toupper(guardaChar));
            aux->datoCliente.genero = guardaChar;
            gotoxy(10, 12);
            printf("<<SE HA MODIFICADO CORRECTAMENTE>>");
            getch();
            break;

        case 0:
            break;

        }

    }
    while(opcion != 0);

    return aux;
}


nodoCliente* buscarNodoUserNameCliente(nodoCliente* lista, char userName[20])
{
    nodoCliente* aux = lista;///creo una variable seguidora

    while((aux != NULL) && (strcmpi(aux->datoCliente.userName, userName)!=0))///recorro la lista mientras no finalize o no se encuentre el nodo
    {
        aux = aux->siguiente;
    }

    return aux;///retorno el nodo donde del que se busco o NULL si no se encuentra
}


nodoCliente* altaUnAdminEnListaCliente(nodoCliente* listaCliente)
{
    stCliente c;
    c = cargaUnCliente();
    int id = ultimoIdCliente(ARCHIVO_CLIENTE);
    id++;
    c.idCliente = id;

    c.rol = 1;
    listaCliente = agregoFinalListaCliente(listaCliente, creaNodoCliente(c));
    guardaClienteCreado(ARCHIVO_CLIENTE, c);

    return listaCliente;
}


int buscaIdListaClientePorUserName(nodoCliente* listaCliente, char userName[])
{
    nodoCliente* aux = listaCliente;
    int id = 0;

    while(aux && id == 0)
    {
        if(strcmpi(aux->datoCliente.userName, userName) == 0)
        {
            id = aux->datoCliente.idCliente;
        }
        aux = aux->siguiente;
    }
    return id;
}


nodoCliente* sumaCostos(nodoCliente* listaCliente)
{
    nodoCliente* auxCliente = listaCliente;

    while(auxCliente)
    {
        nodoPedido* auxPedido = auxCliente->listaPedidos;
        while(auxPedido)
        {
            auxPedido->costoPedido = sumaCostoProducto(auxPedido->listaProducto);
            auxPedido = auxPedido->siguiente;
        }
        auxCliente->costoTotalPedidos = sumaPedidos(auxCliente->listaPedidos);
        auxCliente = auxCliente->siguiente;
    }

    return listaCliente;
}

float sumaPedidos(nodoPedido* listaPedido)
{
    nodoPedido* auxPedido = listaPedido;
    float sumaCosto = 0;

    while(auxPedido)
    {
        sumaCosto += auxPedido->costoPedido;
        auxPedido = auxPedido->siguiente;
    }
    return sumaCosto;
}

///funcion que elimina todo los datos del cliente y el cliente de una lista
nodoCliente * liberarClienteConDatoS(nodoCliente * lista, int id)
{
    if (lista)
    {
        nodoCliente * aux = buscarNodoIdCliente(lista, id);
        if(aux)
        {
            nodoPedido * auxPedido = aux->listaPedidos;
            while(auxPedido)
            {
                auxPedido->listaProducto = borraListaProducto(auxPedido->listaProducto);
                auxPedido=auxPedido->siguiente;
            }

            aux->listaPedidos = borraListaPedido(aux->listaPedidos);
            lista = borrarNodoIdCliente(lista, id);
        }
    }
    return lista;
}







