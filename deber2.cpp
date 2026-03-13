#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// Función para validar que el código de divisa tenga exactamente 3 letras
bool codigoValido(string codigo) {
    if (codigo.length() != 3) {
        return false;
    }

    for (char c : codigo) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

// Función sencilla para mostrar números con separador de miles
string formatearMiles(double valor) {
    string texto = to_string((long long)(valor * 100));
    string resultado = "";
    int contador = 0;

    for (int i = texto.length() - 3; i >= 0; i--) {
        resultado = texto[i] + resultado;
        contador++;

        if (contador == 3 && i != 0) {
            resultado = "," + resultado;
            contador = 0;
        }
    }

    resultado.insert(resultado.length() - 2, ".");
    return resultado;
}

int main() {
    string base, cotizada, timestamp;
    double tasa, montoBase, montoConvertido;
    char continuar;

    do {
        // Captura de divisas
        do {
            cout << "Ingrese la divisa base (3 letras, ej: USD): ";
            cin >> base;
        } while (!codigoValido(base));

        do {
            cout << "Ingrese la divisa cotizada (3 letras, ej: EUR): ";
            cin >> cotizada;
        } while (!codigoValido(cotizada));

        cout << "Par seleccionado: " << base << "/" << cotizada << endl;

        // Captura de tasa
        do {
            cout << "Ingrese la tasa de cambio (mayor que 0): ";
            cin >> tasa;
        } while (tasa <= 0);

        // Captura de monto
        do {
            cout << "Ingrese el monto base en " << base << ": ";
            cin >> montoBase;
        } while (montoBase <= 0);

        montoConvertido = montoBase * tasa;

        cin.ignore();
        cout << "Ingrese el timestamp del snapshot: ";
        getline(cin, timestamp);

        // Reporte final
        cout << "\n================ MARKET SNAPSHOT ================\n";
        cout << "Par de divisas   : " << base << "/" << cotizada << endl;
        cout << "Timestamp       : " << timestamp << endl;

        cout << fixed << setprecision(5);
        cout << "Tasa de cambio  : 1 " << base << " = " << tasa << " " << cotizada << endl;

        cout << setprecision(2);
        cout << "Monto base      : " << formatearMiles(montoBase) << " " << base << endl;
        cout << "Monto convertido: " << formatearMiles(montoConvertido) << " " << cotizada << endl;
        cout << "=================================================\n";

        cout << "\nDesea realizar otra conversion? (s/n): ";
        cin >> continuar;

    } while (continuar == 's' || continuar == 'S');

    cout << "Programa finalizado.\n";
    return 0;
}