#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED

#include "cliente.h"
#include "detallePedido.h"
#include "cabeceraPedido.h"
#define ARCHIVO_PRODUCTO "producto.dat"

typedef struct
{
    int idProducto;     //autoincremental
    char nombre[30];
    char marca[20];
    char estilo[20];
    float precio;
    int eliminado;      //indica 1 o 0 si el producto esta eliminado
    int stock;
} stProducto;


///FUNCIONES DE CARGA Y MUESTRA DE PRODUCTO, FUNCION PARA ID AUTOINCREMENTRAL
stProducto cargaUnProducto();
void cargaArchivoProducto(char nombreArchivo[]);
void muestraUnProducto(stProducto p);
void mostrarArchivoProducto(char nombreArchivo[]);
int ultimoIdProducto(char nombreArchivo[]);

///FUNCION QUE PASA DEL ARCHIVO A UN ARREGLO PARA LUEGO HACER AGREGACION BINARIA EN EL ARBOL DE PRODUCTOS
int archivo2ArrayProducto(stProducto p[], int dim, int v, char nombreArchivo[]);

int cuentaCantProductosActivos (char nombreArchivo[]);

int devuelvePosicionArchivoPorIdProducto(FILE* arch, int idProducto);
void modificarProductoEnArchivo(char nombreArchivo[], int idProducto);

void bajaProducto (char nombreArchivo[], int id);
void activaProductoEnArchivo(char nombreArchivo[], int id);

#endif // PRODUCTO_H_INCLUDED
