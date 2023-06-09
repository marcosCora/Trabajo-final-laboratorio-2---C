#include "producto.h"

stProducto cargaUnProducto()
{
    stProducto p;

    system("cls");
    printf("\n Ingrese nombre: ");
    fflush(stdin);
    gets(p.nombre);

    printf("\n Ingrese marca: ");
    fflush(stdin);
    gets(p.marca);

    printf("\n Ingrese estilo: ");
    fflush(stdin);
    gets(p.estilo);

    printf("\n Ingrese precio: ");
    fflush(stdin);
    scanf("%f", &p.precio);

    printf("\n Ingrese stock: ");
    fflush(stdin);
    scanf("%d", &p.stock);


    p.eliminado = 0;

    return p;
}

void muestraUnProducto(stProducto p)
{
    printf("\n ID........: %d",p.idProducto);
    printf("\n Nombre....: %s",p.nombre);
    printf("\n Marca.....: %s",p.marca);
    printf("\n Estilo....: %s",p.estilo);
    printf("\n Precio....: $ %.2f",p.precio);
    printf("\n Stock.....: %d lts",p.stock);
    printf("\n Eliminado.: %d", p.eliminado);
    printf("\n--------------------------");
}

void cargaArchivoProducto(char nombreArchivo[])
{
    FILE* archi = fopen(nombreArchivo, "ab");
    stProducto p;
    char opcion = 0;
    int id= ultimoIdProducto(ARCHIVO_PRODUCTO);
    if(archi)
    {
        do
        {
            system("cls");
            p = cargaUnProducto();
            id++;
            p.idProducto = id;
            fwrite(&p, sizeof(stProducto), 1, archi);
            printf("\n ESC para salir / cualquier tecla para continuar...\n");
            opcion = getch();

        }
        while(opcion!=27);

        fclose(archi);
    }
}

//FUNCION QUE RETORNA EL ULTIMO ID PARA PODER HACER EL AUTOINCREMENTO DEL ID EN EL ARCHIVO
int ultimoIdProducto(char nombreArchivo[])
{
    int id=0;
    stProducto p;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        fseek(archi, -1*(sizeof(stProducto)), SEEK_END);
        if(fread(&p, sizeof(stProducto), 1, archi)>0)
        {
            id=p.idProducto;
        }
        fclose(archi);
    }
    return id;
}

void mostrarArchivoProducto(char nombreArchivo[])
{
    FILE* archi = fopen(nombreArchivo, "rb");
    stProducto p;
    if(archi)
    {
        while(fread(&p, sizeof(stProducto), 1, archi)>0)
        {
            muestraUnProducto(p);
        }

        fclose(archi);
    }
}


//FUNCION QUE PASA DEL ARCHIVO A UN ARREGLO PARA LUEGO HACER AGREGACION BINARIA EN EL ARBOL DE PRODUCTOS
int archivo2ArrayProducto(stProducto p[], int dim, int v, char nombreArchivo[])
{
    FILE* archi = fopen(nombreArchivo, "rb");
    stProducto producto;

    if(archi)
    {
        while(v < dim && fread(&producto, sizeof(stProducto), 1, archi) > 0)
        {
            if(producto.eliminado == 0)
            {
                p[v] = producto;
                v++;
            }
        }
        fclose(archi);
    }
    return v;
}


///funcion que retorna la cantidad de productos activos que hay en el archivo

int cuentaCantProductosActivos(char nombreArchivo[])
{
    FILE * archi = fopen (nombreArchivo, "rb");
    stProducto p;
    int cont=0;

    if(archi)
    {
        while(fread(&p, sizeof(stProducto), 1, archi)>0)
        {
            if(p.eliminado == 0)
            {
                cont++;
            }
        }
        fclose(archi);
    }
    return cont;
}

//FUNCION QUE ME DEVUELVE LA POSICION DE UN PRODUCTO EN EL ARCHIVO INGRESANDO POR PARAMETRO EL ID DE PRODUCTO
int devuelvePosicionArchivoPorIdProducto(FILE* arch, int idProducto)
{
    stProducto p;
    int flag=0;
    int i=0;

    if(arch)
    {
        while(flag==0 && fread(&p, sizeof(stProducto), 1, arch)>0)
        {

            if(idProducto == p.idProducto)
            {
                flag=1;
            }
            else
            {
                i++;
            }

        }
    }
    return i;
}

//FUNCION PARA DISMINUIR STOCK DE UN PRODUCTO EN ARCHIVO POR EL ID DE PRODUCTO
void modificarProductoEnArchivo(char nombreArchivo[], int idProducto)
{
    stProducto p;
    int pos;

    FILE *archi = fopen(nombreArchivo, "r+b");
    if(archi)
    {
        pos = devuelvePosicionArchivoPorIdProducto(archi, idProducto);
        fseek(archi, sizeof(stProducto)*(pos-1), 0);
        if(fread(&p, sizeof(stProducto), 1, archi)>0)
        {
            p.stock = p.stock - 50;
            fseek(archi, sizeof(stProducto)*(pos-1), 0);
            fwrite(&p, sizeof(stProducto), 1, archi);

        }
        fclose(archi);
    }
}

///FUNCION PARA DAR DE BAJA A UN PRODUCTO EN EL ARCHIVO
void bajaProducto (char nombreArchivo[], int id)
{
    FILE *archi = fopen(nombreArchivo, "r+b");
    int pos = devuelvePosicionArchivoPorIdProducto(archi, id);
    stProducto p;
    if(archi)
    {
        fseek(archi, sizeof(stProducto)*pos, 0);
        fread(&p, sizeof(stProducto),1, archi);

        p.eliminado = 1;

        fseek(archi, sizeof(stProducto)*pos, 0);
        fwrite(&p, sizeof(stProducto), 1, archi);



        fclose(archi);
    }
}

void activaProductoEnArchivo(char nombreArchivo[], int id)
{
    FILE * archi = fopen(nombreArchivo, "r+b");
    stProducto p;
    int pos = devuelvePosicionArchivoPorIdProducto(archi, id);

    if(archi)
    {

        fseek(archi, sizeof(stProducto)*pos, 0 );
        fread(&p, sizeof(stProducto), 1, archi);
        p.eliminado = 0;

        fseek(archi, sizeof(stProducto)*pos, 0 );
        fwrite(&p, sizeof(stProducto), 1, archi);

        fclose(archi);
    }
}






