#include <iostream>
#include <cstdlib>
#include <ctime>
#include "FuncionesFase1.h"
#include "Interfaz.h"
#include "rlutil.h"


using namespace std;

int main()
{
    srand(time(NULL)); // inicializar RNG UNA vez

    ejecutarMenuPrincipal();
    return 0;
}
