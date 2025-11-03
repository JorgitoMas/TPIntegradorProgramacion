#pragma once

//Estructura base del juego y Fase1

//Para tirada random de dado de 6 caras
int tirarDado();

//Tirar N dados y guardarlos en un vector
void tirarNDados(int dados[], int cantidad);

//Competencia numero 2: Devuelve true si los 3 dados son todos distintos
bool tieneTresDistintos(int dados[3]);

//Competencia numero 3: Devuelve true si los 3 dados forman escalera valida
bool esEscaleraValida(int dados[3]);

// Escto correria toda la fase inicial y actualiza oroJugador1, oroJugador2, oroFaseInicialJ1 y oroFaseInicialJ2
void faseInicial(std::string nombreJ1, std::string nombreJ2, int &oroJ1, int &oroJ2, int &oroFaseInicialJ1, int &oroFaseInicialJ2);

//Para pausar milisegundos
void pausarMilisegundos(int ms);



