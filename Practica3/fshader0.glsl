#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

uniform sampler2D texMap;

IN vec2 v_texcoord;

void main()
{
    gl_FragColor = texture2D(texMap, v_texcoord);
}

