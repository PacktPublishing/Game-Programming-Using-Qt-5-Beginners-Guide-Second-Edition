uniform highp mat4 modelViewMatrix;
uniform highp mat3 normalMatrix;
uniform highp mat4 projectionMatrix;
uniform highp mat4 mvpMatrix;

attribute highp vec4 Vertex;
attribute mediump vec3 Normal;

varying mediump vec3 N;
varying highp vec3 v;

void main(void)
{
    N = normalize(normalMatrix * Normal);
    v = vec3(modelViewMatrix * Vertex);

    gl_Position = mvpMatrix * Vertex;
}
