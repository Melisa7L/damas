#include <iostream> //libreria para usar el cin y cout
#define TAMANOMAX 8
#define TAMANIOMAXPOSIBILIDAD 4


using namespace sf;
using namespace std;

//Vector que guarda las posiciones para ubicar al peon

int vec_ejes_y[TAMANOMAX]={42,108,174,242,308,376,442,509};
int vec_ejes_x[TAMANOMAX]={42,110,176,244,310,378,444,511};

//Vector que guarda las posiciones para hacer click en el mouse

int vec_clic_y[]={29,100,166,234,299,367,435,500,571};
int vec_clic_x[]={29,101,166,234,302,367,434,501,568};


struct Tcasilla{ // Estructura de un casillero
    bool boolOcupado; //bandera para saber si esta ocupado o no
	int pos_peonX;//variable que tiene la posicion horizontal del peon
	int pos_peonY; //variable que tiene la posicion vertical del peon
	int pos_Xinicial;
	int pos_Xfinal;
	int pos_Yinicial;
	int pos_Yfinal;
	string ubicacionCasilla;

	//estos punteros nos sirven para recorrer las casillas y saber en que ubicacion se encuentra respecto del tablero
    //son los movimientos basicos(arriba,abajo,izq y der)
	struct Tcasilla *arriba;
	struct Tcasilla *abajo;
	struct Tcasilla *izquierda;
	struct Tcasilla *derecha;
	CircleShape *posiblePeon;  //crea una figura (circulo para el peon)
}*vector_posiciones[TAMANOMAX],  //vector de punteros para las posiciones
*vector_disponibles[TAMANIOMAXPOSIBILIDAD];  //vector de punteros para las posibilidades de movimientos que hay



// busca un casillero por una posicion que le mandamos por parametro

Tcasilla *buscarCasilleroPorPosicion(int x, int y){  //tiene por parametros las coordenadas de X e Y que se mandaron
    Tcasilla *aux; //se usa un puntero auxiliar tipo Tcasilla
    int i;

    for (i=0;i<TAMANOMAX;i++){  //va a recorrer mientras no se pase de las 8 casillas
		aux=vector_posiciones[i];  //carga el valor en el auxiliar
            while (aux!=NULL){ //mientras no sea nulo es decir que tenga un valor cargado
                // mientras se mantenga en los rangos que se establecieron en el x(horizontal)
                if (x>aux->pos_Xinicial&&x<aux->pos_Xfinal){
                    // mientras se mantenga en los rangos que se establecieron en el y(vertical)
                    if(y>aux->pos_Yinicial&&y<aux->pos_Yfinal)
                        return aux;
                }
                aux=aux->derecha;
            }
    }return NULL;
}


// enlaza cada cuadro con su respectivo casillero

void enlaces_graficos_de_casillas(){
    struct Tcasilla *aux;
	int i,j; //se trabajara como una matriz por eso se utilizan los parametros i y j

	for (i=0;i<TAMANOMAX;i++){
		aux=vector_posiciones[i]; // a medida que se va recorriendo el vector se le asigna el nuevo valor al aux
		j=0;
            while (aux!=NULL){
                    //mientras se carguen valores , al auxiliar se le asignan los valores hor y verticales del click
                aux->pos_Xinicial=vec_clic_y[j];
                aux->pos_Xfinal=vec_clic_y[j+1];
                aux->pos_Yinicial=vec_clic_x[i];
                aux->pos_Yfinal=vec_clic_x[i+1];
                aux=aux->derecha;
                j++;
       }
	}

}

// enlaza las posiciones de cada peon con su correspondiente grafico

//es similar al procedimiento anterior solo que aca se relacionan --
//los peones con los graficos respecto de los ejes correspondientes

void enlace_grafico() {
	struct Tcasilla *aux;
	int i,j;

	for (i=0;i<TAMANOMAX;i++){
		aux=vector_posiciones[i];
		j=0;
            while (aux!=NULL){ //mientras existan los valores se recorren
                aux->pos_peonX=vec_ejes_y[j];
                aux->pos_peonY=vec_ejes_x[i];
                aux=aux->derecha;
                j++;
            }
	}
}


// agrega una ubicacion a las casillas como A1,A2,A3,etc. como se hacia en el ajedrez

void agregar_en_casilla(){
    Tcasilla *aux=vector_posiciones[0]; //llegan las coordenadas de las posiciones al puntero
    Tcasilla *aux2=aux;
    string numeroAux, letraAux;
    int numeroInt=56; //numeros en codigoASCII
    int letraInt=65; //letras en codigoASCII


    while (aux2!=NULL) {  //mientras existan los valores de las coordenadas
            aux=aux2;
        while (aux!=NULL){  //mientras no sean nulos
            letraAux=int(letraInt);
            numeroAux=int(numeroInt);
            aux->ubicacionCasilla=letraAux+numeroAux;
            aux=aux->abajo;
            numeroInt--;
        }
        aux2=aux2->derecha;
        letraInt++;
        numeroInt=56;
    }
}

//crea un nuevo elemento un nuevo Tcasillero

struct Tcasilla *nuevoCasillero (){
	struct Tcasilla *nuevoElemento = new Tcasilla;

		if(nuevoCasillero!=NULL){
                //a continuacion se observan todos los atributos que tienen los casilleros
			nuevoElemento->boolOcupado=false;
			nuevoElemento->abajo=NULL;
			nuevoElemento->arriba=NULL;
			nuevoElemento->izquierda=NULL;
			nuevoElemento->derecha=NULL;
			nuevoElemento->posiblePeon=new CircleShape(25);
			nuevoElemento->posiblePeon->setFillColor(Color::Transparent);
			nuevoElemento->posiblePeon->setFillColor(Color::Magenta);
			return nuevoElemento;
		}else{
			printf("No hay Memoria Disponible \n");system("Pause");
		}
}

// llama a crear un casillero y enlaza los casilleros horizontalmente

void enlace_x(){
	struct Tcasilla *nuevo,*aux;
	int i,j;

		for(i=0;i<TAMANOMAX;i++){
			if(vector_posiciones[i]==NULL){ // esto es cuando no se creo ningun casillero todavia
				vector_posiciones[i]=nuevoCasillero();  //aca se crea
			}
				aux=vector_posiciones[i]; //para cuando hay un casillero al menos que haya sido cargado
				for(j=0;j<7;j++){
					nuevo=nuevoCasillero();
					aux->derecha=nuevo; //carga el nuevo casillero en el auxiliar del lado derecho
					nuevo->izquierda=aux; //a nuevo le carga el valor del aux de la izquierda
					aux=aux->derecha;
				}
		}
}

// enlazar los casilleros verticalmente
// cuando termina llama una funcion de poner los nombres a los casilleros osea A1,A2 etc y
//tambien llama a enlazar cada X e Y con su cuadro

void enlace_y(){
	struct Tcasilla *aux1,*aux2;
	int i,j;

		for(i=0;i<7;i++){
			aux1=vector_posiciones[i];
			aux2=vector_posiciones[i+1];

				for(j=0;j<TAMANOMAX;j++){
					aux1->abajo=aux2;
					aux2->arriba=aux1;
					aux1=aux1->derecha;
					aux2=aux2->derecha;
				}
		}

    agregar_en_casilla();
    enlaces_graficos_de_casillas();

}
