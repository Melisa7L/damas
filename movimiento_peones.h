#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

void peones_izq_der (TPeon *auxPeon,Tcasilla *aux,bool boolDamaActivo);
void pueden_comer (Tcasilla *aux,bool &boolAux);
void izq_der_2(TPeon *auxPeon,Tcasilla *aux,bool &boolComioOk,bool &boolDamaActivo);
void pueden_comer_2(TPeon *auxSeleccionado,TPeon *auxPeonMedio,bool boolIzquierdaOk,bool &boolComioOk,bool &boolDamaActivo);

int cantidadPosibilidades=0;
int cantidadPosibilidadesIntermedio=0;
int cantidadPosibilidadesMovimientosLargo=0;


//RECORRE LOS MOVIMIENTOS POSIBLES


void carga_vector_disponibles(Tcasilla *auxCargar){

    vector_disponibles[cantidadPosibilidades]=auxCargar;
    cantidadPosibilidades++;
}


void carga_movimientos_posibles(TPeon *auxPeon){  //ve los movimientos posibles, recorriendo por sectores

	if(auxPeon->NegroOk){
        if(auxPeon->si_dama)
           peones_izq_der(auxPeon,auxPeon->casilleroPeon->abajo,true);
        peones_izq_der(auxPeon,auxPeon->casilleroPeon->arriba,false);
	}else{
        if(auxPeon->si_dama)
           peones_izq_der(auxPeon,auxPeon->casilleroPeon->arriba,true);
        peones_izq_der(auxPeon,auxPeon->casilleroPeon->abajo,false);
	}
}



 //varifica y carga en el vector de disponibilidad


void peones_izq_der(TPeon *auxPeon,Tcasilla *aux,bool boolDamaActivo){
bool boolComioOk;

    if(aux!=NULL){
        if(aux->derecha==NULL && aux->izquierda!=NULL){

            if(buscar_peones_en_casilla(aux->izquierda)!=NULL)
                pueden_comer_2(auxPeon,buscar_peones_en_casilla(aux->izquierda),true,boolComioOk,boolDamaActivo);
            else
                carga_vector_disponibles(aux->izquierda);
        }


        if(aux->izquierda==NULL && aux->derecha!=NULL){

            if(buscar_peones_en_casilla(aux->derecha)!=NULL)
                pueden_comer_2(auxPeon,buscar_peones_en_casilla(aux->derecha),false,boolComioOk,boolDamaActivo);
            else
                carga_vector_disponibles(aux->derecha);
        }

        izq_der_2(auxPeon,aux,boolComioOk,boolDamaActivo);
    }
}

//procedimiento aparte si la izquieda y derecha esta ocupado o no


void izq_der_2(TPeon *auxPeon,Tcasilla *aux,bool &boolComioOk,bool &boolDamaActivo){

    if(aux->derecha!=NULL &&aux->izquierda!=NULL){

       if(buscar_peones_en_casilla(aux->derecha)==NULL && buscar_peones_en_casilla(aux->izquierda)==NULL){
            carga_vector_disponibles(aux->derecha);
            carga_vector_disponibles(aux->izquierda);
       }

        if(buscar_peones_en_casilla(aux->derecha)!=NULL && buscar_peones_en_casilla(aux->izquierda)==NULL){
            pueden_comer_2(auxPeon,buscar_peones_en_casilla(aux->derecha),false,boolComioOk,boolDamaActivo);
                if(not boolComioOk)
                    carga_vector_disponibles(aux->izquierda);
        }


        if(buscar_peones_en_casilla(aux->izquierda)!=NULL && buscar_peones_en_casilla(aux->derecha)==NULL){
            pueden_comer_2(auxPeon,buscar_peones_en_casilla(aux->izquierda),true,boolComioOk,boolDamaActivo);
                if(not boolComioOk)
                    carga_vector_disponibles(aux->derecha);
        }


        if(buscar_peones_en_casilla(aux->izquierda)!=NULL && buscar_peones_en_casilla(aux->derecha)!=NULL){
            pueden_comer_2(auxPeon,buscar_peones_en_casilla(aux->izquierda),true,boolComioOk,boolDamaActivo);
            pueden_comer_2(auxPeon,buscar_peones_en_casilla(aux->derecha),false,boolComioOk,boolDamaActivo);
        }

    }
}


//devuelve un booleano si puede o no mover donde seleciono el jugador
//la funcion solo se encarga de ver las posibilidades se mueve

bool movimientos_posibles (int posicionX, int posicionY){
    int i;
    Tcasilla *aux;
        aux=buscarCasilleroPorPosicion(posicionX,posicionY);

        for(i=0;i<cantidadPosibilidades;i++){
            if(vector_disponibles[i]->pos_peonX==aux->pos_peonX){
                if(vector_disponibles[i]->pos_peonY==aux->pos_peonY)
                    return true;
            }

        }return false;
}


//busca si se puede comer o no dependiendo si hay espacio o si esta

void pueden_comer_2(TPeon *auxSeleccionado,TPeon *auxPeonMedio,bool boolIzquierdaOk,bool &boolComioOk,bool &boolDamaActivo){

        if(auxSeleccionado->NegroOk && not auxPeonMedio->NegroOk){
            if(boolIzquierdaOk){
                    if(boolDamaActivo){
                        if(auxPeonMedio->casilleroPeon->abajo!=NULL)
                            pueden_comer(auxPeonMedio->casilleroPeon->abajo->izquierda,boolComioOk);
                    }else{
                        if(auxPeonMedio->casilleroPeon->arriba!=NULL)
                            pueden_comer(auxPeonMedio->casilleroPeon->arriba->izquierda,boolComioOk);
                    }

            }else{
                    if(boolDamaActivo){
                        if(auxPeonMedio->casilleroPeon->abajo!=NULL)
                            pueden_comer(auxPeonMedio->casilleroPeon->abajo->derecha,boolComioOk);
                    }else{
                        if(auxPeonMedio->casilleroPeon->arriba!=NULL)
                            pueden_comer(auxPeonMedio->casilleroPeon->arriba->derecha,boolComioOk);
                    }
            }
        }


        if(not auxSeleccionado->NegroOk && auxPeonMedio->NegroOk){
                if(boolIzquierdaOk){
                        if(boolDamaActivo){
                            if(auxPeonMedio->casilleroPeon->arriba!=NULL)
                                pueden_comer(auxPeonMedio->casilleroPeon->arriba->izquierda,boolComioOk);
                        }else{
                            if(auxPeonMedio->casilleroPeon->abajo!=NULL)
                                pueden_comer(auxPeonMedio->casilleroPeon->abajo->izquierda,boolComioOk);
                        }

                }else{
                        if(boolDamaActivo){
                            if(auxPeonMedio->casilleroPeon->arriba!=NULL)
                                pueden_comer(auxPeonMedio->casilleroPeon->arriba->derecha,boolComioOk);
                        }else{
                            if(auxPeonMedio->casilleroPeon->abajo!=NULL)
                                pueden_comer(auxPeonMedio->casilleroPeon->abajo->derecha,boolComioOk);
                        }

                }
        }
}




//continuaciond de la funcion de ver si puede comer

void pueden_comer(Tcasilla *aux,bool &boolComioOk){

    if(aux!=NULL && buscar_peones_en_casilla(aux)==NULL){

        vector_disponibles[cantidadPosibilidades]=aux;
        cantidadPosibilidades++;

        vector_movimiento_largo[cantidadPosibilidadesMovimientosLargo]=aux;
        cantidadPosibilidadesMovimientosLargo++;

        boolComioOk=true;
    }
}

//elimina un peon si se elimino

void ver_si_elimino_peon (TPeon *selecionadoAux,int posicionX, int posicionY) {

        int i;
        bool auxActivo=false;
        Tcasilla *nuevaPosicion;
        TPeon *auxPeon;

            nuevaPosicion=buscarCasilleroPorPosicion(posicionX,posicionY);

        for(i=0;i<cantidadPosibilidadesMovimientosLargo;i++){
            if(vector_movimiento_largo[i]->pos_peonX==nuevaPosicion->pos_peonX){
                if(vector_movimiento_largo[i]->pos_peonY==nuevaPosicion->pos_peonY)
                    auxActivo=true;
            }
        }

        if(auxActivo){
            if(nuevaPosicion->pos_peonX>selecionadoAux->casilleroPeon->pos_peonX){
                    if(nuevaPosicion->pos_peonY>selecionadoAux->casilleroPeon->pos_peonY){
                        auxPeon=buscar_peones_en_casilla(selecionadoAux->casilleroPeon->abajo->derecha);
                        auxPeon->boolEliminado=true;
                    }else{
                        auxPeon=buscar_peones_en_casilla(selecionadoAux->casilleroPeon->arriba->derecha);
                        auxPeon->boolEliminado=true;
                    }
            }else{
                    if(nuevaPosicion->pos_peonY>selecionadoAux->casilleroPeon->pos_peonY){
                        auxPeon=buscar_peones_en_casilla(selecionadoAux->casilleroPeon->abajo->izquierda);
                        auxPeon->boolEliminado=true;
                    }else{
                        auxPeon=buscar_peones_en_casilla(selecionadoAux->casilleroPeon->arriba->izquierda);
                        auxPeon->boolEliminado=true;
                    }
            }

        }


}
