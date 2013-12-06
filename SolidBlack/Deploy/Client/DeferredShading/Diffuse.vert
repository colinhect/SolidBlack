#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 3) in vec2 textureCoords;

uniform mat4 modelView;
uniform mat4 modelViewProjection;

mat3 normalMatrix = mat3(
  modelView[0][0], modelView[0][1], modelView[0][2],
  modelView[1][0], modelView[1][1], modelView[1][2],
  modelView[2][0], modelView[2][1], modelView[2][2]
);

out vec3 vertexNormal;
out vec2 vertexTextureCoords;

void main()
{
    gl_Position = modelViewProjection * vec4(position, 1.0);

    vertexNormal = normalize(normalMatrix * normal);
    vertexTextureCoords = textureCoords;
}