#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

uniform sampler2D texMap;

IN vec2 v_texcoord;
IN vec3 position;
IN vec3 normal;

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

float atenuacion(tipoLuz luz)
{
    float a, b, c, distancia;

    distancia = length(luz.posicion.xyz - position);

    a = luz.cuadratica * pow(distancia, 2.0);
    b = luz.lineal * distancia;
    c = luz.constante;

    return (1.0 /(a + b + c));
}

float spot()
{

    float coseno = cos(spotlight.obertura);

    vec3 direccion = normalize(position - spotlight.posicion.xyz);

    float coseno2 = dot(spotlight.direccion, direccion);

    if (coseno2 > coseno)
        return 1.0;

    return 0.0;

}

vec3 blinn_phong(tipoLuz luz)
{
    vec3 N = normalize(normal);

    vec3 E = normalize(position);

    vec3 L;
    if(luz.tipo == 0)           // Direccional
    {
        L = normalize(luz.direccion.xyz);
    }else if(luz.tipo == 1)     // Puntual
    {
        L = normalize(luz.posicion.xyz - position);
    }else if (luz.tipo == 2)    // Spotlight
    {
        L = normalize(luz.direccion.xyz);
    }

    vec3 H = normalize(L+E);

    vec3 ambiente = luz.ambiente.xyz * material.matAmbient.xyz;

    float Kd = max(dot(L, N), 0.0);
    vec3 difusa = Kd * (luz.difusa.xyz * material.matDifusa.xyz);

    float Ks = max(pow(dot(N, H), material.matShininess) , 0.0);
    vec3 especular = Ks * (luz.especular.xyz * material.matEspecular.xyz);

    return (ambienteGlobal + ambiente + difusa + especular);

}

vec4 get_Color()
{
    vec4 color1 = vec4(blinn_phong(direccional), 1.0);
    vec4 color2 = vec4(atenuacion(puntual) * blinn_phong(puntual), 1.0);
    vec4 color3 = vec4(spot() * blinn_phong(spotlight), 1.0);

    //return (color1 + color2 + color3);
    return color1;
}

void main()
{
    if (texture2D(texMap, v_texcoord).xyz == vec3(0,0,0)){
        gl_FragColor = get_Color();
    }else{
        gl_FragColor = 0.25*(get_Color()) + 0.75*texture2D(texMap, v_texcoord);
    }
    gl_FragColor.w = 1.0;

}
