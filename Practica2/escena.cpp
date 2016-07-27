#include "escena.h"

using namespace std;

Escena::Escena()
{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes

    CapsaMinCont3DEscena();
    taulaBillar = NULL;
    plabase = NULL;
    bola = NULL;
    conjuntboles = NULL;

    camGeneral = new Camera();

    cameraActual = true;

    iniCamera(cameraActual, width, height);
}

Escena::~Escena()
{
    // Cal anar fent delete dels objectes que se'l hagi fet new
   delete this->taulaBillar;
   delete this->plabase;
   delete this->bola;
   delete this->conjuntboles;
   delete this->camGeneral;
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

    CapsaMinCont3DEscena();

    iniCamera(cameraActual, width, height);

}


Capsa3D Escena::CapsaMinCont3DEscena()
{
    // Metode a implementar

    if (!objectes.empty())
    {
        vec3 pmin, pmax;

        pmin.x = objectes[0]->capsa.pmin.x;
        pmin.y = objectes[0]->capsa.pmin.y;
        pmin.z = objectes[0]->capsa.pmin.z;

        pmax.x = objectes[0]->capsa.pmin.x + objectes[0]->capsa.a;
        pmax.y = objectes[0]->capsa.pmin.y + objectes[0]->capsa.h;
        pmax.z = objectes[0]->capsa.pmin.z + objectes[0]->capsa.p;

        if (objectes.size() > 1)
        {

            for (int i = 1; i < objectes.size(); i++){
                if (objectes[i]->capsa.pmin.x < pmin.x)
                    pmin.x = objectes[i]->capsa.pmin.x;
                if (objectes[i]->capsa.pmin.y < pmin.y)
                    pmin.y = objectes[i]->capsa.pmin.y;
                if (objectes[i]->capsa.pmin.z < pmin.z)
                    pmin.z = objectes[i]->capsa.pmin.z;

                if (objectes[i]->capsa.pmin.x + objectes[i]->capsa.a > pmax.x)
                    pmax.x = objectes[i]->capsa.pmin.x + objectes[i]->capsa.a;
                if (objectes[i]->capsa.pmin.y + objectes[i]->capsa.h > pmax.y)
                    pmax.y = objectes[i]->capsa.pmin.y + objectes[i]->capsa.h;
                if (objectes[i]->capsa.pmin.z + objectes[i]->capsa.p > pmax.z)
                    pmax.z = objectes[i]->capsa.pmin.z + objectes[i]->capsa.p;
            }

        }

        capsaMinima.pmin = pmin;

        capsaMinima.a = pmax.x - pmin.x;
        capsaMinima.h = pmax.y - pmin.y;
        capsaMinima.p = pmax.z - pmin.z;
    }
    return capsaMinima;

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

        bola->calculCapsa3D();

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
            plabase->capsa=plabase->calculCapsa3D();
            if (fabs((plabase->capsa.pmin.z + plabase->capsa.p) - (bola->capsa.pmin.z + bola->capsa.p)) > bola->deltaDesplacament && distanciaConjunt==true){
                bola->moveDavant();
            }
        }
    }
}

void Escena::moveDarrera(){
    if(bola!=NULL){
        if(plabase!=NULL){
            bola->capsa=bola->calculCapsa3D();
            plabase->capsa=plabase->calculCapsa3D();
            if (fabs(plabase->capsa.pmin.z - bola->capsa.pmin.z) > bola->deltaDesplacament){
                bola->moveDarrera();
            }
        }
    }
}

void Escena::moveDreta(){
    if(bola!=NULL){
        if(plabase!=NULL){
            bola->capsa=bola->calculCapsa3D();
            plabase->capsa=plabase->calculCapsa3D();
            if (fabs((plabase->capsa.pmin.x + plabase->capsa.a) - (bola->capsa.pmin.x + bola->capsa.a)) > bola->deltaDesplacament){
                bola->moveDreta();
            }
        }
    }
}

void Escena::moveEsquerra(){
    if(bola!=NULL){
        if(plabase!=NULL){
            bola->capsa=bola->calculCapsa3D();
            plabase->capsa=plabase->calculCapsa3D();
            if (fabs(plabase->capsa.pmin.x - bola->capsa.pmin.x) > bola->deltaDesplacament){
                bola->moveEsquerra();
            }
        }
    }
}




void Escena::iniCamera(bool cameraActual, int ampladaViewport, int alcadaViewport){

    if(cameraActual){
        camGeneral->piram.proj = PARALLELA;
        camGeneral->ini(ampladaViewport, alcadaViewport, capsaMinima);

        camGeneral->vs.angx = -90;

        setWindowCamera(cameraActual, false, camGeneral->wd);

    }else{
        camGeneral->piram.proj = PERSPECTIVA;
        camGeneral->ini(ampladaViewport, alcadaViewport, capsaMinima);

        camGeneral->vs.angx = 210;
        camGeneral->vs.vrp = conjuntboles->calcularCentre();

        camGeneral->vs.obs.x = bola->capsa.pmin.x + bola->capsa.a/2.;
        camGeneral->vs.obs.y = bola->capsa.pmin.y + bola->capsa.h*2.;
        camGeneral->vs.obs.z = bola->capsa.pmin.z - bola->capsa.p*2.;

        camGeneral->piram.dant = 3;
        camGeneral->piram.dpost = abs(plabase->capsa.pmin.z) + abs(plabase->capsa.p);

        setWindowCamera(cameraActual, false, camGeneral->wd);

    }

    camGeneral->CalculaMatriuModelView();
    camGeneral->CalculaMatriuProjection();

}

void Escena::setAnglesCamera(bool cameraActual, float angX, float angY, float angZ){

    if(cameraActual){

        camGeneral->vs.angx += angX;
        camGeneral->vs.angy += angY;

    }

    else{

        camGeneral->vs.obs.x = bola->capsa.pmin.x + bola->capsa.a/2.;
        camGeneral->vs.obs.y = bola->capsa.pmin.y + bola->capsa.h*2.;
        camGeneral->vs.obs.z = bola->capsa.pmin.z - bola->capsa.p*2.;


    }

    camGeneral->CalculaMatriuModelView();
    camGeneral->CalculaMatriuProjection();

}

void Escena::setVRPCamera(bool cameraActual, point4 vrp){

    if(cameraActual){

        camGeneral->vs.vrp.x += vrp.x;
        camGeneral->vs.vrp.y += vrp.y;
        camGeneral->vs.vrp.z += vrp.z;

    }else{

        camGeneral->vs.vrp = conjuntboles->calcularCentre();

    }

    camGeneral->CalculaMatriuModelView();

}

void Escena::setWindowCamera(bool cameraActual, bool retallat, Capsa2D window){

    if(cameraActual){

        camGeneral->CalculWindow(capsaMinima);

    }else{

        camGeneral->CalculWindow(capsaMinima);
        camGeneral->wd.pmin.x = plabase->capsa.pmin.x;
        camGeneral->wd.a = plabase->capsa.a;

    }

    camGeneral->CalculaMatriuProjection();

}

void Escena::setDCamera(bool cameraActual, float d){

    if(cameraActual){

        camGeneral->AmpliaWindow(d);

        camGeneral->CalculaMatriuProjection();

    }
}
