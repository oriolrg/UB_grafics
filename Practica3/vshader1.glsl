#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

IN vec4 vPosition;
IN vec2 vCoordTexture;
IN vec4 vNormal;

OUT vec2 v_texcoord;
OUT vec4 color;

uniform mat4 model_view;
uniform mat4 projection;

struct tipoLuz{
    int tipo;
    vec4 posicion;
    vec3 direccion;
    float obertura;
    vec4 ambiente;
    vec4 difusa;
    vec4 especular;
    float constante;
    float lineal;
    float cuadratica;

};

struct Material {
    vec4 matAmbient;
    vec4 matDifusa;
    vec4 matEspecular;
    float matShininess;
};

uniform tipoLuz puntual;
uniform tipoLuz direccional;
uniform tipoLuz spotlight;

uniform Material material;

uniform float ambienteGlobal;


float atenuacion()
{
    float a, b, c, distancia;

    distancia = length(puntual.posicion.xyz - vPosition.xyz);

    a = puntual.cuadratica * pow(distancia, 2.0);
    b = puntual.lineal * distancia;
    c = puntual.constante;

    return (1.0 /(a + b + c));
}

void main()
{
    vec3 N = normalize(vNormal.xyz);
    vec3 E = normalize(vPosition.xyz);
    vec3 L = normalize(puntual.posicion.xyz);

    if( puntual.posicion.w != 0.0 ) {

        L = puntual.posicion.xyz - vPosition.xyz;
    }

    vec3 H = normalize( L + E );

    vec4 ambiente = puntual.ambiente * material.matAmbient;

    float Kd = max(dot(L, N), 0.0);
    vec4 difusa = Kd * (puntual.difusa * material.matDifusa);

    float Ks = pow(max(dot(N, H), 0.0), material.matShininess);
    vec4 especular = Ks * (puntual.especular * material.matEspecular);

    if( dot(L, N) < 0.0 ) {
        especular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    color = atenuacion() * (ambienteGlobal + ambiente + difusa + especular);

    gl_Position = (projection * model_view * vPosition) / vPosition.w;

    v_texcoord = vCoordTexture;
}
