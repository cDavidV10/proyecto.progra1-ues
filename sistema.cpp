#include <iostream>
#include <limits>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cctype>
#include <conio.h>
#include <windows.h>

using namespace std;

/* Constantes de longitud*/
const int MAX_LENGTH = 30;
const int MAX_ADDRESS = 200;
const int MAX_CLIENT = 50;
const int MAX_MEDIDORES = 100;

/*Constantes de archivos*/

const string RUTA_USUARIOS = "usuarios.bin";
const string RUTA_REGISTRO = "registro.bin";
const string RUTA_CLIENTE = "clientes.bin";

/* Colores */
const string RED = "\033[1;31m";
const string GREEN = "\033[1;32m";
const string RESET = "\033[0m";

/* Constantes de control */
const int ENTER = 13;
const int BACKSPACE = 8;
const int TECLA_ARRIBA = 72;
const int TECLA_ABAJO = 80;

/* Constantes*/
const double PRECIO_KWH = 0.16;
const double MULTA_RETRASO = 0.03;
const int MES_ACTUAL = 10;
const int ANIO_ACTUAL = 2024;
const string meses[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                          "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

/* Estructuras */
struct Direccion
{
    char zona[MAX_LENGTH];
    char via[MAX_LENGTH];
    int numCasa;
    char municipio[MAX_LENGTH];
    char completa[MAX_ADDRESS];
};

struct Medidor
{
    char ID[20];
    double consumo;
};

struct Clientes
{
    char nombres[MAX_LENGTH];
    char apellidos[MAX_LENGTH];
    Direccion direccion;
    Medidor medidores[MAX_MEDIDORES];
    int numeroMedidores;
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
    char medidor[20];
    double pago;
    int mes;
    int anio;

} registroPago;

/* Inicializacion */
int loginOpcion = 0;
int menuOpcion = 0;
int manteOpcion = 0;
int opcion = 0;
int menu = 0;
int posicion = 0;
int mes = 0;

vector<Usuarios> usuariosAux;
vector<Clientes> clientesAux;
vector<int> posiciones;

/* Funciones de menu*/
void login();
void iniciarSesion();
void crearCuenta();
void menuPrincipal();
void editar();
void busqueda();
int menuSecundario(const char *titulo, const char *opciones[], int n);
void cambiarPassword();

/* Funciones relacionadas al cliente */
void ingresarClientes();
void verClientes();
void agregarPago();
void verPago();
void pago();
void obtenerMes();
void correlativo();
void seccionCliente();
void seleccion();
void getSizeClientes();
void getSizeUsuario();
void user();
string generarNumeroCorrelativo(int numeroCliente, int anio);

/* Funciones encargadas de editar */
void busquedaDui();
void busquedaNombre();
void busquedaApellido();
void edicion();
void funcionEditar();

/* Funciones encargadas de eliminar */
void eliminarCliente();

/* Funciones de validacion */
void validarMayusculas();
bool validarCliente(char[]);
void formatoNombre();
void formatoApellido();
void ingresoNombre();
void ingresoApellido();
bool duiExiste(char[]);
bool validarDui(char[]);
bool validarUsuario();
int leer();

/* Funciones para la valicacion del login */
bool verificarUsuario(bool);
bool comprobarPassword();
void password();

/* Funciones de las direcciones */
void ingresarDireccion();
void formatoZona();
void formatoVia();
void formatoMunicipio();
void formatoDepto();
void validarMayusDireccion(char[]);
void concatenarDireccion(int, int);

/* Estilo */
void gotoxy(int, int);
void cuadro(int, int, int, int);
void CentrarTexto(string &texto, int y);
void color(int fondo, int letra);

/* Medidores*/
void crearMedidor();
void generarMedidor(int, int);
void verMedidores();

int main(int argc, char const *argv[])
{

    do
    {
        system("color 70");
        color(7, 0);
        login();

        switch (loginOpcion)
        {

        case 1:
        {
            iniciarSesion();
            break;
        }

        case 2:
        {
            crearCuenta();
            break;
        }

        default:
            break;
        }

    } while (loginOpcion != 3);

    return 0;
}

void login()
{
    string texto = "BIENVENIDOS AL SISTEMA";

    system("cls");

    system("color 70");
    color(7, 0);

    cuadro(0, 0, 76, 24);
    cuadro(1, 1, 70, 3);
    CentrarTexto(texto, 2);

    gotoxy(3, 5);
    cout << "1. Iniciar Sesion";
    gotoxy(3, 6);
    cout << "2. Registrarse";
    gotoxy(3, 7);
    cout << "3. Salir";
    gotoxy(3, 8);
    cout << "Seleccione una opcion del menu: ";
    loginOpcion = leer();
}

void iniciarSesion()
{
    int intentos = 3;
    bool ingresa = false;
    int key;
    cin.ignore();

    do
    {
        system("cls");
        system("color 70");
        color(7, 0);
        string texto = "INICIAR SESION ";
        cuadro(0, 0, 76, 24);
        cuadro(1, 1, 70, 3);
        CentrarTexto(texto, 2);

        gotoxy(3, 6);
        cout << "Usuario: ";
        cin.getline(usuario.usuario, 20);
        gotoxy(3, 7);
        cout << "Contrase" << (char)164 << "a: ";
        password();

        if (verificarUsuario(true))
        {
            ingresa = true;
        }

        else
        {
            gotoxy(3, 9);
            cout << RED << "El usuario y/o el password son incorrectos" << RESET;
            intentos--;
            color(7, 0);
            gotoxy(3, 10);
            cout << "Has olvidado tu contrase" << char(164) << "a?" << endl;
            gotoxy(3, 11);
            cout << "Presiona esc para cambiar tu contrase" << char(164) << "a" << endl;
            gotoxy(3, 12);
            cout << "Presiona cualquier tecla para continuar" << endl;
            key = _getch();

            if (key == 27)
            {
                cambiarPassword();
                return;
            }
        }

    } while (!ingresa && intentos > 0);

    if (ingresa)
    {
        menuPrincipal();
    }

    else
    {
        color(7, 0);
        gotoxy(15, 20);
        cout << RED << "Acceso denegado. Intenta nuevamente mas tarde" << RESET << endl;
        cin.get();
    }
}

void crearCuenta()
{
    cin.ignore();

    system("cls");
    system("color 70");
    color(7, 0);

    string texto = "CREAR CUENTA ";
    cuadro(0, 0, 76, 24);
    cuadro(1, 1, 70, 3);
    CentrarTexto(texto, 2);

    do
    {

        color(7, 0);
        gotoxy(3, 6);
        cout << "Usuario: ";
        cin.getline(usuario.usuario, 20);

        if (validarUsuario())
        {

            color(7, 0);
            gotoxy(3, 7);
            cout << RED << "El usuario debe detener entre 4 y 20 caracteres" << RESET;
            getch();

            color(7, 0);
            gotoxy(3, 6);
            cout << "                      ";
            gotoxy(3, 7);
            cout << "                                                         ";
        }

    } while (validarUsuario());

    do
    {
        color(7, 0);

        gotoxy(3, 8);
        cout << "Contrase" << (char)164 << "a: ";
        password();

        if (!comprobarPassword())
        {
            color(7, 0);

            color(7, 0);
            gotoxy(3, 9);
            cout << RED << "El password debe de tener minimo 8 caracteres, un numero,";
            gotoxy(3, 10);
            cout << "una mayuscula y un caracter especial" << RESET;

            getch();

            color(7, 0);
            gotoxy(3, 8);
            cout << "                            ";
            gotoxy(3, 9);
            cout << "                                                              ";
            gotoxy(3, 10);
            cout << "                                                              ";
        }

    } while (!comprobarPassword());

    if (verificarUsuario(false))
    {
        color(7, 0);
        gotoxy(3, 11);
        cout << RED << "El usuario ya existe" << RESET;
    }
    else
    {
        FILE *archivo = fopen(RUTA_USUARIOS.c_str(), "ab");

        if (archivo != NULL)
        {
            fwrite(&usuario, sizeof(Usuarios), 1, archivo);
            fclose(archivo);

            gotoxy(3, 11);
            cout << GREEN << "Cuenta creada correctamente" << RESET;
        }

        else
        {
            gotoxy(3, 11);
            cout << RED << "Error al crear el usuario" << RESET;
        }
    }

    color(7, 0);
    gotoxy(3, 12);
    cout << "Presione cualquier tecla para continuar";
    cin.get();
}

void menuPrincipal()
{
    bool repite = true;
    int opcion, n;

    system("color 70");
    color(7, 0);

    const char *titulo =
        "\t\t\t\t+-----------------------------------------------+\n"
        "\t\t\t\t\t|                MENU PRINCIPAL                 |\n"
        "\t\t\t\t\t+-----------------------------------------------+";

    const char *opciones[] =
        {
            "Agregar Cliente    ",
            "Busqueda",
            "Ver Clientes",
            "Ver Pago",
            "Salir"};

    n = 5;

    do
    {
        system("color 70");
        opcion = menuSecundario(titulo, opciones, n);

        switch (opcion)
        {
        case 1:
        {
            ingresarClientes();
            break;
        }

        case 2:
        {

            busqueda();
            break;
        }

        case 3:
        {

            verClientes();
            break;
        }

        case 4:
        {

            verPago();
            break;
        }

        case 5:
        {
            repite = false;
            break;
        }
        }

    } while (repite);
}

int menuSecundario(const char *titulo, const char *opciones[], int n)
{
    int opcionSeleccionada = 1;
    int tecla;
    bool repite = true;

    do
    {
        system("color 70");
        system("cls");

        gotoxy(48, 3 + opcionSeleccionada);
        cout << "==>";

        gotoxy(15, 1);
        cout << titulo;

        for (int i = 0; i < n; i++)
        {
            gotoxy(54, 4 + i);
            cout << i + 1 << ") " << opciones[i];
        }

        tecla = getch();

        switch (tecla)
        {
        case 72:
        {
            opcionSeleccionada--;

            if (opcionSeleccionada < 1)
            {
                opcionSeleccionada = n;
            }
            break;
        }

        case 80:
        {
            opcionSeleccionada++;
            if (opcionSeleccionada > n)
            {
                opcionSeleccionada = 1;
            }
            break;
        }

        case 13:
        {
            repite = false;
            break;
        }
        }

    } while (repite);

    return opcionSeleccionada;
}

void busqueda()
{
    system("cls");
    string texto = "BUSQUEDA DE CLIENTES POR ";
    system("color 70");
    color(7, 0);
    cuadro(0, 0, 76, 24);
    cuadro(1, 1, 70, 3);
    user();
    CentrarTexto(texto, 2);
    gotoxy(3, 6);
    cout << "1. DUI" << endl;
    gotoxy(3, 7);
    cout << "2. Nombres" << endl;
    gotoxy(3, 8);
    cout << "3. Salir" << endl;
    gotoxy(3, 9);
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

    cout << GREEN << "\n\tDatos actualizados correctamente" << RESET;

    clientesAux.clear();
    posiciones.clear();
    fclose(archivo);
}

void ingresarClientes()
{
    bool isEncontrado = false;
    int key;
    int resp;

    system("cls");
    cout << "\n\tPresione cualquier tecla para continuar" << endl;
    cout << "\n\tPresione ESC para salir" << endl;

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
        string texto = "INGRESAR CLIENTE ";
        system("color 70");
        cuadro(0, 0, 76, 24);
        cuadro(1, 1, 70, 3);
        CentrarTexto(texto, 2);
        user();

        do
        {
            color(7, 0);
            gotoxy(3, 4);
            cout << "Ingrese el DUI del cliente: ";
            cin.getline(cliente.dui, 100);

            if (duiExiste(cliente.dui))
            {
                gotoxy(3, 6);
                cout << RED << "El DUI ya esta registrado." << RESET << endl;
                getch();
                color(7, 0);
                gotoxy(3, 4);
                cout << "                                               ";
                gotoxy(3, 6);
                cout << "                                               ";
                gotoxy(3, 7);
                cout << "Desea agregar otro medidor? (si -> 1, no -> 0): ";
                resp = leer();

                if (resp == 1)
                {
                    crearMedidor();
                    cin.ignore();
                    cin.get();
                    return;
                }
            }
            else if (!validarDui(cliente.dui))
            {
                gotoxy(3, 6);
                cout << RED << "DUI invalido." << RESET << endl;
                getch();
                color(7, 0);
                gotoxy(3, 4);
                cout << "                                               ";
                gotoxy(3, 6);
                cout << "                                               ";
            }

        } while (!validarDui(cliente.dui) || duiExiste(cliente.dui));

        fflush(stdin);

        gotoxy(3, 8);
        ingresoNombre();

        fflush(stdin);

        gotoxy(3, 10);
        ingresoApellido();

        fflush(stdin);

        do
        {
            color(7, 0);

            ingresarDireccion();

            char aux[MAX_ADDRESS];
            strcpy(aux, cliente.direccion.completa);

            getSizeClientes();

            for (auto i = clientesAux.begin(); i != clientesAux.end(); i++)
            {
                isEncontrado = false;
                if (strcmp(i->direccion.completa, aux) == 0)
                {
                    cout << RED << "\n[ADVERTENCIA]: No puede ingresar dos veces la misma direccion. Intente de nuevo." << RESET << endl;
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

        crearMedidor();
        cout << GREEN << "\n\nCliente agregado correctamente" << RESET << endl;
        cin.get();

        fflush(stdin);
    }
    else
    {
        cout << RED << "\n[ERROR]: Creacion de archivo invalida." << RESET;
    }
    fclose(archivo);
}

string generarNumeroCorrelativo(int numeroCliente, int anio)
{

    string numeroStr = to_string(numeroCliente);

    while (numeroStr.length() < 4)
    {
        numeroStr = "0" + numeroStr;
    }

    return to_string(anio) + "-" + numeroStr;
}

void verClientes()
{
    system("cls");

    int i = 0;
    int op = 0;
    Clientes cliente;

    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "rb");

    if (archivo != NULL)
    {
        system("color 70");
        color(7, 0);

        user();
        string texto = " LISTA DE CLIENTES ";
        cuadro(1, 1, 70, 3);
        CentrarTexto(texto, 2);

        gotoxy(1, 5);
        cout << "No ";
        gotoxy(5, 5);
        cout << "Cuenta";
        gotoxy(20, 5);
        cout << "Nombres ";
        gotoxy(45, 5);
        cout << "Apellidos ";
        gotoxy(65, 5);
        cout << "DUI ";
        gotoxy(80, 5);
        cout << "Distrito";
        gotoxy(110, 5);
        cout << "Medidores";

        while (!feof(archivo))
        {
            fread(&cliente, sizeof(Clientes), 1, archivo);

            if (!feof(archivo))
            {

                string numeroCorrelativo = generarNumeroCorrelativo(i + 1, ANIO_ACTUAL);

                gotoxy(1, 7 + i);
                cout << i + 1;
                gotoxy(5, 7 + i);
                cout << numeroCorrelativo;
                gotoxy(20, 7 + i);
                cout << cliente.nombres;
                gotoxy(45, 7 + i);
                cout << cliente.apellidos;
                gotoxy(65, 7 + i);
                cout << cliente.dui;
                gotoxy(80, 7 + i);
                cout << cliente.direccion.municipio;
                gotoxy(110, 7 + i);
                cout << cliente.numeroMedidores;
            }

            i++;
        }
    }
    else
    {
        cout << RED << "[ERROR]: Creacion de archivo invalida." << RESET;
    }

    fclose(archivo);

    cout << "\n\n[Mostrar Medidores] -> 1 " << endl;
    cout << "[Salir] -> 2" << endl;
    cout << "Opcion: ";

    op = leer();

    if (op == 1)
    {
        verMedidores();
    }

    color(7, 0);
    cout << "\n\nPresione cualquier tecla para continuar";
    cin.get();
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

    if (clientesAux.empty())
    {
        cout << "No hay clientes registrados" << endl;
        cin.get();
        return;
    }

    FILE *archivoPagos = fopen(RUTA_REGISTRO.c_str(), "a+b");
    FILE *archivoCliente = fopen(RUTA_CLIENTE.c_str(), "wb");

    system("cls");
    string texto = "INGRESAR PAGO";
    system("color 70");
    cuadro(1, 1, 70, 3);
    CentrarTexto(texto, 2);

    if (archivoPagos != NULL)
    {
        cout << "\n\n   Cliente encontrado: " << clientesAux[posicion].nombres << " " << clientesAux[posicion].apellidos << endl;

        cout << "\n   Presione cualquier tecla para continuar" << endl;
        cout << "\n   Presione esc para salir" << endl;

        key = _getch();

        if (key == 27)
        {
            fseek(archivoCliente, 0, SEEK_SET);
            for (auto i = clientesAux.begin(); i != clientesAux.end(); i++)
            {
                fwrite(&(*i), sizeof(Clientes), 1, archivoCliente);
            }

            clientesAux.clear();
            posiciones.clear();
            fclose(archivoPagos);
            fclose(archivoCliente);
            return;
        }

        cout << "\n   Lista de medidores del cliente: " << endl;
        for (int i = 0; i < clientesAux[posicion].numeroMedidores; i++)
        {
            cout << "   No. " << i + 1 << "\tMedidor ID: " << clientesAux[posicion].medidores[i].ID << endl;
        }

        int numMedidor;
        do
        {
            cout << "\n   Ingrese el numero del medidor (1-" << clientesAux[posicion].numeroMedidores << "): ";
            cin >> numMedidor;
        } while (numMedidor < 1 || numMedidor > clientesAux[posicion].numeroMedidores);

        cout << "\n   Ingrese el consumo en kWh para el medidor [" << clientesAux[posicion].medidores[numMedidor - 1].ID << "]: ";
        cin >> consumoKw;

        if (consumoKw > 80)
        {
            consumoKw -= 80;
            cout << "\n   Seleccione el mes para el pago:" << endl;
            obtenerMes();

            mes = mes - 1;

            fseek(archivoPagos, 0, SEEK_SET);

            while (fread(&pagoExistente, sizeof(RegistroPago), 1, archivoPagos))
            {
                if (strcmp(pagoExistente.persona, clientesAux[posicion].nombres) == 0 &&
                    pagoExistente.mes == mes && pagoExistente.anio == ANIO_ACTUAL &&
                    strcmp(pagoExistente.medidor, clientesAux[posicion].medidores[numMedidor - 1].ID) == 0)
                {
                    pagoRegistrado = true;
                    break;
                }
            }

            if (pagoRegistrado)
            {
                cout << "\n  Este cliente ya ha pagado en el mes " << meses[mes] << " del a" << (char)164 << "o " << ANIO_ACTUAL << "." << endl;
                clientesAux[posicion].medidores[numMedidor - 1].consumo = consumoKw;
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
                pago = round(pago * pow(10, decimales)) / pow(10, decimales);
                cout << "\n  Se ha aplicado una multa del 3% por retraso. El monto total a pagar es: $" << pago << endl;
            }
            else
            {
                pago = (consumoKw * PRECIO_KWH) + (consumoKw * 0.3) + (consumoKw * 0.13);
                pago = round(pago * pow(10, decimales)) / pow(10, decimales);
            }

            RegistroPago registroPago;
            strcpy(registroPago.persona, clientesAux[posicion].nombres);
            strcpy(registroPago.medidor, clientesAux[posicion].medidores[numMedidor - 1].ID);
            registroPago.pago = pago;
            registroPago.mes = mes;
            registroPago.anio = ANIO_ACTUAL;

            fseek(archivoPagos, 0, SEEK_END);
            fwrite(&registroPago, sizeof(RegistroPago), 1, archivoPagos);

            clientesAux[posicion].medidores[numMedidor - 1].consumo = consumoKw;

            clientesAux[posicion].pago = true;

            cout << "\n  Pago de $" << pago << " agregado correctamente para el medidor ["
                 << clientesAux[posicion].medidores[numMedidor - 1].ID << "] en el mes "
                 << meses[mes] << " del a" << (char)164 << "o: " << ANIO_ACTUAL << "\n\n";
            system("pause");
        }
        else
        {
            cout << "\n  El consumo debe ser mayor a 0 kWh" << endl;
            system("pause");
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
    int sitio = 5;
    bool pagoCliente;

    cin.ignore();
    system("cls");

    string texto = "REGISTRO DE PAGO";
    system("color 70");
    color(7, 0);
    cuadro(1, 1, 70, 3);
    CentrarTexto(texto, 2);

    FILE *archivoPagos = fopen(RUTA_REGISTRO.c_str(), "rb");

    getSizeClientes();

    if (clientesAux.empty())
    {
        cout << "\n  No hay usuarios registrados" << endl;
        cin.get();
        return;
    }

    vector<RegistroPago> pagos;

    if (archivoPagos != NULL)
    {
        RegistroPago pago;
        sitio = 5;

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
            color(7, 0);
            cout << RED << "\n\tNo hay registros de pagos" << RESET << endl;
            cin.get();
            clientesAux.clear();
            pagos.clear();
            fclose(archivoPagos);
            return;
        }

        cout << "\n\n  Seleccione el mes para ver el pago:" << endl;
        obtenerMes();
        mes = mes - 1;

        system("cls");

        string texto = "REGISTRO DE PAGO DE CLIENTES";
        system("color 70");
        color(7, 0);
        cuadro(1, 1, 70, 3);
        CentrarTexto(texto, 2);

        for (int i = 0; i < clientesAux.size(); i++)
        {
            bool pagoRealizado = false;

            for (int j = 0; j < pagos.size(); j++)
            {
                for (int k = 0; k < clientesAux[i].numeroMedidores; k++)
                {
                    if (strcmp(clientesAux[i].nombres, pagos[j].persona) == 0 && pagos[j].mes == mes && strcmp(clientesAux[i].medidores[k].ID, pagos[j].medidor) == 0)
                    {
                        color(7, 0);
                        gotoxy(0, sitio);
                        cout << "Medidor: " << clientesAux[i].medidores[k].ID;
                        cout << " | Cliente: " << clientesAux[i].nombres << " " << clientesAux[i].apellidos;
                        cout << " | DUI: " << clientesAux[i].dui;
                        cout << " | Mes: " << meses[mes] << " | A" << (char)164 << "o " << pagos[j].anio;
                        cout << " | Monto: $" << pagos[j].pago;

                        if (clientesAux[i].pago)
                        {
                            color(7, 0);
                            cout << " | Estado: " << GREEN << "Pagado" << RESET << "\n\n";
                        }

                        else
                        {
                            color(7, 0);
                            cout << " | Estado: " << RED << "Sin pagar" << RESET << "\n\n";
                        }

                        sitio++;
                        pagoRealizado = true;
                        break;
                    }
                }
            }

            if (!pagoRealizado)
            {
                color(7, 0);
                gotoxy(0, sitio);
                for (int k = 0; k < clientesAux[i].numeroMedidores; k++)
                {
                    cout << "Medidor: " << clientesAux[i].medidores[k].ID;
                    cout << " | Cliente: " << clientesAux[i].nombres << " " << clientesAux[i].apellidos;
                    cout << " | DUI: " << clientesAux[i].dui;
                    cout << " | Mes: " << meses[mes] << " | Estado: " << RED << "Sin pagar" << RESET << endl;
                    sitio++;
                }
            }
        }
    }
    else
    {
        color(7, 0);
        cout << RED << "\n\n\n\tError al abrir los archivos de pagos" << RESET << endl;
    }

    pagos.clear();
    clientesAux.clear();
    fclose(archivoPagos);

    color(7, 0);
    cout << "\n\n\tPresione cualquier tecla para continuar";
    cin.ignore();
    cin.get();
}

void obtenerMes()
{
    for (int i = 0; i <= 11; i++)
    {
        cout << "   " << i + 1 << ". " << meses[i] << endl;
    }

    do
    {
        cout << "   Mes (1-12): ";
        mes = leer();

    } while (mes < 1 || mes > 12);
}

void busquedaDui()
{
    posicion = 0;
    char dui[100];
    bool existe = false;

    cin.ignore();

    user();
    system("cls");
    user();
    string texto = "BUSCADA POR DUI ";
    system("color 70");
    cuadro(1, 1, 70, 3);
    CentrarTexto(texto, 2);

    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "rb");
    getSizeClientes();

    do
    {
        cout << "\n\n\n\tIngrese el DUI del cliente: ";
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
        cout << "\t" << clientesAux[posicion].dui << " " << clientesAux[posicion].nombres << " " << clientesAux[posicion].apellidos;
        seleccion();
    }
    else
    {
        cout << RED << "\n\tNo hay clientes registrados con ese dui" << RESET << endl;
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

    user();
    string texto = "BUSCADA POR NOMBRE ";
    system("color 70");
    cuadro(1, 1, 70, 3);
    CentrarTexto(texto, 2);

    cin.ignore();

    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "rb");
    getSizeClientes();

    cout << "\n\n\n\t";
    ingresoNombre();

    if (archivo != NULL)
    {
        for (auto i = clientesAux.begin(); i != clientesAux.end(); i++)
        {
            if (strcmp(i->nombres, cliente.nombres) == 0)
            {
                cout << "\t" << lista << ". " << i->dui << " " << i->nombres << " " << i->apellidos << "\n\n";
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

    cout << "\n\t- - - - -  - - - - - - - -";
    cout << "\n\tQue desea Editar" << endl;
    cout << "\t1. Nombre" << endl;
    cout << "\t2. Apellidos" << endl;
    cout << "\t3. DUI" << endl;
    cout << "\tSeleccione una opcion: ";
    edicion = leer();
    cin.ignore();

    switch (edicion)
    {
    case 1:
        do
        {
            color(7, 0);
            cout << "\n\tIngrese los nombres del cliente: ";
            cin.getline(cliente.nombres, MAX_LENGTH);
            formatoNombre();

        } while (!validarCliente(cliente.nombres));
        validarMayusculas();
        strcpy(clientesAux[posicion].nombres, cliente.nombres);
        break;

    case 2:
        do
        {
            color(7, 0);
            cout << "\n\tIngrese los apellidos del cliente: ";
            cin.getline(cliente.apellidos, MAX_LENGTH);
            formatoApellido();
            cout << endl;

        } while (!validarCliente(cliente.apellidos));
        validarMayusculas();
        strcpy(clientesAux[posicion].apellidos, cliente.apellidos);
        break;

    case 3:
        do
        {
            cout << "\n\tIngrese el DUI del cliente: ";
            cin.getline(cliente.dui, 100);

            if (duiExiste(cliente.dui))
            {
                cout << RED << "\n\tEl dui ya esta registrado" << RESET << endl;
            }
            else if (!validarDui(cliente.dui))
            {
                cout << RED << "\n\tDUI invalido" << RESET << endl;
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
        cout << RED << "\n\tNo hay clientes registrados con ese nombre" << RESET << endl;
        cin.get();
        clientesAux.clear();
        return;
    }
    else
    {

        cout << "\n\tSeleccione el cliente: ";
        posicion = leer();
        cout << "\n\n";
        posicion = posiciones[posicion - 1];

        seleccion();
    }
}

void seleccion()
{
    cin.ignore();
    int key;
    cout << "\tQue desea realizar con el cliente" << endl;
    cout << "\tEsc para salir" << endl;
    cout << "\tF1 para agregar pago" << endl;
    cout << "\tF2 para editar" << endl;
    cout << "\tF3 para eliminar" << endl;
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

    user();

    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "wb");

    system("color 70");

    if (archivo != NULL)
    {
        cout << "\n\n\tEsta seguro de eliminar el cliente? (si->1, no->0): ";
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
            color(7, 0);

            cout << "\n\tEscriba su contrase" << (char)164 << "a: ";
            password();

            if (verificarUsuario(true))
            {
                elimina = true;
            }
            else
            {
                cout << RED << "\n\tEl password es incorrecto" << RESET << endl;
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

            color(7, 0);
            cout << endl
                 << GREEN << "\n\tDatos eliminado correctamente" << RESET;
        }

        else
        {

            color(7, 0);
            cout << endl
                 << RED << "\n\tNo se puedo eliminar al cliente" << RESET << endl;
            cin.get();
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
        color(7, 0);
        cout << "Ingrese los nombres del cliente: ";
        cin.getline(cliente.nombres, MAX_LENGTH);
        formatoNombre();

    } while (!validarCliente(cliente.nombres));
}

void ingresoApellido()
{
    do
    {
        color(7, 0);
        cout << "Ingrese los apellidos del cliente: ";
        cin.getline(cliente.apellidos, MAX_LENGTH);
        formatoApellido();
        cout << endl;

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
        string texto = "DIRECCION DEL CLIENTE";
        system("color 70");
        cuadro(1, 1, 70, 3);
        CentrarTexto(texto, 2);

        gotoxy(10, 4);
        cout << " Estas en la seccion: [";
        color(7, 2);
        cout << "Zona";
        color(7, 0);
        cout << ", Via, No.Casa, Municipio]\n";
        gotoxy(2, 6);
        cout << "Seleccione el formato de su direccion: " << endl;
        gotoxy(2, 8);
        cout << "1. Colonia." << endl;
        gotoxy(2, 9);
        cout << "2. Barrio." << endl;
        gotoxy(2, 10);
        cout << "3. Urbanizacion." << endl;
        gotoxy(2, 11);
        cout << "4. Sector." << endl;
        gotoxy(2, 13);
        cout << "Opcion: ";
        op = leer();
    } while (op <= 0 || op >= 5);

    fflush(stdin);

    do
    {
        switch (op)
        {
        case 1:
            cout << "  Ingrese el nombre de la colonia: ";
            cin.getline(cliente.direccion.zona, MAX_ADDRESS);
            break;

        case 2:
            cout << "   Ingrese el nombre del barrio: ";
            cin.getline(cliente.direccion.zona, MAX_ADDRESS);
            break;

        case 3:
            cout << "   Ingrese el nombre de la urbanizacion: ";
            cin.getline(cliente.direccion.zona, MAX_ADDRESS);
            break;

        case 4:
            cout << "   Ingrese el nombre del sector: ";
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
        gotoxy(10, 1);
        cout << " Estas en la seccion: [Zona, ";
        color(7, 2);
        cout << "Via";
        color(7, 0);
        cout << ", No.Casa, Municipio]\n";
        gotoxy(2, 3);
        cout << "\tSeleccione el formato de su direccion: " << endl;
        cout << "\n\t1. Calle." << endl;
        cout << "\t2. Boulevard." << endl;
        cout << "\t3. Paseo." << endl;
        cout << "\t4. Autopista." << endl;
        cout << "\t5. Carretera." << endl;
        cout << "\t6. Calle Principal." << endl;
        cout << "\t7. Via." << endl;
        gotoxy(2, 12);
        cout << "\n\tOpcion: ";
        op = leer();
    } while (op <= 0 || op >= 8);

    fflush(stdin);

    do
    {
        switch (op)
        {
        case 1:
            cout << "\tIngrese el nombre de la calle: ";
            cin.getline(cliente.direccion.via, MAX_ADDRESS);
            break;

        case 2:
            cout << "\tIngrese el nombre del boulevard: ";
            cin.getline(cliente.direccion.via, MAX_ADDRESS);
            break;

        case 3:
            cout << "\tIngrese el nombre de la paseo: ";
            cin.getline(cliente.direccion.via, MAX_ADDRESS);
            break;

        case 4:
            cout << "\tIngrese el nombre de la autopista: ";
            cin.getline(cliente.direccion.via, MAX_ADDRESS);
            break;

        case 5:
            cout << "\tIngrese el nombre de la carretera: ";
            cin.getline(cliente.direccion.via, MAX_ADDRESS);
            break;

        case 6:
            cout << "\tIngrese el nombre de la calle principal: ";
            cin.getline(cliente.direccion.via, MAX_ADDRESS);
            break;

        case 7:
            cout << "\tIngrese el nombre de la via: ";
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

    cont++;

    validarMayusDireccion(cliente.direccion.via);

    concatenarDireccion(op, cont);

    system("cls");

    fflush(stdin);

    gotoxy(10, 1);
    cout << " Estas en la seccion: [Zona, Via, ";
    color(7, 2);
    cout << "No.Casa";
    color(7, 0);
    cout << ", Municipio]\n";

    cout << "\n  Ingrese el numero de casa: #";
    cliente.direccion.numCasa = leer();

    cont++;

    concatenarDireccion(op, cont);

    fflush(stdin);

    do
    {
        system("cls");
        color(7, 0);
        gotoxy(10, 1);
        cout << " Estas en la seccion: [Zona, Via, No.Casa, ";
        color(7, 2);
        cout << "Municipio";
        color(7, 0);
        cout << "]";

        gotoxy(8, 4);
        cout << "San Vicente Norte";

        for (int i = 0; i < 7; i++)
        {
            gotoxy(9, 5 + i);
            validarMayusDireccion(sanviNorte[i]);
            cout << i + 1 << ". " << sanviNorte[i];
        }

        gotoxy(50, 4);
        cout << "San Vicente Sur";

        for (int i = 0; i < 6; i++)
        {
            gotoxy(51, 5 + i);
            validarMayusDireccion(sanviSur[i]);
            cout << 8 + i << ". " << sanviSur[i];
        }
        fflush(stdin);

        gotoxy(3, 13);
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

    cont++;

    concatenarDireccion(op, cont);

    cont++;

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
    getSizeUsuario();

    for (Usuarios temp : usuariosAux)
    {
        if (strcmp(usuario.usuario, temp.usuario) == 0)
        {
            if (verificarPass)
            {
                if (strcmp(temp.password, usuario.password) == 0)
                {
                    usuariosAux.clear();
                    return true;
                }
            }
            else
            {
                usuariosAux.clear();
                return true;
            }
        }
    }

    usuariosAux.clear();
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
            cout << "\n\tDato incorrecto, ingrese nuevamente: ";
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

void cuadro(int xs, int ys, int xi, int yi)
{
    int i;

    for (i = xs; i <= xi; i++)
    {
        gotoxy(i, ys);
        printf("%c", 196);
        gotoxy(i, yi);
        printf("%c", 196);
    }
    for (i = ys; i <= yi; i++)
    {
        gotoxy(xs, i);
        printf("%c", 179);
        gotoxy(xi, i);
        printf("%c", 179);
    }
    gotoxy(xs, ys);
    printf("%c", 218);
    gotoxy(xi, yi);
    printf("%c", 217);
    gotoxy(xi, ys);
    printf("%c", 191);
    gotoxy(xs, yi);
    printf("%c", 192);
}

void CentrarTexto(string &texto, int y)
{
    int longitud = texto.length();
    gotoxy(38 - (longitud / 2), y);
    cout << texto;
}

void color(int fondo, int letra)
{
    int x = fondo * 16 + letra;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
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

    gotoxy(70, 0);
}

void cambiarPassword()
{
    char newPassword[20];
    bool cambio;

    getSizeUsuario();

    system("cls");

    system("color 70");
    color(7, 0);
    string texto = "CAMBIAR CLAVE";
    cuadro(1, 1, 70, 3);
    CentrarTexto(texto, 2);

    if (usuariosAux.empty())
    {
        cout << "\n\n\n\tNo hay usuarios registrados" << endl;
        cin.get();
        usuariosAux.clear();
        return;
    }

    if (strlen(usuario.usuario) == 0)
    {
        cout << endl;
        do
        {
            color(7, 0);
            cout << "\n\tUsuario: ";
            cin.getline(usuario.usuario, 20);
            if (validarUsuario())
            {
                cout << RED << "\tEl usuario debe detener entre 4 y 20 caracteres" << RESET << endl;
            }
        } while (validarUsuario());
    }

    do
    {
        cambio = false;

        cout << "\n\n\t- - - - - - - - - - - - - - - - - - - - - -\n";
        cout << "\tUsuario: " << usuario.usuario << endl;

        do
        {
            color(7, 0);
            cout << "\n\tNueva contrase" << char(164) << "a: ";
            password();

            if (!comprobarPassword())
            {
                color(7, 0);
                cout << RED << "\n\tEl password debe de tener minimo 8 caracteres, un numero, una mayuscula y un caracter especial" << RESET;
            }

        } while (!comprobarPassword());

        strcpy(newPassword, usuario.password);

        cout << endl;

        cout << "\n\tEscriba nuevamente su contrase" << char(164) << "a: ";
        password();

        if (strcmp(newPassword, usuario.password) == 0)
        {

            for (auto i = usuariosAux.begin(); i != usuariosAux.end(); i++)
            {
                if (strcmp(i->usuario, usuario.usuario) == 0)
                {
                    if (strcmp(i->password, usuario.password) == 0)
                    {
                        cout << "\n\tLa contrase" << char(164) << "a no puede ser la misma" << endl;
                        break;
                    }
                    else
                    {
                        color(7, 0);
                        strcpy(i->password, usuario.password);
                        cambio = true;
                        break;
                    }
                }
            }
        }
        else
        {
            color(7, 0);
            cout << endl;
            cout << "\nLas contrase" << char(164) << "a no coincide" << endl;
        }
    } while (!cambio);

    FILE *archivo = fopen(RUTA_USUARIOS.c_str(), "wb");

    if (archivo != NULL)
    {
        fseek(archivo, 0, SEEK_SET);

        for (auto i = usuariosAux.begin(); i != usuariosAux.end(); i++)
        {
            fwrite(&(*i), sizeof(Usuarios), 1, archivo);
        }

        color(7, 0);
        cout << endl;
        cout << "\n\n\t\tContrase" << char(164) << "a actulizada correctamente" << endl;
        cin.get();
    }

    fclose(archivo);
    usuariosAux.clear();
}

void getSizeUsuario()
{
    FILE *archivo = fopen(RUTA_USUARIOS.c_str(), "rb");
    Usuarios temp;
    if (archivo != NULL)
    {
        while (!feof(archivo))
        {
            fread(&temp, sizeof(Usuarios), 1, archivo);
            if (!feof(archivo))
            {
                usuariosAux.push_back(temp);
            }
        }
    }

    fclose(archivo);
}

void crearMedidor()
{
    system("color 70");

    bool clienteEncontrado = false;
    int numMedidor = cliente.numeroMedidores;
    int i = 0, pos = 0;

    getSizeClientes();

    for (int j = 0; j < clientesAux.size(); j++)
    {
        if (strcmp(clientesAux[j].dui, cliente.dui) == 0)
        {
            clienteEncontrado = true;
            numMedidor = clientesAux[j].numeroMedidores;
            i = numMedidor;
            break;
        }
        pos++;
    }

    if (!clienteEncontrado)
    {
        cout << "\n Cliente nuevo. Creando medidor..." << endl;
        numMedidor = 0;
        i = numMedidor;
        cliente.numeroMedidores = 1;

        color(7, 0);
        strcpy(cliente.medidores[i].ID, "\nMD-0000-0000");
        cliente.medidores[i].consumo = 80;
        clientesAux.push_back(cliente);
    }
    else
    {
        cout << "\n Cliente ya existente. Agregando nuevo medidor..." << endl;
        clientesAux[pos].numeroMedidores++;
        numMedidor = clientesAux[pos].numeroMedidores;
    }

    color(7, 0);
    cout << "\n  Generando nuevo medidor..." << endl;
    cout << "\n  Numero de medidor: " << i + 1 << endl;
    cout << "\n  Cantidad de medidores ahora: " << clientesAux[pos].numeroMedidores << endl;

    generarMedidor(numMedidor, pos);

    cin.get();

    clientesAux[pos].medidores[i].consumo = 80;

    color(7, 0);
    cout << "\n ID de medidor generado correctamente";
    color(7, 2);
    cout << "\n ID: " << clientesAux[pos].medidores[i].ID << endl;
    color(7, 0);
    cout << "\n Consumo por defecto: " << clientesAux[pos].medidores[i].consumo << " kW" << endl;

    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "r+b");
    if (archivo != NULL)
    {
        fseek(archivo, 0, SEEK_SET);

        for (const Clientes &clienteTemp : clientesAux)
        {
            fwrite(&clienteTemp, sizeof(Clientes), 1, archivo);
        }

        color(7, 0);
        fclose(archivo);
        cout << GREEN << "\n Medidor guardado correctamente." << RESET << endl;
    }
    else
    {
        color(7, 0);
        cout << RED << "\n [ERROR]: No se pudo abrir el archivo para guardar los cambios." << RESET << endl;
    }
    clientesAux.clear();
}

void generarMedidor(int cantidad, int pos)
{
    system("color 70");
    string medidor;
    string municipio = string(clientesAux[pos].direccion.municipio);
    string dui = string(clientesAux[pos].dui);
    string completo;
    bool encontrado = false;
    bool existe = false;
    int pos1 = -1, pos2 = -1;

    for (int i = 0; i < municipio.length(); i++)
    {
        if (municipio[i] == ' ')
        {
            if (!encontrado)
            {
                encontrado = true;
                pos1 = i;
            }
            else if (encontrado && !existe)
            {
                existe = true;
                pos2 = i;
                break;
            }
        }
    }

    if (!encontrado)
    {
        municipio = municipio.substr(0, 4);
    }
    else if (!existe)
    {
        municipio = municipio.substr(0, 1) + municipio.substr(pos1 + 1, 3);
    }
    else
    {
        municipio = municipio.substr(0, 1) + municipio.substr(pos1 + 1, 1) + municipio.substr(pos2 + 1, 2);
    }

    for (int i = 0; i < municipio.length(); i++)
    {
        completo += toupper(municipio[i]);
    }

    const int numeroFinalMedidor = cantidad == 0 ? 1 : cantidad;

    const int indiceMedidorAgregarID = cantidad == 0 ? 0 : cantidad - 1;

    color(7, 0);
    medidor = "MD-" + completo + "-" + dui.substr(4, 9) + "-" + to_string(numeroFinalMedidor);

    strcpy(clientesAux[pos].medidores[indiceMedidorAgregarID].ID, medidor.c_str());
}

void verMedidores()
{
    system("cls");
    system("color 70");

    int fila = 6;
    Clientes cliente;

    FILE *archivo = fopen(RUTA_CLIENTE.c_str(), "rb");

    color(7, 0);

    if (archivo != NULL)
    {

        string texto = "LISTA DE MEDIDORES";
        system("color 70");
        cuadro(1, 1, 70, 3);
        CentrarTexto(texto, 2);

        gotoxy(1, 5);
        cout << "ID ";
        gotoxy(25, 5);
        cout << "Cliente  ";
        gotoxy(70, 5);
        cout << "Consumo (kW) ";

        while (fread(&cliente, sizeof(Clientes), 1, archivo))
        {
            for (int i = 0; i < cliente.numeroMedidores; i++)
            {
                gotoxy(1, fila);
                cout << cliente.medidores[i].ID;
                gotoxy(25, fila);
                cout << cliente.nombres << " " << cliente.apellidos;
                gotoxy(70, fila);

                if (cliente.medidores[i].consumo > 80)
                {
                    cliente.medidores[i].consumo -= 80;
                }

                cout << cliente.medidores[i].consumo << "kW";

                fila++;
            }
        }
    }
    else
    {
        color(7, 0);
        cout << RED << "\n[ERROR]: Creacion de archivo invalida." << RESET;
    }

    fclose(archivo);

    cout << "\n\n";
    system("pause");
}