#ifndef LLUM_H
#define LLUM_H

#include <stdio.h>
#include <Common.h>
#include <QGLShaderProgram>

typedef struct{
    vec4 ambiente;
    vec4 difusa;
    vec4 especular;
} Intensidad;


typedef struct{
    float constante;
    float lineal;
    float cuadratica;
} Atenuacion;



class Llum
{

    public:

        Llum(QString nombre, int tipo);
        void toGPU(QGLShaderProgram *program);

    private:

        QString nombre;
        int tipo;
        Intensidad intensidad;
        Atenuacion atenuacion;
        vec4 posicion;
        vec3 direccion;
        float obertura;
        char * luz;

};

#endif // LLUM_H
