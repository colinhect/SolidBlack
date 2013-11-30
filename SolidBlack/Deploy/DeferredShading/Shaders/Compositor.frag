#version 330

uniform float exposure;
uniform float oneOverGamma;

uniform sampler2D colorTexture;
uniform sampler2D normalTexture;

in vec2 vertexTextureCoords;

out vec4 outputColor;

vec3 correctGamma(vec3 color, float oneOverGamma)
{
    return pow(color, vec3(oneOverGamma));
}

vec3 expose(vec3 color, float exposure)
{
    return vec3(1.0) - exp2(-exposure * color);
}

void main()
{
    vec3 color = texture(colorTexture, vertexTextureCoords).rgb;
    color = expose(color, exposure);
    color = correctGamma(color, oneOverGamma);
    outputColor = vec4(color, 1.0);

    vec3 normal = texture(normalTexture, vertexTextureCoords).rgb * 0.5 + 0.5;
    outputColor = vec4(normal, 1.0);
}