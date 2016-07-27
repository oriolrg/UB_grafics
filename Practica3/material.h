#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdio.h>
#include <Common.h>
#include <QGLShaderProgram>

using namespace std;


class Material
{

    public:

        Material();
        void toGPU(QGLShaderProgram *program);

        vec4 kAmbiente;
        vec4 kDifusa;
        vec4 kEspecular;

        float coefReflexion;


};

#endif // MATERIAL_H
