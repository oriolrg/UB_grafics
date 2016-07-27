#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

uniform sampler2D texMap;

IN vec2 v_texcoord;

IN vec3 fN;
IN vec3 fE;
IN vec3 fL;

uniform mat4 model_view;
uniform mat4 projection;

struct tipoLuz{

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

void main()
{

    vec3 N = normalize(fN);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL);

    vec3 H = normalize( L + E );

    vec4 ambiente = direccional.ambiente * material.matAmbient;

    float Kd = max(dot(L, N), 0.0);
    vec4 difusa = Kd * (direccional.difusa * material.matDifusa);

    float Ks = pow(max(dot(N, H), 0.0), material.matShininess);
    vec4 especular = Ks * (direccional.especular * material.matEspecular);

    if( dot(L, N) < 0.0 ) {
        especular = vec4(0.0, 0.0, 0.0, 1.0);
    }


    float intensity;
    vec4 color;
    intensity = dot(direccional.direccion, N);

    if (texture2D(texMap, v_texcoord).xyz == vec3(0,0,0)){
        if (intensity > 0.95)
            color = 1.0*(ambienteGlobal + ambiente + difusa + especular);
        else if (intensity > 0.5)
            color = 0.6*(ambienteGlobal + ambiente + difusa + especular);
        else if (intensity > 0.25)
            color = 0.4*(ambienteGlobal + ambiente + difusa + especular);
        else
            color = 0.2*(ambienteGlobal + ambiente + difusa + especular);
    }else{
        if (intensity > 0.95)
            color = 1.0*(0.25*(ambienteGlobal + ambiente + difusa + especular) + 0.75*texture2D(texMap, v_texcoord));
        else if (intensity > 0.5)
            color = 0.6*(0.25*(ambienteGlobal + ambiente + difusa + especular) + 0.75*texture2D(texMap, v_texcoord));
        else if (intensity > 0.25)
            color = 0.4*(0.25*(ambienteGlobal + ambiente + difusa + especular) + 0.75*texture2D(texMap, v_texcoord));
        else
            color = 0.2*(0.25*(ambienteGlobal + ambiente + difusa + especular) + 0.75*texture2D(texMap, v_texcoord));
    }
    gl_FragColor = color;
    gl_FragColor.w = 1.0;

}

