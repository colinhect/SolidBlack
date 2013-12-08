#version 330

uniform vec3 color;
uniform vec3 direction;
uniform sampler2D normalTexture;
uniform mat4 view;

mat3 normalMatrix = mat3(
  view[0][0], view[0][1], view[0][2],
  view[1][0], view[1][1], view[1][2],
  view[2][0], view[2][1], view[2][2]
);

in vec2 vertexTextureCoords;

out vec4 outputColor;

void main()
{
    float x = texture(normalTexture, vertexTextureCoords).a;
    if (x > 0.0)
    {
        vec3 normal = texture(normalTexture, vertexTextureCoords).rgb;
        outputColor = vec4(color, 1.0) * max(dot(normal, normalize(normalMatrix * direction)), 0.0);
    }
    else
    {
        discard;
    }
}