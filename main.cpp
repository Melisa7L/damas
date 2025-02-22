#include <iostream>
#include <SFML/Graphics.hpp>
#include "tablero.h"
#include "pantallas.h"

using namespace sf;
using namespace std;


int main()
{

    enlace_x();  // conecta los casilleros de forma horizontal
    enlace_y();  //conecta los casilleros de forma vertical
    enlace_grafico();
    carga_imagenes_fichas();
    ventana_inicio();
    return 0;
}
