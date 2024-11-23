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
const int MAX_LENGTH = 30; // Cambie el tamano de 20 a 30
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

struct Direccion
{
    char zona[MAX_LENGTH];
    char via[MAX_LENGTH];
    int numCasa;
    char municipio[MAX_LENGTH];
    char depto[MAX_LENGTH];
    char completa[MAX_ADDRESS];
};

struct Clientes
{
    char nombres[MAX_CLIENT];
    char apellidos[MAX_CLIENT];
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

vector<Clientes> clientesAux;

// Funciones de menus
void login();
void iniciarSesion();
void crearCuenta();
void menuPrincipal();
void mantenimiento();
void menuMantenimiento();
void editar();
// Funciones relacionadas al cliente
void ingresarClientes();
void verClientes();
void agregarPago();
void verPago();
void correlativo();
void seccionCliente();
// Funciones encargadas de editar
void busquedaDui();
void busquedaNombre();
void busquedaApellido();
void edicion(vector<Clientes> &, int);
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
        cout << "Contrase" << (char)164 << "a: ";
        password();

        if (verificarUsuario(true))
        {
            ingresa = true;
        }
        else
        {
            cout << RED << "\nEl usuario y/o el password son incorrectos" << RESET << endl;
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
    system("pause>null");
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
        cout << "5. Mantenimiento" << endl;
        cout << "6. Salir" << endl;
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
        case 5:
            mantenimiento();
            break;

        default:
            break;
        }

    } while (menuOpcion != 6);
}

void mantenimiento()
{
    do
    {
        system("cls");
        cout << "------     MANTENIMIENTO     ------" << endl;
        cout << "1. Editar Cliente" << endl;
        cout << "2. Eliminar Cliente" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
        manteOpcion = leer();

        switch (manteOpcion)
        {
        case 1:
            editar();
            break;
        case 2:
            eliminarCliente();
            break;

        default:
            break;
        }
    } while (manteOpcion != 3);
}

void menuMantenimiento()
{
    system("cls");
    cout << "-----    BUSQUEDA DE CLIENTES POR    -----" << endl;
    cout << "1. DUI" << endl;
    cout << "2. Nombres" << endl;
    cout << "3. Apellidos" << endl;
    cout << "4. Salir" << endl;
    cout << "Seleccione una opcion: ";
    opcion = leer();
}

void editar()
{
    do
    {
        menuMantenimiento();

        switch (opcion)
        {
        case 1:
            busquedaDui();
            break;
        case 2:
            busquedaNombre();
            break;
        case 3:
            busquedaApellido();
            break;

        default:
            break;
        }
    } while (opcion != 4);
}

void ingresarClientes()
{
    bool isEncontrado = false;
    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "a+b");

    if (archivo != NULL)
    {
        cin.ignore();
        system("cls");

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

            for (auto i = clientesAux.begin(); i != clientesAux.end(); i++)
            {
                isEncontrado = false;
                if (strcmp(i->direccion.completa, aux) == 0)
                {
                    cout << RED << "[ADVERTENCIA]: No puede ingresar dos veces la misma direccion. Intente de nuevo." << RESET << endl;
                    isEncontrado = true;
                    system("pause");
                }
            }

        } while (isEncontrado);

        fflush(stdin);

        validarMayusculas();

        fflush(stdin);

        cliente.pago = false;

        fwrite(&cliente, sizeof(Clientes), 1, archivo);

        cout << GREEN << "Cliente agregado correctamente" << RESET << endl;
        system("pause>null");

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
        cout << RED << "[ERROR]: Creacion de archivo invalida." << RESET; // le agregue color
    }

    fclose(archivo);

    cout << "\n\n";
    system("pause");
}

//////////////////////////////////////////////////////////////
///////////////////////////////////////////////Modificaciones

void agregarPago()
{
    bool clienteEncontrado;
    int numClientes;

    Clientes clientes[MAX_CLIENT];

    cin.ignore();
    system("cls");
    cout << "------     PAGO    ------" << endl;

    char duiCliente[100];
    double pago;
    int decimales = 2;
    int mes;
    int anio;
    double consumoKw;
    int mesActual = 10;
    int anioActual = 2024;
    RegistroPago pagoExistente;
    bool pagoRegistrado = false;

    FILE *archivoClientes = fopen(RUTA_CLIENTE.c_str(), "r+b");
    FILE *archivoPagos = fopen(RUTA_REGISTRO.c_str(), "a+b");

    if (archivoClientes != NULL && archivoPagos != NULL)
    {
        Clientes cliente;
        RegistroPago registroPago;
        clienteEncontrado = false;
        numClientes = 0;

        while (fread(&cliente, sizeof(Clientes), 1, archivoClientes) == 1)
        {
            clientes[numClientes++] = cliente;
        }

        if (numClientes == 0)
        {
            cout << "\nNo hay usuarios registrados" << endl;
            fclose(archivoClientes);
            fclose(archivoPagos);
            system("pause");
            return;
        }

        cout << "Ingrese el DUI del cliente: ";
        cin.getline(duiCliente, 100);

        for (int i = 0; i < numClientes; i++)
        {
            if (strcmp(clientes[i].dui, duiCliente) == 0)
            {
                clienteEncontrado = true;

                cout << "Ingrese el consumo en kWh: ";
                cin >> consumoKw;

                if (consumoKw > 0)
                {
                    cout << "Ingrese el anio (2020-2024): ";
                    cin >> anio;

                    if (anio < 2020 || anio > 2024)
                    {
                        cout << "\nAnio invalido. Ingrese nuevamente" << endl;
                        system("pause");
                        break;
                    }

                    cout << "Seleccione el mes para el pago:" << endl;
                    cout << "1. Enero\n2. Febrero\n3. Marzo\n4. Abril\n5. Mayo\n6. Junio\n";
                    cout << "7. Julio\n8. Agosto\n9. Septiembre\n10. Octubre\n11. Noviembre\n12. Diciembre\n";
                    cout << "Mes (1-12): ";
                    cin >> mes;

                    if (mes < 1 || mes > 12)
                    {
                        cout << "\nMes invalido. Ingrese nuevamente" << endl;
                        system("pause");
                        break;
                    }

                    // FILE *archivoPagosExistentes = fopen(RUTA_REGISTRO.c_str(), "rb");

                    if (archivoPagos != NULL)
                    {
                        while (fread(&pagoExistente, sizeof(RegistroPago), 1, archivoPagos) == 1)
                        {
                            if (strcmp(pagoExistente.persona, clientes[i].nombres) == 0 &&
                                pagoExistente.mes == mes && pagoExistente.anio == anio)
                            {
                                pagoRegistrado = true;
                                break;
                            }
                        }
                    }

                    if (pagoRegistrado)
                    {
                        cout << "\nEste cliente ya ha pagado en el mes " << mes << " del anio " << anio << "." << endl;
                        system("pause");
                        break;
                    }

                    int mesesDeRetraso = (anioActual - anio) * 12 + (mesActual - mes);

                    if (mesesDeRetraso > 2)
                    {

                        pago = consumoKw * 0.16 * 1.05;
                        cout << "\nSe ha aplicado una multa del 5% por retraso. El monto total a pagar es: " << pago << endl;
                    }
                    else
                    {
                        pago = (consumoKw * 0.16) + ((consumoKw * 0.16) * 0.3);
                    }

                    pago = round(pago * pow(10, decimales)) / pow(10, decimales);

                    strcpy(registroPago.persona, clientes[i].nombres);
                    registroPago.pago = pago;
                    registroPago.mes = mes;
                    registroPago.anio = anio;

                    fseek(archivoPagos, 0, SEEK_SET);
                    fseek(archivoClientes, 0, SEEK_SET);
                    fwrite(&registroPago, sizeof(RegistroPago), 1, archivoPagos);

                    clientes[i].pago = true;

                    // fclose(archivoClientes);
                    // archivoClientes = fopen(RUTA_CLIENTE.c_str(), "wb");

                    for (int j = 0; j < numClientes; j++)
                    {
                        fwrite(&clientes[j], sizeof(Clientes), 1, archivoClientes);
                    }

                    cout << "\nPago de $" << pago << " agregado correctamente para el mes " << mes << " del anio " << anio << endl;
                    system("pause");
                    break;
                }

                else
                {
                    cout << "\nEl consumo debe ser mayor a 0 kWh" << endl;
                    system("pause");
                    break;
                }
            }
        }

        if (!clienteEncontrado)
        {
            cout << "\nCliente no encontrado" << endl;
            system("pause");
        }

        fclose(archivoClientes);
        fclose(archivoPagos);
    }

    else
    {
        cout << "\nError al abrir los archivos de clientes o pagos" << endl;
        system("pause");
    }
}

/////////////////////////// fin

void verPago()
{
    bool pagoRealizado;
    bool registroEncontrado;

    system("cls");
    cout << "------     VER PAGO     ------" << endl;

    FILE *archivoClientes = fopen(RUTA_CLIENTE.c_str(), "rb");
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
                    cout << " | Estado: " << GREEN << "Pagado" << RESET << endl;

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
                cout << " | Estado:" << RED << "Sin Pago" << RESET << endl;
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

void busquedaDui()
{
    bool clienteEncontrado = false;
    char dui[100];
    int edicion = 0;
    Clientes temp;
    system("cls");

    cin.ignore();

    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "r+b");
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
                cout << i->nombres << " " << i->apellidos << endl;
                clienteEncontrado = true;
                cout << "Que desea Editar" << endl;
                cout << "1. Nombre" << endl;
                cout << "2. Apellidos" << endl;
                cout << "Seleccione una opcion: ";
                edicion = leer();
                cin.ignore();
                switch (edicion)
                {
                case 1:
                    ingresoNombre();
                    validarMayusculas();
                    strcpy(i->nombres, cliente.nombres);
                    break;
                case 2:
                    ingresoApellido();
                    validarMayusculas();
                    strcpy(i->apellidos, cliente.apellidos);
                    break;

                default:
                    break;
                }
                break;
            }
        }

        if (!clienteEncontrado)
        {
            cout << RED << "Cliente no encontrado" << RESET << endl;
            system("pause>null");
            fclose(archivo);
            return;
        }

        fseek(archivo, 0, SEEK_SET);
        for (auto i = clientesAux.begin(); i != clientesAux.end(); i++)
        {
            fwrite(&(*i), sizeof(Clientes), 1, archivo);
        }
    }
    fclose(archivo);
    clientesAux.clear();
    cout << GREEN << "Datos actualizados correctamente" << RESET;
    system("pause>null");
}

void busquedaNombre()
{
    char nombre[MAX_CLIENT];
    int posicion = 0, lista = 1;
    Clientes temp;
    system("cls");

    cin.ignore();

    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "r+b");
    getSizeClientes();
    vector<int> posiciones;

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

        if (posiciones.empty())
        {
            cout << RED << "No hay clientes registrados con ese nombre" << RESET << endl;
            fclose(archivo);
            system("pause>null");
            clientesAux.clear();
            return;
        }
        else
        {
            cout << "0. Salir" << endl;
            cout << "Seleccione el usuario a editar: ";
            posicion = leer();

            if (posicion == 0)
            {
                fclose(archivo);
                clientesAux.clear();
                return;
            }

            posicion = posiciones[posicion - 1];

            edicion(clientesAux, posicion);

            fseek(archivo, 0, SEEK_SET);
            for (auto i = clientesAux.begin(); i != clientesAux.end(); i++)
            {
                fwrite(&(*i), sizeof(Clientes), 1, archivo);
            }
        }
    }

    fclose(archivo);
    clientesAux.clear();
    cout << GREEN << "Datos actualizados correctamente" << RESET;
    system("pause>null");
}

void busquedaApellido()
{
    char nombre[MAX_CLIENT];
    int posicion = 0, lista = 1;
    Clientes temp;
    system("cls");

    cin.ignore();

    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "r+b");
    getSizeClientes();
    vector<int> posiciones;

    ingresoApellido();

    if (archivo != NULL)
    {
        for (auto i = clientesAux.begin(); i != clientesAux.end(); i++)
        {
            if (strcmp(i->apellidos, cliente.apellidos) == 0)
            {
                cout << lista << ". " << i->dui << " " << i->nombres << " " << i->apellidos << endl;
                lista++;
                posiciones.push_back(posicion);
            }
            posicion++;
        }

        if (posiciones.empty())
        {
            cout << RED << "No hay clientes registrados con ese apellido" << RESET << endl;
            fclose(archivo);
            clientesAux.clear();
            return;
        }
        else
        {
            cout << "Seleccione el usuario a editar: ";
            posicion = leer();

            if (posicion == 0)
            {
                fclose(archivo);
                clientesAux.clear();
                return;
            }

            posicion = posiciones[posicion - 1];

            edicion(clientesAux, posicion);

            fseek(archivo, 0, SEEK_SET);
            for (auto i = clientesAux.begin(); i != clientesAux.end(); i++)
            {
                fwrite(&(*i), sizeof(Clientes), 1, archivo);
            }
        }
    }

    fclose(archivo);
    clientesAux.clear();
    cout << GREEN << "Datos actualizados correctamente" << RESET;
    system("pause>null");
}

void edicion(vector<Clientes> &editar, int index)
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
        strcpy(editar[index].nombres, cliente.nombres);
        break;
    case 2:
        ingresoApellido();
        validarMayusculas();
        strcpy(editar[index].apellidos, cliente.apellidos);
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
        strcpy(editar[index].dui, cliente.dui);
        break;

    default:
        break;
    }
}

void eliminarCliente()
{
    bool clienteEncontrado = false;
    char dui[100];
    int edicion = 0;
    system("cls");

    cin.ignore();

    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "r+b");
    getSizeClientes();

    do
    {
        cout << "Ingrese el DUI del cliente: ";
        cin.getline(dui, 100);

    } while (!validarDui(dui));

    if (archivo != NULL)
    {
        for (auto i = clientesAux.begin(); i != clientesAux.end();)
        {
            if (strcmp(i->dui, dui) == 0)
            {
                clienteEncontrado = true;
                cout << "Esta seguro de eliminar el cliente? (si->1, no->0): " << endl;
                edicion = leer();
                cin.ignore();

                if (edicion == 0)
                {
                    fclose(archivo);
                    return;
                }
                else
                {

                    i = clientesAux.erase(i);
                }
            }
            else
            {
                i++;
            }
        }

        if (!clienteEncontrado)
        {
            cout << RED << "Cliente no encontrado" << RESET << endl;
            system("pause>null");
            fclose(archivo);
            return;
        }

        fseek(archivo, 0, SEEK_SET);
        ftruncate(fileno(archivo), 0);

        for (auto &cliente : clientesAux)
        {
            fwrite(&cliente, sizeof(Clientes), 1, archivo);
        }
    }

    fclose(archivo);
    clientesAux.clear();
    cout << GREEN << "Datos eliminado correctamente" << RESET;
    system("pause>null");
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

void formatoMunicipio()
{
    char cadena[MAX_LENGTH];
    char *auxiliar;

    strcpy(cadena, cliente.direccion.municipio);
    strcpy(cliente.direccion.municipio, "");

    auxiliar = strtok(cadena, " ");

    while (auxiliar != NULL)
    {
        strcat(cliente.direccion.municipio, auxiliar);
        auxiliar = strtok(NULL, " ");

        if (auxiliar != NULL)
        {
            strcat(cliente.direccion.municipio, " ");
        }
    }
}

void formatoDepto()
{
    char cadena[MAX_LENGTH];
    char *auxiliar;

    strcpy(cadena, cliente.direccion.depto);
    strcpy(cliente.direccion.depto, "");

    auxiliar = strtok(cadena, " ");

    while (auxiliar != NULL)
    {
        strcat(cliente.direccion.depto, auxiliar);
        auxiliar = strtok(NULL, " ");

        if (auxiliar != NULL)
        {
            strcat(cliente.direccion.depto, " ");
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

    gotoxy(10, 0);
    cout << "Estas en la seccion: [Zona, Via, " << GREEN << "No.Casa" << RESET << ", Municipio]\n";

    cout << "\nIngrese el numero de casa: #";
    cliente.direccion.numCasa = leer();

    cont++; // 3

    concatenarDireccion(op, cont);

    fflush(stdin);

    do
    {
        system("cls");
        gotoxy(10, 0);
        cout << "Estas en la seccion: [Zona, Via, No.Casa, " << GREEN << "Municipio" << RESET << "]\n";
        cout << "\nIngrese el municipio: ";
        cin.getline(cliente.direccion.municipio, MAX_ADDRESS);

        formatoMunicipio();

        /////////////////// Mayusculas //////////////////////

        strcpy(aux, cliente.direccion.municipio);

        for (int i = 0; i < strlen(cliente.direccion.municipio); i++)
        {
            aux[i] = toupper(cliente.direccion.municipio[i]);
        }

        /////////////////////////////////////////////////////

        for (int i = 0; i < 14; i++)
        {
            if (strcmp(aux, sanviNorte[i]) == 0)
            {
                isReal = true;
                op = 1; // Para saber si entro en SanviNorte
                break;
            }

            if (strcmp(aux, sanviSur[i]) == 0)
            {
                isReal = true;
                op = 2; // Para saber si entro en sanviSur
                break;
            }
        }

    } while (!validarCliente(cliente.direccion.municipio));

    cont++; // 4

    validarMayusDireccion(cliente.direccion.municipio);

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

void gotoxy(int x, int y)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}