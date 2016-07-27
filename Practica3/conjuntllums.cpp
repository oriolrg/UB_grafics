#include "conjuntllums.h"

ConjuntLlums::ConjuntLlums()
{

}

void ConjuntLlums::add(Llum *llum)
{
    this->listaLuces.push_back(llum);
}

void ConjuntLlums::setAmbientToGPU(QGLShaderProgram *program)
{
    GLuint GL_ambienteGlobal = program->uniformLocation("ambienteGlobal");
    glUniform1f(GL_ambienteGlobal,  this->ambienteGlobal);
}

void ConjuntLlums::toGPU(QGLShaderProgram *program)
{
    for (iterador = this->listaLuces.begin(); iterador < this->listaLuces.end(); ++iterador)
    {
        if(*iterador!=NULL)(*iterador)->toGPU(program);
    }
}
