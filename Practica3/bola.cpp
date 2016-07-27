#include "bola.h"

Bola::Bola(int id, float x, float y, float z) : Objecte(NumVerticesB)
{

    v[0] = point4( 0.0, 0.0,  1.0, 1.0 );
    v[1] = point4( 0.0, 2.*sqrt(2)/3., -1/3, 1.0);
    v[2] = point4( -sqrt(6)/3., -sqrt(2.)/3., -1./3., 1.0 );
    v[3] = point4( sqrt(6)/3., -sqrt(2.)/3., -1./3., 1.0 );

    make();

    //movem l'objecte a la posicio desitjada
    mat4 mTranslacion = Translate(x, y, z);
    aplicaTG(mTranslacion);

    m = new Material();
    m->kAmbiente = vec4(0.0, 0.0, 0.0, 1.0);
    m->kDifusa = vec4(0.55, 0.55, 0.55 , 1.0);
    m->kEspecular = vec4(0.70, 0.70, 0.70 , 1.0);
    m->coefReflexion = 0.25;

    calculCapsa3D();

    initTextura(id);


}

Bola::~Bola()
{

}

// Realitzacio de la geometria del Bola en una genList o en el vertex array, segons el que visualitzem

void Bola::make()
{
    // generacio de la geometria dels triangles per a visualitzar-lo
    Index = 0;
    tetraedro(NumIteracionsEsfera);

    escalar(0.60);
}

void Bola::initTextura(int id)
 {

     std::ostringstream id_string;
     id_string << id;
     string ruta_string = "://resources/Bola" + id_string.str() + ".jpg";
     const char * ruta = ruta_string.c_str();

     // Carregar la textura
     glActiveTexture(GL_TEXTURE0 + id);
     texture = new QOpenGLTexture(QImage(ruta));
     texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
     texture->setMagnificationFilter(QOpenGLTexture::Linear);

 }

void Bola::tetraedro(int n){

    divide_triangle(v[0], v[1], v[2], n);
    divide_triangle(v[3], v[2], v[1], n);
    divide_triangle(v[0], v[3], v[1], n);
    divide_triangle(v[0], v[2], v[3], n);
}

void Bola::divide_triangle(point4 a, point4 b, point4 c, int n)
{
    if (n > 0){
        point4 v1 = calculVectorUnitari( point4(a.x+b.x, a.y+b.y, a.z+b.z, 1.0 ));
        point4 v2 = calculVectorUnitari( point4(a.x+c.x, a.y+c.y, a.z+c.z, 1.0 ));
        point4 v3 = calculVectorUnitari( point4(b.x+c.x, b.y+c.y, b.z+c.z, 1.0 ));

        divide_triangle(a ,v2, v1, n-1);
        divide_triangle(c ,v3, v2, n-1);
        divide_triangle(b ,v1, v3, n-1);
        divide_triangle(v1 ,v2, v3, n-1);

    }
    else{
        triangle(a, b, c);
    }
}

void Bola::triangle( point4 a, point4 b, point4 c)
{

    vec4 normal = normalize( cross(b - a, c - b) );

    points[Index] = a;
    vertexsTextura[Index] = calculUV(a);
    normals[Index] = normal;
    normals2[Index] = normalize(a);
    Index++;

    points[Index] = b;
    vertexsTextura[Index] = calculUV(b);
    normals[Index] = normal;
    normals2[Index] = normalize(b);
    Index++;

    points[Index] = c;
    vertexsTextura[Index] = calculUV(c);
    normals[Index] = normal;
    normals2[Index] = normalize(c);
    Index++;
}

point2 Bola::calculUV(point4 a)
{
    float u, v;

    u = 0.5 + atan2(a.z, a.x) / (2.0 * M_PI);
    v = 0.5 - asin(a.y) / M_PI;

    if (u < 0.0) u = 0.0;
    if (u > 1.0) u = 1.0;

    if (v < 0.0) v = 0.0;
    if (v > 1.0) v = 1.0;

    return point2(u, v);

}

point4 Bola::calculVectorUnitari(point4 vertice){

    float a = sqrt((vertice.x*vertice.x) + (vertice.y*vertice.y) + (vertice.z*vertice.z));
    vertice.x = vertice.x/a;
    vertice.y = vertice.y/a;
    vertice.z = vertice.z/a;
    return vertice;
}

void Bola::moveDavant(){

    mat4 mTranslacion = Translate(0.0, 0.0, deltaDesplacament);
    aplicaTG(mTranslacion);

}

void Bola::moveDarrera(){

    mat4 mTranslacion = Translate(0.0, 0.0, -deltaDesplacament);
    aplicaTG(mTranslacion);
}

void Bola::moveDreta(){

    mat4 mTranslacion = Translate(deltaDesplacament, 0.0, 0.0);
    aplicaTG(mTranslacion);
}

void Bola::moveEsquerra(){

    mat4 mTranslacion = Translate(-deltaDesplacament, 0.0, 0.0);
    aplicaTG(mTranslacion);

}
