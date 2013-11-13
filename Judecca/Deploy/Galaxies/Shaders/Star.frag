#version 330

uniform sampler2D colorMap;

in vec3 starColor;

out vec4 outputColor;

void main()
{
    outputColor = texture(colorMap, gl_PointCoord) * vec4(starColor, 1.0);
}