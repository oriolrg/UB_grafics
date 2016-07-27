#include "conjuntboles.h"

ConjuntBoles::ConjuntBoles() : Objecte(NumVerticesCB)
{
    std::cout<<"Estic en el constructor del conjunt de boles\n";

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

    capsa = this->calculCapsa3D();

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

    bool init = false;

    for (iterador = this->boles.begin(); iterador < this->boles.end(); ++iterador) {
        if(*iterador!=NULL){

           if (init == false){
               capsaconjunt.pmin = (*iterador)->capsa.pmin ;
               capsaconjunt.a = (*iterador)->capsa.a;
               capsaconjunt.h = (*iterador)->capsa.h;
               capsaconjunt.p = (*iterador)->capsa.p;
               init = true;
           } else{
               if (capsaconjunt.pmin.x > (*iterador)->capsa.pmin.x)
                   capsaconjunt.pmin.x = (*iterador)->capsa.pmin.x;
               if (capsaconjunt.pmin.y > (*iterador)->capsa.pmin.y)
                   capsaconjunt.pmin.y = (*iterador)->capsa.pmin.y;
               if (capsaconjunt.pmin.z > (*iterador)->capsa.pmin.z)
                   capsaconjunt.pmin.z = (*iterador)->capsa.pmin.z;

               if (capsaconjunt.a < (*iterador)->capsa.a)
                   capsaconjunt.a = (*iterador)->capsa.a;
               if (capsaconjunt.h < (*iterador)->capsa.h)
                   capsaconjunt.h = (*iterador)->capsa.h;
               if (capsaconjunt.p < (*iterador)->capsa.p)
                   capsaconjunt.p = (*iterador)->capsa.p;
           }
        }
    }
}
