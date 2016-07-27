#include "llum.h"

Llum::Llum(QString nombre, int tipo)
{

    this->nombre = nombre;
    this->tipo = tipo;

    // Direccional
    if (tipo == 0){

        this->direccion = vec3(5.0, 2.5, 5.0);

        this->intensidad.difusa = vec4(0.5, 0.5, 0.5, 1.0);
        this->intensidad.especular = vec4(0.2, 0.1, 0.9, 1.0);
        this->intensidad.ambiente = vec4(0.0, 0.0, 0.0, 1.0);

    }

    // Puntual
    else if (tipo == 1){

        this->posicion = vec4(15.0, 5.0, 15.0, 0.0);

        this->intensidad.difusa = vec4(1.0, 1.0, 1.0, 1.0);
        this->intensidad.especular = vec4(10.0, 10.0, 10.0, 1.0);
        this->intensidad.ambiente = vec4(0.0, 0.0, 0.0, 1.0);

        this->atenuacion.constante = 1.0;
        this->atenuacion.lineal = 0.09;
        this->atenuacion.cuadratica = 0.032;
    }

    // Spotlight
    else if (tipo == 2){

        this->direccion = vec3(-5.0, -2.5, -5.0);
        this->posicion = vec4(-20.0, 5.0, -20.0, 0.0);
        this->obertura = 5.0;

        this->intensidad.difusa = vec4(1.0, 1.0, 1.0, 1.0);
        this->intensidad.especular = vec4(1.0, 1.0, 1.0, 1.0);
        this->intensidad.ambiente = vec4(0.0, 0.0, 0.0, 1.0);

        this->atenuacion.constante = 1.0;
        this->atenuacion.lineal = 0.09;
        this->atenuacion.cuadratica = 0.032;
    }

}

void Llum::toGPU(QGLShaderProgram *program)
{
    // 1. Per a passar els diferents atributs del shader declarem
    // una estructura amb els identificadors de la GPU

    struct{

        GLuint tipo;
        GLuint posicion;
        GLuint direccion;
        GLuint obertura;

        GLuint ambiente;
        GLuint difusa;
        GLuint especular;

        GLuint constante;
        GLuint lineal;
        GLuint cuadratica;

    }gl_IdLlum;

    // 2. obtencio dels identificadors de la GPU

    gl_IdLlum.tipo =program->uniformLocation(this->nombre + ".tipo");
    gl_IdLlum.posicion =program->uniformLocation(this->nombre +".posicion");
    gl_IdLlum.direccion =program->uniformLocation(this->nombre +".direccion");
    gl_IdLlum.obertura = program->uniformLocation(this->nombre+".obertura");

    gl_IdLlum.ambiente =program->uniformLocation(this->nombre+".ambiente");
    gl_IdLlum.difusa =program->uniformLocation(this->nombre+".difusa");
    gl_IdLlum.especular =program->uniformLocation(this->nombre+".especular");

    gl_IdLlum.constante =program->uniformLocation(this->nombre+".constante");
    gl_IdLlum.lineal =program->uniformLocation(this->nombre+".lineal");
    gl_IdLlum.cuadratica =program->uniformLocation(this->nombre+".cuadratica");

    // 3. Bind de les zones de memoria que corresponen

    glUniform1i(gl_IdLlum.tipo,  this->tipo);
    glUniform4fv(gl_IdLlum.posicion, 1, this->posicion);
    glUniform3fv(gl_IdLlum.direccion, 1, this->direccion);
    glUniform1f(gl_IdLlum.obertura,this->obertura);

    glUniform4fv(gl_IdLlum.ambiente, 1, this->intensidad.ambiente);
    glUniform4fv(gl_IdLlum.difusa, 1, this->intensidad.difusa);
    glUniform4fv(gl_IdLlum.especular, 1, this->intensidad.especular);

    glUniform1f(gl_IdLlum.constante,  this->atenuacion.constante);
    glUniform1f(gl_IdLlum.lineal,  this->atenuacion.lineal);
    glUniform1f(gl_IdLlum.cuadratica, this->atenuacion.cuadratica);

}
