#ifndef FUNCIONESFASE2_H_INCLUDED
#define FUNCIONESFASE2_H_INCLUDED
#include <string>
using namespace std;

void faseBusquedaTesoros(
  string j1, string j2,
  int &oroJ1, int &oroJ2,
  int &llaveGJ1, int &llaveGJ2,
  int &cofresJ1, int &cofresJ2,
  int &usoLGJ1, int &usoLGJ2,
  int &vendEJ1, int &vendRJ1, int &vendDJ1,
  int &vendEJ2, int &vendRJ2, int &vendDJ2
);

// --------------------- HELPERS DE FLUJO ---------------------

void turnoRondaJugador(
  string nombre, int ronda,
  int &oro, int &llaveGuardada,
  int &cofresAbiertos, int &usoLlaveGuardada,
  int &vendE, int &vendR, int &vendD,
  int oroJ1Vis, int oroJ2Vis, bool esJugador1
);

// --------------------- HELPERS LÓGICOS ---------------------

void contarCaras5(const int tirada[5], int conteo[7]);
bool puedeAbrirCofre(int ronda, const int conteo[7], int llaveGuardada);
void consumirLlaveApertura(int ronda, int conteo[7], int &llaveGuardada, int &usoLlaveGuardada);
int  valorLlave(int tipo);  // 1->10, 2->20, 3->30
int  valorGema (int tipo);  // 4->40, 5->50, 6->60
int  oroPorLlavesRestantes(const int conteo[7]);  // suma 1..3*valor
int  oroPorGemas(const int conteo[7], int &vendE, int &vendR, int &vendD);

// --------------------- HELPERS DE UI / I/O ---------------------

const char* nombreCofre(int ronda); // "Madera"/"Piedra"/"Metal"

void mostrarTirada5(const int tirada[5]);
void mostrarConteoLlaves(const int conteo[7]);   // “Madera x?, Piedra x?, Metal x?”
void mostrarConteoGemas (const int conteo[7]);   // “Esmeraldas x?, Rubies x?, Diamantes x?”
void mostrarEstadoJugadorF2(
  string nombre, int ronda, int oroJ1, int oroJ2,
  int llaveGuardada, const int tirada[5], const int conteo[7]
);

char leerOpcionVG();                    // devuelve 'V' o 'G'
int  elegirLlaveAGuardar(const int conteo[7]); // 1/2/3 (o 0 si no hay ninguna)
void aplicarDecisionNoAbre(
  char opcionVG, const int conteo[7],
  int &oro, int &llaveGuardada
);

void pausaSiguiente(const char* msg);   // wrapper de anykey con texto

#endif // FUNCIONESFASE2_H_INCLUDED
