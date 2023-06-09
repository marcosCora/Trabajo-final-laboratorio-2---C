#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "utilidades.h"


void cleanAndSetScreen();
void titulo();
int leerOpcion();
void menuPrincipal();
void logIn(nodoCliente* listaCliente, int *guardaRol, int *idCliente);
void SubProgramaLogIn(nodoCliente* listaCliente, arbolProducto* productosArbol);
void registrarse(nodoCliente* listaCliente);
void marco();
void lineaRecta(int x);
void lineaRectavertical(int x,int y);
void subMenuAdmin(nodoCliente* listaCliente, arbolProducto* productosArbol);
void subMenuUsuario(nodoCliente* listaCliente, arbolProducto* productosArbol, int id);
void adminCliente(nodoCliente* listaCliente, arbolProducto* productos);
void usuarioCliente(nodoCliente* listaCliente, int id);
void adminPedido(nodoCliente* listaCliente);
void usuarioPedido(nodoCliente* listaCliente, int idCliente, arbolProducto* productosArbol);
void adminProducto(arbolProducto* productosArbol);
void verProductoPorEstiloMenu(arbolProducto* productosArbol);
void subMenuArchivos();



#endif // MENU_H_INCLUDED
