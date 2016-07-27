#include "plabase.h"

Plabase::Plabase() : Objecte(NumVerticesP)
{

    // Vertices of a unit plabase centered at origin, sides aligned with axes
    vertices[0] = point4( -5.0, 0.0, -5.0, 1.0 );
    vertices[1] = point4( -5.0, 0.0, 5.0, 1.0 );
    vertices[2] = point4(  5.0, 0.0, 5.0, 1.0 );
    vertices[3] = point4(  5.0, 0.0, -5.0, 1.0 );

    make();

    m = new Material();
    m->kAmbiente = vec4(0.0, 0.05, 0.0, 1.0);
    m->kDifusa = vec4(0.4, 0.5, 0.4, 1.0);
    m->kEspecular = vec4(0.04, 0.7, 0.04, 1.0);
    m->coefReflexion = 0.78125;

    initTextura();
    capsa = calculCapsa3D();
}

// Destructora
Plabase::~Plabase()
{
}

// quad generates two triangles for each face and assigns colors
//    to the vertices

void Plabase::quad( int a, int b, int c, int d )
{

    vec4 normal = normalize( cross(vertices[b] - vertices[a], vertices[c] - vertices[b]) );

    points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0);
    normals[Index] = normal;
    normals2[Index] = normalize(vertices[a]);
    Index++;

    points[Index] = vertices[b];
    vertexsTextura[Index] = vec2(1.0, 0.0);
    normals[Index] = normal;
    normals2[Index] = normalize(vertices[b]);
    Index++;

    points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0);
    normals[Index] = normal;
    normals2[Index] = normalize(vertices[c]);
    Index++;

    normal = normalize( cross(vertices[c] - vertices[a], vertices[d] - vertices[c]) );

    points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0);
    normals[Index] = normal;
    normals2[Index] = normalize(vertices[a]);
    Index++;

    points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0);
    normals[Index] = normal;
    normals2[Index] = normalize(vertices[c]);
    Index++;

    points[Index] = vertices[d];
    vertexsTextura[Index] = vec2(0.0, 1.0);
    normals[Index] = normal;
    normals2[Index] = normalize(vertices[d]);
    Index++;
}


// Realitzacio de la geometria del plabase en una genList o en el vertex array, segons el que visualitzem

void Plabase::make()
{

    // generacio de la geometria dels triangles per a visualitzar-lo
    Index = 0;

    quad(1, 0, 3, 2 );
    quad(1, 2, 3, 0);

    aplicaTGCentrat(Scale(1.2, 1.0, 1.8));

}
void Plabase::initTextura()
 {

     // Carregar la textura
     glActiveTexture(GL_TEXTURE16);
     texture = new QOpenGLTexture(QImage("://resources/Fabric_Green_L.jpg"));
     texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
     texture->setMagnificationFilter(QOpenGLTexture::Linear);

 }

