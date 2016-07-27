#include "plabase.h"

Plabase::Plabase() : Objecte(NumVerticesP)
{

    // Vertices of a unit plabase centered at origin, sides aligned with axes
    vertices[0] = point4( -5.0, 0.0, -5.0, 1.0 );
    vertices[1] = point4( -5.0, 0.0, 5.0, 1.0 );
    vertices[2] = point4(  5.0, 0.0, 5.0, 1.0 );
    vertices[3] = point4(  5.0, 0.0, -5.0, 1.0 );

    // RGBA colors
    vertex_colors[0] =    color4( 0.0, 1.0, 0.0, 1.0 );  // green
    vertex_colors[1] =    color4( 0.0, 1.0, 0.0, 1.0 );  // green
    vertex_colors[2] =    color4( 0.0, 1.0, 0.0, 1.0 );  // green
    vertex_colors[3] =    color4( 0.0, 1.0, 0.0, 1.0 );  // green

    make();
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
    colors[Index] = vertex_colors[a];
    points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0);
    Index++;

    colors[Index] = vertex_colors[b];
    points[Index] = vertices[b];
    vertexsTextura[Index] = vec2(1.0, 0.0);
    Index++;

    colors[Index] = vertex_colors[c];
    points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0);
    Index++;

    colors[Index] = vertex_colors[a];
    points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0);
    Index++;

    colors[Index] = vertex_colors[c];
    points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0);
    Index++;

    colors[Index] = vertex_colors[d];
    points[Index] = vertices[d];
    vertexsTextura[Index] = vec2(0.0, 1.0);
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

