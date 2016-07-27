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
OUT vec3 position;
OUT vec3 normal;

uniform mat4 model_view;
uniform mat4 projection;

void main()
{
    normal = vNormal.xyz;
    position = vPosition.xyz;

    gl_Position = (projection * model_view * vPosition) / vPosition.w;
    v_texcoord = vCoordTexture;
}
