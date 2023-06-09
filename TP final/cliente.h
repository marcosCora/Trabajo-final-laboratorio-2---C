#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define ARCHIVO_CLIENTE "cliente.dat"

#define ESC 27

typedef struct{
    int idCliente;
    char nombre[30];
    char apellido[30];
    char userName[20];
    char password[20];
    char mail[30];
    char genero;
    int rol;                         //1: es admin - 0: es comun
    int activo;                      //1 activo - 0 inactivo
}stCliente;

stCliente cargaUnCliente();
void muestraUnClienteAdmin(stCliente c);
void muestraUnClienteUsuario(stCliente c);
void cargaArchivoCliente(char nombreArchivo[]); //OPCION PARA CARGAR VARIOS CLIENTES (MODO ADMIN)
int ultimoIdCliente(char nombreArchivo[]);
void mostrarArchivoCliente(char nombreArchivo[]);
void bajaCliente (char nombreArchivo[], int id);
int buscaPosArchivoCliente (FILE* archi, int id);

/// VALIDACIONES /////////////////////
int validMayYEspaciosNombre(char nom[]); /// cuentas la cantidad de espacios mayusculas y verifica que sean letras, si esta algo mal retorna 1
int IsdigitNombre(char nombre[]);    /// verificca que el nombre no tenga numeros, si los tiene retorna 1
void validacionGeneralNombre (char nom[]);   /// evalua las funciones anteriores y vuelve a validar hasta que cumpla con las condiciones

char validacionGenero (char genero);    /// valida que la letra sea M o F

int validacionEmailArrobaYPunto (char email[]);    /// cuanta la cantidad de arrobas puntos y espacios, retorna 1 si algo esta mal
int validacionEmailCantCaracteres(char email[]);   /// valida la cantidad de caracteres si son pocos o muchos, retorna 1
void validacionGeneralEmail (char email[]);      /// evalua lo que retornan estas 2 funciones y vefifica si esta todo bien


int validacionPass (char pass[]);
void validacionGeneralPass(char pass[]);

int existeUserName (char nombreArchivo[], char user[]);
void existeUserNameEnArchivoGeneral(char nombreArchivo[], char user[]);

int existeEmail(char nombreArchivo[], char email[]);
void existeEmailEnArchivoGeneral(char nombreArchivo[], char email[]);

stCliente activaCliente (char nombreArchivo[], int id);
void guardaClienteCreado(char nombreArchivo[], stCliente c);


#endif // CLIENTE_H_INCLUDED
