#ifndef ESCENA_H
#define ESCENA_H

#include <cmath>
#include <iostream>
#include <stdlib.h>

#include <list>
#include <vector>
#include <string>
#include <stdio.h>

#include <Common.h>
#include <objecte.h>
#include <camera.h>
#include <taulabillar.h>
#include <plabase.h>
#include <bola.h>
#include <conjuntboles.h>
using namespace std;

class Escena
{
public:
    Escena();
    ~Escena();

    void addObjecte(Objecte *obj);
    void aplicaTG(mat4 m);

    void aplicaTGCentrat(mat4 m);
    void reset();

    void draw();
    void moveDavant();
    void moveDarrera();
    void moveDreta();
    void moveEsquerra();

    void iniCamera(bool camGeneralTipo, int ampladaViewport, int alcadaViewport);
    void setAnglesCamera(bool camGeneralTipo, float angX, float angY, float angZ);
    void setVRPCamera(bool camGeneralTipo, point4 vrp);
    void setWindowCamera(bool camGeneralTipo, bool retallat, Capsa2D window);
    void setDCamera(bool camGeneralTipo, float d);

    Capsa3D CapsaMinCont3DEscena();

    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;

    // Objectes de l'escena: a modificar. Ara nomes té un objecte: la taula de billar.
    // Cal afegir la bola blanca o el pla base per testejar o les 15 boles
    TaulaBillar *taulaBillar;
    Plabase *plabase;
    Bola *bola;
    ConjuntBoles *conjuntboles;
    vector<Objecte *> objectes;
    vector<Objecte *>::iterator iterador;

    Camera *camGeneral;
    bool cameraActual;

    float width, height;

};

#endif // ESCENA_H
