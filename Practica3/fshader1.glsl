#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

uniform sampler2D texMap;

IN vec2 v_texcoord;

IN vec4 color;

void main()
{
    if (texture2D(texMap, v_texcoord).xyz == vec3(0,0,0)){
        gl_FragColor = color;
    }else{
        gl_FragColor = 0.25*(color) + 0.75*texture2D(texMap, v_texcoord);
    }
    gl_FragColor.w = 1.0;

}

