#include <iostream>
#include <cstdlib>  // rand , para obtener numeros random
#include <ctime>    // time
#include "FuncionesFase1.h"
#include "rlutil.h"
#include <thread>
#include <chrono>


using namespace std;

// Utilidades basicas para todo el juego

//Para demorar un poco las tiradas
void pausarMilisegundos(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int tirarDado(){
    return (rand() % 6) + 1; // Esto me da un numero aleatorio entre 1 y 6
}

// con esto solucionamos las veces que se tiran dados (en cantidad le mandamos cuantas veces se tiran y
//llenamos en dados lo que salio en cada tirada con numeros random de tirarDado())

void tirarNDados(int dados[], int cantidad){
    for(int i = 0; i < cantidad; i++){
        dados[i] = tirarDado();
    }
}

//Para las reglas del juego esto devuelve true si los resultados de los dados son todos distintos
bool tieneTresDistintos(int dados[3]){
    if(dados[0] != dados[1] && dados[0] != dados[2] && dados[1] != dados[2]){
        return true;
    }else{
        return false;
    }

}

//ordenar 3 enteros de menor a mayor
void ordenar3(int &a, int &b, int &c){
    int aux;
    if(a > b){ // si a es mayor que b cambiamos los valores de a por b para ir ordenando de menor a mayor
        aux = a;
        a = b;
        b = aux;
    }
    if(a > c){
        aux = a;
        a = c;
        c = aux;
    }
    if(b > c){
        aux = b;
        b = c;
        c = aux;
    }
}

//Devuelva true si la tirada es una de las escaleras validas
bool esEscaleraValida(int dados[3]){
    int a = dados[0];
    int b = dados[1];
    int c = dados[2];

    //ordenamos a,b,c para poder comparar
    ordenar3(a,b,c);

    // Escaleras v lidas exactas:
    // {1,2,3} {4,5,6} {1,3,5} {2,4,6}
    bool e1 = (a==1 && b==2 && c==3);
    bool e2 = (a==4 && b==5 && c==6);
    bool e3 = (a==1 && b==3 && c==5);
    bool e4 = (a==2 && b==4 && c==6);

    if(e1 || e2 || e3 || e4){
        return true;
    }else{
        return false;
    }

}
 //Mostrar dados ordenados
void mostrarDadosOrdenados3(int dados[3]) {
    int a = dados[0];
    int b = dados[1];
    int c = dados[2];
    ordenar3(a,b,c);

    cout << "[" << a << ", " << b << ", " << c << "]";
}

// Mostrar tirada
void mostrarDados(int dados[], int cantidad){
    cout << "[";
    for (int i = 0; i < cantidad; i++){
        if(i > 0) cout << ", ";
        cout << dados[i];
    }
    cout << "]";
}

//---------FASE INICIAL-------------

void faseInicial(string nombreJ1, string nombreJ2,
                 int &oroJ1, int &oroJ2,
                 int &oroFaseInicialJ1, int &oroFaseInicialJ2)
{
    rlutil::cls();
    rlutil::setColor(rlutil::WHITE);
    cout << "==== Fase Inicial ====\n\n";

    // Ambos empiezan con 150 de oro
    oroJ1 = 150;
    oroJ2 = 150;

    // vamos a reutilizar estos arreglos en comp2 y comp3
    int dadosJ1[3];
    int dadosJ2[3];

    // ======================
    // COMPETENCIA 1
    // ======================
    cout << "Competencia numero 1 - Dado mas alto gana 50 oro\n\n";

    int d1 = tirarDado();
    int d2 = tirarDado();

    // Suspenso jugador 1
    cout << nombreJ1 << " tira";
    pausarMilisegundos(300);
    cout << ".";
    pausarMilisegundos(300);
    cout << ".";
    pausarMilisegundos(300);
    cout << ". ";
    cout << d1 << "\n";

    // Suspenso jugador 2
    cout << nombreJ2 << " tira";
    pausarMilisegundos(300);
    cout << ".";
    pausarMilisegundos(300);
    cout << ".";
    pausarMilisegundos(300);
    cout << ". ";
    cout << d2 << "\n";

    cout << "\nCalculando resultado";
    pausarMilisegundos(400);
    cout << ".";
    pausarMilisegundos(400);
    cout << ".";
    pausarMilisegundos(400);
    cout << ".\n";

    if(d1 > d2){
        oroJ1 += 50;
        cout << "Resultado: " << nombreJ1 << " gana 50 oro.\n";
    } else if (d2 > d1){
        oroJ2 += 50;
        cout << "Resultado: " << nombreJ2 << " gana 50 oro.\n";
    } else {
        oroJ1 += 25;
        oroJ2 += 25;
        cout << "Resultado: Empate. Ganan 25 oro cada uno.\n";
    }
    cout << "Presione una tecla para pasar a la competencia 2 de la Fase 1";
    rlutil::anykey();

    // ======================
    // COMPETENCIA 2
    // ======================
    rlutil::cls();
    cout << "Competencia numero 2 - Sin repetidos (3 dados) (50 oro)\n\n";

    tirarNDados(dadosJ1, 3);
    tirarNDados(dadosJ2, 3);

    // Jugador 1
    cout << nombreJ1 << " tira";
    pausarMilisegundos(300);
    cout << ".";
    pausarMilisegundos(300);
    cout << ".";
    pausarMilisegundos(300);
    cout << ". ";
    mostrarDados(dadosJ1, 3);
    if(tieneTresDistintos(dadosJ1)){
        cout << " -> sin repetidos\n";
    } else {
        cout << " -> hay repetidos\n";
    }

    // Jugador 2
    cout << nombreJ2 << " tira";
    pausarMilisegundos(300);
    cout << ".";
    pausarMilisegundos(300);
    cout << ".";
    pausarMilisegundos(300);
    cout << ". ";
    mostrarDados(dadosJ2, 3);
    if(tieneTresDistintos(dadosJ2)){
        cout << " -> sin repetidos\n";
    } else {
        cout << " -> hay repetidos\n";
    }

    bool j1Ok = tieneTresDistintos(dadosJ1);
    bool j2Ok = tieneTresDistintos(dadosJ2);

    cout << "\nCalculando resultado";
    pausarMilisegundos(400);
    cout << ".";
    pausarMilisegundos(400);
    cout << ".";
    pausarMilisegundos(400);
    cout << ".\n";

    if (j1Ok && !j2Ok) {
        oroJ1 += 50;
        cout << "Resultado: " << nombreJ1 << " gana 50 oro.\n";
    }
    else if (!j1Ok && j2Ok) {
        oroJ2 += 50;
        cout << "Resultado: " << nombreJ2 << " gana 50 oro.\n";
    }
    else if (j1Ok && j2Ok) {
        oroJ1 += 25;
        oroJ2 += 25;
        cout << "Resultado: Ambos sin repetidos. 25 oro c/u.\n";
    }
    else {
        cout << "Resultado: Nadie gana oro.\n";
    }
    cout << "Presione una tecla para pasar a la competencia 3 de la Fase 1";
    rlutil::anykey();

    // ======================
    // COMPETENCIA 3
    // ======================
    rlutil::cls();
    cout << "Competencia numero 3 - Escaleras validas (3 dados) (50 oro)\n";
    cout << "Escaleras validas: {1,2,3} {4,5,6} {2,4,6} {1,3,5}\n\n";

    tirarNDados(dadosJ1, 3);
    tirarNDados(dadosJ2, 3);

    // Jugador 1
    cout << nombreJ1 << " tira";
    pausarMilisegundos(300);
    cout << ".";
    pausarMilisegundos(300);
    cout << ".";
    pausarMilisegundos(300);
    cout << ". ";
    mostrarDados(dadosJ1, 3);
    cout << "  -> ordenado ";
    mostrarDadosOrdenados3(dadosJ1);

    if(esEscaleraValida(dadosJ1)){
        cout << " -> Escalera!\n";
    } else {
        cout << " -> No es escalera\n";
    }

    // Jugador 2
    cout << nombreJ2 << " tira";
    pausarMilisegundos(300);
    cout << ".";
    pausarMilisegundos(300);
    cout << ".";
    pausarMilisegundos(300);
    cout << ". ";
    mostrarDados(dadosJ2, 3);
    cout << "  -> ordenado ";
    mostrarDadosOrdenados3(dadosJ2);

    if(esEscaleraValida(dadosJ2)){
        cout << " -> Escalera!\n";
    } else {
        cout << " -> No es escalera\n";
    }

    j1Ok = esEscaleraValida(dadosJ1);
    j2Ok = esEscaleraValida(dadosJ2);

    cout << "\nCalculando resultado";
    pausarMilisegundos(400);
    cout << ".";
    pausarMilisegundos(400);
    cout << ".";
    pausarMilisegundos(400);
    cout << ".\n";

    if (j1Ok && !j2Ok) {
        oroJ1 += 50;
        cout << "Resultado: " << nombreJ1 << " gana 50 oro.\n";
    }
    else if (!j1Ok && j2Ok) {
        oroJ2 += 50;
        cout << "Resultado: " << nombreJ2 << " gana 50 oro.\n";
    }
    else if (j1Ok && j2Ok) {
        oroJ1 += 25;
        oroJ2 += 25;
        cout << "Resultado: Ambos con escalera. 25 oro c/u.\n";
    }
    else {
        cout << "Resultado: Nadie gana oro.\n";
    }

    // Guardar oro de la fase inicial
    oroFaseInicialJ1 = oroJ1;
    oroFaseInicialJ2 = oroJ2;

    cout << "\nOro FINAL Fase Inicial:\n";
    pausarMilisegundos(400);
    cout << ".";
    pausarMilisegundos(400);
    cout << ".";
    pausarMilisegundos(400);
    cout << ".\n";

    cout << " - " << nombreJ1 << ": " << oroJ1 << "\n";
    cout << " - " << nombreJ2 << ": " << oroJ2 << "\n";

    cout << "Presione una tecla para pasar a la Fase 2";
    rlutil::anykey();
}
