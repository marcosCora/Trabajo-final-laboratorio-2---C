#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED

#include "producto.h"
#include <windows.h>
#include "gotoxy.h"

#include "listaCliente.h"///ESTA CONTIENE A TODAS

void archivoCabeceraPedido2ListaPedido(nodoCliente* listaCliente, char nombreArch[]);
void altaPedido(nodoCliente* listaCliente, stCabeceraPedido cabecera);
void archivoDetalleProducto2ListaProductos(nodoCliente* listaCliente, arbolProducto* productos, char nombreArch[]);
void altaProducto(nodoCliente* cliente, stDetallePedidos detalleProducto, arbolProducto* productos);
nodoCliente* subProgramaCargaSistema(nodoCliente* listaCliente, arbolProducto* productos, char archCliente[], char archCabeceraPedido[], char archDetalleProducto[]);
int cargaPedidoCliente(nodoCliente* cliente, arbolProducto* productos);
int cargaProductosAPedido(nodoPedido* pedido, arbolProducto* productos);

void verProductoPorEstilo(arbolProducto* productos);
int validaPasswordCliente(nodoCliente* cliente, char passWord[]);
int validaUserNameCliente(nodoCliente* listaCliente, char userName[]);
arbolProducto* subProgramaDisminuyeStock(arbolProducto* productosArbol, char nombreArch[], int idProducto);
void persistirDatosCabeceraYDetalle (nodoCliente * listaCliente, char archivoCabecera[], char archivoDetalle[]);
void guardaClienteModificado (char nombreArchivo[], int id, stCliente clienteModificado);

nodoCliente * liberarSistema(nodoCliente * lista);
nodoCliente* subProgramaBajaCliente(char nombreArch[], nodoCliente* listaCliente, int id);
nodoCliente* subProgramaActivaCliente(nodoCliente* listaCliente, char nombreArch[], int id, arbolProducto* productosArbol);

int ingresaIdCliente();
int ingresaIdProducto();
int ingresaIdPedido();

nodoPedido* subProgramaBuscaPedido(nodoCliente* listaCliente, int idPedido);
void muestraPedidosSistema(nodoCliente* listaCliente);
void muestraPedidosSistemaUnCliente(nodoCliente* listaCliente);
int eliminaPedido(nodoCliente* listaCliente, int idPedido);
int borraPedidoYproductosCliente(nodoPedido* pedidos, int idPedido);
arbolProducto* subProgramaBajaProducto(arbolProducto* productos, int id);

#endif // UTILIDADES_H_INCLUDED
