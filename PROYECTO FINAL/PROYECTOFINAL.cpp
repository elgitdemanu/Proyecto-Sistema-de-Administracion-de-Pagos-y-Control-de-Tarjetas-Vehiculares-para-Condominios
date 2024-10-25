#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>  // Para FILE y funciones de archivos
#include <cstdlib> // Para exit()
#include <windows.h> // Mensaje de salida 
#include <ctime>    // Para manejar fecha y hora

using namespace std;

// Estructura para almacenar los datos de un vehículo
struct Vehiculo {
    char placa[15];
    char marca[20];
    char modelo[20];
    char color[15];
    char propietarioVehiculo[30];
    char tipoVehiculo[20];
    bool vehiculoActivo;
};

// Estructura para almacenar los datos de una casa
struct Casa {
    int idCasa;
    char sector[30];
    char propietario[30];
    char direccion[30];
    char telefono[15];
    Vehiculo vehiculo; // Vehículo asociado a la casa
    bool activo;
};

// Estructura para almacenar datos de pagos
struct Pago {
    int numeroCasa;
    float monto;
    char fecha[11];      // Formato: AÑO-MES-DIA
    char metodoPago[20];
    bool pagado;
    char descripcion[50];
};

// Estructura para almacenar datos de usuarios (incluyendo contraseñas)
struct Usuario {
    string username;
    string password;
};

// Variable global para almacenar el tipo de usuario
string tipoUsuario;

// Función para cambiar el color del texto en la consola
void cambiarColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Función para validar usuario
bool validarUsuario(Usuario usuarios[], int n, string username, string password) {
    for (int i = 0; i < n; i++) {
        if (usuarios[i].username == username && usuarios[i].password == password) {
            tipoUsuario = username; // Guardamos el tipo de usuario
            return true;
        }
    }
    return false;
}

void mostrarMenu() {
    // Obtener la fecha y hora actual
    time_t ahora = time(0);
    tm *tiempo_local = localtime(&ahora);
    char buffer[80];

    // Título de bienvenida
    cout << "===================================================\n";
    cout << "      Bienvenido al Sistema de Gestion     \n";
    cout << "===================================================\n\n";

    // Mostrar fecha
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", tiempo_local);
    cout << "Fecha: " << buffer << endl;

    // Mostrar hora
    strftime(buffer, sizeof(buffer), "%H:%M:%S", tiempo_local);
    cout << "Hora: " << buffer << endl << endl;

    cout << "----- Menu Principal -----\n";
    cout << "1. Registrar casa y sector\n";
    cout << "2. Modificar casa\n";
    cout << "3. Registrar pagos\n";
    cout << "4. Consultar estado de pagos\n";
    cout << "5. Generar reporte de casas\n";
    cout << "6. Generar reporte de pagos\n";
    cout << "7. Ver datos de casas\n";
    cout << "8. Ver datos de pagos\n";
    cout << "9. Salir\n";
    cout << "---------------------------\n";
}

// Función para mostrar datos de casas
void mostrarDatosCasas() {
    FILE *archivo = fopen("casas.txt", "rb"); // Abrir en modo lectura binaria
    if (!archivo) {
        cout << "Error al abrir el archivo de casas.\n";
        return;
    }

    Casa casa;
    cambiarColor(10); // Cambiar a verde
    cout << "Datos de las casas:\n";
    cout << "-------------------\n";
    while (fread(&casa, sizeof(Casa), 1, archivo) == 1) {
        cout << "ID: " << casa.idCasa << ", Sector: " << casa.sector 
             << ", Propietario: " << casa.propietario 
             << ", Direccion: " << casa.direccion 
             << ", Telefono: " << casa.telefono 
             << ", Vehiculo - Placa: " << casa.vehiculo.placa 
             << ", Marca: " << casa.vehiculo.marca 
             << ", Modelo: " << casa.vehiculo.modelo 
             << ", Color: " << casa.vehiculo.color 
             << ", Estado: " << (casa.activo ? "Activa" : "Inactiva") << endl;
    }
    fclose(archivo);
    cambiarColor(15); // Cambiar a blanco
}

// Función para mostrar datos de pagos
void mostrarDatosPagos() {
    FILE *archivo = fopen("pagos.txt", "rb"); // Abrir en modo lectura binaria
    if (!archivo) {
        cout << "Error al abrir el archivo de pagos.\n";
        return;
    }

    Pago pago;
    cambiarColor(10); // Cambiar a verde
    cout << "Datos de los pagos:\n";
    cout << "-------------------\n";
    while (fread(&pago, sizeof(Pago), 1, archivo) == 1) {
        cout << "Casa ID: " << pago.numeroCasa << ", Monto: " << pago.monto 
             << ", Fecha: " << pago.fecha 
             << ", Metodo: " << pago.metodoPago 
             << ", Estado: " << (pago.pagado ? "Pagado" : "No pagado") 
             << ", Descripcion: " << pago.descripcion << endl;
    }
    fclose(archivo);
    cambiarColor(15); // Cambiar a blanco
}

// Función para registrar una casa
void registrarCasa() {
    Casa casa;
    FILE *archivo = fopen("casas.txt", "ab"); // Abrir en modo append binario
    if (!archivo) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    cout << "Ingrese ID de la casa: ";
    cin >> casa.idCasa;
    cin.ignore();  // Limpiar el buffer después de un input de tipo entero

    cout << "Ingrese sector de la casa: ";
    cin.getline(casa.sector, 30);
    cout << "Ingrese nombre del propietario: ";
    cin.getline(casa.propietario, 30);
    cout << "Ingrese la dirección: ";
    cin.getline(casa.direccion, 30);
    cout << "Ingrese el numero de telefono: ";
    cin.getline(casa.telefono, 15);

    // Captura de datos del vehículo
    cout << "Ingrese placa del vehiculo: ";
    cin.getline(casa.vehiculo.placa, 15);
    cout << "Ingrese marca del vehiculo: ";
    cin.getline(casa.vehiculo.marca, 20);
    cout << "Ingrese modelo del vehiculo: ";
    cin.getline(casa.vehiculo.modelo, 20);
    cout << "Ingrese color del vehiculo: ";
    cin.getline(casa.vehiculo.color, 15);

    casa.vehiculo.vehiculoActivo = true;  // Vehículo activo por defecto al registrar
    casa.activo = true; // Casa activa por defecto al registrar

    // Guardar los datos de la casa en el archivo
    fwrite(&casa, sizeof(Casa), 1, archivo);
    fclose(archivo);

    cout << "Casa registrada exitosamente.\n";
}

// Función para modificar una casa en casas.txt
void modificarCasa(int idCasa) {
    FILE *archivo = fopen("casas.txt", "r+b"); // Abrir en modo lectura y escritura binaria
    if (!archivo) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    Casa casa;
    long posicion;
    bool encontrado = false;

    // Buscar el registro
    while (fread(&casa, sizeof(Casa), 1, archivo) == 1) {
        if (casa.idCasa == idCasa) {
            encontrado = true;
            posicion = ftell(archivo) - sizeof(Casa); // Guardar la posición del registro encontrado

            // Solicitar nueva información
            cout << "Modificar sector (actual: " << casa.sector << "): ";
            cin.ignore();
            cin.getline(casa.sector, 30);
            cout << "Modificar propietario (actual: " << casa.propietario << "): ";
            cin.getline(casa.propietario, 30);
            cout << "Modificar direccion (actual: " << casa.direccion << " ): ";
            cin.getline(casa.direccion, 30);
            cout << "Modificar telefono (actual: " << casa.telefono << "): ";
            cin.getline(casa.telefono, 15);

            // Modificar datos del vehículo
            cout << "Modificar placa del vehiculo (actual: " << casa.vehiculo.placa << "): ";
            cin.getline(casa.vehiculo.placa, 15);
            cout << "Modificar marca del vehiculo (actual: " << casa.vehiculo.marca << "): ";
            cin.getline(casa.vehiculo.marca, 20);
            cout << "Modificar modelo del vehiculo (actual: " << casa.vehiculo.modelo << "): ";
            cin.getline(casa.vehiculo.modelo, 20);
            cout << "Modificar color del vehiculo (actual: " << casa.vehiculo.color << "): ";
            cin.getline(casa.vehiculo.color, 15);

            cout << "Modificar estado de la casa (actual: " << (casa.activo ? "Activa" : "Inactiva") << "): ";
            char estado[10];
            cin.getline(estado, 10);
            casa.activo = (strcmp(estado, "Activa") == 0); // Comparar cadena para establecer el estado

            // Volver a la posición y sobrescribir
            fseek(archivo, posicion, SEEK_SET);
            fwrite(&casa, sizeof(Casa), 1, archivo);
            cout << "Casa modificada exitosamente.\n";
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontro la casa con ID " << idCasa << ".\n";
    }

    fclose(archivo);
}

// Función para registrar pagos
void registrarPago() {
    Pago pago;
    FILE *archivo = fopen("pagos.txt", "ab"); // Abrir en modo append binario
    if (!archivo) {
        cout << "Error al abrir el archivo de pagos.\n";
        return;
    }

    cout << "Ingrese numero de casa: ";
    cin >> pago.numeroCasa;

    cout << "Ingrese monto del pago: ";
    cin >> pago.monto;
    cin.ignore(); // Limpiar el buffer después de un input de tipo float

    cout << "Ingrese fecha del pago (Año-Mes-Dia): ";
    cin.getline(pago.fecha, 11);

    cout << "Ingrese metodo de pago: ";
    cin.getline(pago.metodoPago, 20);

    cout << "¿El pago está realizado? (1 para si, 0 para no): ";
    int estado;
    cin >> estado;
    pago.pagado = estado == 1;

    cout << "Ingrese descripcion: ";
    cin.ignore(); // Limpiar el buffer antes de leer descripción
    cin.getline(pago.descripcion, 50);

    // Guardar los datos del pago en el archivo
    fwrite(&pago, sizeof(Pago), 1, archivo);
    fclose(archivo);

    cout << "Pago registrado exitosamente.\n";
}

// Función para consultar estado de pagos (lógica a implementar)
void consultarPagos() {
    // Implementar la consulta de pagos
    cout << "Funcion de consulta de pagos no implementada.\n";
}

// Función para generar reporte de casas en archivo txt
void generarReporteCasas() {
    FILE *reporte = fopen("reporte_casas.txt", "w");  // Abrir archivo de reporte de casas en modo escritura
    if (!reporte) {
        cout << "Error al abrir el archivo de reporte.\n";
        return;
    }

    fprintf(reporte, "Reporte de Casas:\n");
    fprintf(reporte, "-----------------\n");

    // Leer archivo de casas y generar reporte
    FILE *archivoCasas = fopen("casas.txt", "rb"); // Abrir en modo lectura binaria
    if (!archivoCasas) {
        cout << "Error al abrir el archivo de casas.\n";
        fclose(reporte);
        return;
    }

    Casa casa;
    while (fread(&casa, sizeof(Casa), 1, archivoCasas) == 1) {
        fprintf(reporte, "ID: %d, Sector: %s, Propietario: %s, Vehiculo - Placa: %s, Marca: %s, Modelo: %s, Color: %s\n",
            casa.idCasa, casa.sector, casa.propietario, casa.vehiculo.placa,
            casa.vehiculo.marca, casa.vehiculo.modelo, casa.vehiculo.color);
    }
    fclose (archivoCasas);

    fclose(reporte);
    cout << "Reporte de casas generado exitosamente.\n";
}

// Función para generar reporte de pagos en archivo txt
void generarReportePagos() {
    FILE *reporte = fopen("reporte_pagos.txt", "w");  // Abrir archivo de reporte de pagos en modo escritura
    if (!reporte) {
        cout << "Error al abrir el archivo de reporte.\n";
        return;
    }

    fprintf(reporte, "Reporte de Pagos:\n");
    fprintf(reporte, "-----------------\n");

    // Leer archivo de pagos y generar reporte
    FILE *archivoPagos = fopen("pagos.txt", "rb"); // Abrir en modo lectura binaria
    if (!archivoPagos) {
        cout << "Error al abrir el archivo de pagos.\n";
        fclose(reporte);
        return;
    }

    Pago pago;
    while (fread(&pago, sizeof(Pago), 1, archivoPagos) == 1) {
        fprintf(reporte, "Casa ID: %d, Monto: %.2f, Fecha: %s, Metodo: %s, Estado: %s, Descripcion: %s\n",
            pago.numeroCasa, pago.monto, pago.fecha, pago.metodoPago,
            (pago.pagado ? "Pagado" : "No pagado"), pago.descripcion);
    }
    fclose(archivoPagos);

    fclose(reporte);
    cout << "Reporte de pagos generado exitosamente.\n";
}

// Función principal
int main() {
    Usuario usuarios[2] = {{"admin", "admin123"}, {"caja", "caja123"}};
    string username, password;

    // Inicio de sesión
    cout << "Ingrese su nombre de usuario : ";
    cin >> username;
    cout << "Ingrese su contraseña: ";
    cin >> password;

    // Validar usuario
    if (!validarUsuario(usuarios, 2, username, password)) {
        cout << "Usuario o contraseña incorrectos.\n";
        exit(1);
    }  
    system("cls"); // Limpiar la pantalla

    int opcion;
    do {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarCasa();
                break;
            case 2:
                if (tipoUsuario == "caja") {
                    cout << "Esta opcion no está disponible para el usuario caja.\n";
                } else {
                    int idCasa;
                    cout << "Ingrese ID de la casa a modificar: ";
                    cin >> idCasa;
                    modificarCasa(idCasa);
                }
                break;
            case 3:
                registrarPago();
                break;
            case 4:
                consultarPagos();
                break;
            case 5:
                generarReporteCasas();
                break;
            case 6:
                generarReportePagos();
                break;
            case 7:
                mostrarDatosCasas();
                break;
            case 8:
                mostrarDatosPagos();
                break;
			case 9: {
			    const string mensaje = "Saliendo del programa";
			    const int ancho_pantalla = 80; // Asume un ancho de pantalla de 80 caracteres
			    
			    for (int i = ancho_pantalla; i >= -static_cast<int>(mensaje.length()); i--) {
			        system("cls"); // Limpia la pantalla
			        for (int j = 0; j < i; j++) {
			            cout << " ";
			        }
			        cout << mensaje;
			        Sleep(50); // Pausa de 50 milisegundos
			    }
			    cout << endl;
			    break;
			}
            default:
                cout << "Opción no valida. Intente nuevamente.\n";
        }
    } while (opcion != 9);

    return 0;
}
