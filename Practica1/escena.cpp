#include "escena.h"

using namespace std;

Escena::Escena()
{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes

    capsaMinima = CapsaMinCont3DEscena();

    taulaBillar = NULL;
    plabase = NULL;
    bola = NULL;
    conjuntboles = NULL;
}

Escena::~Escena()
{
    // Cal anar fent delete dels objectes que se'l hagi fet new
   delete this->taulaBillar;
   delete this->plabase;
   delete this->bola;
   delete this->conjuntboles;
}

void Escena::addObjecte(Objecte *obj) {

    if (dynamic_cast<TaulaBillar*>(obj))
    {
        this->taulaBillar = (TaulaBillar*)obj;
        objectes.push_back(taulaBillar);
    }

    if (dynamic_cast<Plabase*>(obj))
    {
        this->plabase = (Plabase*)obj;
        objectes.push_back(plabase);
    }

    if (dynamic_cast<Bola*>(obj))
    {
        this->bola = (Bola*)obj;
        objectes.push_back(bola);
    }

    if (dynamic_cast<ConjuntBoles*>(obj)){
        this->conjuntboles = (ConjuntBoles*)obj;
        objectes.push_back(conjuntboles);
    }

    capsaMinima = CapsaMinCont3DEscena();

}


Capsa3D Escena::CapsaMinCont3DEscena()
{
    // Metode a implementar

    bool init = false;

    for (iterador = this->objectes.begin(); iterador < this->objectes.end(); ++iterador) {
        if(*iterador!=NULL){

           if (init == false){
               capsaMinima.pmin = (*iterador)->capsa.pmin ;
               capsaMinima.a = (*iterador)->capsa.a;
               capsaMinima.h = (*iterador)->capsa.h;
               capsaMinima.p = (*iterador)->capsa.p;
               init = true;
           } else{
               if (capsaMinima.pmin.x > (*iterador)->capsa.pmin.x)
                   capsaMinima.pmin.x = (*iterador)->capsa.pmin.x;
               if (capsaMinima.pmin.y > (*iterador)->capsa.pmin.y)
                   capsaMinima.pmin.y = (*iterador)->capsa.pmin.y;
               if (capsaMinima.pmin.z > (*iterador)->capsa.pmin.z)
                   capsaMinima.pmin.z = (*iterador)->capsa.pmin.z;

               if (capsaMinima.a < (*iterador)->capsa.a)
                   capsaMinima.a = (*iterador)->capsa.a;
               if (capsaMinima.h < (*iterador)->capsa.h)
                   capsaMinima.h = (*iterador)->capsa.h;
               if (capsaMinima.p < (*iterador)->capsa.p)
                   capsaMinima.p = (*iterador)->capsa.p;
           }
        }
    }
}

void Escena::aplicaTG(mat4 m) {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->aplicaTG(m);
    if (plabase != NULL)
        plabase-> aplicaTG(m);
    if (bola != NULL)
        bola-> aplicaTG(m);
    if (conjuntboles != NULL)
        conjuntboles-> aplicaTG(m);

}

void Escena::aplicaTGCentrat(mat4 m) {

    // Metode a modificar

    point4 centre_escena;
    centre_escena.x = capsaMinima.pmin.x + (capsaMinima.a /2.);
    centre_escena.y = capsaMinima.pmin.y + (capsaMinima.h /2.);
    centre_escena.z = capsaMinima.pmin.z + (capsaMinima.p /2.);

    mat4 m1 = Translate(-centre_escena);
    mat4 m2 = Translate(centre_escena);
    mat4 mTotal = m2 * m * m1;

    if (taulaBillar!=NULL)
        taulaBillar->aplicaTG(mTotal);
    if(plabase != NULL)
        plabase -> aplicaTG(mTotal);
    if(bola != NULL)
        bola -> aplicaTG(mTotal);
    if(conjuntboles != NULL)
        conjuntboles -> aplicaTG(mTotal);


}

void Escena::draw() {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->draw();
    if (plabase != NULL)
        plabase -> draw();
    if (bola != NULL)
        bola -> draw();
    if (conjuntboles != NULL)
        conjuntboles -> draw();

}

void Escena::moveDavant(){

    if(bola!=NULL){

        bola->capsa=bola->calculCapsa3D();

        bool distanciaConjunt = true;

        if(conjuntboles!=NULL){
            for (conjuntboles->iterador = conjuntboles->boles.begin(); conjuntboles->iterador < conjuntboles->boles.end(); ++conjuntboles->iterador) {
                if(*conjuntboles->iterador!=NULL){
                    (*conjuntboles->iterador)->capsa=(*conjuntboles->iterador)->calculCapsa3D();
                    if (fabs((*conjuntboles->iterador)->capsa.pmin.z - bola->capsa.pmin.z) <= bola->capsa.p + bola->deltaDesplacament*1.5
                            && fabs((*conjuntboles->iterador)->capsa.pmin.x - bola->capsa.pmin.x) <= bola->capsa.a + bola->deltaDesplacament){
                        distanciaConjunt=false;
                    }
                }
            }
        }

        if(plabase!=NULL){
            plabase->capsaplabase=plabase->calculCapsa3D();
            if (fabs((plabase->capsaplabase.pmin.z + plabase->capsaplabase.p) - (bola->capsa.pmin.z + bola->capsa.p)) > bola->deltaDesplacament && distanciaConjunt==true){
                bola->moveDavant();
            }
        }
    }
}

void Escena::moveDarrera(){
    if(bola!=NULL){
        if(plabase!=NULL){
            bola->capsa=bola->calculCapsa3D();
            plabase->capsaplabase=plabase->calculCapsa3D();
            if (fabs(plabase->capsaplabase.pmin.z - bola->capsa.pmin.z) > bola->deltaDesplacament){
                bola->moveDarrera();
            }
        }
    }
}

void Escena::moveDreta(){
    if(bola!=NULL){
        if(plabase!=NULL){
            bola->capsa=bola->calculCapsa3D();
            plabase->capsaplabase=plabase->calculCapsa3D();
            if (fabs((plabase->capsaplabase.pmin.x + plabase->capsaplabase.a) - (bola->capsa.pmin.x + bola->capsa.a)) > bola->deltaDesplacament){
                bola->moveDreta();
            }
        }
    }
}
void Escena::moveEsquerra(){
    if(bola!=NULL){
        if(plabase!=NULL){
            bola->capsa=bola->calculCapsa3D();
            plabase->capsaplabase=plabase->calculCapsa3D();
            if (fabs(plabase->capsaplabase.pmin.x - bola->capsa.pmin.x) > bola->deltaDesplacament){
                bola->moveEsquerra();
            }
        }
    }
}

