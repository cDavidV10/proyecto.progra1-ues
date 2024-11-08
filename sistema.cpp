#include <iostream>
#include <limits>
#include <cstring>
#include <fstream>
#include <vector>
#include <conio.h>
#include <windows.h>

using namespace std;
const int MAX_LENGTH = 20;
const int ENTER = 13;
const int BACKSPACE = 8;
const string RUTA_USUARIOS = "usuarios.bin";
const string RUTA_REGISTRO = "registro.bin";

const string RED = "\033[1;31m";
const string GREEN = "\033[1;32m";
const string RESET = "\033[0m";

///////////////////////////// Enmanuel ///////////////////////////
const int MAX_CLIENT = 50;
const string Registro = "clientes.bin";

struct Clientes
{
    char nombres[MAX_CLIENT];
    char apellidos[MAX_CLIENT];
    char dui[MAX_CLIENT];
} cliente;

///////////////////////////////////////////////////////////////////

struct Usuarios
{
    char usuario[20];
    char password[20];
} usuario;

struct RegistroPago
{
    char persona[20];
    double pago;
} registroPago;

int loginOpcion = 0;
int menuOpcion = 0;

void login();
void iniciarSesion();
void crearCuenta();
bool verificarUsuario(bool);
bool comprobarPassword();
bool validarUsuario();
void password();
int leer();
void menuPrincipal();
void agregarPago();
void verPago();

//////////////////////////////////////////////
void correlativo();
void seccionCliente();
void ingresarClientes();
void verClientes();
void gotoxy(int, int);
//////////////////////////////////////////////

int main(int argc, char const *argv[])
{
    do
    {
        login();

        switch (loginOpcion)
        {
        case 1:
            iniciarSesion();
            break;
        case 2:
            crearCuenta();
            break;

        default:
            break;
        }
    } while (loginOpcion != 3);

    return 0;
}
//////////////////////////
void gotoxy(int x, int y)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}
//////////////////////////
void login()
{
    system("cls");
    cout << "------     BIENVENIDOS AL SISTEMA     ------" << endl;
    cout << "1. Iniciar Sesion" << endl;
    cout << "2. Crear Cuenta" << endl;
    cout << "3. Salir" << endl;
    cout << "Seleccione una opcion del menu: ";
    loginOpcion = leer();
}

void iniciarSesion()
{
    int intentos = 3;
    bool ingresa = false;
    cin.ignore();

    do
    {
        system("cls");
        cout << "------     INICIAR SESION     ------" << endl;
        cout << "Usuario: ";
        cin.getline(usuario.usuario, 20);
        cout << "Password: ";
        password();

        if (verificarUsuario(true))
        {
            ingresa = true;
        }
        else
        {
            cout << RED << "\nEl usuario y/o el password son incorrectos" << RESET << endl;
            intentos--;
            system("pause>null");
        }
    } while (!ingresa && intentos > 0);

    if (ingresa)
    {
        cout << "\nBienvenidos al sistema" << endl;
        menuPrincipal();
    }
    else
    {
        cout << RED << "\nNo pudo entrar al sistema" << RESET << endl;
    }

    system("pause");
}

void crearCuenta()
{
    cin.ignore();

    system("cls");
    cout << "------     CREAR CUENTA     ------" << endl;
    do
    {
        cout << "Usuario: ";
        cin.getline(usuario.usuario, 20);
        if (validarUsuario())
        {
            cout << RED << "El usuario debe detener entre 4 y 20 caracteres" << RESET << endl;
        }
    } while (validarUsuario());

    do
    {
        cout << "Password: ";
        password();

        if (!comprobarPassword())
        {
            cout << RED << "\nEl password debe de tener minimo 8 caracteres, un numero y una mayuscula" << RESET << endl;
        }

    } while (!comprobarPassword());

    if (verificarUsuario(false))
    {
        cout << RED << "\nEl usuario ya existe" << RESET << endl;
    }
    else
    {
        FILE *archivo = fopen(RUTA_USUARIOS.c_str(), "ab");

        if (archivo != NULL)
        {
            fwrite(&usuario, sizeof(Usuarios), 1, archivo);
            fclose(archivo);
            cout << GREEN << "\nCuenta creada correctamente" << RESET << endl;
        }
        else
        {
            cout << RED << "\nError al crear el usuario" << RESET << endl;
        }
    }

    system("Pause");
}

void menuPrincipal()
{
    do
    {
        system("cls");
        cout << "------     MENU PRINCIPAL     ------" << endl;
        cout << "1. Agregar Cliente" << endl;
        cout << "2. Agregar Pago" << endl;
        cout << "3. Ver Clientes" << endl;
        cout << "4. Ver Pago" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion del menu: ";
        menuOpcion = leer();

        switch (menuOpcion)
        {
        case 1:
            ingresarClientes();
            break;
        case 2:
            agregarPago();
            break;
        case 3:
            verClientes();
            break;
        case 4:
            verPago();
            break;
        default:
            break;
        }

    } while (menuOpcion != 5);
}

void agregarPago()
{
    cin.ignore();
    system("cls");
    cout << "------PAGO------" << endl;

    strcpy(registroPago.persona, "Genesis");
    registroPago.pago = 5.56;

    FILE *archivo = fopen(RUTA_REGISTRO.c_str(), "ab");

    if (archivo != NULL)
    {
        fwrite(&registroPago, sizeof(RegistroPago), 1, archivo);
        fclose(archivo);
        cout << GREEN << "\nPago agregado correctamente" << RESET << endl;
    }
    else
    {
        cout << RED << "\nError al agregar el pago" << RESET << endl;
    }

    system("pause");
}

void verPago()
{
    system("cls");
    cout << "------     VER PAGO     ------" << endl;

    FILE *archivo = fopen(RUTA_REGISTRO.c_str(), "rb");

    if (archivo != NULL)
    {
        bool registroEncontrado = false;
        while (fread(&registroPago, sizeof(RegistroPago), 1, archivo) == 1)
        {
            cout << "Persona: " << registroPago.persona << endl;
            cout << "Pago: $" << registroPago.pago << endl;
            registroEncontrado = true;
            cout << "----------------------------" << endl;
        }

        if (!registroEncontrado)
        {
            cout << RED << "\nNo se han encontrado registros de pago" << RESET << endl;
        }

        fclose(archivo);
    }
    else
    {
        cout << RED << "\nError al abrir el archivo de pagos" << RESET << endl;
    }

    system("pause");
}

bool validarUsuario()
{
    return (strlen(usuario.usuario) < 4 || strlen(usuario.usuario) > MAX_LENGTH);
}

bool comprobarPassword()
{
    bool largo = false;
    bool mayus = false;
    bool numero = false;

    if (strlen(usuario.password) > 8)
    {
        largo = true;
    }

    for (int i = 0; i < strlen(usuario.password); i++)
    {
        if (isupper(usuario.password[i]))
        {
            mayus = true;
        }

        if (isdigit(usuario.password[i]))
        {
            numero = true;
        }
    }

    if (largo && mayus && numero)
    {
        return true;
    }
    return false;
}

bool verificarUsuario(bool verificarPass)
{
    FILE *archivo = fopen(RUTA_USUARIOS.c_str(), "rb");

    if (archivo != NULL)
    {
        Usuarios usuarioTemp;
        while (!feof(archivo))
        {
            fread(&usuarioTemp, sizeof(Usuarios), 1, archivo);
            if (!feof(archivo))
            {
                if (strcmp(usuario.usuario, usuarioTemp.usuario) == 0)
                {
                    if (verificarPass)
                    {
                        if (strcmp(usuario.password, usuarioTemp.password) == 0)
                        {
                            fclose(archivo);
                            return true;
                        }
                    }
                    else
                    {
                        fclose(archivo);
                        return true;
                    }
                }
            }
        }
        fclose(archivo);
    }

    return false;
}

void password()
{
    int index = 0;
    char caracter;

    caracter = getch();
    while (caracter != ENTER)
    {
        if (caracter != BACKSPACE)
        {
            if (index < MAX_LENGTH - 1)
            {
                usuario.password[index++] = caracter;
                cout << "*";
            }
        }
        else if (index > 0)
        {
            cout << "\b \b";
            usuario.password[--index] = '\0';
        }
        caracter = getch();
    }
    usuario.password[index] = '\0';
}

int leer()
{
    int numero;

    while (true)
    {
        cin >> numero;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Dato incorrecto, ingrese nuevamente: ";
        }
        else
        {
            break;
        }
    }
    return numero;
}

///////////////////////////////////////////////////////////////////////////////////

void ingresarClientes()
{
    char r = 's';

    FILE *archivo = fopen(Registro.c_str(), "ab");

    if (archivo != NULL)
    {

        while (r == 's' || r == 'S')
        {
            system("cls");

            fflush(stdin);

            cout << "Ingrese los nombres del cliente: ";
            cin.getline(cliente.nombres, MAX_CLIENT);

            fflush(stdin);

            cout << "Ingrese los apellidos del cliente: ";
            cin.getline(cliente.apellidos, MAX_CLIENT);

            fflush(stdin);

            cout << "Ingrese el DUI del cliente: ";
            cin.getline(cliente.dui, MAX_CLIENT);

            fwrite(&cliente, sizeof(Clientes), 1, archivo);

            cout << "Desea seguir agregando clientes? (s/n) \nRespuesta: ";
            cin >> r;

            fflush(stdin);
        }
    }
    else
    {
        cout << "[ERROR]: Creacion de archivo invalida.";
    }

    fclose(archivo);
}

void verClientes()
{
    system("cls");

    int i = 0;
    Clientes cliente;

    FILE *archivo = fopen(Registro.c_str(), "rb");

    if (archivo != NULL)
    {
        gotoxy(30, 0);
        cout << "***** LISTA DE CLIENTES *****";
        gotoxy(1, 2);
        cout << "No ";
        gotoxy(5, 2);
        cout << "Nombres ";
        gotoxy(30, 2);
        cout << "Apellidos ";
        gotoxy(50, 2);
        cout << "DUI ";

        while (!feof(archivo))
        {
            fread(&cliente, sizeof(Clientes), 1, archivo);

            if (!feof(archivo))
            {
                gotoxy(1, 3 + i);
                cout << i + 1;
                gotoxy(5, 3 + i);
                cout << cliente.nombres;
                gotoxy(30, 3 + i);
                cout << cliente.apellidos;
                gotoxy(50, 3 + i);
                cout << cliente.dui;
            }

            i++;
        }
    }
    else
    {
        cout << "[ERROR]: Creacion de archivo invalida.";
    }

    fclose(archivo);

    cout << "\n\n";
    system("pause");
}
//////////////////////////////////////////////////////////////////////////////