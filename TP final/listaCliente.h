#ifndef LISTACLIENTE_H_INCLUDED
#define LISTACLIENTE_H_INCLUDED

#include "listaPedido.h"
#include "cliente.h"

typedef struct _nodoCliente
{
    stCliente datoCliente;
    struct _nodoCliente * siguiente;
    nodoPedido* listaPedidos;
    float costoTotalPedidos;

}nodoCliente;

nodoCliente* inicListaCliente();
nodoCliente* creaNodoCliente(stCliente dato);
nodoCliente* agregarPrincipioListaCliente(nodoCliente* lista,nodoCliente * nodoNuevo);
nodoCliente* agregoFinalListaCliente(nodoCliente* lista, nodoCliente* nuevoNodo);
nodoCliente* buscaUltimoNodoCliente(nodoCliente* lista);
nodoCliente* agregarEnOrdenListaXIdCliente(nodoCliente* lista, nodoCliente* nuevoNodo);
void muestraListaClienteAdmin(nodoCliente* lista);
void muestraListaClienteUsuario(nodoCliente* lista);
void muestraUnNodoClienteAdmin(nodoCliente* listaCliente);
void muestraUnNodoClienteUsuario(nodoCliente* listaCliente);
nodoCliente* borraListaCliente(nodoCliente* lista);///modificar
nodoCliente* eliminaUltimoNodoCliente(nodoCliente* lista);
nodoCliente* eliminaPrimerNodoCliente(nodoCliente* lista);
nodoCliente* buscarNodoIdCliente(nodoCliente* lista, int id);
nodoCliente* borrarNodoIdCliente(nodoCliente* lista, int id);
nodoCliente* desvinculaNodoCliente(nodoCliente** pLista);

int buscaRolEnListaCliente(nodoCliente* lista, char userName[20]);

///manejo de archivo
nodoCliente* archivoCliente2ListaClientes(nodoCliente* listaCliente, char nombreArch[]);
nodoCliente* altaUnUsuariEnListaCliente(nodoCliente* listaCliente);

nodoCliente* modificaClienteUsuario(nodoCliente* listaCliente, char userName[20]);
nodoCliente* modificaClienteAdmin(nodoCliente* listaCliente, int id);
nodoCliente* buscarNodoUserNameCliente(nodoCliente* lista, char userName[20]);
nodoCliente* altaUnAdminEnListaCliente(nodoCliente* listaCliente);

int buscaIdListaClientePorUserName(nodoCliente* listaCliente, char userName[]);
nodoCliente* sumaCostos(nodoCliente* listaCliente);
float sumaPedidos(nodoPedido* listaPedido);
nodoCliente * liberarClienteConDatoS(nodoCliente * lista, int id);




#endif // LISTACLIENTE_H_INCLUDED
