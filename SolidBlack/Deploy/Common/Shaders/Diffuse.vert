#version 330

layout(location = 0) in vec3 position;
layout(location = 3) in vec2 textureCoords;

uniform mat4 modelViewProjection;

out vec2 vertexTextureCoords;

void main()
{
    gl_Position = modelViewProjection * vec4(position, 1.0);
    vertexTextureCoords = textureCoords;
}