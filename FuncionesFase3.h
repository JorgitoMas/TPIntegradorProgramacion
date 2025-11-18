#ifndef FUNCIONESFASE3_H_INCLUDED
#define FUNCIONESFASE3_H_INCLUDED

#include <string>
using namespace std;

//FASE FINAL
void faseFinalPDV(
    string nombreJ1, string nombreJ2,
    int oroJ1, int oroJ2,
    int oroFaseInicialJ1, int oroFaseInicialJ2,
    int cofresAbiertosJ1, int cofresAbiertosJ2,
    int usoLlaveGuardadaJ1, int usoLlaveGuardadaJ2,
    int vendioEJ1, int vendioRJ1, int vendioDJ1,
    int vendioEJ2, int vendioRJ2, int vendioDJ2
);

//ESTADÍSTICAS
void actualizarEstadisticasSiMejora(const string &nombre, int pdvTotal);
void mostrarEstadisticas(); // imprime mejor jugador y puntaje

// ---------- CRÉDITOS ----------
void mostrarCreditos();


#endif // FUNCIONESFASE3_H_INCLUDED
