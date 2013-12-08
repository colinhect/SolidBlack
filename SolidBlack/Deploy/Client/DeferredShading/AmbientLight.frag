#version 330

uniform vec3 color;
uniform sampler2D normalTexture;

in vec2 vertexTextureCoords;

out vec4 outputColor;

void main()
{
    float x = texture(normalTexture, vertexTextureCoords).a;
    if (x > 0.0)
    {
        outputColor = vec4(color, 1.0);
    }
    else
    {
        discard;
    }
}