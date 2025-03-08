// Cuentasbancarias.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class CuentaBancaria {
private:
    int numeroCuenta;
    string propietario;
    double saldo;
    bool activa;
    bool bloqueada;
    int intentosFallidos;

public:
    CuentaBancaria(int num, string nombre, double saldoInicial)
        : numeroCuenta(num), propietario(nombre), saldo(saldoInicial), activa(true), bloqueada(false), intentosFallidos(0) {
    }

    void depositar(double cantidad) {
        if (!activa) {
            cout << "Cuenta inactiva. No se pueden realizar depositos.\n";
            return;
        }
        if (bloqueada) {
            cout << "Cuenta bloqueada. No se pueden realizar operaciones.\n";
            return;
        }
        saldo += cantidad;
        cout << "Deposito exitoso. Nuevo saldo: " << saldo << "\n";
    }

    void retirar(double cantidad) {
        if (bloqueada) {
            cout << "Cuenta bloqueada. No se pueden realizar operaciones.\n";
            return;
        }
        if (cantidad > saldo) {
            cout << "Saldo insuficiente. Retiro fallido.\n";
            intentosFallidos++;
            if (intentosFallidos >= 3) {
                bloqueada = true;
                cout << "Cuenta bloqueada por intentos fallidos.\n";
            }
            return;
        }
        saldo -= cantidad;
        intentosFallidos = 0;
        cout << "Retiro exitoso. Nuevo saldo: " << saldo << "\n";
        if (saldo < 50) {
            cout << "Advertencia: Saldo bajo.\n";
        }
    }

    void bloquearCuenta() {
        bloqueada = true;
        cout << "Cuenta " << numeroCuenta << " bloqueada manualmente.\n";
    }

    void mostrarInfo() const {
        cout << "Cuenta #: " << numeroCuenta << " | Propietario: " << propietario
            << " | Saldo: " << saldo
            << " | Estado: " << (activa ? "Activa" : "Inactiva")
            << " | " << (bloqueada ? "Bloqueada" : "Operativa") << "\n";
    }

    int getNumeroCuenta() const {
        return numeroCuenta;
    }
};

int main() {
    vector<CuentaBancaria> cuentas;
    int opcion, numCuenta;
    double cantidad;

    do {
        if (cuentas.empty()) {
            cout << "No hay cuentas registradas. Agregue una cuenta primero.\n";
            int nuevoNumero;
            string nombrePropietario;
            double saldoInicial;
            cout << "Ingrese el numero de cuenta: ";
            cin >> nuevoNumero;
            cout << "Ingrese el nombre del propietario: ";
            cin.ignore();
            getline(cin, nombrePropietario);
            cout << "Ingrese el saldo inicial: ";
            cin >> saldoInicial;
            cuentas.emplace_back(nuevoNumero, nombrePropietario, saldoInicial);
            cout << "Cuenta " << nuevoNumero << " agregada exitosamente.\n";
        }

        cout << "\n--- Menu de Gestion de Cuentas Bancarias ---\n";
        cout << "1. Agregar nueva cuenta\n2. Depositar\n3. Retirar\n4. Mostrar informacion de cuenta\n5. Bloquear cuenta\n6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 6) break;

        if (opcion == 1) {
            int nuevoNumero;
            string nombrePropietario;
            double saldoInicial;
            cout << "Ingrese el numero de cuenta: ";
            cin >> nuevoNumero;
            cout << "Ingrese el nombre del propietario: ";
            cin.ignore();
            getline(cin, nombrePropietario);
            cout << "Ingrese el saldo inicial: ";
            cin >> saldoInicial;
            cuentas.emplace_back(nuevoNumero, nombrePropietario, saldoInicial);
            cout << "Cuenta " << nuevoNumero << " agregada exitosamente.\n";
            continue;
        }

        cout << "Ingrese el numero de cuenta: ";
        cin >> numCuenta;
        bool encontrada = false;
        for (auto& cuenta : cuentas) {
            if (cuenta.getNumeroCuenta() == numCuenta) {
                encontrada = true;
                switch (opcion) {
                case 2:
                    cout << "Ingrese la cantidad a depositar: ";
                    cin >> cantidad;
                    cuenta.depositar(cantidad);
                    break;
                case 3:
                    cout << "Ingrese la cantidad a retirar: ";
                    cin >> cantidad;
                    cuenta.retirar(cantidad);
                    break;
                case 4:
                    cuenta.mostrarInfo();
                    break;
                case 5:
                    cuenta.bloquearCuenta();
                    break;
                default:
                    cout << "Opcion no valida.\n";
                }
                break;
            }
        }
        if (!encontrada) {
            cout << "Numero de cuenta no encontrado.\n";
        }
    } while (true);

    return 0;
}





// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
