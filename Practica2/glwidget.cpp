

#include <math.h>

#include <glwidget.h>
#include <QString>


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)

{
    setFocusPolicy( Qt::StrongFocus );

    esc = new Escena();
    esc->width = this->size().width();
    esc->height = this->size().height();

    xRot = 0;
    yRot = 0;
    zRot = 0;

    a = 20.0;
    h = 20.0;
    p = 20.0;

    clearColor = Qt::black;
    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

    program = 0;
    moviment = false;

}


GLWidget::~GLWidget()
{
    makeCurrent();
    delete esc;
}


// Create a GLSL program object from vertex and fragment shader files
void
GLWidget::InitShader(const char* vShaderFile, const char* fShaderFile)
{           

    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);

    // Compilació del vertex shader
    vshader->compileSourceFile(vShaderFile);
    fshader->compileSourceFile(fShaderFile);

    program = new QGLShaderProgram(this);
    program->addShader(vshader);
    program->addShader(fshader);

    program->bindAttributeLocation("vPosition", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("vColor", PROGRAM_COLOR_ATTRIBUTE);
    // muntatge del shader en el pipeline gràfic per a ser usat
    program->link();

    // unió del shader al pipeline gràfic
    program->bind();

}

void GLWidget::initShadersGPU()
{
// Carrega dels shaders i posa a punt per utilitzar els programes carregats a la GPU
   InitShader( "://vshader1.glsl", "://fshader1.glsl" );

}


QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const

{
    return QSize(400, 400);
}


void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    //std::cout<<"Estic inicialitzant el shaders"<<std::ends;
    initShadersGPU();

    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}


void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);

    if (angle != xRot) {

        xRot = angle;
        esc->setAnglesCamera(esc->cameraActual, xRot, 0.0, 0.0);
        update();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);

    if (angle != yRot) {
        yRot = angle;
        esc->setAnglesCamera(esc->cameraActual, 0.0, yRot, 0.0);
        update();
    }
}
void GLWidget::Pan(float dx, float dy)
{
    point4 vrp;
    vrp.x = dx;
    vrp.y = 0.0;
    vrp.z = dy;
    esc->setVRPCamera(esc->cameraActual,vrp);
}

void GLWidget::Zoom(float zoom)
{
    esc->setDCamera(esc->cameraActual, zoom);
}

void GLWidget::paintGL()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   qNormalizeAngle(xRot);
   qNormalizeAngle(yRot);
   qNormalizeAngle(zRot);

   esc->camGeneral->toGPU(program);

   esc->draw();

}


void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);

    esc->width = this->size().width();
    esc->height = this->size().height();

    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-1.5, +1.5, -1.5, +1.5, 0.0, 15.0);
#else
    glOrtho(-1.5, +1.5, -1.5, +1.5, 0.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton && esc->cameraActual) {
        if(lastPos.y()!=event->y()&&lastPos.x()!=event->x())
        {
            setXRotation(xRot + 1.0 * dy);
            setYRotation(yRot + 1.0 * dx);
        }
        else if(lastPos.y()!= event->y()){
            setXRotation(xRot + 1.0 * dy);
        }
        else if(lastPos.x()!= event->x()){
            setYRotation(yRot + 1.0 * dx);
        }
    }

    lastPos = event->pos();
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
    // Metode a implementar

    switch ( event->key() )
    {
    case Qt::Key_Up:
        if (event->modifiers().testFlag(Qt::AltModifier)){
            Pan(0.0,0.1);
        }else{
            esc->moveDavant();
            if (!esc->cameraActual){
                esc->setVRPCamera(esc->cameraActual, point4(0, 0, 0, 0));
                esc->setAnglesCamera(esc->cameraActual, 0, 0, 0);

            }
        }
        break;

    case Qt::Key_Down:
        if (event->modifiers().testFlag(Qt::AltModifier)){
            Pan(0.0,-0.1);
        }else{
            esc->moveDarrera();
            if (!esc->cameraActual){
                esc->setVRPCamera(esc->cameraActual, point4(0, 0, 0, 0));
                esc->setAnglesCamera(esc->cameraActual, 0, 0, 0);
            }
        }
        break;

    case Qt::Key_Left:
        if (event->modifiers().testFlag(Qt::AltModifier)){
            Pan(0.1,0.0);
        }else{
            esc->moveDreta();
            if (!esc->cameraActual){
                esc->setVRPCamera(esc->cameraActual, point4(0, 0, 0, 0));
                esc->setAnglesCamera(esc->cameraActual, 0, 0, 0);
            }
        }
        break;

    case Qt::Key_Right:
        if (event->modifiers().testFlag(Qt::AltModifier)){
            Pan(-0.1,0.0);
        }else{
            esc->moveEsquerra();
            if (!esc->cameraActual){
                esc->setVRPCamera(esc->cameraActual, point4(0, 0, 0, 0));
                esc->setAnglesCamera(esc->cameraActual, 0, 0, 0);
            }
        }
        break;

    case Qt::Key_Plus:
        Zoom(-0.05);
        break;

    case Qt::Key_Minus:
        Zoom(0.05);
        break;

    case Qt::Key_B:
        esc->cameraActual = false;
        esc->iniCamera(esc->cameraActual, this->size().width(), this->size().height());
        break;

    case Qt::Key_T:
        esc->cameraActual = true;
        esc->iniCamera(esc->cameraActual, this->size().width(), this->size().height());
        break;
    }

}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    updateGL();
}



void GLWidget::adaptaObjecteTamanyWidget(Objecte *obj)
{
     // Metode a implementar

    float factor = 2.0 / 20.0;

    point4 obj_centro = obj->calcularCentre();

    mat4 mCentro = Translate(-obj_centro);

    mat4 mEscalar = Scale(factor, factor, factor);

    mat4 mCentroRelativo = Translate(obj_centro.x * factor, obj_centro.y * factor, obj_centro.z * factor);

    mat4 mAdaptar = mCentroRelativo * mEscalar * mCentro;

    obj->aplicaTGPoints(mAdaptar);

}

void GLWidget::newObjecte(Objecte * obj)
{
    //adaptaObjecteTamanyWidget(obj);
    obj->toGPU(program);
    esc->addObjecte(obj);

    updateGL();
}

void GLWidget::newPlaBase()
{
    // Metode que crea un objecte plabase poligon amb el punt central al (0,0,0) i perpendicular a Y=0

    // Metode a implementar

    Plabase *obj;

    obj = new Plabase();
    newObjecte(obj);

}

void GLWidget::newObj(QString fichero)
{
    // Metode que carrega un fitxer .obj llegit de disc
    TaulaBillar *obj;

    obj = new TaulaBillar(fichero);
    newObjecte(obj);
}

void GLWidget::newBola()
{
    // Metode que crea la Bola blanca de joc
     // Metode a implementar

    Bola *obj;

    obj = new Bola(0, 0.0, 1.2, -4.0);
    newObjecte(obj);

}

void GLWidget::newConjuntBoles()
{
    // Metode que crea les 15 Boles del billar america
    // Metode a implementar

    ConjuntBoles *obj;
    int i;

    obj = new ConjuntBoles();

    for (i = 0; i < 15; i++)
    {
        //adaptaObjecteTamanyWidget(obj->boles[i]);
        obj->boles[i]->toGPU(program);
    }
    esc->addObjecte(obj);
    updateGL();

}

void GLWidget::newSalaBillar()
{
    // Metode que construeix tota la sala de billar: taula, 15 boles i bola blanca

    newPlaBase();
    newBola();
    newConjuntBoles();
}

// Metode per iniciar la dinàmica del joc
void GLWidget::Play()
{

}
