#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

IN vec4 vPosition;
IN vec4 vColor;
IN vec2 vCoordTexture;

OUT vec4 color;
OUT vec2 v_texcoord;

uniform mat4 model_view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * model_view * (vPosition / vPosition.w);

    color = vColor;
    v_texcoord = vCoordTexture;
}
