#include <iostream>
#include "Interfaz.h"

// Aqui agregamos los menu y mensajes
//Region Menu
void mostrarMenu() {
    rlutil::setBackgroundColor(rlutil::LIGHTMAGENTA);
    rlutil::cls();
    rlutil::setColor(rlutil::WHITE);

    std::cout << "ÛÛÛÛÛÛ»   ÛÛÛÛÛ» ÛÛÛ»   ÛÛ»ÛÛÛÛÛÛ»  ÛÛÛÛÛÛ»\n";
    std::cout << "ÛÛÉÍÍÛÛ» ÛÛÉÍÍÛÛ»ÛÛÛÛ»  ÛÛºÛÛÉÍÍÛÛ» ÛÛÉÍÍÛÛ»\n";
    std::cout << "ÛÛÛÛÛÛÉ¼ ÛÛÛÛÛÛÛºÛÛÉÛÛ» ÛÛºÛÛº  ÛÛº ÛÛÛÛÛÛÉ¼\n";
    std::cout << "ÛÛÉÍÍÛÛ» ÛÛÉÍÍÛÛºÛÛºÈÛÛ»ÛÛºÛÛº  ÛÛº ÛÛÉÍÍÛÛ»\n";
    std::cout << "ÛÛº  ÛÛº ÛÛº  ÛÛºÛÛº ÈÛÛÛÛºÛÛÛÛÛÛÉ¼ ÛÛº  ÛÛº\n";
    std::cout << "ÈÍ¼  ÈÍ¼ ÈÍ¼  ÈÍ¼ÈÍ¼  ÈÍÍÍ¼ÈÍÍÍÍÍ¼  ÈÍ¼  ÈÍ¼\n";


    rlutil::setColor(rlutil::CYAN);
    std::cout << "=============================\n";
    std::cout << "     MENU PRINCIPAL\n";
    std::cout << "=============================\n";
    rlutil::setColor(rlutil::WHITE);
    std::cout << "1 - JUGAR\n";
    std::cout << "2 - ESTADISTICAS\n";
    std::cout << "3 - CREDITOS\n";
    std::cout << "-----------------------------\n";
    std::cout << "0 - SALIR\n";
    std::cout << "=============================\n";
    std::cout << "Seleccione una opci¢n: ";
}

void jugar() {
    rlutil::cls();
    std::cout << "Iniciando el juego...\n";
    rlutil::anykey();
}

void estadisticas() {
    rlutil::cls();
    std::cout << "Mostrando estad¡sticas...\n";
    rlutil::anykey();
}

void creditos() {
    rlutil::cls();
    std::cout << "Cr‚ditos del juego:\n";
    rlutil::anykey();
}

void ejecutarMenuPrincipal() {
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;

        switch(opcion) {
            case 1: jugar(); break;
            case 2: estadisticas(); break;
            case 3: creditos(); break;
            case 0: std::cout << "Saliendo...\n"; break;
            default:
                rlutil::setColor(rlutil::LIGHTRED);
                std::cout << "Opci¢n inv lida. Intente de nuevo.\n";
                rlutil::anykey();
        }
    } while(opcion != 0);
}
// Fin Region Menu
