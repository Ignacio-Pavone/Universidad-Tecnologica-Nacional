#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#define Usuarios "Usuarios.bin"
#define CryptosArchivo "Cryptos.bin"

#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#define LONGITUD 15
#define MAX_INTENTOS 3

typedef struct
{
    char nombre[15];
    char descripcion[1000];
    float valor;
    float cantidad;
    int codigo;
} crypto;

typedef struct
{
    char nombre[30];
    int edad;
    int id;
    char nick[16];
    char password[32];
    float dinero;
    float cantidadWalrus;
} usuario;

//|Funciones de menu y estetica||
void gotoxy(int x, int y);
int menu();
int ejecutarSeleccion();
int MenuCompra();
void fechaYhora();
void login();

//|Funciones para la cryptomoenda|
void cargarCryptoWalrusCoin();
void mostrarCrypto(int id);
float cantidadAConvertir();
float cantidadAConvertirDolar();
void mostrarInversionesWalrus();
void modificadorWalrusDolar(usuario *fullcrypto);
void modificadorDolarWalrus(usuario *fullcrypto);
void modificarCrypto(crypto modificada);
crypto obtenerCryptoActual();
void variacionesWallrus(int fecha);
void eventoAleatorioCaida();
void eventoAleatorioAlza();
void CargarDineroABilletera(int id);
void mostrarrCrypto();
void mostrarUnaCrypto(crypto aux);

//|Funciones de Usuario|
void modificarUsuarioPorPos(usuario user, int pos);
int obtenerPosicionPorID(int id);
int pedirID();
void cargarRegistro();
usuario registro();
int comprobarUser(char username[]);
void mostrarArchivo();
void mostrarUno(usuario aux);
int cantidadDeRegistros();

int main()
{
    srand(time(NULL));
    cargarCryptoWalrusCoin(); //Funciona solo 1 vez para cargar datos.
    login();
    int cantidadRegistros = cantidadDeRegistros();
    usuario arrayUsuarios;
    crypto arrayCryptos;
    ejecutarSeleccion();
    int ocurrido = 0;
    int x = 0;

    if (ocurrido == 0)
    {
        eventoAleatorioAlza();
        eventoAleatorioCaida();
        ocurrido = 1;
        x = ejecutarSeleccion();
    }

    return 0;
}
void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD posicionPos;
    posicionPos.X = x;
    posicionPos.Y = y;
    SetConsoleCursorPosition(hCon, posicionPos);
}
int menu()
{
    int opcion = 0;

    system("pause");
    system("cls");

    gotoxy(50, 1);
    fechaYhora();
    printf("\n\n\t\t |||Por favor a continuacion seleccione la operacion que desea realizar|||\n\n\n");
    gotoxy(50, 3);
    printf("\n\n\n\n1-Comprar-Venta de cryptomonedas.\n");
    gotoxy(50, 5);
    printf("\n\n\n\n2-Consultar inversiones. \n");
    gotoxy(50, 7);
    printf("\n\n\n\n3-Ingresar dinero a tu monedero virtual \n");
    gotoxy(50, 9);
    printf("\n\n\n\n4-Informacion sobre nuestra moneda \n");
    gotoxy(50, 11);
    printf("\n\n\n\n0-Salir. \n");
    scanf("%d", &opcion);
    return opcion;
}
int ejecutarSeleccion()
{
    bool ocurrido = false;
    int opcion = menu();
    int id = 0;
    int flag = 0;
    int registros = 0;
    usuario temp;
    int seleccion;
    int encontrado = 0;
    int x = 0;
    system("cls");
    fechaYhora();

    do
    {
        system("cls");
        FILE *buffer;
        buffer = fopen(Usuarios, "rb");
        switch (opcion)
        {
        case 1:
            id = pedirID();
            if (buffer != NULL)
            {
                while (fread(&temp, sizeof(usuario), 1, buffer) > 0)
                {
                    if (temp.id == id)
                    {
                        encontrado = 1;
                        seleccion = MenuCompra();
                        do
                        {
                            switch (seleccion)
                            {
                            case 1:
                                modificadorDolarWalrus(&temp);
                                return ocurrido = 1;
                                system("pause");
                                break;
                            case 2:
                                modificadorWalrusDolar(&temp);
                                system("pause");
                                break;
                            case 0:
                                x = ejecutarSeleccion();
                                break;
                            default:
                                printf("Error opcion incorrecta");
                                break;
                            }
                            break;
                        }
                        while (seleccion > 0 || seleccion < 2);
                    }
                }
                if (encontrado == 0)
                {
                    printf("\t\t\t                >>>ID INCORRECTO<<<\n");
                    printf("\t\t                  >>>ID Ingreselo nuevamente<<<\n");
                    scanf("%d", &id);
                }
                fclose(buffer);
                if (ocurrido == false)
                {
                    eventoAleatorioAlza();
                    eventoAleatorioCaida();
                    ocurrido = true;
                }
            }
            break;
        case 2:

            id = pedirID();
            mostrarCrypto(id);
            ejecutarSeleccion();

            break;
        case 3:
            id = pedirID();
            CargarDineroABilletera(id);
            ejecutarSeleccion();
            break;
        case 4:
            mostrarrCrypto();
            system("pause");
            break;
        case 5:
            break;
        case 0:
            exit(0);
        default:
            break;
        }
    }
    while (opcion > 0 || opcion <= 4);
}
int MenuCompra()
{
    system("cls");
    int seleccion = 0;
    fechaYhora();
    printf("Bienvenido a nuestro sector de cambio\n");
    printf("Seleccione que intercambio quiere hacer\n");
    gotoxy(1, 3);
    printf("1-Dolar - Walrus Coin\n");
    gotoxy(1, 4);
    printf("2-Walrus Coin-Dolar \n");
    gotoxy(1, 6);
    printf("0-Para volver al menu\n");
    do
    {
        if (seleccion <= 0 && seleccion >= 2)
        {
            printf("Numero invalido, porfavor seleccione una opcion entre 0, 1 o 2. \n");
        }
        scanf("%d", &seleccion);
        system("pause");
        system("cls");

    }
    while (seleccion < 0 || seleccion > 2);

    return seleccion;
}
void fechaYhora()
{
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    strftime(output, 128, "%d/%m/%y %H:%M:%S", tlocal);
    gotoxy(40, 1);
    printf("%s\n", output);
}
void cargarCryptoWalrusCoin()
{
    FILE *buffer;
    crypto temp;

    bool cargado = false;
    while (cargado == false)
    {
        buffer = fopen(CryptosArchivo, "ab");
        if (buffer != NULL)
        {
            strcpy(temp.nombre, "Walrus Coin\n");
            temp.valor = 1.0782;
            temp.cantidad = 4307234.38;
            temp.codigo = 1;
            fwrite(&temp, sizeof(crypto), 1, buffer);
            cargado = true;
            fclose(buffer);
        }
    }
}
void mostrarCrypto(int id)
{
    FILE *buffer;
    buffer = fopen(CryptosArchivo, "rb");
    crypto aux;

    FILE *archi;
    archi = fopen(Usuarios, "rb");
    usuario datos;
    float total = 0;

    if (archi != NULL)
    {
        while (fread(&datos, sizeof(usuario), 1, archi) > 0 && id == datos.id)
        {
            fechaYhora();
            puts("\n-----------------------------------------------------------------\n");
            printf("Usted tiene $ %.2f DOLARES y tiene %.2f WALRUS COINS \n", datos.dinero, datos.cantidadWalrus);
        }
        fclose(archi);
    }
    if (buffer != NULL)
    {
        while (fread(&aux, sizeof(crypto), 1, buffer) > 0)
        {
            total = aux.cantidad * aux.valor;
            printf("El stock de WALRUS COINS es %.2f y la capitalizacion de mercado es de $ %.2f\n", aux.cantidad, total);
            printf("El walrus tiene un valor de %.4f\n", aux.valor);
            puts("-----------------------------------------------------------------\n");
            break;
        }
        fclose(buffer);
    }
}
float cantidadAConvertir()
{
    float cantidad = 0;
    printf("Ingrese la cantidad de dolares que quiere convertir \n");
    scanf("%f", &cantidad);
    return cantidad;
}
float cantidadAConvertirDolar()
{
    float cantidad = 0;
    printf("Ingrese la cantidad de Walrrus Coin que quiere convertir \n");
    scanf("%f", &cantidad);
    return cantidad;
}
void modificadorWalrusDolar(usuario *fullcrypto)
{
    FILE *buffer;
    buffer = fopen(Usuarios, "rb");
    crypto actual = obtenerCryptoActual();
    float cantidad = cantidadAConvertirDolar();
    fclose(buffer);

    if (cantidad <= fullcrypto->cantidadWalrus)
    {
        fullcrypto->cantidadWalrus -= cantidad;
        actual.cantidad -= cantidad;
        cantidad = cantidad * actual.valor;
        fullcrypto->dinero += cantidad;

        printf("Tu cantidad de Walrus Coin es %.2f\n", fullcrypto->cantidadWalrus);

        printf("Tus walrus se convirtieron en %.2f DOLARES\n", cantidad);
        int pos = obtenerPosicionPorID(fullcrypto->id);
        modificarUsuarioPorPos(*fullcrypto, pos);

        modificarCrypto(actual);
        printf("Gracias por usar nuestra pagina de cambio,los esperamos pronto!\n");
    }
    else
    {
        printf("Ingrese una cantidad valida para procesar\n");
    }
}
void modificadorDolarWalrus(usuario *fullcrypto)
{
    FILE *buffer;
    buffer = fopen(Usuarios, "rb");
    crypto actual = obtenerCryptoActual();
    float cantidad = cantidadAConvertir();
    if (cantidad <= fullcrypto->dinero)
    {
        fullcrypto->dinero -= cantidad;
        cantidad = cantidad / actual.valor;
        fullcrypto->cantidadWalrus = cantidad;
        printf("Tu cantidad de Walrus Coin es %.2f\n", fullcrypto->cantidadWalrus);
        actual.cantidad -= cantidad;
        printf("Walrus Coins quedan %.2f\n", actual.cantidad);
        int pos = obtenerPosicionPorID(fullcrypto->id);
        modificarUsuarioPorPos(*fullcrypto, pos);
        modificarCrypto(actual);
        printf("Gracias por usar nuestra pagina de cambio,los esperamos pronto!\n");
    }
    else
    {
        printf("Ingrese una cantidad valida para procesar\n");
    }
}
void modificarCrypto(crypto modificada)
{
    FILE *buffer;
    buffer = fopen(CryptosArchivo, "wb");
    if (buffer != NULL)
    {
        fwrite(&modificada, sizeof(crypto), 1, buffer);
        fclose(buffer);
    }
}
crypto obtenerCryptoActual()
{
    FILE *buffer;
    crypto aux;
    buffer = fopen(CryptosArchivo, "rb");
    if (buffer != NULL)
    {
        fseek(buffer, 0, 0);
        fread(&aux, sizeof(crypto), 1, buffer);
        fclose(buffer);
        return aux;
    }
    else
    {
        printf("No existen datos de la CRYPTO\n");
    }
    fclose(buffer);
}
void modificarUsuarioPorPos(usuario user, int pos)
{
    FILE *buffer;
    usuario temp;
    buffer = fopen(Usuarios, "r+b");
    if (buffer != NULL)
    {
        fseek(buffer, sizeof(usuario) * (pos - 1), 0);
        fwrite(&user, sizeof(usuario), 1, buffer);
    }
    else
    {
        printf("Error");
    }
    fclose(buffer);
}
int obtenerPosicionPorID(int id)
{
    FILE *buffer;
    usuario aux;
    buffer = fopen(Usuarios, "rb");
    if (buffer != NULL)
    {
        while (fread(&aux, sizeof(usuario), 1, buffer) > 0)
        {
            if (id == aux.id)
            {
                fclose(buffer);
                return ftell(buffer) / sizeof(usuario);
            }
        }
    }
    else
    {
        printf("ERROR:Archivo corrupto \n");
    }
    fclose(buffer);
}
void login()
{

    usuario aux;

    int intento = 0;
    int ingresa = 0;
    char caracter;
    char opcion = 'n';
    int contador = 0;
    int i = 0;
    system("cls");
    fechaYhora();
    printf("\n\t\t\tINICIO DE SESION\n");
    printf("\t\t\t---------------\n");
    printf("Usted ya tiene cuenta(S/N)?:  \n");
    fflush(stdin);
    scanf("%c", &opcion);
    opcion = tolower(opcion);

    system("cls");
    fechaYhora();
    if (opcion == 'n')
    {
        cargarRegistro();
    }

    do
    {
        do
        {
            i = 0;
            printf("\n\t\t\tINICIE SESION");
            printf("\n\tUSUARIO: ");
            fflush(stdin);
            gets(aux.nick);
            printf("\tCLAVE: ");
            fflush(stdin);

            while (caracter = getch())
            {
                if (caracter == TECLA_ENTER)
                {
                    aux.password[i] = '\0';
                    break;
                }
                else if (caracter == TECLA_BACKSPACE)
                {
                    if (i > 0)
                    {
                        i--;
                        printf("\b \b");
                    }
                }
                else
                {
                    if (i < LONGITUD)
                    {
                        printf("*");
                        aux.password[i] = caracter;
                        i++;
                    }
                }
            }
            FILE *buffer;
            usuario temp;
            buffer = fopen(Usuarios, "rb");
            int count = 0;
            int flag = 0;

            if (buffer != NULL)
            {
                while (fread(&temp, sizeof(usuario), 1, buffer) > 0)
                {

                    if (strcmp(aux.nick, temp.nick) == 0 && strcmp(aux.password, temp.password) == 0)
                    {
                        ingresa = 1;
                        break;
                    }
                }
                fclose(buffer);
            }
            if (ingresa == 0)
            {
                printf("\n\tUsuario y/o clave son incorrectos\n");
                intento++;
                getchar();
            }
        }
        while (intento < MAX_INTENTOS && ingresa == 0);

        if (ingresa == 1)
        {
            printf("\n\n\t|||Bienvenido a nuestra plaforma Walrus Wallet|||\n");
            break;
        }
        else
        {
            printf("\n\n\tHa sobrepasado el numero maximo de intentos permitidos\n");
            exit(0);
        }
    }
    while (opcion == 's');
}
void cargarRegistro()
{
    FILE *buffer;
    buffer = fopen(Usuarios, "ab");
    usuario aux;
    if (buffer != NULL)
    {
        aux = registro();
        fwrite(&aux, sizeof(usuario), 1, buffer);
    }
    fclose(buffer);
}
usuario registro()
{
    usuario aux;

    int id = 0;
    int leng = 0;
    int comprobacion = 0;
    printf("\n\t\t\tREGISTRO\n\n");
    printf("Ingrese su nombre y apellido: \n");
    fflush(stdin);
    gets(aux.nombre);
    printf("Ingrese su edad: \n");
    scanf("%d", &aux.edad);

    if (aux.edad < 18)
    {
        printf("Usted es menor de edad, no puede ingresar a nuestra pagina debido a nuestra politica de menores.\n");
        exit(0);
    }
    printf("Ingrese su nombre de usuario: (max 16 caracteres)\n");
    fflush(stdin);
    gets(aux.nick);

    comprobacion = comprobarUser(aux.nick);
    if (comprobacion == 0)
    {

        system("cls");
        fechaYhora();
        printf("\n\t|||El usuario ya existe,porfavor reeintente nuevamente|||\n");

        registro();

    }
    else
    {
        do
        {
            printf("Ingrese su contrasenia (Entre 8-16 caracterres): \n");
            fflush(stdin);
            gets(aux.password);
            leng = strlen(aux.password);

        }
        while (leng < 8 || leng > 16);
        id = rand() % 500;
        aux.id = id;
        cantidadDeRegistros();
        printf("\n\n\tSu numero de id es %d, por favor anotelo que mas adelante de lo pedira el sistema, no lo olvide ni se lo pase a NADIE. \n", id);
        system("pause");
        system("cls");
    }
    return aux;
}
void mostrarArchivo()
{
    FILE *buffer;
    usuario aux;
    buffer = fopen(Usuarios, "rb");
    if (buffer != NULL)
    {
        while (fread(&aux, sizeof(usuario), 1, buffer) > 0)
        {
            mostrarUno(aux);
        }
    }
    else
    {
        printf("Error\n");
        exit(0);
    }
    fclose(buffer);
}
void mostrarUno(usuario aux)
{
    printf("|||Usuario||| \n");

    printf("nick: %s \n", aux.nick);
    printf("password: %s \n", aux.password);
    printf("El ID es %d\n", aux.id);
    printf("Dolares $ %.2f", aux.dinero);
    printf("walrus coins %.2f", aux.cantidadWalrus);
    system("pause");
    system("cls");
    //login();
}
int cantidadDeRegistros()
{
    FILE *buffer;
    buffer = fopen(Usuarios, "rb");
    int cantidad = 0;
    if (buffer != NULL)
    {
        fseek(buffer, 0, SEEK_END);
        cantidad = ftell(buffer) / sizeof(usuario);
    }
    fclose(buffer);
    return cantidad;
}
void variacionesWallrus(int fecha)
{
    float numeroAleatorio = 0;

    fecha = fecha * 24;
    for (int i = 0; i < fecha; i++)
    {
        numeroAleatorio = rand() % 1 - 0.04;
    }
}
void eventoAleatorioCaida()
{
    system("cls");
    crypto aux = obtenerCryptoActual();
    bool ocurrido = false;
    float numeroAleatorio = 0;
    while (!ocurrido)
    {
        for (int i = 1; i <= 5; i++)
        {
            numeroAleatorio = rand() % 15 + 1;

            if (numeroAleatorio == 3)
            {
                printf("ALERTA!!.\n");
                system("pause");
                printf("Oh no, Elon Musk ha twitteado que el Walrus es malo para el medio ambiente, lamentablemente, el mundo le esta haciendo caso y el valor del Walrus ha caido un 30%, por lo tanto las demas cryptomonedas tambien caeran un porcentaje importante.\n ");
                printf("Seria recomendable convertir tus criptomonedas a Dolar, antes de que se siga devaluando tu dinero. \n");

                aux.valor = aux.valor * 0.70;
                modificarCrypto(aux);
                ocurrido = true;
            }
        }
    }
}
void eventoAleatorioAlza()
{
    system("cls");
    bool ocurrido = false;
    float numeroAleatorio = 0;
    crypto aux = obtenerCryptoActual();
    while (!ocurrido)
    {
        for (int i = 1; i <= 30; i++)
        {
            numeroAleatorio = rand() % 30 + 1;

            if (numeroAleatorio == 9)
            {
                fechaYhora();
                printf("ALERTA!!.\n");
                system("pause");
                printf("Parece que Amazon ahora acepta ahora cryptomonedas, parece que todas las monedas estan en un alza masiva.\n ");
                printf("Aprovecha es un buen momento para holdear tus monedas!. \n");

                aux.valor = aux.valor * 1.75;
                modificarCrypto(aux);
                ocurrido = true;
            }
        }
    }
}
void CargarDineroABilletera(int id)
{
    usuario temporal;
    int existe = 0;
    int pos = 0;
    float dinero = 0;
    FILE *buffer;
    buffer = fopen(Usuarios, "r+b");

    if (buffer != NULL)
    {
        while (fread(&temporal, sizeof(usuario), 1, buffer) > 0 && existe == 0)
        {
            if (temporal.id == id)
            {
                fechaYhora();
                pos = ftell(buffer) - sizeof(usuario);
                existe = 1;
                printf("Ingrese el dinero a invertir \n");
                scanf("%f", &dinero);
                if (dinero < 0)
                {
                    printf("Ingrese cantidad valida de dinero\n");
                }
                else
                {
                    fseek(buffer, pos, SEEK_SET);
                    temporal.dinero = temporal.dinero + dinero;
                    fwrite(&temporal, sizeof(usuario), 1, buffer);
                }
            }
        }
        fclose(buffer);
    }
}
int pedirID()
{
    int id = 0;
    printf("\t\t\t |||PARA COMPRA VENTA DE CRYPTOS NECESITAMOS SU ID|||\n ");
    fflush(stdin);
    scanf("%d", &id);
    system("cls");
    return id;
}
void mostrarrCrypto()
{
    FILE *buffer;
    crypto aux;
    buffer = fopen(CryptosArchivo, "rb");
    if (buffer != NULL)
    {
        while (fread(&aux, sizeof(crypto), 1, buffer) > 0)
        {
            mostrarUnaCrypto(aux);
        }
    }
    fclose(buffer);
}
void mostrarUnaCrypto(crypto aux)
{
    fechaYhora();
    printf("Nombre: %s \n", aux.nombre);
    printf("Valor actual: %.2f\n", aux.valor);
    printf("Cantidad en stock: %.2f\n", aux.cantidad);
    printf("Codigo: %d\n", aux.codigo);
}
int ProyeccionFuturo()
{
    int numero = 0;
    printf("Ingrese un numero para poder ver una posible proyeccion de la fluctuacion de la moneda \n");
    scanf("%d", &numero);
    return numero;
}
//comprobacion de existencia de nombre de usuario
int comprobarUser(char username[])
{
    FILE *buffer;
    buffer = fopen(Usuarios, "rb");
    usuario temp;
    int flag;
    int i = 0;

    while (fread(&temp, sizeof(usuario), 1, buffer) > 0)
    {
        if (strcmp(temp.nick, username) == 0 && flag == 0)
        {
            flag = 0;
            break;
        }
        else
        {
            flag = 1;
        }
    }
    return flag;
}
