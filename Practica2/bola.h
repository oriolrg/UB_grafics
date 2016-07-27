#ifndef BOLA_H
#define BOLA_H

#include <Common.h>
#include <QGLShaderProgram>
#include <QOpenGLTexture>

#include <objecte.h>
#include <stdio.h>

#include <sstream>

const int NumIteracionsEsfera = 6;
const int NumVerticesB = 64000;

typedef vec4  color4;
typedef vec4  point4;
typedef vec2  point2;

class Bola : public Objecte
{
    public:
        const double deltaDesplacament = 0.3;

        Bola(int id, float x, float y, float z);
        ~Bola();
        void make();
        void initTextura(int id);

        void moveDavant();
        void moveDarrera();
        void moveDreta();
        void moveEsquerra();

    private:

        void triangle( point4 a, point4 b, point4 c);
        void tetraedro(int n);
        void divide_triangle(point4 a, point4 b, point4 c, int n);
        point4 calculVectorUnitari(point4 vertice);
        point2 calculUV(point4 a);
        point4 v[4];

};

#endif // BOLA_H
