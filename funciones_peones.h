#include <iostream>

int blancos = 0; //contadores de fichas blancas
int negros = 0; //contadores de fichas negras

//selecciona un peon desde el vector de peones con el click derecho

TPeon *seleccionarPeon (TPeon *vectorPeones[],int posicionX,int posicionY)
{

    int i;
    Tcasilla *aux;
    //en un auxiliar guarda las coordenadas que se reciben con el click
    aux=buscarCasilleroPorPosicion(posicionX,posicionY);
    if(aux!=NULL){

        for(i=0;i<12;i++){
             //la primera condicion es que no haya seleccionado una zona donde el peon fue eliminado ya que seria un lugar vacio
            if(!vectorPeones[i]->boolEliminado){
   //teniendo en cuenta el vectorPeones, si el seleccionado con el click coincide con una coordenada que tiene el peon
   //guarda las coordenadas correspondientes ya que si se cumple que haya un peon alli
                if(vectorPeones[i]->casilleroPeon->pos_peonX==aux->pos_peonX){
                    if(vectorPeones[i]->casilleroPeon->pos_peonY==aux->pos_peonY)
                        return vectorPeones[i]; //devuelve el peon elegido
                }
            }

        }
    }
    return NULL;
}

//Al hacer click con el izquierdo se elije y se mueve la ficha

void mover_ficha (TPeon *peonSeleccionado,int posicionX,int posicionY){

    Tcasilla *aux;
    aux=buscarCasilleroPorPosicion(posicionX,posicionY); //guarda las coordenadas del casillero elegido

    //con una bandera verifica si esta ocupada con un peon la casilla o no
        peonSeleccionado->casilleroPeon->boolOcupado=false;
        aux->boolOcupado=true;
        peonSeleccionado->casilleroPeon=aux; //guarda a ese peon en un auxiliar

}



//limpia el vector los posibles movimientos que tiene cada ficha segun su situacion
void limpiar_vector_disponibles(int &cantidadPosibilidades,int &cantidadPosibilidadesMovimientosLargo){
    int k;
        for(k=0;k<cantidadPosibilidades;k++){
            vector_disponibles[k]->posiblePeon->setFillColor(Color::Transparent); //con el color transparente las oculta a las fichas
            vector_disponibles[k]=NULL; //deja el vector en esa posicion en null
        }   cantidadPosibilidades=0;


        for(k=0;k<cantidadPosibilidadesMovimientosLargo;k++){
            vector_movimiento_largo[k]=NULL;
        }   cantidadPosibilidadesMovimientosLargo=0;
}

//fucncion que busca los peones eliminados y no lo muestra
void oculta_peones_eliminados (){
    int i;

    for(i=0;i<12;i++){
       if(PeonesBlancos[i]->boolEliminado){
            //Pone en transparente a los peones y damas blancas para ocultarlas
            PeonesBlancos[i]->Peon->setFillColor(Color::Transparent);
            PeonesBlancos[i]->Rey->setFillColor(Color::Transparent);

       }
       if(PeonesNegros[i]->boolEliminado){
            //Pone en transparente a los peones y damas negras para ocultarlas
             PeonesNegros[i]->Peon->setFillColor(Color::Transparent);
             PeonesNegros[i]->Rey->setFillColor(Color::Transparent);
       }

    }

}


//busca un peon por un casillero enviado por parametro

TPeon *buscar_peones_en_casilla (Tcasilla *aux){
    int i;

    for(i=0;i<12;i++){

        if(!PeonesBlancos[i]->boolEliminado){ //si el peon no fue eliminado
            if(PeonesBlancos[i]->casilleroPeon->pos_peonX==aux->pos_peonX){ //manda valores de X
                 if(PeonesBlancos[i]->casilleroPeon->pos_peonY==aux->pos_peonY)  //manda valores de Y
                    return PeonesBlancos[i];
            }
        }


        if(!PeonesNegros[i]->boolEliminado){ //si el peon no fue eliminado
            if(PeonesNegros[i]->casilleroPeon->pos_peonX==aux->pos_peonX){ //manda valores de X
                 if(PeonesNegros[i]->casilleroPeon->pos_peonY==aux->pos_peonY) //manda valores de Y
                    return PeonesNegros[i];
            }
        }
    }
    return NULL;
}


//verifica si es dama ,revisa cada vez que se mueva una ficha
void es_dama (TPeon *aux){

    if(aux->NegroOk){
        if(aux->casilleroPeon->arriba==NULL){
//con esta condicion analiza si ubicando el puntero hacia arriba--
//no hay ningun casillero es porque se llego a la zona de las damas porque se llego al otro extremo
            aux->si_dama=true;
            aux->Rey->setFillColor(Color::White);
        }

    }else{
//con esta condicion analiza si ubicando el puntero hacia abajo--
//no hay ningun casillero es porque se llego a la zona de las damas porque se llego al otro extremo
        if(aux->casilleroPeon->abajo==NULL){
            aux->si_dama=true;
            aux->Rey->setFillColor(Color::White);
        }
    }
}

int contar_eliminados_blancos(TPeon *PeonesBlancos[],int blancos){
    for(int i=0; i<12; i++){
        if(PeonesBlancos[i]->boolEliminado){
            blancos ++; //si algun elemento del vector de peones blancos se elimino se incrementa el contador
        }
    }
    return blancos;   //devuelve las cantidades actuales de peones blancos
}

int contar_eliminados_negros(TPeon *PeonesNegros[],int negros){
    int cantidad2;
    for(int i=0; i<12; i++){
        if(PeonesNegros[i]->boolEliminado){
            negros ++;  //si algun elemento del vector de peones negros se elimino se incrementa el contador
        }
    }
    return negros; //devuelve las cantidades actuales de peones negros
}
