#include <iostream>
#include <limits>
#include <cstring>
#include <fstream>
#include <vector>
#include <conio.h>
#include <windows.h>

using namespace std;
const int MAX_LENGTH = 30; // Cambie el tamano de 20 a 30
const int ENTER = 13;
const int BACKSPACE = 8;
const string RUTA_USUARIOS = "usuarios.bin";
const string RUTA_REGISTRO = "registro.bin";

const string RED = "\033[1;31m";
const string GREEN = "\033[1;32m";
const string RESET = "\033[0m";
const int MAX_CLIENT = 50;
const string Registro = "clientes.bin";

struct Clientes
{
    char nombres[MAX_CLIENT];
    char apellidos[MAX_CLIENT];
    char dui[11];
    bool pago;
} cliente;

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
void correlativo();
void seccionCliente();
void ingresarClientes();
bool validarCliente(char[]);
bool validarDui(char[]);
void verClientes();
void gotoxy(int, int);

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

void login()
{
    system("cls");
    cout << "------     BIENVENIDOS AL SISTEMA     ------" << endl;
    cout << "1. Iniciar Sesion" << endl;
    cout << "2. Registrarse" << endl; // Cambie de crear cuenta a registrarse
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
        menuPrincipal();
    }
    else
    {
        cout << RED << "\nNo pudo entrar al sistema" << RESET << endl;
    }
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
            cout << RED << "\nEl password debe de tener minimo 8 caracteres, un numero, una mayuscula y un caracter especial" << RESET << endl;
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

void ingresarClientes()
{

    FILE *archivo = fopen(Registro.c_str(), "ab");

    if (archivo != NULL)
    {

        system("cls");

        fflush(stdin);

        do
        {
            cout << "Ingrese los nombres del cliente: ";
            cin.getline(cliente.nombres, MAX_CLIENT);

        } while (!validarCliente(cliente.nombres));

        fflush(stdin);

        do
        {
            cout << "Ingrese los apellidos del cliente: ";
            cin.getline(cliente.apellidos, MAX_CLIENT);

        } while (!validarCliente(cliente.apellidos));

        fflush(stdin);

        do
        {
            cout << "Ingrese el DUI del cliente: ";
            cin.getline(cliente.dui, 11);

        } while (!validarDui(cliente.dui));

        cliente.pago = false;

        fwrite(&cliente, sizeof(Clientes), 1, archivo);

        fflush(stdin);
    }

    else
    {
        cout << RED << "[ERROR]: Creacion de archivo invalida." << RESET; // le agregue color
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
        gotoxy(65, 2);
        cout << "ESTADO"; // cambie pagos por estado

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

                if (cliente.pago)
                {
                    gotoxy(65, 3 + i);
                    cout << GREEN << "Pagado" << RESET;
                }

                else
                {
                    gotoxy(65, 3 + i);
                    cout << RED << "Sin Pago" << RESET;
                }
            }

            i++;
        }
    }

    else
    {
        cout << RED << "[ERROR]: Creacion de archivo invalida." << RESET; // le agregue color
    }

    fclose(archivo);

    cout << "\n\n";
    system("pause");
}

/////////////////////////////////////////////////
/////////////////////Genesis////////////////////

void agregarPago()
{

    bool clienteEncontrado;
    int numClientes;

    cin.ignore();
    system("cls");
    cout << "------     PAGO    ------" << endl;

    char duiCliente[11];
    double pago;

    FILE *archivoClientes = fopen(Registro.c_str(), "rb");
    FILE *archivoPagos = fopen(RUTA_REGISTRO.c_str(), "ab");

    if (archivoClientes != NULL && archivoPagos != NULL)
    {
        Clientes cliente;
        RegistroPago registroPago;
        clienteEncontrado = false;
        numClientes = 0;
        Clientes clientes[MAX_CLIENT];

        while (fread(&cliente, sizeof(Clientes), 1, archivoClientes) == 1)
        {
            clientes[numClientes++] = cliente;
        }

        if (numClientes == 0)
        {
            cout << RED << "\nNo hay usuarios registrados." << RESET << endl;
            fclose(archivoClientes);
            fclose(archivoPagos);
            system("pause");
            return;
        }

        cout << "Ingrese el DUI del cliente: ";
        cin.getline(duiCliente, 11);

        for (int i = 0; i < numClientes; i++)
        {
            if (strcmp(clientes[i].dui, duiCliente) == 0)
            {
                clienteEncontrado = true;
                cout << "Ingrese el monto del pago: $";
                cin >> pago;

                if (pago > 0)
                {
                    strcpy(registroPago.persona, clientes[i].nombres);
                    registroPago.pago = pago;
                    fwrite(&registroPago, sizeof(RegistroPago), 1, archivoPagos);

                    clientes[i].pago = true;

                    fclose(archivoClientes);
                    archivoClientes = fopen(Registro.c_str(), "wb");

                    for (int j = 0; j < numClientes; j++)
                    {
                        fwrite(&clientes[j], sizeof(Clientes), 1, archivoClientes);
                    }

                    cout << GREEN << "\nPago agregado correctamente" << RESET << endl;
                    system("pause");
                    break;
                }

                else
                {
                    cout << RED << "\nEl pago debe ser mayor a 0" << RESET << endl;
                    system("pause");
                    break;
                }
            }
        }

        if (!clienteEncontrado)
        {
            cout << RED << "\nCliente no encontrado" << RESET << endl;
            system("pause");
        }

        fclose(archivoClientes);
        fclose(archivoPagos);
    }

    else
    {
        cout << RED << "\nError al abrir los archivos de clientes o pagos" << RESET << endl;
        system("pause");
    }
}

void verPago()
{
    bool pagoRealizado;
    bool registroEncontrado;

    system("cls");
    cout << "------     VER PAGO     ------" << endl;

    FILE *archivoClientes = fopen(Registro.c_str(), "rb");
    FILE *archivoPagos = fopen(RUTA_REGISTRO.c_str(), "rb");

    if (archivoClientes != NULL && archivoPagos != NULL)
    {
        Clientes cliente;

        RegistroPago pago;

        registroEncontrado = false;

        while (fread(&cliente, sizeof(Clientes), 1, archivoClientes) == 1)
        {
            fseek(archivoPagos, 0, SEEK_SET);

            pagoRealizado = false;

            while (fread(&pago, sizeof(RegistroPago), 1, archivoPagos) == 1)
            {
                if (strcmp(cliente.nombres, pago.persona) == 0)
                {
                    gotoxy(0, 3 + registroEncontrado);
                    cout << "Cliente: " << cliente.nombres << " " << cliente.apellidos;
                    cout << " | DUI: " << cliente.dui;
                    cout << " | Monto: $" << pago.pago;
                    cout << " | " << GREEN << "Pagado" << RESET << endl;

                    pagoRealizado = true;

                    registroEncontrado = true;

                    break;
                }
            }

            if (!pagoRealizado)
            {
                gotoxy(0, 3 + registroEncontrado);
                cout << "Cliente: " << cliente.nombres << " " << cliente.apellidos;
                cout << " | DUI: " << cliente.dui;
                cout << " | " << RED << "Sin Pago" << RESET << endl;
                registroEncontrado = true;
            }
        }

        if (!registroEncontrado)
        {
            cout << RED << "\nNo se han encontrado registros de clientes o pagos." << RESET << endl;
        }

        fclose(archivoClientes);
        fclose(archivoPagos);
    }

    else
    {
        cout << RED << "\nError al abrir los archivos de clientes o pagos" << RESET << endl;
    }

    system("pause");
}

/////////////////////////////////////////////////
/////////////////////Fin////////////////////////

bool validarUsuario()
{
    return (strlen(usuario.usuario) < 4 || strlen(usuario.usuario) > MAX_LENGTH);
}

bool validarCliente(char cliente[])
{
    for (int i = 0; i < strlen(cliente); i++)
    {
        if (!((cliente[i] >= 'A' && cliente[i] <= 'Z') ||
              (cliente[i] >= 'a' && cliente[i] <= 'z') || cliente[i] == ' '))
        {
            return false;
        }
    }
    return true;
}

bool validarDui(char dui[])
{
    if (strlen(dui) > 10 || dui[8] != '-')
    {
        return false;
    }

    for (int i = 0; i < strlen(dui); i++)
    {
        if (dui[i] >= '0' && dui[i] <= '9')
        {
            return true;
        }
    }
    return false;
}

bool comprobarPassword() // Te agregue lo del caracter especial
{
    bool largo = false;
    bool mayus = false;
    bool numero = false;
    bool especial = false;

    const char caracteres[] = "!@#$%^&*()-_=+[]{}|;:'\",.<>?/";

    if (strlen(usuario.password) >= 8) // te cambie que la contrasena sea desde 8 en adelante
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

        for (int j = 0; j < strlen(caracteres); j++)
        {
            if (usuario.password[i] == caracteres[j])
            {
                especial = true;
                break;
            }
        }

        if (largo && mayus && numero && especial)
        {
            return true;
        }
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

void gotoxy(int x, int y)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}