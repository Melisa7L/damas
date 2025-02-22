#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "estrucctura_peones.h"
#include "funciones_peones.h"
#include "movimiento_peones.h"

using namespace std;
using namespace sf;


 //A continuacion se declaran los procedimientos y las funciones para crear y mostrar las ventanas

//Ventana Inicial
int ventana_inicio();
void abrir_inicio (RenderWindow &window,Sprite *sprite);
void mostrar_inicio(RenderWindow &window,Sprite *sprite);
int texto_inicio();

//Ventana Sonido

int ventana_sonido();
void abrir_sonido(RenderWindow &window, Sprite *sprite);
void mostrar_sonido(RenderWindow &window, Sprite *sprite);
int texto_sonido();

//Ventana Intrucciones
int ventana_reglas();
void abrir_reglas (RenderWindow &window, Sprite *sprite);
void mostrar_reglas(RenderWindow &window,Sprite *sprite);
int texto_reglas();

int ventana_reglas2();
void reglas2(RenderWindow &window,Sprite *sprite);
void mostrar_reglas2(RenderWindow &window, Sprite *sprite);

//Ventana de Creditos
int ventana_creditos();
void abrir_creditos(RenderWindow &window, Sprite *sprite);
void mostrar_creditos(RenderWindow &window, Sprite *sprite);
int texto_creditos();

//Ventana ganador

int ventana_ganador();
void abrir_ganador(RenderWindow &window, Sprite *sprite);
void mostrar_ganador(RenderWindow &window, Sprite *sprite);
int texto_ganador();

//Ventana del tablero
int ventana_juego();
void abrir_juego(RenderWindow &window,TPeon *seleccionadoAux,Sprite *sprite);
void mostrar_juego(RenderWindow &window,Sprite *sprite);
int texto_juego();

void eventoClickMouse(Event &event,TPeon *&seleccionadoAux);

void texto_jugador1 ();
void texto_jugador2 ();
void comprobar ();

string convertir();

//En esta seccion se declaran los atributos de los textos que van en las ventanas

//Variables fuentes
Font *fuente1=new Font; //para titulos
Font *fuente2=new Font;//para subtitulos

//Texto para la pantalla de inicio
Text *titulo;
Text *jugar;
Text *opciones;
Text *reglas_texto;
Text *creditos;
Text *volveratras;//para volver al inicio

//Texto para la pantalla de juego

Text *equipo_blanco;
Text *equipo_negro;
Text *fichas1;
Text *fichas2;
Text *cantfichas1;
Text *cantfichas2;

//Para usos
Text *textrandom;
Text *textrandom2;
Text *rendirse;//////////



Text *sonido;
Text *musica;

Music cancion;
Music tema1;
Music tema2;
Music tema3;
Music ganador;


//Banderas

bool turno_negro = false; //varia dependiendo de quien sea el turno
bool sonido_activo = true; //Guarda una variable de tipo bool si el sonido esta encendido
bool sonido_inicial=true;
bool ganadores = true;//si es que gana el negro
bool se_rinde =true;
int sonando;//toma un numero dependiendo de que sonido se encuentra activo

//FUNCION QUE CONVIERTE ENTEROS A TEXTO
string convertir(int numero){
    ostringstream buff;
    buff<<numero;
    return buff.str();
}

//VENTANA DE INICIO
int ventana_inicio()
{
    Texture *pantalla=new Texture;
    Sprite *sprite=new Sprite;
    RenderWindow window1(VideoMode(620, 620),"Juego de Damas",Style::Titlebar); //crea la ventana y titulo
    if(!pantalla->loadFromFile("ventana_inicio.jpg")) //Carga imagen
            return EXIT_FAILURE;

    sprite->setTexture(*pantalla); //Son las texturas de la imagen,el sprite utiliza la textura
    sprite->setScale(0.18,0.18);
    sprite->setColor(Color(228,228,228));
    texto_inicio(); //Abre el texto que se mostrara en la ventana

    abrir_inicio(window1,sprite); //muestra la ventaba
}

void abrir_inicio(RenderWindow &window1,Sprite *sprite)
{
    Event event;
    //En est ventana se abren los archivos de sonido pero solo uno se va a reproducir por ahora
    cancion.openFromFile("lgante.ogg");
    tema1.openFromFile("bichota.ogg");
    tema2.openFromFile("peluso.ogg");
    tema3.openFromFile("trueno.ogg");
    ganador.openFromFile("fuegos_artificiales.ogg");
    if(sonido_inicial){
            sonando =1;
            sonido_inicial=false;
    }
    if(sonido_activo){  //Reproduce la cancion predeterminada
        if(sonando==1){
            cancion.setLoop(true);
            cancion.play();
        }
        else{
        //A partir de aca segun la opcion que seleccione el usuario en los ajustes de sonido --
        //--va a reproducir la cancion solicitada
            if(sonando==2){
                tema1.setLoop(true);
                tema1.play();
            }else{
                if(sonando==3){
                    tema2.setLoop(true);
                    tema2.play();
                }else{
                    if(sonando==4){
                        tema3.setLoop(true);
                        tema3.play();
                    }
                }
            }
        }
    }

        while (window1.isOpen()){ //Cuando la ventana se abra

            while (window1.pollEvent(event)){

                if (event.type == Event::Closed)
                    window1.close();

                if (event.type == Event::MouseButtonPressed){ //cuando se haga click

                        //Segun las coordenadas del click se realizara alguna accion(de acuerdo al boton)
                       if (event.mouseButton.button == Mouse::Left){

                           if(((event.mouseButton.x>=215)&&(event.mouseButton.x<=490))&&((event.mouseButton.y>=125)&&(event.mouseButton.y<=170)))
                            {
                                window1.close();
                                ventana_juego();
                            }
                            else
                                {
                                    if(((event.mouseButton.x>=155)&&(event.mouseButton.x<=480))&&((event.mouseButton.y>=295)&&(event.mouseButton.y<=330)))
                                    {
                                        window1.close();
                                        ventana_reglas();
                                    }
                                    else{
                                            if(((event.mouseButton.x>=215)&&(event.mouseButton.x<=490))&&((event.mouseButton.y>=210)&&(event.mouseButton.y<=255)))
                                                {
                                                    window1.close();
                                                    ventana_sonido();
                                                }
                                                else{
                                                   if(((event.mouseButton.x>=215)&&(event.mouseButton.x<=490))&&((event.mouseButton.y>=380)&&(event.mouseButton.y<=420)))
                                                    {
                                                        window1.close();
                                                        ventana_creditos();
                                                    }else{
                                                        if(((event.mouseButton.x>=215)&&(event.mouseButton.x<=490))&&((event.mouseButton.y>=465)&&(event.mouseButton.y<=510)))
                                                        {
                                                            window1.close();
                                                        }
                                                    }

                                                }
                                        }
                                }
                            }
                        }

                    }
            mostrar_inicio(window1,sprite); //Todas las ventanas deben tener la opcion de volver al inicio
            //A continuacion en cada boton ,al pasar el mouse por alli se cambiara de color para darle mas efectos de boton

            if(event.type == sf::Event::MouseMoved)
                {
                    if(((event.mouseMove.x >=215)&&(event.mouseMove.x<=490))&&((event.mouseMove.y>=125)&&(event.mouseMove.y<=170))){//jugar
                            jugar->setColor(Color::Green); //color verde al que se cambian las letras
                            jugar->setOutlineThickness(3);
                            reglas_texto->setColor(Color(242,161,18));
                            opciones->setColor(Color(242,161,18));
                            creditos->setColor(Color(242,161,18));
                            rendirse->setColor(Color(242,161,18));
                    }else{
                         if(((event.mouseMove.x >=155)&&(event.mouseMove.x<=480))&&((event.mouseMove.y>=295)&&(event.mouseMove.y<=330))){//reglas
                            reglas_texto->setColor(Color::Green);
                            reglas_texto->setOutlineThickness(3);
                            jugar->setColor(Color(242,161,18));
                            opciones->setColor(Color(242,161,18));
                            creditos->setColor(Color(242,161,18));
                            rendirse->setColor(Color(242,161,18));

                    }else{
                        if(((event.mouseMove.x >215)&&(event.mouseMove.x<490))&&((event.mouseMove.y>=210)&&(event.mouseMove.y<=255))){//opciones
                            opciones->setColor(Color::Green);
                            opciones->setOutlineThickness(3);
                            jugar->setColor(Color(242,161,18));
                            reglas_texto->setColor(Color(242,161,18));
                            creditos->setColor(Color(242,161,18));
                            rendirse->setColor(Color(242,161,18));
                            }
                            else{
                               if(((event.mouseMove.x >=215)&&(event.mouseMove.x<=490))&&((event.mouseMove.y>=380)&&(event.mouseMove.y<=420))){//creditos
                                    creditos->setColor(Color::Green);
                                    creditos->setOutlineThickness(3);
                                    jugar->setColor(Color(242,161,18));
                                    reglas_texto->setColor(Color(242,161,18));
                                    opciones->setColor(Color(242,161,18));
                                    rendirse->setColor(Color(242,161,18));
                                }else{
                                    if(((event.mouseMove.x >=215)&&(event.mouseMove.x<=490))&&((event.mouseMove.y>=465)&&(event.mouseMove.y<=510))){//salir
                                    rendirse->setColor(Color::Green);
                                    rendirse->setOutlineThickness(3);
                                    jugar->setColor(Color(242,161,18));
                                    reglas_texto->setColor(Color(242,161,18));
                                    opciones->setColor(Color(242,161,18));
                                    creditos->setColor(Color(242,161,18));
                                    }

                                }
                            }
                        }
                    }
                }
            }
    }
void mostrar_inicio(RenderWindow &window1,Sprite *sprite)  //aca dibuja con todos los cambios de texto en la ventana
{

        window1.clear(Color::White);
        window1.draw(*sprite);
        window1.draw(*titulo);
        window1.draw(*jugar);
        window1.draw(*opciones);
        window1.draw(*reglas_texto);
        window1.draw(*creditos);
        window1.draw(*rendirse);
        window1.display();

}

int texto_inicio(){

    if(!fuente1->loadFromFile("Damage.ttf")) //Carga de la fuente utilizada en las ventanas
        return EXIT_FAILURE;

        //Mensajes que van a aparecer en pantalla
    String cadenaTitulo="DAMAS";
    String cadenaJugar= "Jugar";
    String cadenaOpc= "Opciones";
    String cadenaReglas = "Instrucciones";
    String cadenaCreditos = "Creditos";
    String cadenaSalir= "Salir";
    String cadenaAbandonarPartida="ABANDONAR";

    titulo=new Text(cadenaTitulo,*fuente1,60);
    titulo->setPosition(200,15);
    titulo->setColor(Color::White);
    titulo->setOutlineColor(Color::Black);
    titulo->setOutlineThickness(3);


    jugar= new Text (cadenaJugar,*fuente1,30);
    jugar->setColor(Color(242,161,18));
    jugar->setPosition(260,130);
    jugar->setOutlineColor(Color::Black);
    jugar->setOutlineThickness(3);

    opciones= new Text (cadenaOpc,*fuente1,30);
    opciones->setColor(Color(242,161,18));
    opciones->setPosition(233,212);
    opciones->setOutlineColor(Color::Black);
    opciones->setOutlineThickness(3);

    reglas_texto= new Text (cadenaReglas,*fuente1,30);
    reglas_texto->setColor(Color(242,161,18));
    reglas_texto->setPosition(180,300);
    reglas_texto->setOutlineColor(Color::Black);
    reglas_texto->setOutlineThickness(3);

    creditos= new Text (cadenaCreditos,*fuente1,30);
    creditos->setColor(Color(242,161,18));
    creditos->setPosition(230,385);
    creditos->setOutlineColor(Color::Black);
    creditos->setOutlineThickness(3);


    rendirse=new Text(cadenaSalir,*fuente1,30);
    rendirse->setColor(Color(242,161,18));
    rendirse->setOutlineColor(Color::Black);
    rendirse->setOutlineThickness(3);
    rendirse->setPosition(270,470);



}

//VENTANA DE OPCIONES

int ventana_sonido(){
    Texture *textura = new Texture;
    Sprite *sprite = new Sprite;
    RenderWindow window2(VideoMode(610,660),"Sonido",Style::Titlebar);
    if(!textura->loadFromFile("ventana_sonido.jpg"))
        return EXIT_FAILURE;
    sprite->setTexture(*textura);
    sprite->setScale(0.25,0.25);
    texto_sonido();
    abrir_sonido(window2,sprite);
}

void abrir_sonido(RenderWindow &window2, Sprite *sprite)
{
    Event event;
    tema1.openFromFile("bichota.ogg");
    tema2.openFromFile("peluso.ogg");
    tema3.openFromFile("trueno.ogg");

    if(sonido_activo){
        if(sonando==1){
            cancion.setLoop(true);
            cancion.play();
        }else{
            if(sonando==2){
                tema1.setLoop(true);
                tema1.play();
            }else{
                if(sonando==3){
                    tema2.setLoop(true);
                    tema2.play();
                }else{
                    if(sonando==4){
                        tema3.setLoop(true);
                        tema3.play();
                    }
                }
            }
        }
    }
        while (window2.isOpen()){

            while (window2.pollEvent(event)){

                if (event.type == Event::Closed)
                    window2.close();

                if (event.type == Event::MouseButtonPressed){

                    if (event.mouseButton.button == Mouse::Left){
                        if(((event.mouseButton.x>=490)&&(event.mouseButton.x<=545))&&((event.mouseButton.y>=75)&&(event.mouseButton.y<=125)))//boton apagado
                            {
                                cancion.stop();
                                tema1.stop();
                                tema2.stop();
                                tema3.stop();
                                sonido_activo=false;
                            }
                         if(((event.mouseButton.x>=355)&&(event.mouseButton.x<=410))&&((event.mouseButton.y>=75)&&(event.mouseButton.y<=125)))
                            {
                                if(sonido_activo==false){
                                    sonando=1;
                                    cancion.setLoop(true);
                                    cancion.play();
                                    sonido_activo=true;
                                    }
                            }
                        if(((event.mouseButton.x>=305)&&(event.mouseButton.x<=590))&&((event.mouseButton.y>=175)&&(event.mouseButton.y<=235)))
                        {
                                sonando = 2;
                                tema1.setLoop(true);
                                tema1.play();
                                tema2.stop();
                                tema3.stop();
                                cancion.stop();
                                sonido_activo = true;
                        }
                        if(((event.mouseButton.x>=305)&&(event.mouseButton.x<=590))&&((event.mouseButton.y>=265)&&(event.mouseButton.y<=325)))
                        {
                            sonando=3;
                            tema2.setLoop(true);
                            tema2.play();
                            tema1.stop();
                            tema3.stop();
                            cancion.stop();
                            sonido_activo=true;

                        }
                        if(((event.mouseButton.x>=305)&&(event.mouseButton.x<=590))&&((event.mouseButton.y>=355)&&(event.mouseButton.y<=410)))
                        {
                            sonando=4;
                            tema3.setLoop(true);
                            tema3.play();
                            tema1.stop();
                            tema2.stop();
                            cancion.stop();
                            sonido_activo=true;

                        }
                        if(((event.mouseButton.x>=370)&&(event.mouseButton.x<=590))&&((event.mouseButton.y>=535)&&(event.mouseButton.y<=595)))
                        {
                            window2.close();
                            ventana_inicio();
                        }
                    }

                }
            mostrar_sonido(window2,sprite);
            if(event.type == sf::Event::MouseMoved)
                {
                    if(((event.mouseMove.x >=370)&&(event.mouseMove.x<=535))&&((event.mouseMove.y>=535)&&(event.mouseMove.y<=595))){
                            volveratras->setColor(Color::Green);
                    }else{
                        volveratras->setColor(Color(242,161,18));
                    }
                    //tema1
                    if(((event.mouseMove.x >=305)&&(event.mouseMove.x<=590))&&((event.mouseMove.y>=175)&&(event.mouseMove.y<=235))){
                            jugar->setColor(Color::Green);
                    }else{
                        jugar->setColor(Color(242,161,18));
                    }
                    if(((event.mouseMove.x >=305)&&(event.mouseMove.x<=590))&&((event.mouseMove.y>=265)&&(event.mouseMove.y<=325))){
                            creditos->setColor(Color::Green);
                    }else{
                        creditos->setColor(Color(242,161,18));
                    }
                    if(((event.mouseMove.x >=305)&&(event.mouseMove.x<=490))&&((event.mouseMove.y>=355)&&(event.mouseMove.y<=410))){
                            opciones->setColor(Color::Green);
                    }else{
                        opciones->setColor(Color(242,161,18));
                    }
                    if(((event.mouseMove.x >=355)&&(event.mouseMove.x<=410))&&((event.mouseMove.y>=75)&&(event.mouseMove.y<=125))){
                                textrandom->setOutlineColor(Color::Green);
                                textrandom->setOutlineThickness(2);
                    }else{
                        textrandom->setOutlineColor(Color(213, 219, 219));
                    }
                    if(((event.mouseMove.x >=490)&&(event.mouseMove.x<=545))&&((event.mouseMove.y>=75)&&(event.mouseMove.y<=125))){
                                textrandom2->setOutlineColor(Color::Red);
                                textrandom2->setOutlineThickness(2);
                    }else{
                        textrandom2->setOutlineColor(Color(213, 219, 219));
                    }
                }
        }
}
}
void mostrar_sonido(RenderWindow &window2,Sprite *sprite)
{

        window2.clear(Color::White);
        window2.draw(*sprite);
        window2.draw(*sonido);
        window2.draw(*musica);
        window2.draw(*jugar);
        window2.draw(*creditos);
        window2.draw(*opciones);
        window2.draw(*volveratras);
        window2.draw(*textrandom);
        window2.draw(*textrandom2);
        window2.display();

}
int texto_sonido(){
    if(!fuente1->loadFromFile("Damage.ttf"))
        return EXIT_FAILURE;

    if(!fuente2->loadFromFile("circlethings.ttf"))
        return EXIT_FAILURE;

    String volver="Inicio";
    String sonidos = "Sonido";
    String musi = "Musica";
    String cancion1 = "Cancion1";
    String cancion2 = "Cancion2";
    String cancion3 = "Cancion3";
    String simbolo = "A";

    sonido=new Text(sonidos,*fuente1,30);
    sonido->setColor(Color(242,161,18));
    sonido->setOutlineColor(Color::Black);
    sonido->setOutlineThickness(3);
    sonido->setPosition(100,85);

    musica=new Text(musi,*fuente1,30);
    musica->setColor(Color(242,161,18));
    musica->setOutlineColor(Color::Black);
    musica->setOutlineThickness(3);
    musica->setPosition(100,275);

    jugar=new Text(cancion1,*fuente1,30);
    jugar->setColor(Color(242,161,18));
    jugar->setOutlineColor(Color::Black);
    jugar->setOutlineThickness(3);
    jugar->setPosition(355,185);

    creditos=new Text(cancion2,*fuente1,30);
    creditos->setColor(Color(242,161,18));
    creditos->setOutlineColor(Color::Black);
    creditos->setOutlineThickness(3);
    creditos->setPosition(355,275);

    opciones=new Text(cancion3,*fuente1,30);
    opciones->setColor(Color(242,161,18));
    opciones->setOutlineColor(Color::Black);
    opciones->setOutlineThickness(3);
    opciones->setPosition(355,365);

    volveratras=new Text(volver,*fuente1,30);
    volveratras->setColor(Color(242,161,18));
    volveratras->setOutlineColor(Color::Black);
    volveratras->setOutlineThickness(3);
    volveratras->setPosition(430,550);

    textrandom=new Text(simbolo,*fuente2,50);
    textrandom->setColor(Color(213, 219, 219));
    textrandom->setPosition(354,67);

    textrandom2=new Text(simbolo,*fuente2,50);
    textrandom2->setColor(Color(213, 219, 219));
    textrandom2->setPosition(491,67);



}

//VENTANAS DE REGLAS

int ventana_reglas(){
    Texture *textura = new Texture;
    Sprite *sprite = new Sprite;
    RenderWindow window3(VideoMode(900,660),"Reglas",Style::Titlebar);
    if(!textura->loadFromFile("ventana_reglas2.jpg"))
        return EXIT_FAILURE;
    sprite->setTexture(*textura);
    sprite->setScale(0.3,0.3);
    sprite->setColor(Color(228,228,228));
    texto_reglas();
    abrir_reglas(window3,sprite);
}

void abrir_reglas(RenderWindow &window3, Sprite *sprite)
{
    Event event;

        while (window3.isOpen()){

            while (window3.pollEvent(event)){

                if (event.type == Event::Closed)
                    window3.close();

                if (event.type == Event::MouseButtonPressed){
                       if (event.mouseButton.button == Mouse::Left){
                           if(((event.mouseButton.x>=705)&&(event.mouseButton.x<=870))&&((event.mouseButton.y>=610)&&(event.mouseButton.y <=655)))
                            {
                            window3.close();
                            ventana_inicio();
                           }else{
                               if(((event.mouseButton.x>=30)&&(event.mouseButton.x<=195))&&((event.mouseButton.y>=610)&&(event.mouseButton.y <=655)))
                            {
                            window3.close();
                            ventana_reglas2();
                           }
                           }
                       }
                    }
            }
            mostrar_reglas(window3,sprite);
            if(event.type == sf::Event::MouseMoved)
                {
                    if(((event.mouseMove.x >=705)&&(event.mouseMove.x<=870))&&((event.mouseMove.y>=610)&&(event.mouseMove.y<=655))){
                            opciones->setColor(Color::Green);
                    }else{
                        opciones->setColor(Color(242,161,18));
                    }
                    if(((event.mouseMove.x >=30)&&(event.mouseMove.x<=195))&&((event.mouseMove.y>=610)&&(event.mouseMove.y<=655))){
                            volveratras->setColor(Color::Green);
                    }else{
                        volveratras->setColor(Color(242,161,18));
                    }
                }
        }
}
void mostrar_reglas(RenderWindow &window3,Sprite *sprite)
{

        window3.clear(Color::White);
        window3.draw(*sprite);
        window3.draw(*opciones);
        window3.draw(*volveratras);
        window3.display();

}
int texto_reglas(){
    if(!fuente1->loadFromFile("Damage.ttf"))
        return EXIT_FAILURE;


    String volver="Reglas";
    String inicio="Inicio";

    opciones=new Text(inicio,*fuente1,25);
    opciones->setColor(Color(242,161,18));
    opciones->setOutlineColor(Color::Black);
    opciones->setOutlineThickness(3);
    opciones->setPosition(750,615);

    volveratras=new Text(volver,*fuente1,25);
    volveratras->setColor(Color(242,161,18));
    volveratras->setOutlineColor(Color::Black);
    volveratras->setOutlineThickness(3);
    volveratras->setPosition(55,615);

}

int ventana_reglas2(){
    Texture *textura = new Texture;
    Sprite *sprite = new Sprite;
    RenderWindow window4(VideoMode(900,660),"Reglas",Style::Titlebar);
    if(!textura->loadFromFile("ventana_reglas.jpg"))
        return EXIT_FAILURE;
    sprite->setTexture(*textura);
    sprite->setScale(0.3,0.3);
    sprite->setColor(Color(228,228,228));
    texto_reglas();
    reglas2(window4,sprite);
}

void reglas2(RenderWindow &window4, Sprite *sprite)
{
    Event event;

        while (window4.isOpen()){

            while (window4.pollEvent(event)){

                if (event.type == Event::Closed)
                    window4.close();

                if (event.type == Event::MouseButtonPressed){

                       if (event.mouseButton.button == Mouse::Left){
                        if(((event.mouseButton.x>=705)&&(event.mouseButton.x<=870))&&((event.mouseButton.y>=610)&&(event.mouseButton.y <=655)))
                            {
                            window4.close();
                            ventana_inicio();
                           }
                       }
                    }
            }
            mostrar_reglas2(window4,sprite);
                if(event.type == sf::Event::MouseMoved)
                {
                    if(((event.mouseMove.x >=705)&&(event.mouseMove.x<=870))&&((event.mouseMove.y>=610)&&(event.mouseMove.y<=655))){
                            opciones->setColor(Color::Green);
                    }else{
                        opciones->setColor(Color(242,161,18));
                    }
                }
        }
}
void mostrar_reglas2(RenderWindow &window4,Sprite *sprite)
{

        window4.clear(Color::White);
        window4.draw(*sprite);
        window4.draw(*opciones);
        window4.display();

}

//FUNCION VENTANA DE CREDITO


int ventana_creditos(){
    Texture *textura = new Texture;
    Sprite *sprite = new Sprite;
    RenderWindow window5(VideoMode(635,630),"Creditos",Style::Titlebar);
    if(!textura->loadFromFile("ventana_creditos.jpg"))
        return EXIT_FAILURE;
    sprite->setTexture(*textura);
    sprite->setScale(0.18,0.18);
    sprite->setColor(Color(228,228,228));
    texto_creditos();
    abrir_creditos(window5,sprite);
}

void abrir_creditos(RenderWindow &window5, Sprite *sprite)
{
    Event event;

        while (window5.isOpen()){

            while (window5.pollEvent(event)){

                if (event.type == Event::Closed)
                    window5.close();

                if (event.type == Event::MouseButtonPressed){

                       if (event.mouseButton.button == Mouse::Left){
                           if(((event.mouseButton.x>=440)&&(event.mouseButton.x<=600))&&((event.mouseButton.y>=560)&&(event.mouseButton.y<=600)))
                            {
                            window5.close();
                            ventana_inicio();
                           }
                       }
                    }
            }
            mostrar_creditos(window5,sprite);
            if(event.type == sf::Event::MouseMoved)
                {
                    if(((event.mouseMove.x >=440)&&(event.mouseMove.x<=600))&&((event.mouseMove.y>=560)&&(event.mouseMove.y<=600))){
                            volveratras->setColor(Color::Green);
                    }else{
                        volveratras->setColor(Color(242,161,18));
                    }
                }
}
}
void mostrar_creditos(RenderWindow &window5,Sprite *sprite)
{

        window5.clear(Color::White);
        window5.draw(*sprite);
        window5.draw(*volveratras);
        window5.display();

}

int texto_creditos(){
    if(!fuente1->loadFromFile("Damage.ttf"))
        return EXIT_FAILURE;


    String volver="Inicio";

    volveratras=new Text(volver,*fuente1,30);
    volveratras->setColor(Color(242,161,18));
    volveratras->setOutlineColor(Color::Black);
    volveratras->setOutlineThickness(3);
    volveratras->setPosition(475,560);

}
//VENTANA DE GANADORES

int ventana_ganador()
{
    Texture *textura = new Texture;
    Sprite *sprite = new Sprite;
    RenderWindow window6(VideoMode(635,630),"Ganadores",Style::Titlebar);
    if(!textura->loadFromFile("pantalla_ganadores.jpg"))
        return EXIT_FAILURE;
    sprite->setTexture(*textura);
    sprite->setScale(0.18,0.18);
    sprite->setColor(Color(228,228,228));
    texto_ganador();
    abrir_ganador(window6,sprite);
}
void abrir_ganador(RenderWindow &window6, Sprite *sprite)
{
    Event event;
    ganador.openFromFile("fuegos_artificiales.ogg");
    ganador.setLoop(true);
    ganador.play();
    cancion.stop();
    tema1.stop();
    tema2.stop();
    tema3.stop();
        while (window6.isOpen()){

            while (window6.pollEvent(event)){

                if (event.type == Event::Closed)
                    window6.close();

                if (event.type == Event::MouseButtonPressed){
                       if (event.mouseButton.button == Mouse::Left){
                           if(((event.mouseButton.x>=440)&&(event.mouseButton.x<=600))&&((event.mouseButton.y>=560)&&(event.mouseButton.y<=600)))
                            {
                                window6.close();
                                ventana_inicio();
                           }
                       }
                    }
            }
            mostrar_ganador(window6,sprite);
            if(event.type == sf::Event::MouseMoved)
                {
                    if(((event.mouseMove.x >=440)&&(event.mouseMove.x<=600))&&((event.mouseMove.y>=560)&&(event.mouseMove.y<=600))){
                            volveratras->setColor(Color::Green);
                    }else{
                        volveratras->setColor(Color(242,161,18));
                    }
                }
}
}
void mostrar_ganador(RenderWindow &window6,Sprite *sprite)
{

        window6.clear(Color::White);
        window6.draw(*sprite);
        window6.draw(*volveratras);
        if(se_rinde){
            window6.draw(*textrandom);
        }
        else{
            window6.draw(*textrandom2);
        }
        window6.draw(*opciones);
        window6.display();

}
int texto_ganador(){
    if(!fuente1->loadFromFile("Damage.ttf"))
        return EXIT_FAILURE;


    String volver="Inicio";
    String ganador_blanco="Ganador equipo blanco!!";
    String ganador_negro="Ganador equipo negro!!";
    String felicidades="Felicidades";

    volveratras=new Text(volver,*fuente1,30);
    volveratras->setColor(Color(242,161,18));
    volveratras->setOutlineColor(Color::Black);
    volveratras->setOutlineThickness(3);
    volveratras->setPosition(475,560);

    textrandom=new Text(ganador_blanco,*fuente1,30);
    textrandom->setColor(Color(242,161,18));
    textrandom->setOutlineColor(Color::Black);
    textrandom->setOutlineThickness(3);
    textrandom->setPosition(90,300);

    textrandom2=new Text(ganador_negro,*fuente1,30);
    textrandom2->setColor(Color(242,161,18));
    textrandom2->setOutlineColor(Color::Black);
    textrandom2->setOutlineThickness(3);
    textrandom2->setPosition(90,300);

    opciones=new Text (felicidades,*fuente1,30);
    opciones->setColor(Color(242,161,18));
    opciones->setOutlineColor(Color::Black);
    opciones->setOutlineThickness(3);
    opciones->setPosition(220,350);

    carga_imagenes_fichas();


}
//*****************************************************************************************

int ventana_juego()
{

    TPeon *seleccionadoAux=NULL;
    Texture *textura=new Texture;
    Sprite *sprite=new Sprite;

    RenderWindow window(VideoMode(600,660), "Tablero de Damas",Style::Titlebar);

        if(!textura->loadFromFile("tablero2.jpg"))
            return EXIT_FAILURE;

    sprite->setTexture(*textura);
    sprite->setScale(0.2,0.2);

    texto_juego();

    abrir_juego(window,seleccionadoAux,sprite);

}

//mantiene abierto el window hasta que lo cerremos manualmente
//tambien llama a una funcion cuando hacen click

void abrir_juego(RenderWindow &window,TPeon *seleccionadoAux,Sprite *sprite)
{
    Event event;

        while (window.isOpen()){

            while (window.pollEvent(event)){

                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::MouseButtonPressed){
                        eventoClickMouse(event,seleccionadoAux);
                        if (event.mouseButton.button == Mouse::Left){
                           if(((event.mouseButton.x>=410)&&(event.mouseButton.x<=630))&&((event.mouseButton.y>=615)&&(event.mouseButton.y<=640)))
                            {
                                if(turno_negro){
                                    window.close();
                                    se_rinde=true;
                                    turno_negro=false;
                                    ventana_ganador();
                                    carga_imagenes_fichas();
                                }
                                else{
                                    window.close();
                                    se_rinde=false;
                                    turno_negro=false;
                                    ventana_ganador();
                                    carga_imagenes_fichas();                                }
                            }
                       }
                       if((contar_eliminados_blancos(PeonesBlancos,blancos))==12){
                                    window.close();
                                    se_rinde=false;
                                    ventana_ganador();
                                    carga_imagenes_fichas();
                        }
                            if(contar_eliminados_negros(PeonesNegros,negros)==12){
                                    window.close();
                                    se_rinde=true;
                                    ventana_ganador();
                                    carga_imagenes_fichas();
                            }

                    }
            }
            mostrar_juego(window,sprite);
            if(event.type == sf::Event::MouseMoved)
            {
                if(((event.mouseMove.x >=410)&&(event.mouseMove.x<=530))&&((event.mouseMove.y>=615)&&(event.mouseMove.y<=640))){
                            rendirse->setOutlineColor(Color::Red);
                            rendirse->setOutlineThickness(3);
                }else{
                            rendirse->setOutlineColor(Color::Black);
                            rendirse->setOutlineThickness(3);
                }
            }
}
}
//funcion para mostrar en pantalla el color y las damas en pantalla

void mostrar_juego(RenderWindow &window,Sprite *sprite){
    int i;
        oculta_peones_eliminados();
        window.clear(Color::Transparent);
        window.draw(*sprite);

             for(i=0;i<12;i++){
                PeonesBlancos[i]->Peon->setPosition(PeonesBlancos[i]->casilleroPeon->pos_peonX,PeonesBlancos[i]->casilleroPeon->pos_peonY);
                PeonesBlancos[i]->Rey->setPosition(PeonesBlancos[i]->casilleroPeon->pos_peonX,PeonesBlancos[i]->casilleroPeon->pos_peonY);
                PeonesNegros[i]->Peon->setPosition(PeonesNegros[i]->casilleroPeon->pos_peonX,PeonesNegros[i]->casilleroPeon->pos_peonY);
                PeonesNegros[i]->Rey->setPosition(PeonesNegros[i]->casilleroPeon->pos_peonX,PeonesNegros[i]->casilleroPeon->pos_peonY);
                window.draw(*PeonesBlancos[i]->Peon);
                window.draw(*PeonesNegros[i]->Peon);
                window.draw(*PeonesNegros[i]->Rey);
                window.draw(*PeonesBlancos[i]->Rey);
            }

            for(i=0;i<cantidadPosibilidades;i++){
                vector_disponibles[i]->posiblePeon->setPosition(vector_disponibles[i]->pos_peonX,vector_disponibles[i]->pos_peonY);
                vector_disponibles[i]->posiblePeon->setFillColor(Color(238,136,87));
                window.draw(*vector_disponibles[i]->posiblePeon);
            }
        if(turno_negro){
            cantfichas2->setString((convertir(contar_eliminados_negros(PeonesNegros,negros))));
            window.draw(*equipo_negro);
            window.draw(*fichas2);
            window.draw(*cantfichas2);
        }else{
            cantfichas1->setString(convertir((contar_eliminados_blancos(PeonesBlancos,blancos))));
            window.draw(*equipo_blanco);
            window.draw(*fichas1);
            window.draw(*cantfichas1);
        }
        window.draw(*rendirse);
        window.display();
}

//cuando hacen un click con el boton llaman a esta funcion

void eventoClickMouse(Event &event,TPeon *&seleccionadoAux){
        if(seleccionadoAux!=NULL)
            seleccionadoAux->Peon->setOutlineThickness(0);  //coloca contorno a la ficha seleccionada
                                cout<<"El boton fue presionado"<<endl;
                                cout<<"mouse x:"<<event.mouseButton.x<<endl;
                                cout<<"mouse y:"<<event.mouseButton.y<<endl;

 if (event.mouseButton.button == Mouse::Left){ //confirma el movimiento

                        if(seleccionadoAux!=NULL){
                            if(movimientos_posibles(event.mouseButton.x ,event.mouseButton.y)){


                                if(turno_negro)
                                    turno_negro=false;
                                else
                                    turno_negro=true;

                                ver_si_elimino_peon(seleccionadoAux,event.mouseButton.x ,event.mouseButton.y);
                                mover_ficha(seleccionadoAux,event.mouseButton.x ,event.mouseButton.y);
                                es_dama(seleccionadoAux);

                            }limpiar_vector_disponibles(cantidadPosibilidades,cantidadPosibilidadesMovimientosLargo);
                            seleccionadoAux=NULL;
                        }
                }

                if(event.mouseButton.button==Mouse::Left){//Primer clic dice el posible movimiento

                    if (turno_negro){
                        seleccionadoAux=seleccionarPeon(PeonesNegros,event.mouseButton.x ,event.mouseButton.y);
                    }else{
                        seleccionadoAux=seleccionarPeon(PeonesBlancos,event.mouseButton.x ,event.mouseButton.y);
                    }
                    if(cantidadPosibilidades!=0)
                        limpiar_vector_disponibles(cantidadPosibilidades,cantidadPosibilidadesMovimientosLargo);

                        if(seleccionadoAux!=NULL){
                            carga_movimientos_posibles(seleccionadoAux);
                            seleccionadoAux->Peon->setOutlineColor(Color::Green);
                            seleccionadoAux->Peon->setOutlineThickness(3);
                        }

                }
}

//muestra el texto en pantalla general

int texto_juego(){

    if(!fuente1->loadFromFile("Damage.ttf"))
        return EXIT_FAILURE;

    if(!fuente2->loadFromFile("Gameplay.ttf"))
        return EXIT_FAILURE;

    String cadenaAbandonarPartida="Rendirse";

    rendirse=new Text(cadenaAbandonarPartida,*fuente1,30);
    rendirse->setColor(Color::Yellow);
    rendirse->setOutlineColor(Color::Black);
    rendirse->setOutlineThickness(3);
    rendirse->setPosition(410,610);

    texto_jugador1();
    texto_jugador2();

}

//Texto que aparecera cuando sea el turno del jugador blanco
void texto_jugador1(){


    String jugador1="Turno Blanco";
    String cadenaCantidadFichas1="Fichas Capturadas: ";

    equipo_blanco=new Text(jugador1,*fuente2,15);
    equipo_blanco->setColor(Color::Green);
    equipo_blanco->setOutlineColor(Color::Black);
    equipo_blanco->setOutlineThickness(3);
    equipo_blanco->setPosition(25,590);

    fichas1=new Text(cadenaCantidadFichas1,*fuente2,15);
    fichas1->setColor(Color::Green);
    fichas1->setOutlineColor(Color::Black);
    fichas1->setOutlineThickness(3);
    fichas1->setPosition(25,620);

    cantfichas1=new Text("0",*fuente2,30);
    cantfichas1->setColor(Color::Green);
    cantfichas1->setOutlineColor(Color::Black);
    cantfichas1->setOutlineThickness(3);
    cantfichas1->setPosition(210,610);

}

//Texto que aparecera cuando sea el turno del jugador negro
void texto_jugador2 (){

    String jugador2="Turno Negro";
    String cadenaCantidadFichas2="Fichas Capturadas: ";

    equipo_negro=new Text(jugador2,*fuente2,15);
    equipo_negro->setColor(Color::Green);
    equipo_negro->setOutlineColor(Color::Black);
    equipo_negro->setOutlineThickness(3);
    equipo_negro->setPosition(25,590);

    fichas2=new Text(cadenaCantidadFichas2,*fuente2,15);
    fichas2->setColor(Color::Green);
    fichas2->setOutlineColor(Color::Black);
    fichas2->setOutlineThickness(3);
    fichas2->setPosition(25,620);

    cantfichas2=new Text("0",*fuente2,30);
    cantfichas2->setColor(Color::Green);
    cantfichas2->setOutlineColor(Color::Black);
    cantfichas2->setOutlineThickness(3);
    cantfichas2->setPosition(210,610);

}
