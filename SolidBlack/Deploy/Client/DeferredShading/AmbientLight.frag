#version 330

uniform vec3 color;
uniform sampler2D normalBuffer;

in vec2 vertexTextureCoords;

out vec3 outputColor;

void main()
{
    float depth = texture(normalBuffer, vertexTextureCoords).a;
    if (depth > 0.0)
    {
        outputColor = color;
    }
    else
    {
        discard;
    }
}