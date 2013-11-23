#version 330

uniform sampler2D diffuseTexture;
uniform vec2 diffuseIntensityRange;

in vec2 vertexTextureCoords;
out vec4 outputColor;

void main()
{
    float blackPoint = diffuseIntensityRange.x;
    float intensity = diffuseIntensityRange.y - diffuseIntensityRange.x;

    vec4 diffuse = texture(diffuseTexture, vertexTextureCoords);
    outputColor = blackPoint + diffuse * intensity;
}