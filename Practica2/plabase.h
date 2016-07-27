#ifndef plabase_H
#define plabase_H
#include <Common.h>
#include <QGLShaderProgram>
#include <QOpenGLTexture>

#include <objecte.h>
#include <stdio.h>


const int NumVerticesP = 12; //(1 face)(2 triangles/face)(3 vertices/triangle)

typedef vec4  color4;
typedef vec4  point4;

class Plabase : public Objecte
    {
    public:
        Plabase();
        ~Plabase();
        void make();
        void initTextura();
    private:

        void quad( int a, int b, int c, int d );

        point4 vertices[4]; // 4 vertexs del plabase
        color4 vertex_colors[4]; // 4 colors RGBA associats a cada vertex
};

#endif // plabase_H
