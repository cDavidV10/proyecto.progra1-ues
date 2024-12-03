#include <iostream>
#include <limits>
#include <cstring>
#include <cmath>
#include <fstream>
#include <vector>
#include <cctype>
#include <conio.h>
#include <windows.h>

using namespace std;
const int MAX_LENGTH = 30;
const int MAX_ADDRESS = 200;
const int ENTER = 13;
const int BACKSPACE = 8;
const string RUTA_USUARIOS = "usuarios.bin";
const string RUTA_REGISTRO = "registro.bin";
const string RUTA_CLIENTE = "clientes.bin";

const string RED = "\033[1;31m";
const string GREEN = "\033[1;32m";
const string RESET = "\033[0m";
const int MAX_CLIENT = 50;
const double PRECIO_KWH = 0.16;
const double MULTA_RETRASO = 0.03;
const int MES_ACTUAL = 10;
const int ANIO_ACTUAL = 2024;
const string meses[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                          "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

struct Direccion
{
    char zona[MAX_LENGTH];
    char via[MAX_LENGTH];
    int numCasa;
    char municipio[MAX_LENGTH];
    char completa[MAX_ADDRESS];
};

struct Clientes
{
    char nombres[MAX_LENGTH];
    char apellidos[MAX_LENGTH];
    Direccion direccion;
    char dui[100];
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
    int mes;
    int anio;

} registroPago;

int loginOpcion = 0;
int menuOpcion = 0;
int manteOpcion = 0;
int opcion = 0;
int menu = 0;
int posicion = 0;
int mes = 0;

vector<Clientes> clientesAux;
vector<int> posiciones;

// Funciones de menus
void login();
void iniciarSesion();
void crearCuenta();
void menuPrincipal();
void editar();
void busqueda();

// Funciones relacionadas al cliente
void ingresarClientes();
void verClientes();
void agregarPago();
void verPago();
void pago();
void obtenerMes();
void correlativo();
void seccionCliente();
void seleccion();

// Funciones encargadas de editar
void busquedaDui();
void busquedaNombre();
void edicion();
void funcionEditar();

// Funciones encargadas de eliminar
void eliminarCliente();

// Funciones de validacion
void validarMayusculas();
bool validarCliente(char[]);
void formatoNombre();
void formatoApellido();
void ingresoNombre();
void ingresoApellido();
bool duiExiste(char[]);
bool validarDui(char[]);
bool validarUsuario();

// Funciones pde valicacion para el login
bool verificarUsuario(bool);
bool comprobarPassword();
void password();
//
void getSizeClientes();
int leer();
void user();
void gotoxy(int, int);

void ingresarDireccion();
void formatoZona();
void formatoVia();
void formatoMunicipio();
void formatoDepto();
void validarMayusDireccion(char[]);
void concatenarDireccion(int, int);

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
    cout << "2. Registrarse" << endl;
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
        cout << "Contrase" << (char)164 << "a: ";
        password();

        if (verificarUsuario(true))
        {
            ingresa = true;
        }
        else
        {
            cout << RED << "\nEl usuario y/o el password son incorrectos" << RESET << endl;
            cin.get();
            intentos--;
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
        cout << "Contrase" << (char)164 << "a: ";
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

    cin.get();
}

void menuPrincipal()
{
    do
    {
        system("cls");
        user();
        cout << "------     MENU PRINCIPAL     ------" << endl;
        cout << "1. Agregar Cliente" << endl;
        cout << "2. Busqueda" << endl;
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
            busqueda();
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

void busqueda()
{
    system("cls");
    user();
    cout << "-----    BUSQUEDA DE CLIENTES POR    -----" << endl;
    cout << "1. DUI" << endl;
    cout << "2. Nombres" << endl;
    cout << "3. Salir" << endl;
    cout << "Ingrse una opcion del menu: ";
    menu = leer();

    switch (menu)
    {
    case 1:
        busquedaDui();
        break;
    case 2:
        busquedaNombre();
        break;

    default:
        break;
    }
}

void editar()
{
    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "wb");

    if (archivo != NULL)
    {
        edicion();

        fseek(archivo, 0, SEEK_SET);
        for (auto i = clientesAux.begin(); i != clientesAux.end(); i++)
        {
            fwrite(&(*i), sizeof(Clientes), 1, archivo);
        }
    }

    cout << GREEN << "Datos actualizados correctamente" << RESET;

    clientesAux.clear();
    posiciones.clear();
    fclose(archivo);
}

void ingresarClientes()
{
    bool isEncontrado = false;
    int key;

    system("cls");
    cout << "Presione cualquier tecla para continuar" << endl;
    cout << "Presione esc para salir" << endl;

    key = _getch();

    if (key == 27)
    {
        return;
    }
    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "a+b");

    if (archivo != NULL)
    {
        cin.ignore();
        system("cls");
        user();

        do
        {
            cout << "Ingrese el DUI del cliente: ";
            cin.getline(cliente.dui, 100);

            if (duiExiste(cliente.dui))
            {
                cout << RED << "El dui ya esta registrado" << RESET << endl;
            }
            else if (!validarDui(cliente.dui))
            {
                cout << RED << "DUI invalido" << RESET << endl;
            }

        } while (!validarDui(cliente.dui) || duiExiste(cliente.dui));

        fflush(stdin);

        ingresoNombre();

        fflush(stdin);

        ingresoApellido();

        fflush(stdin);

        do
        {
            ingresarDireccion();

            char aux[MAX_ADDRESS];

            strcpy(aux, cliente.direccion.completa);

            getSizeClientes();

            for (auto i = clientesAux.begin(); i != clientesAux.end(); i++)
            {
                isEncontrado = false;
                if (strcmp(i->direccion.completa, aux) == 0)
                {
                    cout << RED << "[ADVERTENCIA]: No puede ingresar dos veces la misma direccion. Intente de nuevo." << RESET << endl;
                    isEncontrado = true;
                    cin.get();
                    break;
                }
            }
            clientesAux.clear();
        } while (isEncontrado);

        fflush(stdin);

        validarMayusculas();

        fflush(stdin);

        cliente.pago = false;

        fwrite(&cliente, sizeof(Clientes), 1, archivo);

        cout << GREEN << "Cliente agregado correctamente" << RESET << endl;
        cin.get();

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

    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "rb");

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
        gotoxy(70, 2);
        cout << "Distrito";

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
                gotoxy(70, 3 + i);
                cout << cliente.direccion.municipio;
            }

            i++;
        }
    }

    else
    {
        cout << RED << "[ERROR]: Creacion de archivo invalida." << RESET;
    }

    fclose(archivo);

    cout << "\n\n";
    system("pause");
}

void agregarPago()
{
    double pago;
    int decimales = 2;
    int key;
    double consumoKw;
    RegistroPago pagoExistente;
    bool pagoRegistrado = false;
    int mesesDeRetraso;

    system("cls");
    cout << "Presione cualquier tecla para continuar" << endl;
    cout << "Presione esc para salir" << endl;

    key = _getch();

    if (key == 27)
    {
        return;
    }

    if (clientesAux.empty())
    {
        cout << RED << "No hay clientes registrados" << RESET << endl;
        cin.get();
        return;
    }

    FILE *archivoPagos = fopen(RUTA_REGISTRO.c_str(), "a+b");
    FILE *archivoCliente = fopen(RUTA_CLIENTE.c_str(), "wb");

    system("cls");
    user();

    cout << "------     PAGO    ------" << endl;

    if (archivoPagos != NULL)
    {

        cout << "Cliente encontrado: " << clientesAux[posicion].nombres << " " << clientesAux[posicion].apellidos << endl;

        cout << "Ingrese el consumo en kWh: ";
        cin >> consumoKw;

        if (consumoKw > 0)
        {

            cout << "Seleccione el mes para el pago:" << endl;
            obtenerMes();

            mes = mes - 1;

            while (!feof(archivoPagos))
            {
                fread(&pagoExistente, sizeof(RegistroPago), 1, archivoPagos);
                if (strcmp(pagoExistente.persona, clientesAux[posicion].nombres) == 0 &&
                    pagoExistente.mes == mes && pagoExistente.anio == ANIO_ACTUAL)
                {
                    pagoRegistrado = true;
                    break;
                }
            }

            if (pagoRegistrado)
            {
                cout << "\nEste cliente ya ha pagado en el mes " << meses[mes] << " del a" << (char)164 << "o " << ANIO_ACTUAL << "." << endl;
                fseek(archivoCliente, 0, SEEK_SET);
                for (auto i = clientesAux.begin(); i != clientesAux.end(); i++)
                {
                    fwrite(&(*i), sizeof(Clientes), 1, archivoCliente);
                }
                cin.ignore();
                cin.get();
                clientesAux.clear();
                posiciones.clear();
                fclose(archivoPagos);
                fclose(archivoCliente);
                return;
            }

            mesesDeRetraso = (ANIO_ACTUAL - ANIO_ACTUAL) * 12 + (MES_ACTUAL - mes);

            if (mesesDeRetraso > 2)
            {
                pago = consumoKw * PRECIO_KWH * (1 + MULTA_RETRASO) * (1 + 0.30) * (1 + 0.13);
                cout << "\nSe ha aplicado una multa del 3% por retraso. El monto total a pagar es: " << pago << endl;
            }
            else
            {
                pago = (consumoKw * PRECIO_KWH) + (consumoKw * 0.3) + (consumoKw * 0.13);
            }

            pago = round(pago * pow(10, decimales)) / pow(10, decimales);

            RegistroPago registroPago;
            strcpy(registroPago.persona, clientesAux[posicion].nombres);
            registroPago.pago = pago;
            registroPago.mes = mes;
            registroPago.anio = ANIO_ACTUAL;

            fseek(archivoPagos, 0, SEEK_END); // para ver si esta al final del archivo
            fwrite(&registroPago, sizeof(RegistroPago), 1, archivoPagos);

            clientesAux[posicion].pago = true;

            cout << "\nPago de $" << pago << " agregado correctamente para el mes " << meses[mes] << " del a" << (char)164 << "o: " << ANIO_ACTUAL << endl;
            cin.get();
        }

        else
        {
            cout << "\nEl consumo debe ser mayor a 0 kWh" << endl;
            cin.get();
        }

        fseek(archivoCliente, 0, SEEK_SET);
        for (auto i = clientesAux.begin(); i != clientesAux.end(); i++)
        {
            fwrite(&(*i), sizeof(Clientes), 1, archivoCliente);
        }
    }

    clientesAux.clear();
    posiciones.clear();
    fclose(archivoPagos);
    fclose(archivoCliente);
}

void verPago()
{
    bool registroEncontrado = false;
    int sitio, key;
    bool pagoRealizado;
    bool pagoCliente;

    cin.ignore();

    system("cls");

    cout << "Presione cualquier tecla para continuar" << endl;
    cout << "Presione esc para salir" << endl;

    key = _getch();

    if (key == 27)
    {
        return;
    }
    cout << "------     VER PAGO     ------" << endl;

    system("cls");
    user();

    FILE *archivoPagos = fopen(RUTA_REGISTRO.c_str(), "rb");

    getSizeClientes();

    if (clientesAux.empty())
    {
        cout << "\nNo hay usuarios registrados" << endl;
        cin.get();
        return;
    }

    vector<RegistroPago> pagos;
    if (archivoPagos != NULL)
    {
        RegistroPago pago;
        sitio = 3;

        while (!feof(archivoPagos))
        {
            fread(&pago, sizeof(RegistroPago), 1, archivoPagos);

            if (!feof(archivoPagos))
            {

                pagos.push_back(pago);
            }
        }

        if (pagos.empty())
        {
            cout << RED << "No hay registros de pagos" << RESET << endl;
            cin.get();
            clientesAux.clear();
            pagos.clear();
            fclose(archivoPagos);
            return;
        }

        cout << "Seleccione el mes para ver el pago:" << endl;

        obtenerMes();

        mes = mes - 1;

        system("cls");
        user();

        cout << "------     LISTA DE CLIENTE     ------" << endl;

        for (size_t i = 0; i < clientesAux.size(); i++)
        {
            for (size_t j = 0; j < pagos.size(); j++)
            {
                if (strcmp(clientesAux[i].nombres, pagos[j].persona) == 0 && pagos[j].mes == mes)
                {
                    gotoxy(0, sitio);
                    cout << "Cliente: " << clientesAux[i].nombres << " " << clientesAux[i].apellidos;
                    cout << " | DUI: " << clientesAux[i].dui;
                    cout << " | Mes: " << meses[mes] << " | A" << (char)164 << "o " << pagos[j].anio;
                    cout << " | Monto: $" << pagos[j].pago;
                    if (clientesAux[i].pago)
                    {

                        cout << " | Estado: " << GREEN << "Pagado" << RESET << endl;
                    }
                    else
                    {
                        cout << " | Estado: " << RED << "Sin pagar" << RESET << endl;
                    }
                    sitio++;

                    break;
                }
            }
        }
    }
    else
    {
        cout << RED << "\nError al abrir los archivos de pagos" << RESET << endl;
    }
    pagos.clear();
    clientesAux.clear();
    fclose(archivoPagos);
    cin.ignore();
    cin.get();
}

void obtenerMes()
{
    for (int i = 0; i <= 11; i++)
    {
        cout << i + 1 << ". " << meses[i] << endl;
    }

    do
    {
        cout << "Mes (1-12): ";
        mes = leer();
    } while (mes < 0 || mes > 12);
}

void busquedaDui()
{
    posicion = 0;
    char dui[100];
    bool existe = false;
    cin.ignore();

    system("cls");
    user();

    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "rb");
    getSizeClientes();

    do
    {
        cout << "Ingrese el DUI del cliente: ";
        cin.getline(dui, 100);

    } while (!validarDui(dui));

    if (archivo != NULL)
    {
        for (auto i = clientesAux.begin(); i != clientesAux.end(); i++)
        {
            if (strcmp(i->dui, dui) == 0)
            {
                existe = true;
                break;
            }
            posicion++;
        }
    }

    fclose(archivo);

    if (existe)
    {
        cout << clientesAux[posicion].dui << " " << clientesAux[posicion].nombres << " " << clientesAux[posicion].apellidos;
        seleccion();
    }
    else
    {
        cout << RED << "No hay clientes registrados con ese dui" << RESET << endl;
        cin.get();
        clientesAux.clear();
        return;
    }
}

void busquedaNombre()
{
    posicion = 0;
    int lista = 1;
    system("cls");

    cin.ignore();

    user();

    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "rb");
    getSizeClientes();

    ingresoNombre();

    if (archivo != NULL)
    {
        for (auto i = clientesAux.begin(); i != clientesAux.end(); i++)
        {
            if (strcmp(i->nombres, cliente.nombres) == 0)
            {
                cout << lista << ". " << i->dui << " " << i->nombres << " " << i->apellidos << endl;
                lista++;
                posiciones.push_back(posicion);
            }
            posicion++;
        }
    }
    fclose(archivo);

    funcionEditar();
}

void edicion()
{
    int edicion = 0;
    cout << "Que desea Editar" << endl;
    cout << "1. Nombre" << endl;
    cout << "2. Apellidos" << endl;
    cout << "3. DUI" << endl;
    cout << "Seleccione una opcion: ";
    edicion = leer();
    cin.ignore();
    switch (edicion)
    {
    case 1:
        ingresoNombre();
        validarMayusculas();
        strcpy(clientesAux[posicion].nombres, cliente.nombres);
        break;
    case 2:
        ingresoApellido();
        validarMayusculas();
        strcpy(clientesAux[posicion].apellidos, cliente.apellidos);
        break;
    case 3:
        do
        {
            cout << "Ingrese el DUI del cliente: ";
            cin.getline(cliente.dui, 100);

            if (duiExiste(cliente.dui))
            {
                cout << RED << "El dui ya esta registrado" << RESET << endl;
            }
            else if (!validarDui(cliente.dui))
            {
                cout << RED << "DUI invalido" << RESET << endl;
            }

        } while (!validarDui(cliente.dui) || duiExiste(cliente.dui));
        strcpy(clientesAux[posicion].dui, cliente.dui);
        break;

    default:
        break;
    }
}

void funcionEditar()
{
    if (posiciones.empty())
    {
        cout << RED << "No hay clientes registrados con ese nombre" << RESET << endl;
        cin.get();
        clientesAux.clear();
        return;
    }
    else
    {

        cout << "Seleccione el cliente: ";
        posicion = leer();

        posicion = posiciones[posicion - 1];

        seleccion();
    }
}

void seleccion()
{
    cin.ignore();
    int key;
    cout << "Que desea realizar con el cliente" << endl;
    cout << "Esc para salir" << endl;
    cout << "F1 para agregar pago" << endl;
    cout << "F2 para editar" << endl;
    cout << "F3 para eliminar" << endl;
    key = _getch();

    if (key == 27)
    {
        clientesAux.clear();
        posiciones.clear();
        return;
    }

    if (key == 0 || key == 224)
    {
        key = _getch();

        if (key == 59)
        {
            agregarPago();
            return;
        }

        if (key == 60)
        {
            editar();
            cin.get();

            return;
        }

        if (key == 61)
        {
            eliminarCliente();
            return;
        }
    }
}

void eliminarCliente()
{
    int eliminar = 0, intentos = 3;
    bool elimina = false;

    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "wb");

    if (archivo != NULL)
    {
        cout << "Esta seguro de eliminar el cliente? (si->1, no->0): ";
        eliminar = leer();

        if (eliminar == 0)
        {
            fclose(archivo);
            clientesAux.clear();
            posiciones.clear();
            return;
        }

        do
        {
            cout << "Escriba su contrase" << (char)164 << "a: ";
            password();

            if (verificarUsuario(true))
            {
                elimina = true;
            }
            else
            {
                cout << RED << "\nEl usuario y/o el password son incorrectos" << RESET << endl;
                cin.ignore();
                cin.get();
                intentos--;
            }
        } while (!elimina && intentos > 0);

        if (elimina)
        {
            clientesAux.erase(clientesAux.begin() + posicion);

            fseek(archivo, 0, SEEK_SET);

            for (auto &cliente : clientesAux)
            {
                fwrite(&cliente, sizeof(Clientes), 1, archivo);
            }

            cout << endl
                 << GREEN << "Datos eliminado correctamente" << RESET;
        }
        else
        {
            cout << endl
                 << RED << "No se puedo eliminar al cliente" << RESET << endl;
        }
    }
    cin.ignore();
    cin.get();
    fclose(archivo);

    clientesAux.clear();
    posiciones.clear();
}

bool validarUsuario()
{
    return (strlen(usuario.usuario) < 4 || strlen(usuario.usuario) > MAX_LENGTH);
}

bool validarCliente(char cliente[])
{
    if (strlen(cliente) <= 0)
    {
        return false;
    }
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

void formatoNombre()
{
    char cadena[MAX_LENGTH];
    char *auxiliar;

    strcpy(cadena, cliente.nombres);
    strcpy(cliente.nombres, "");

    auxiliar = strtok(cadena, " ");

    while (auxiliar != NULL)
    {
        strcat(cliente.nombres, auxiliar);
        auxiliar = strtok(NULL, " ");
        if (auxiliar != NULL)
        {
            strcat(cliente.nombres, " ");
        }
    }
}

void formatoApellido()
{
    char cadena[MAX_LENGTH];
    char *auxiliar;

    strcpy(cadena, cliente.apellidos);
    strcpy(cliente.apellidos, "");
    auxiliar = strtok(cadena, " ");

    while (auxiliar != NULL)
    {
        strcat(cliente.apellidos, auxiliar);
        strcat(cliente.apellidos, " ");
        auxiliar = strtok(NULL, " ");
    }
}

void formatoZona()
{
    char cadena[MAX_LENGTH];
    char *auxiliar;

    strcpy(cadena, cliente.direccion.zona);
    strcpy(cliente.direccion.zona, "");

    auxiliar = strtok(cadena, " ");

    while (auxiliar != NULL)
    {
        strcat(cliente.direccion.zona, auxiliar);
        auxiliar = strtok(NULL, " ");

        if (auxiliar != NULL)
        {
            strcat(cliente.direccion.zona, " ");
        }
    }
}

void formatoVia()
{
    char cadena[MAX_LENGTH];
    char *auxiliar;

    strcpy(cadena, cliente.direccion.via);
    strcpy(cliente.direccion.via, "");

    auxiliar = strtok(cadena, " ");

    while (auxiliar != NULL)
    {
        strcat(cliente.direccion.via, auxiliar);
        auxiliar = strtok(NULL, " ");

        if (auxiliar != NULL)
        {
            strcat(cliente.direccion.via, " ");
        }
    }
}

void ingresoNombre()
{
    do
    {
        cout << "Ingrese los nombres del cliente: ";
        cin.getline(cliente.nombres, MAX_LENGTH);
        formatoNombre();

    } while (!validarCliente(cliente.nombres));
}

void ingresoApellido()
{
    do
    {
        cout << "Ingrese los apellidos del cliente: ";
        cin.getline(cliente.apellidos, MAX_LENGTH);
        formatoApellido();

    } while (!validarCliente(cliente.apellidos));
}

void ingresarDireccion()
{
    int op;
    int cont = 1;
    bool isReal = false;
    bool isEspacio = true;
    bool isEncontrado = false;
    bool isValido = false;
    char aux[MAX_LENGTH];
    char sanviNorte[7][MAX_LENGTH] = {"APASTEPEQUE", "SANTA CLARA", "SAN IDELFONSO", "SAN ESTEBAN CATARINA", "SAN SEBASTIAN", "SAN LORENZO", "SANTO DOMINGO"};
    char sanviSur[6][MAX_LENGTH] = {"SAN VICENTE", "GUADALUPE", "VERAPAZ", "TEPETITAN", "TECOLUCA", "SAN CAYETANO ISTEPEQUE"};

    do
    {
        system("cls");
        user();
        gotoxy(30, 0);
        cout << "Ingrese la direccion del cliente." << endl;
        gotoxy(10, 2);
        cout << "Estas en la seccion: [" << GREEN << "Zona" << RESET << ", Via, No.Casa, Municipio]\n";
        gotoxy(0, 4);
        cout << "Seleccione el formato de su direccion: " << endl;
        gotoxy(0, 6);
        cout << "1. Colonia." << endl;
        cout << "2. Barrio." << endl;
        cout << "3. Urbanizacion." << endl;
        cout << "4. Sector." << endl;
        gotoxy(0, 11);
        cout << "Opcion: ";
        op = leer();
    } while (op <= 0 || op >= 5);

    fflush(stdin);

    do
    {
        switch (op)
        {
        case 1:
            cout << "Ingrese el nombre de la colonia: ";
            cin.getline(cliente.direccion.zona, MAX_ADDRESS);
            break;

        case 2:
            cout << "Ingrese el nombre del barrio: ";
            cin.getline(cliente.direccion.zona, MAX_ADDRESS);
            break;

        case 3:
            cout << "Ingrese el nombre de la urbanizacion: ";
            cin.getline(cliente.direccion.zona, MAX_ADDRESS);
            break;

        case 4:
            cout << "Ingrese el nombre del sector: ";
            cin.getline(cliente.direccion.zona, MAX_ADDRESS);
            break;
        }

        formatoZona();

    } while (!validarCliente(cliente.direccion.zona));

    validarMayusDireccion(cliente.direccion.zona);

    concatenarDireccion(op, cont);

    fflush(stdin);

    do
    {
        system("cls");
        user();
        gotoxy(10, 0);
        cout << "Estas en la seccion: [Zona, " << GREEN << "Via" << RESET << ", No.Casa, Municipio]\n";
        gotoxy(0, 2);
        cout << "Seleccione el formato de su direccion: " << endl;
        cout << "\n1. Calle." << endl;
        cout << "2. Boulevard." << endl;
        cout << "3. Paseo." << endl;
        cout << "4. Autopista." << endl;
        cout << "5. Carretera." << endl;
        cout << "6. Calle Principal." << endl;
        cout << "7. Via." << endl;
        gotoxy(0, 12);
        cout << "Opcion: ";
        op = leer();
    } while (op <= 0 || op >= 8);

    fflush(stdin);

    do
    {
        switch (op)
        {
        case 1:
            cout << "Ingrese el nombre de la calle: ";
            cin.getline(cliente.direccion.via, MAX_ADDRESS);
            break;

        case 2:
            cout << "Ingrese el nombre del boulevard: ";
            cin.getline(cliente.direccion.via, MAX_ADDRESS);
            break;

        case 3:
            cout << "Ingrese el nombre de la paseo: ";
            cin.getline(cliente.direccion.via, MAX_ADDRESS);
            break;

        case 4:
            cout << "Ingrese el nombre de la autopista: ";
            cin.getline(cliente.direccion.via, MAX_ADDRESS);
            break;

        case 5:
            cout << "Ingrese el nombre de la carretera: ";
            cin.getline(cliente.direccion.via, MAX_ADDRESS);
            break;

        case 6:
            cout << "Ingrese el nombre de la calle principal: ";
            cin.getline(cliente.direccion.via, MAX_ADDRESS);
            break;

        case 7:
            cout << "Ingrese el nombre de la via: ";
            cin.getline(cliente.direccion.via, MAX_ADDRESS);
            break;
        }

        if (strlen(cliente.direccion.via) <= 0)
        {
            isValido = false;
        }

        for (int i = 0; i < strlen(cliente.direccion.via); i++)
        {
            if (!((cliente.direccion.via[i] >= 'A' && cliente.direccion.via[i] <= 'Z') ||
                  (cliente.direccion.via[i] >= 'a' && cliente.direccion.via[i] <= 'z') ||
                  (cliente.direccion.via[i] >= '1' && cliente.direccion.via[i] <= '9') ||
                  (cliente.direccion.via[i] == '#') ||
                  cliente.direccion.via[i] == ' '))
            {
                isValido = false;
                break;
            }

            isValido = true;
        }

    } while (!isValido);

    cont++; // 2

    validarMayusDireccion(cliente.direccion.via);

    concatenarDireccion(op, cont);

    system("cls");

    fflush(stdin);
    user();

    gotoxy(10, 0);
    cout << "Estas en la seccion: [Zona, Via, " << GREEN << "No.Casa" << RESET << ", Municipio]\n";

    cout << "\nIngrese el numero de casa: #";
    cliente.direccion.numCasa = leer();

    cont++; // 3

    concatenarDireccion(op, cont);

    fflush(stdin);

    do // Este do-while es lo que muestra y permite ingresar el municipio
    {
        system("cls");
        user();

        gotoxy(10, 0);
        cout << "Estas en la seccion: [Zona, Via, No.Casa, " << GREEN << "Municipio" << RESET << "]\n";

        gotoxy(8, 2);
        cout << "San Vicente Norte";

        for (int i = 0; i < 7; i++)
        {
            gotoxy(9, 3 + i);
            validarMayusDireccion(sanviNorte[i]);
            cout << i + 1 << ". " << sanviNorte[i];
        }

        gotoxy(50, 2);
        cout << "San Vicente Sur";

        for (int i = 0; i < 6; i++)
        {
            gotoxy(51, 3 + i);
            validarMayusDireccion(sanviSur[i]);
            cout << 8 + i << ". " << sanviSur[i];
        }
        fflush(stdin);

        gotoxy(0, 11);
        cout << "Seleccione su municipio: ";
        op = leer();

    } while (!(op >= 1 && op <= 13));

    if (op < 8)
    {
        strcpy(cliente.direccion.municipio, sanviNorte[op - 1]);
    }
    else
    {
        strcpy(cliente.direccion.municipio, sanviSur[op - 8]);
    }

    cont++; // 4

    concatenarDireccion(op, cont);

    cont++; // 5

    concatenarDireccion(op, cont);

    fflush(stdin);
}

void concatenarDireccion(int num, int cont)
{
    char zona[4][MAX_LENGTH] = {{"Col. "}, {"Barr. "}, {"Urb. "}, {"Sect. "}};
    char via[7][MAX_LENGTH] = {{"C. "}, {"Blvd. "}, {"Pso. "}, {"Autop. "}, {"Carr. "}, {"C. Ppal."}, {"Via "}};

    if (cont == 1)
    {
        switch (num)
        {
        case 1:
            strcat(cliente.direccion.completa, zona[0]);
            strcat(cliente.direccion.completa, cliente.direccion.zona);
            break;

        case 2:
            strcat(cliente.direccion.completa, zona[1]);
            strcat(cliente.direccion.completa, cliente.direccion.zona);
            break;

        case 3:
            strcat(cliente.direccion.completa, zona[2]);
            strcat(cliente.direccion.completa, cliente.direccion.zona);
            break;

        case 4:
            strcat(cliente.direccion.completa, zona[3]);
            strcat(cliente.direccion.completa, cliente.direccion.zona);
            break;
        }

        return;
    }

    if (cont == 2)
    {
        switch (num)
        {
        case 1:
            strcat(cliente.direccion.completa, ", ");
            strcat(cliente.direccion.completa, via[0]);
            strcat(cliente.direccion.completa, cliente.direccion.via);
            break;

        case 2:
            strcat(cliente.direccion.completa, ", ");
            strcat(cliente.direccion.completa, via[1]);
            strcat(cliente.direccion.completa, cliente.direccion.via);
            break;

        case 3:
            strcat(cliente.direccion.completa, ", ");
            strcat(cliente.direccion.completa, via[2]);
            strcat(cliente.direccion.completa, cliente.direccion.via);
            break;

        case 4:
            strcat(cliente.direccion.completa, ", ");
            strcat(cliente.direccion.completa, via[3]);
            strcat(cliente.direccion.completa, cliente.direccion.via);
            break;

        case 5:
            strcat(cliente.direccion.completa, ", ");
            strcat(cliente.direccion.completa, via[4]);
            strcat(cliente.direccion.completa, cliente.direccion.via);
            break;

        case 6:
            strcat(cliente.direccion.completa, ", ");
            strcat(cliente.direccion.completa, via[5]);
            strcat(cliente.direccion.completa, cliente.direccion.via);
            break;

        case 7:
            strcat(cliente.direccion.completa, ", ");
            strcat(cliente.direccion.completa, via[6]);
            strcat(cliente.direccion.completa, cliente.direccion.via);
            break;
        }

        return;
    }

    if (cont == 3)
    {
        strcat(cliente.direccion.completa, ", Casa #");
        string num = to_string(cliente.direccion.numCasa);
        strcat(cliente.direccion.completa, num.c_str());

        return;
    }

    if (cont == 4)
    {
        strcat(cliente.direccion.completa, ", ");
        strcat(cliente.direccion.completa, cliente.direccion.municipio);

        return;
    }

    if (cont == 5)
    {
        if (num == 1)
        {
            strcat(cliente.direccion.completa, ", ");
            strcat(cliente.direccion.completa, "San Vicente Norte");
        }

        if (num == 2)
        {
            strcat(cliente.direccion.completa, ", ");
            strcat(cliente.direccion.completa, "San Vicente Sur");
        }

        return;
    }
}

void validarMayusDireccion(char direccion[])
{
    bool isEspacio = false;

    if (islower(direccion[0]))
    {
        direccion[0] = toupper(direccion[0]);
    }

    for (int i = 1; i < strlen(direccion); i++)
    {
        isEspacio = true;

        if (direccion[i - 1] == ' ' && islower(direccion[i]))
        {
            direccion[i] = toupper(direccion[i]);
            isEspacio = false;
        }
        else if (direccion[i - 1] == ' ' && isupper(direccion[i]))
        {
            isEspacio = false;
        }

        if (i > 0 && isupper(direccion[i]) && isEspacio)
        {
            direccion[i] = tolower(direccion[i]);
        }
    }
}

void validarMayusculas()
{
    bool isEspacio = true;

    if (islower(cliente.nombres[0]))
    {
        cliente.nombres[0] = toupper(cliente.nombres[0]);
    }

    for (int i = 1; i < strlen(cliente.nombres); i++)
    {
        isEspacio = true;

        if (cliente.nombres[i - 1] == ' ' && islower(cliente.nombres[i]))
        {
            cliente.nombres[i] = toupper(cliente.nombres[i]);
            isEspacio = false;
        }
        else if (cliente.nombres[i - 1] == ' ' && isupper(cliente.nombres[i]))
        {
            isEspacio = false;
        }

        if (i > 0 && isupper(cliente.nombres[i]) && isEspacio)
        {
            cliente.nombres[i] = tolower(cliente.nombres[i]);
        }
    }

    if (isupper(cliente.apellidos[0]) == false)
    {
        cliente.apellidos[0] = toupper(cliente.apellidos[0]);
    }

    for (int i = 1; i < strlen(cliente.apellidos); i++)
    {
        isEspacio = true;

        if (cliente.apellidos[i - 1] == ' ' && islower(cliente.apellidos[i]))
        {
            cliente.apellidos[i] = toupper(cliente.apellidos[i]);
            isEspacio = false;
        }
        else if (cliente.apellidos[i - 1] == ' ' && isupper(cliente.apellidos[i]))
        {
            isEspacio = false;
        }

        if (i > 0 && isupper(cliente.apellidos[i]) && isEspacio)
        {
            cliente.apellidos[i] = tolower(cliente.apellidos[i]);
        }
    }
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

bool duiExiste(char dui[])
{
    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "rb");

    if (archivo != NULL)
    {
        Clientes clienteAux;

        while (!feof(archivo))
        {
            fread(&clienteAux, sizeof(Clientes), 1, archivo);
            if (!feof(archivo))
            {
                if (strcmp(clienteAux.dui, dui) == 0)
                {
                    fclose(archivo);
                    return true;
                }
            }
        }
    }

    fclose(archivo);
    return false;
}

bool comprobarPassword()
{
    bool largo = false;
    bool mayus = false;
    bool numero = false;
    bool especial = false;

    const char caracteres[] = "!@#$%^&*()-_=+[]{}|;:'\",.<>?/";

    if (strlen(usuario.password) >= 8)
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

void getSizeClientes()
{
    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "rb");
    Clientes temp;
    if (archivo != NULL)
    {
        while (!feof(archivo))
        {
            fread(&temp, sizeof(Clientes), 1, archivo);
            if (!feof(archivo))
            {
                clientesAux.push_back(temp);
            }
        }
    }
    fclose(archivo);
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

void user()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int x = width - strlen(usuario.usuario);
    int y = 0;

    gotoxy(x, y);
    cout << usuario.usuario;

    gotoxy(0, 1);
}

void gotoxy(int x, int y)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}