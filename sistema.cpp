#include <iostream>
#include <limits>
#include <cstring>
#include <fstream>
#include <vector>
#include <conio.h>

using namespace std;
const int MAX_LENGTH = 20;
const int ENTER = 13;
const int BACKSPACE = 8;
const string RUTA_USUARIOS = "usuarios.bin";

// Códigos de color
const string RED = "\033[1;31m";   // Rojo
const string GREEN = "\033[1;32m"; // Verde
const string RESET = "\033[0m";    // Restablecer color

struct Usuarios
{
    char usuario[20];
    char password[20];
} usuario;

int loginOpcion = 0;

void login();
void iniciarSesion();
void crearCuenta();
bool verificarUsuario(bool);
void password();
int leer();

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
    cout << "Usuario: ";
    cin.getline(usuario.usuario, 20);
    cout << "Password: ";
    password();

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
            cout << GREEN << "\nCuanta creada correctamente" << RESET << endl;
        }
        else
        {
            cout << RED << "\nError al crear el usuario" << RESET << endl;
        }
    }

    system("Pause");
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
