#ifndef CONJUNTBOLES_H
#define CONJUNTBOLES_H

#include <Common.h>
#include <QGLShaderProgram>
#include <QOpenGLTexture>

#include <objecte.h>
#include <stdio.h>
#include <bola.h>

const int NumVerticesCB = 1;

typedef vec4  color4;
typedef vec4  point4;

class ConjuntBoles : public Objecte
{
public:
    ConjuntBoles();
    ~ConjuntBoles();

    void aplicaTG(mat4 trans);
    void aplicaTGPoints(mat4 trans);
    void aplicaTGCentrat(mat4 trans);
    void draw();
    vector<Bola*> boles;
    Bola *bola;
    vector<Bola *>::iterator iterador;
    Capsa3D calculCapsa3D();
    bool texturas = true;
    int normales = 1;


};

#endif // CONJUNTBOLES_H
