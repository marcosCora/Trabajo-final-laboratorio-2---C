#include "cliente.h"

stCliente cargaUnCliente()
{
    stCliente c;

    cleanAndSetScreen();
    printf("Ingrese Nombre......: ");
    fflush(stdin);
    gets(c.nombre);
    validacionGeneralNombre(c.nombre);
    gotoxy(10,11);

    printf("Ingrese Apellido....: ");
    fflush(stdin);
    gets(c.apellido);
    validacionGeneralNombre(c.apellido);
    gotoxy(10,12);

    printf("Ingrese UserName....: ");
    fflush(stdin);
    gets(c.userName);
    existeUserNameEnArchivoGeneral(ARCHIVO_CLIENTE, c.userName);
    gotoxy(10,13);

    printf("Ingrese Password....: ");
    fflush(stdin);
    gets(c.password);
    validacionGeneralPass(c.password);
    gotoxy(10,14);

    printf("Ingrese Mail........: ");
    fflush(stdin);
    gets(c.mail);
    validacionGeneralEmail(c.mail);
    existeEmailEnArchivoGeneral(ARCHIVO_CLIENTE, c.mail);
    gotoxy(10,15);

    printf("Ingrese Genero......: ");
    fflush(stdin);
    scanf("%c", &c.genero);
    c.genero=validacionGenero(toupper(c.genero));

    c.rol = 0;
    c.activo = 1;

    return c;
}

void muestraUnCliente(stCliente c)
{
    printf("\n ID..............: %d", c.idCliente);
    printf("\n Nombre..........: %s", c.nombre);
    printf("\n Apellido........: %s", c.apellido);
    printf("\n UserName........: %s", c.userName);
    printf("\n Password........: %s", c.password);
    printf("\n Mail............: %s", c.mail);
    printf("\n Genero..........: %c", c.genero);
    printf("\n Rol.............: %d", c.rol);
    printf("\n Activo..........: %d", c.activo);
    printf("\n-------------------------------");
}

void cargaArchivoCliente(char nombreArchivo[])
{
    FILE* archi = fopen(nombreArchivo, "ab");
    stCliente c;
    char opcion = 0;
    int id = ultimoIdCliente(ARCHIVO_CLIENTE);
    if(archi)
    {
        do
        {
            system("cls");
            c = cargaUnCliente();
            id++;
            c.idCliente = id;
            fwrite(&c, sizeof(stCliente), 1, archi);
            printf("\n ESC para salir / cualquier tecla para seguir cargando...\n");
            opcion = getch();

        }
        while(opcion!=ESC);
        fclose(archi);
    }
}

//FUNCION QUE RETORNA EL ULTIMO ID PARA PODER HACER EL AUTOINCREMENTO DEL ID EN EL ARCHIVO
int ultimoIdCliente(char nombreArchivo[])
{
    int id=0;
    stCliente c;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        fseek(archi, -1*(sizeof(stCliente)), SEEK_END);
        if(fread(&c, sizeof(stCliente), 1, archi)>0)
        {
            id=c.idCliente;
        }
        fclose(archi);
    }
    return id;
}

void mostrarArchivoCliente(char nombreArchivo[])
{
    FILE* archi = fopen(nombreArchivo, "rb");
    stCliente c;
    if(archi)
    {
        while(fread(&c, sizeof(stCliente), 1, archi)>0)
        {
            muestraUnCliente(c);
        }
        fclose(archi);
    }
}


void bajaCliente (char nombreArchivo[], int id)
{
    FILE * archi = fopen(nombreArchivo, "r+b");
    stCliente c;
    int pos=buscaPosArchivoCliente(archi, id);/// me da la posicion del registro,el cursor ya listo para modificar

    if(archi)
    {
        fseek(archi, sizeof(stCliente)*pos, 0);          /// me posiciono y lo muestro
        fread(&c, sizeof(stCliente), 1, archi);

        c.activo=0;                                         /// le cambio el estado

        fseek(archi, sizeof(stCliente)*pos, 0);        /// me vuelvo a posicionar
        fwrite(&c,sizeof(stCliente), 1, archi );      ///sobreescribo el registro

        fclose(archi);
    }

}



/// busco la posicion en la que se encuentre el cliente con ese id en el archivo
int buscaPosArchivoCliente (FILE* archi, int id)
{
    stCliente c;
    int i=0;
    int flag=0;

    if(archi)
    {
        while(fread(&c, sizeof(stCliente), 1, archi)>0 && flag==0)
        {
            if(c.idCliente != id)
            {
                i++;
            }
            else
            {
                flag =1;
            }
        }
    }
    return i;
}

/// VALIDACIONES /////////////////////////////////////////////////////////////////////
int validMayYEspaciosNombre(char nom[])
{
    int i=0;                         ///creo subindice
    int flag=0;                      /// creo bandera
    int mayus=0;                     /// contador de mayusculas
    int espacio=0;                   /// contador de espacios

    while (nom[i]!='\0' && flag ==0)    ///si no es final de cadena y flag es 0, entro
    {
        if (nom[i]==' ')
        {
            espacio++;                   /// si algun caracter el espacio, incremento contador
        }
        else if (isupper(nom[i]))
        {
            mayus++;                       /// si algun caracter el mayuscula, incremento contador
        }
        else if(isalpha(nom[i]) || isupper(nom[0]))  /// si el caracter es letra o la posicion 0 tiene mayuscula
            flag = 0;
        else
        {
            flag = 1;
        }

        i++;
    }

    if (espacio>2 || mayus>3 || i<3)  ///si el string tiene mas de 2 espacios, mas de 3 mayusculas o la cantidad es menor a 3 flag 1
    {
        flag = 1;
    }
    return flag; // retorno flag
}




/// funcion qe verifica que los caracteres no puedan ser in numero
int IsdigitNombre(char nombre[])
{
    int i=0;   /// contador
    int flag =0; /// bandera

    while (nombre[i]!='\0' && flag==0)
    {
        if(isdigit(nombre[i]))  /// si es nunero
        {
            flag=1;
        }
        i++;

    }
    return flag;
}

void validacionGeneralNombre (char nom[])
{
    int flag1 =0;                                /// creo bandera
    int flag2 =0;                                /// creo bandera
    flag1 = validMayYEspaciosNombre(nom);              /// bandera es lo que devulve la otra funcion
    flag2 = IsdigitNombre(nom);

    while(flag1 == 1 || flag2 == 1)                            /// si flag es 1, hay error
    {
        titulo();
        gotoxy(9, 23);

        printf("ERROR, NO VALIDO");
        gotoxy(10,10);
        printf("Ingrese nuevamente....: ");
        fflush(stdin);

        gets(nom);
        flag1 = validMayYEspaciosNombre(nom);          /// vuelvo a validar
        flag2 = IsdigitNombre(nom);

    }
}

/// funcion que verifica las letras del genero, si no no deja continuar
char validacionGenero (char genero)
{

    while(genero != 'M' && genero != 'F')
    {
        titulo();
        gotoxy(9, 23);
        printf("ERROR, GENERO NO VALIDO");
        gotoxy(10,10);
        printf("Ingrese nuevamente....: ");

        fflush(stdin);
        scanf("%c", &genero);
    }

    return genero;
}


/// FUNCION QUE CUENTA LA CANTIDAD DE ARROBAS, ESPACIOS Y PUNTOS
int validacionEmailArrobaYPunto (char email[])
{
    int flag=0;

    int arroba=0;
    int punto=0;
    int espacio=0;

    int i=0;

    while(email[i]!= '\0')
    {

        if(email[i] == '@')
        {
            arroba++;
        }
        else if(email[i]=='.')
        {
            punto++;
        }
        else if(email[i]== ' ')
        {
            espacio++;
        }

        i++;
    }


    /// SI CUMPLE AL MENOS UNA DE ESTAS CARACTERISTICAS FLG 1
    if(arroba != 1 || punto > 4 || punto < 1 || espacio >0)
    {
        flag=1;
    }


    return flag;
}

/// VERIFICA QUE LA CANTIDAD DE CARACTERES NO SE PASE DE DE 30 Y NO SEA MENOR A 9
int validacionEmailCantCaracteres(char email[])
{
    int flag=0;
    int cant=strlen(email);

    if(cant < 9 || cant >30)
    {
        flag=1;
    }
    return flag;
}

/// si algo esta mal, hacer que cargue otra vez el email hasta q lo pone correctamente
void validacionGeneralEmail (char email[])
{
    int flag1=0;
    int flag2=0;
    flag1 = validacionEmailArrobaYPunto(email);
    flag2 = validacionEmailCantCaracteres(email);


    while(flag1 == 1 || flag2==1)
    {
        titulo();
        gotoxy(9, 23);
        printf("ERROR-EMAIL INCORRECTO");
        gotoxy(10,10);
        printf("Ingrese nuevamente....: ");
        gets(email);
        flag1 = validacionEmailArrobaYPunto(email);
        flag2 = validacionEmailCantCaracteres(email);
    }
}



/// VERIFICA QUE LA CNIDAD DE CRACTERES DE LA PASSWORD NO SEA MENOR A 8
int validacionPass(char pass[])
{
    int flag=0;
    if(strlen(pass)<8)
    {
        flag = 1;
    }
    return flag;
}



void validacionGeneralPass(char pass[])
{
    int flag=0;
    flag = validacionPass(pass);
    while (flag == 1)
    {
        titulo();
        gotoxy(9, 23);
        printf("ERROR, MINIMO DE CARACTERES 8");
        gotoxy(10, 10);
        printf("Ingrese nuevamente: ");
        gets(pass);
        flag = validacionPass(pass);
    }

}


int existeUserName (char nombreArchivo[], char user[])
{
    FILE * archi = fopen(nombreArchivo, "rb");
    int flag = 0;
    stCliente c;

    if(archi)
    {
        while(fread(&c, sizeof(stCliente), 1, archi)>0 && flag == 0)
        {
            if(strcmp(c.userName, user)== 0)
            {
                flag = 1;
            }

        }

        fclose(archi);
    }
    return flag;
}

void existeUserNameEnArchivoGeneral(char nombreArchivo[], char user[])
{
    int flag=0;
    flag = existeUserName(nombreArchivo, user);

    while(flag == 1)
    {
        titulo();
        gotoxy(9, 23);
        printf("ERROR, ESE NOMBRE DE USUARIO YA EXISTE");
        gotoxy(10, 10);
        printf("Ingrese nuevamente......: ");
        gets(user);
        flag = existeUserName(nombreArchivo, user);
    }

}


int existeEmail(char nombreArchivo[], char email[])
{
    FILE * archi = fopen(nombreArchivo, "rb");
    int flag=0;
    stCliente c;

    if(archi)
    {
        while(fread(&c, sizeof(stCliente), 1, archi)>0 && flag ==0)
        {

            if(strcmp(c.mail, email)==0)
            {
                flag = 1;
            }

        }

        fclose(archi);
    }

    return flag;
}

void existeEmailEnArchivoGeneral(char nombreArchivo[], char email[])
{
    int flag =0;
    flag = existeEmail(nombreArchivo, email);

    while (flag==1)
    {
        titulo();
        gotoxy(9, 23);

        printf("ERROR-ESE MAIL YA EXISTE");
        gotoxy(10, 10);
        printf("Ingrese nuevamente......: ");
        gets(email);
        flag = existeEmail(nombreArchivo, email);
    }
}


stCliente activaCliente (char nombreArchivo[], int id)
{
    FILE * archi = fopen(nombreArchivo, "r+b");
    stCliente c;
    int pos = buscaPosArchivoCliente(archi, id);

    if(archi)
    {
        fseek(archi, sizeof(stCliente)*pos, 0);
        fread(&c, sizeof(stCliente), 1, archi);

        c.activo = 1;

        fseek(archi, sizeof(stCliente)*pos, 0);
        fwrite(&c, sizeof(stCliente), 1, archi);

        fclose(archi);
    }

    return c;
}

void guardaClienteModificado (char nombreArchivo[], int id, stCliente clienteModificado)
{
    FILE * archi = fopen(nombreArchivo, "r+b");
    stCliente c;
    int pos = buscaPosArchivoCliente(archi, id);

    if(archi)
    {
        fseek(archi, sizeof(stCliente)*pos, 0);
        fread(&c, sizeof(stCliente), 1, archi);

        c = clienteModificado;

        fseek(archi, sizeof(stCliente)*pos, 0);
        fwrite(&c, sizeof(stCliente), 1, archi);

        fclose(archi);
    }
}

void guardaClienteCreado(char nombreArchivo[], stCliente c)
{

    FILE * archi = fopen(nombreArchivo, "ab");

    if(archi)
    {

        fwrite(&c, sizeof(stCliente), 1, archi);
    }
    fclose(archi);
}

void muestraUnClienteAdmin(stCliente c)
{
    printf("\n ID..............: %d", c.idCliente);
    printf("\n Nombre..........: %s", c.nombre);
    printf("\n Apellido........: %s", c.apellido);
    printf("\n UserName........: %s", c.userName);
    printf("\n Password........: %s", c.password);
    printf("\n Mail............: %s", c.mail);
    printf("\n Genero..........: %c", c.genero);
    printf("\n Rol.............: %d", c.rol);
    printf("\n Activo..........: %d", c.activo);
    printf("\n-------------------------");

}

void muestraUnClienteUsuario(stCliente c)
{
    printf("\n Nombre..........: %s", c.nombre);
    printf("\n Apellido........: %s", c.apellido);
    printf("\n UserName........: %s", c.userName);
    printf("\n Password........: %s", c.password);
    printf("\n Mail............: %s", c.mail);
    printf("\n Genero..........: %c", c.genero);
    printf("\n-------------------------");
}










