#ifndef CONJUNTLLUMS_H
#define CONJUNTLLUMS_H

#include <stdio.h>
#include <Common.h>
#include <llum.h>

using namespace std;

class ConjuntLlums
{

    public:

        ConjuntLlums();
        void add(Llum *llum);
        void toGPU(QGLShaderProgram *program);
        void setAmbientToGPU(QGLShaderProgram *program);

        float ambienteGlobal;

    private:
        vector<Llum * > listaLuces;
        vector<Llum * >::iterator iterador;
};

#endif // CONJUNTLLUMS_H
