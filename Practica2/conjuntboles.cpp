#include "conjuntboles.h"

ConjuntBoles::ConjuntBoles() : Objecte(NumVerticesCB)
{
    int id_bola[15] = {1,11,3,6,8,14,13,15,4,9,7,2,10,5,12};
    int id = 0;
    float x, z, i;

    for (z = 2.0; z < 7.0; z++)
    {
        for (x = 0.0 - i; x < i + 0.6; x+=1.2)
        {
            bola = new Bola(id_bola[id], x, 1.2, z);
            boles.push_back(bola);
            id++;
        }
        i = i + 0.6;
    }

    calculCapsa3D();

}

ConjuntBoles::~ConjuntBoles()
{

}

void ConjuntBoles::aplicaTG(mat4 trans){
    for (iterador = this->boles.begin(); iterador < this->boles.end(); ++iterador) {
        if(*iterador!=NULL)
            (*iterador)->aplicaTG(trans);
    }
}

void ConjuntBoles::aplicaTGCentrat(mat4 trans){
    for (iterador = this->boles.begin(); iterador < this->boles.end(); ++iterador) {
        if(*iterador!=NULL)
            (*iterador)->aplicaTGCentrat(trans);
    }
}

void ConjuntBoles::aplicaTGPoints(mat4 trans){
    for (iterador = this->boles.begin(); iterador < this->boles.end(); ++iterador) {
        if(*iterador!=NULL)
            (*iterador)->aplicaTGPoints(trans);
    }
}

void ConjuntBoles::draw(){
    for (iterador = this->boles.begin(); iterador < this->boles.end(); ++iterador) {
        if(*iterador!=NULL)
            (*iterador)->draw();
    }
}

Capsa3D ConjuntBoles::calculCapsa3D(){

    vec3 pmin, pmax;

    pmin.x = boles[0]->capsa.pmin.x;
    pmin.y = boles[0]->capsa.pmin.y;
    pmin.z = boles[0]->capsa.pmin.z;

    pmax.x = boles[0]->capsa.pmin.x + boles[0]->capsa.a;
    pmax.y = boles[0]->capsa.pmin.y + boles[0]->capsa.h;
    pmax.z = boles[0]->capsa.pmin.z + boles[0]->capsa.p;

    for (int i = 1; i < 15; i++){
        if (boles[i]->capsa.pmin.x < pmin.x)
            pmin.x = boles[i]->capsa.pmin.x;
        if (boles[i]->capsa.pmin.y < pmin.y)
            pmin.y = boles[i]->capsa.pmin.y;
        if (boles[i]->capsa.pmin.z < pmin.z)
            pmin.z = boles[i]->capsa.pmin.z;

        if (boles[i]->capsa.pmin.x + boles[i]->capsa.a > pmax.x)
            pmax.x = boles[i]->capsa.pmin.x + boles[i]->capsa.a;
        if (boles[i]->capsa.pmin.y + boles[i]->capsa.h > pmax.y)
            pmax.y = boles[i]->capsa.pmin.y + boles[i]->capsa.h;
        if (boles[i]->capsa.pmin.z + boles[i]->capsa.p > pmax.z)
            pmax.z = boles[i]->capsa.pmin.z + boles[i]->capsa.p;
    }

    capsa.pmin = pmin;

    capsa.a = pmax.x - pmin.x;
    capsa.h = pmax.y - pmin.y;
    capsa.p = pmax.z - pmin.z;

    return capsa;
}
