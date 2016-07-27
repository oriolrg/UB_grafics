#include "material.h"

Material::Material()
{

}

void Material::toGPU(QGLShaderProgram *program){

    struct{
        GLuint kAmbiente;
        GLuint kDifusa;
        GLuint kEspecular;
        GLuint coefReflexion;
    } gl_IdMaterial;

    gl_IdMaterial.kAmbiente = program->uniformLocation("material.matAmbient");
    gl_IdMaterial.kDifusa = program->uniformLocation("material.matDifusa");
    gl_IdMaterial.kEspecular = program->uniformLocation("material.matEspecular");
    gl_IdMaterial.coefReflexion = program->uniformLocation("material.matShininess");


    glUniform4fv(gl_IdMaterial.kAmbiente, 1, this->kAmbiente);
    glUniform4fv(gl_IdMaterial.kDifusa, 1, this->kDifusa);
    glUniform4fv(gl_IdMaterial.kEspecular, 1, this->kEspecular);
    glUniform1f(gl_IdMaterial.coefReflexion, this->coefReflexion);

}
