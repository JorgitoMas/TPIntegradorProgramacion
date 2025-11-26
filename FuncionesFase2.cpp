#include <iostream>
#include <cstdlib>
#include "rlutil.h"
#include "FuncionesFase2.h"
#include "FuncionesFase1.h" // para usar tirarNDados(), pausarMilisegundos(), etc.

using namespace std;
//Principal fase2

void faseBusquedaTesoros(
  string j1, string j2,
  int &oroJ1, int &oroJ2,
  int &llaveGJ1, int &llaveGJ2,
  int &cofresJ1, int &cofresJ2,
  int &usoLGJ1, int &usoLGJ2,
  int &vendEJ1, int &vendRJ1, int &vendDJ1,
  int &vendEJ2, int &vendRJ2, int &vendDJ2
) {
    rlutil::cls();
    rlutil::setColor(rlutil::WHITE);
    cout << "=== Fase 2: Busqueda de Tesoros ===\n\n";
    cout << "1 = Llave Madera\n";
    cout << "2 = Llave Piedra\n";
    cout << "3 = Llave Metal\n";
    cout << "4 = Esmeralda\n";
    cout << "5 = Rubi\n";
    cout << "6 = Diamante \n\n";

    for (int ronda = 1; ronda <= 3; ronda++) {
        cout << "RONDA " << ronda << " - Cofre de " << nombreCofre(ronda) << "\n";
        cout << "Oro: " << j1 << "=" << oroJ1 << " | " << j2 << "=" << oroJ2 << "\n\n";

        // Turno jugador 1
        turnoRondaJugador(j1, ronda,
                          oroJ1, llaveGJ1, cofresJ1, usoLGJ1,
                          vendEJ1, vendRJ1, vendDJ1,
                          oroJ1, oroJ2);
        pausaSiguiente("Presione una tecla para continuar con el turno del siguiente jugador...");


        // Turno jugador 2
        rlutil::cls();
        turnoRondaJugador(j2, ronda,
                          oroJ2, llaveGJ2, cofresJ2, usoLGJ2,
                          vendEJ2, vendRJ2, vendDJ2,
                          oroJ1, oroJ2);
        pausaSiguiente("Presione una tecla para continuar...");

        rlutil::cls();
        cout << "Fin de la ronda " << ronda << " (" << nombreCofre(ronda) << ")\n";
        cout << "Oro: " << j1 << "=" << oroJ1 << " | " << j2 << "=" << oroJ2 << "\n";
        pausaSiguiente("Presione una tecla para pasar a la siguiente ronda...");
        rlutil::cls();
    }

    cout << "Fase de Busqueda terminada.\n";
    pausaSiguiente("Presione una tecla para continuar a la Fase Final...");
}

//por jugador
void turnoRondaJugador(
  string nombre, int ronda,
  int &oro, int &llaveGuardada,
  int &cofresAbiertos, int &usoLlaveGuardada,
  int &vendE, int &vendR, int &vendD,
  int oroJ1Vis, int oroJ2Vis) {
    int tirada[5];
    tirarNDados(tirada, 5);

    int conteo[7] = {0};
    contarCaras5(tirada, conteo);

    pausarMilisegundos(600);
    mostrarEstadoJugadorF2(nombre, ronda, oroJ1Vis, oroJ2Vis, llaveGuardada, tirada, conteo);

    bool abre = puedeAbrirCofre(ronda, conteo, llaveGuardada);
    pausarMilisegundos(350);

    if (abre) {
        pausarMilisegundos(300);
        cout << "\nPuede abrir el cofre con llave " << nombreCofre(ronda) << ".\n";

        // Consumimos la llave (de tirada si hay, o la guardada)
        consumirLlaveApertura(ronda, conteo, llaveGuardada, usoLlaveGuardada);

        // Vender gemas y llaves sobrantes
        int oroG = oroPorGemas(conteo, vendE, vendR, vendD);
        int oroL = oroPorLlavesRestantes(conteo);
        int total = oroG + oroL;
        oro += total;
        cofresAbiertos++;

        pausarMilisegundos(300);
        cout << "Venta de gemas: +" << oroG << " oro\n";
        pausarMilisegundos(300);
        cout << "Venta de llaves sobrantes: +" << oroL << " oro\n";
        pausarMilisegundos(300);
        cout << "Ganancia total de la ronda: +" << total << " oro\n";
    } else {
        pausarMilisegundos(300);
        cout << "\nNO puede abrir el cofre.\n";

        int totalLlaves = conteo[1] + conteo[2] + conteo[3];

        if(totalLlaves == 0){
            pausarMilisegundos(300);
            cout << "No obtuvo ninguna llave en esta tirada.\n";
            pausarMilisegundos(300);
            cout << "No hay llaves para vender ni para guardar.\n";
            pausarMilisegundos(300);
            cout << "Ganancia de la ronda: 0 oro.\n";

        }else{
            pausarMilisegundos(300);
            cout << "Elija: (V)ender todas las llaves  |  (G)uardar una llave para proximas rondas\n";
            char op = leerOpcionVG();

            if (op == 'V') {
                int oroL = oroPorLlavesRestantes(conteo);
                oro += oroL;
                cout << "Vendio llaves por +" << oroL << " oro.\n";
            } else { // 'G'
                int tipo = elegirLlaveAGuardar(conteo);
                if (tipo == 0) {
                    cout << "No tiene llaves en la tirada para guardar. No se gana oro.\n";
                } else {
                    // Si ya tenia una, se reemplaza (la anterior se pierde sin vender)
                    llaveGuardada = tipo;
                    cout << "Guarda una llave de " << nombreCofre(tipo) << " para proximas rondas.\n";
                }
            }
        }

    }

    cout << "Oro actual de " << nombre << ": " << oro << "\n";
}


void contarCaras5(const int tirada[5], int conteo[7]) {
    for (int f = 1; f <= 6; f++) conteo[f] = 0;
    for (int i = 0; i < 5; i++) {
        int cara = tirada[i];
        if (cara >= 1 && cara <= 6) conteo[cara]++;
    }
}

bool puedeAbrirCofre(int ronda, const int conteo[7], int llaveGuardada) {
    // ronda 1-> llave 1 (madera) ; 2-> piedra ; 3-> metal
    if (ronda < 1 || ronda > 3) return false;
    return (conteo[ronda] > 0) || (llaveGuardada == ronda);
}

void consumirLlaveApertura(int ronda, int conteo[7], int &llaveGuardada, int &usoLlaveGuardada) {
    // Si tengo llave de la tirada, consumo una de esa cara; sino, uso la guardada.
    if (conteo[ronda] > 0) {
        conteo[ronda]--; // se consume de la tirada
    } else if (llaveGuardada == ronda) {
        usoLlaveGuardada = 1;
        llaveGuardada = 0; // se consumio la guardada
    }
}

int valorLlave(int tipo) {
    if (tipo == 1) return 10;   // madera
    if (tipo == 2) return 20;   // piedra
    if (tipo == 3) return 30;   // metal
    return 0;
}

int valorGema(int tipo) {
    if (tipo == 4) return 40;   // esmeraldas
    if (tipo == 5) return 50;   // rubies
    if (tipo == 6) return 60;   // diamantes
    return 0;
}

int oroPorLlavesRestantes(const int conteo[7]) {
    int sum = 0;
    for (int k = 1; k <= 3; k++) {
        sum += conteo[k] * valorLlave(k);
    }
    return sum;
}

int oroPorGemas(const int conteo[7], int &vendE, int &vendR, int &vendD) {
    int sum = 0;
    if (conteo[4] > 0) vendE = 1;
    if (conteo[5] > 0) vendR = 1;
    if (conteo[6] > 0) vendD = 1;

    sum += conteo[4] * valorGema(4);
    sum += conteo[5] * valorGema(5);
    sum += conteo[6] * valorGema(6);

    return sum;
}


// interfaz

const char* nombreCofre(int ronda) {
    if (ronda == 1) return "Madera";
    if (ronda == 2) return "Piedra";
    if (ronda == 3) return "Metal";
    return "(desconocido)";
}

void mostrarTirada5(const int tirada[5]) {
    cout << "[";
    for (int i = 0; i < 5; i++) {
        if (i > 0) cout << ", ";
        cout << tirada[i];
    }
    cout << "]";
}

void mostrarConteoLlaves(const int conteo[7]) {
    pausarMilisegundos(300);
    cout << "Madera x" << conteo[1] << ", \n";
         pausarMilisegundos(300);
    cout << "Piedra x" << conteo[2] << ", \n";
         pausarMilisegundos(300);
    cout << "Metal x"  << conteo[3] << "\n\n";
         pausarMilisegundos(300);
}

void mostrarConteoGemas(const int conteo[7]) {
    pausarMilisegundos(300);
    cout << "Esmeraldas x" << conteo[4] << ",\n";
         pausarMilisegundos(300);
    cout << "Rubies x"     << conteo[5] << ",\n";
         pausarMilisegundos(300);
    cout << "Diamantes x"  << conteo[6] << "\n\n";
         pausarMilisegundos(300);
}

void mostrarEstadoJugadorF2(
  string nombre, int ronda, int oroJ1, int oroJ2,
  int llaveGuardada, const int tirada[5], const int conteo[7]
) {
    rlutil::setColor(rlutil::WHITE);
    cout << "Fase: Busqueda | Ronda " << ronda
         << " (Cofre de " << nombreCofre(ronda) << ") | Turno: " << nombre << "\n";
    cout << "Oro Jugador 1= " << oroJ1 << "\n";
    cout << "Oro Jugador 2= " << oroJ2 << "\n\n";

    cout << nombre << " tira";
    pausarMilisegundos(300);
    cout << ".";
    pausarMilisegundos(300);
    cout << ".";
    pausarMilisegundos(300);
    cout << ". ";
    cout << "   ";
    mostrarTirada5(tirada);
    cout << "\n\n";
    pausarMilisegundos(400);
    cout << "Llaves obtenidas:\n\n";
    pausarMilisegundos(300);
    mostrarConteoLlaves(conteo);
    cout << "\n";
    pausarMilisegundos(300);
    cout << "Gemas obtenidas:\n\n";
    pausarMilisegundos(300);
    mostrarConteoGemas(conteo);
    cout << "\n";

    pausarMilisegundos(400);
    cout << "Llave guardada actual: ";
    if (llaveGuardada == 0) cout << "(ninguna)\n";
    else cout << nombreCofre(llaveGuardada) << "\n\n";
}

char leerOpcionVG() {
    while (true) {
        cout << "> ";
        char c; cin >> c;
        c = (char)toupper((unsigned char)c);
        if (c == 'V' || c == 'G') return c;
        cout << "Opcion invalida. Ingrese V o G.\n";
    }
}

int elegirLlaveAGuardar(const int conteo[7]) {
    bool hayLlave = (conteo[1] > 0) || (conteo[2] > 0) || (conteo[3] > 0);
    if (!hayLlave) return 0;

    cout << "Seleccione llave a guardar: ";
    cout << "[1] Madera" << (conteo[1] > 0 ? "" : " (no disponible)") << "  ";
    cout << "[2] Piedra" << (conteo[2] > 0 ? "" : " (no disponible)") << "  ";
    cout << "[3] Metal"  << (conteo[3] > 0 ? "" : " (no disponible)") << "\n";

    while (true) {
        cout << "> ";
        int t; cin >> t;
        if (t >= 1 && t <= 3 && conteo[t] > 0) return t;
        cout << "Opcion invalida. Elija 1/2/3 y que exista en la tirada.\n";
    }
}

void aplicarDecisionNoAbre(
  char opcionVG, const int conteo[7],
  int &oro, int &llaveGuardada
) {
    if (opcionVG == 'V') {
        int oroL = oroPorLlavesRestantes(conteo);
        oro += oroL;
        pausarMilisegundos(300);
        cout << "Vendio llaves por +" << oroL << " oro.\n";
        return;
    }

    // opcion 'G'
    int tipo = elegirLlaveAGuardar(conteo);
    if (tipo == 0) {
        pausarMilisegundos(300);
        cout << "No hay llaves para guardar. No se gana oro.\n";
    } else {
        llaveGuardada = tipo; // si ya habia, se reemplaza (la anterior se pierde)
        pausarMilisegundos(300);
        cout << "Guarda llave de " << nombreCofre(tipo) << ".\n";
    }
}

void pausaSiguiente(const char* msg) {
    cout << "\n" << msg;
    rlutil::anykey();
}
