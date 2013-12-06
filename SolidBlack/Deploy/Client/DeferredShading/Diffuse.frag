#version 330

uniform sampler2D diffuseTexture;
uniform vec2 diffuseIntensityRange;

in vec3 vertexNormal;
in vec2 vertexTextureCoords;

out vec4 outputColor;
out vec4 outputNormal;

void main()
{
    float blackPoint = diffuseIntensityRange.x;
    float intensity = diffuseIntensityRange.y - diffuseIntensityRange.x;

    vec4 diffuse = texture(diffuseTexture, vertexTextureCoords);
    outputColor = blackPoint + diffuse * intensity;
    
    outputNormal = vec4(vertexNormal, 1.0);
}