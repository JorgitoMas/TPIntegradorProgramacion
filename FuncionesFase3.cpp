/* Enunciado

*/

#include <iostream>
#include <fstream>
#include "rlutil.h"
#include "FuncionesFase3.h"
#include "FuncionesFase2.h"
#include "FuncionesFase1.h"
using namespace std;

//helpers internos

static int paquetesDe30(int oro) { return oro / 30; }
static int monedasSueltas(int oro) { return oro % 30; }

static int bonusMasMonedasFaseInicial(int oroF1J1, int oroF1J2, int soyJ1) {
    // Si empatan, AMBOS ganan +100
    if (oroF1J1 == oroF1J2) return 100;
    // Si no empatan, solo gana el que tiene m s
    if (soyJ1) return (oroF1J1 > oroF1J2) ? 100 : 0;
    else       return (oroF1J2 > oroF1J1) ? 100 : 0;
}

static int bonusAbrioTresCofres(int cofresAbiertos) {
    return (cofresAbiertos >= 3) ? 200 : 0;
}

static int bonusVendioTresTiposGemas(int vendE, int vendR, int vendD) {
    return (vendE && vendR && vendD) ? 200 : 0;
}

static int bonusAbrioConLlaveGuardada(int usoLlaveGuardada) {
    return (usoLlaveGuardada ? 300 : 0);
}

static void imprimirDesgloseJugador(
    const string &nombre, int oro, int oroFaseInicial,
    int cofresAbiertos, int usoLlaveGuardada,
    int vendE, int vendR, int vendD,
    int oroF1J1, int oroF1J2, int soyJ1,
    int &pdvOut
) {
    rlutil::setColor(rlutil::WHITE);
    cout << "------------------------------------------------------------\n";
    cout << nombre << " (" << oro << " monedas de oro)\n";

    int pdv = 0;

    // +100 M s monedas Fase Inicial (ambos si empatan)
    int mfi = bonusMasMonedasFaseInicial(oroF1J1, oroF1J2, soyJ1);
    pdv += mfi;
    cout << "+ " << mfi << " (M s monedas en Fase Inicial)\n";

    // Paquetes de 30 y sueltas
    int packs = paquetesDe30(oro);
    int sueltas = monedasSueltas(oro);
    int pdvPacks = packs * 50;
    int pdvSueltas = sueltas * 1;
    pdv += pdvPacks + pdvSueltas;

    cout << "+ " << pdvPacks << " (Paquetes de 30): " << packs
         << " paquetes y " << sueltas << " sueltas\n";
    cout << "+ " << pdvSueltas << " (Monedas sueltas)\n";

    // +200 Abrir todos los cofres
    int b3c = bonusAbrioTresCofres(cofresAbiertos);
    pdv += b3c;
    cout << "+ " << b3c << " (Abrio 3 cofres)\n";

    // +200 Vendi¢ los 3 tipos de gemas
    int b3g = bonusVendioTresTiposGemas(vendE, vendR, vendD);
    pdv += b3g;
    cout << "+ " << b3g << " (Vendio 3 tipos de gemas)\n";

    // +300 Abri¢ con llave guardada
    int blg = bonusAbrioConLlaveGuardada(usoLlaveGuardada);
    pdv += blg;
    cout << "+ " << blg << " (Abri¢ cofre con llave guardada)\n";

    cout << "= TOTAL: " << pdv << " PDV\n";
    pdvOut = pdv;
}

// Fase 3

void faseFinalPDV(
    string nombreJ1, string nombreJ2,
    int oroJ1, int oroJ2,
    int oroFaseInicialJ1, int oroFaseInicialJ2,
    int cofresAbiertosJ1, int cofresAbiertosJ2,
    int usoLlaveGuardadaJ1, int usoLlaveGuardadaJ2,
    int vendioEJ1, int vendioRJ1, int vendioDJ1,
    int vendioEJ2, int vendioRJ2, int vendioDJ2
) {
    rlutil::cls();
    rlutil::setColor(rlutil::WHITE);
    cout << "Fase Final: Calculo de Puntos de Victoria\n\n";

    int pdvJ1 = 0, pdvJ2 = 0;

    imprimirDesgloseJugador(
        nombreJ1, oroJ1, oroFaseInicialJ1,
        cofresAbiertosJ1, usoLlaveGuardadaJ1,
        vendioEJ1, vendioRJ1, vendioDJ1,
        oroFaseInicialJ1, oroFaseInicialJ2, /*soyJ1=*/1,
        pdvJ1
    );

    cout << "\n";

    imprimirDesgloseJugador(
        nombreJ2, oroJ2, oroFaseInicialJ2,
        cofresAbiertosJ2, usoLlaveGuardadaJ2,
        vendioEJ2, vendioRJ2, vendioDJ2,
        oroFaseInicialJ1, oroFaseInicialJ2, /*soyJ1=*/0,
        pdvJ2
    );

    cout << "\n========================================\n";

    // Desempate: PDV mayor gana; si empate, gana quien abrio 3 cofres; si persiste, empate.
    if (pdvJ1 > pdvJ2) {
        cout << "      GANADOR: " << nombreJ1 << " (" << pdvJ1 << " PDV)\n";
        actualizarEstadisticasSiMejora(nombreJ1, pdvJ1);
    } else if (pdvJ2 > pdvJ1) {
        cout << "      GANADOR: " << nombreJ2 << " (" << pdvJ2 << " PDV)\n";
        actualizarEstadisticasSiMejora(nombreJ2, pdvJ2);
    } else {
        // PDV iguales: mirar 3 cofres
        bool j1Tres = (cofresAbiertosJ1 >= 3);
        bool j2Tres = (cofresAbiertosJ2 >= 3);
        if (j1Tres != j2Tres) {
            if (j1Tres) {
                cout << "      GANADOR (desempate por 3 cofres): " << nombreJ1
                     << " (" << pdvJ1 << " PDV)\n";
                actualizarEstadisticasSiMejora(nombreJ1, pdvJ1);
            } else {
                cout << "      GANADOR (desempate por 3 cofres): " << nombreJ2
                     << " (" << pdvJ2 << " PDV)\n";
                actualizarEstadisticasSiMejora(nombreJ2, pdvJ2);
            }
        } else {
            cout << "      RESULTADO: EMPATE (" << pdvJ1 << " PDV)\n";
            // Igual actualizamos estad¡sticas si mejora el r‚cord para cualquiera
            actualizarEstadisticasSiMejora(nombreJ1, pdvJ1);
            actualizarEstadisticasSiMejora(nombreJ2, pdvJ2);
        }
    }

    cout << "========================================\n";
    pausaSiguiente("Presione una tecla para volver al menu...");
}

// Estadisticas
// Persistimos el mejor registro en un archivo de texto simple.
// Formato: primera linea nombre, segunda linea PDV (entero)

static const char* STATS_FILE = "rr_estadisticas.txt";

void actualizarEstadisticasSiMejora(const string &nombre, int pdvTotal) {
    // Leer r‚cord actual
    string bestName = "";
    int bestScore = -1;

    ifstream in(STATS_FILE);
    if (in.good()) {
        getline(in, bestName);
        in >> bestScore;
    }
    in.close();

    // Si no hab¡a o si superamos el r‚cord, guardamos
    if (pdvTotal > bestScore) {
        ofstream out(STATS_FILE, ios::trunc);
        out << nombre << "\n" << pdvTotal << "\n";
        out.close();
    }
}

void mostrarEstadisticas() {
    rlutil::cls();
    rlutil::setColor(rlutil::WHITE);
    cout << "=== ESTADISTICAS ===\n\n";

    string bestName = "";
    int bestScore = -1;

    ifstream in(STATS_FILE);
    if (in.good()) {
        getline(in, bestName);
        in >> bestScore;
    }
    in.close();

    if (bestScore >= 0 && bestName.size() > 0) {
        cout << "Mejor puntaje:\n";
        cout << "- " << bestName << " : " << bestScore << " PDV\n";
    } else {
        cout << "Aun no hay estadisticas registradas.\n";
    }

    pausaSiguiente("Presione una tecla para volver...");
}

// Creditos

void mostrarCreditos() {
    rlutil::cls();
    rlutil::setColor(rlutil::WHITE);
    cout << "=== CREDITOS ===\n\n";
    cout << "Equipo: R&&R Devs\n\n";
    cout << "Integrantes:\n";
    cout << "- Mas, Jorge Ariel, Legajo: 12345\n";
    cout << "- (Completar cada uno su nombre y legajo)\n\n";
    cout << "Juego inventado por Angel Simon \n";
    pausaSiguiente("Presione una tecla para volver...");
}
