#include <iostream>
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;


struct TPeon { //Estrucctura del peon
    bool NegroOk;
    Tcasilla *casilleroPeon;
    bool boolEliminado;
    bool si_dama;
    CircleShape *Peon;
    CircleShape *Rey;
    };


    TPeon *PeonesBlancos[12];
    TPeon *PeonesNegros[12];
    //sirve para cuando se puede comer mas de una vez las fichas adyacentes
    Tcasilla *vector_movimiento_largo[TAMANIOMAXPOSIBILIDAD];


// esta funcion agrega al vector de los peones su ubicacion

void colocar_peones_casilla (TPeon *vectorAux[] , int i,int j)
{
   int k;
   Tcasilla *aux;
   int contador = 0;          //1,5,7 principio y 0,2,6 uno despues

    for(i;i<=j;i++)
        {
        aux=vector_posiciones[i];
            if(i%2==0)
                aux=aux->derecha;

                    for (k=0;k<4;k++)
                    {
                        vectorAux[contador]->casilleroPeon=aux; //una vez que se cargo el peon en la casilla
                        vectorAux[contador]->casilleroPeon->boolOcupado=true; //se coloca el casillero como ocupado
                        if(aux->derecha!=NULL)
                            aux=aux->derecha->derecha;
                        contador++;
                    }
        }
}


//creo un solo peon negro

void crearPeonNegro(Texture *texturaAuxPeon,Texture *texturaAuxRey,int &contadorNegro){
    TPeon *peonAux=new TPeon;

    peonAux->Peon=new CircleShape(25);
    peonAux->Rey=new CircleShape(25);
    peonAux->Peon->setTexture(texturaAuxPeon);
    peonAux->Rey->setTexture(texturaAuxRey);
    peonAux->Rey->setFillColor(Color::Transparent);
    peonAux->si_dama=false;
    peonAux->NegroOk=true;
    peonAux->boolEliminado=false;
    PeonesNegros[contadorNegro]=peonAux;
    contadorNegro++;

}

// creo un solo peon blanco

void crearPeonBlanco(Texture *texturaAuxPeon,Texture *texturaAuxRey, int &contadorBlanco){

    TPeon *peonAux=new TPeon;
    peonAux->Peon=new CircleShape(25);
    peonAux->Rey=new CircleShape(25);
    peonAux->Peon->setTexture(texturaAuxPeon);
    peonAux->Rey->setTexture(texturaAuxRey);
    peonAux->Rey->setFillColor(Color::Transparent);
    peonAux->si_dama=false;
    peonAux->NegroOk=false;
    peonAux->boolEliminado=false;
    PeonesBlancos[contadorBlanco]=peonAux;
    contadorBlanco++;

}

//funcion de carga peones negros y blancos

int carga_imagenes_fichas (){
    int i,contadorNegro=0, contadorBlanco=0;

    Texture *texturaPeonNegro=new Texture;
    Texture *texturaPeonBlanco=new Texture;
    Texture *texturaReyBlanco=new Texture;
    Texture *texturaReyNegro=new Texture;

    //A continuacion se van a cargar las imagenes pertenecientes a las damas y peones
    if(!texturaPeonNegro->loadFromFile("ficha_negra2.png"))
        return EXIT_FAILURE;
    if(!texturaPeonBlanco->loadFromFile("ficha_blanca2.png"))
        return EXIT_FAILURE;
    if(!texturaReyBlanco->loadFromFile("reyna_blanca2.png"))
        return EXIT_FAILURE;
     if(!texturaReyNegro->loadFromFile("reyna_negra.png"))
        return EXIT_FAILURE;

    for(i=0;i<12;i++)
    {
        //Aca se van a cargar las 12 fichas blancas y negras
       crearPeonBlanco(texturaPeonBlanco,texturaReyBlanco,contadorBlanco);
       crearPeonNegro(texturaPeonNegro,texturaReyNegro,contadorNegro);
    }
    //Con este procedimiento se los ubica luego de cargar las fichas
        colocar_peones_casilla(PeonesBlancos,0,2);
        colocar_peones_casilla(PeonesNegros,5,7);
}
