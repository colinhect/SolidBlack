#version 330

uniform mat4 modelViewProjection;

layout(location = 0) in vec3 position;
layout(location = 1) in float spectralType;

out vec3 starColor;

void main()
{
    /*
    // O
    if (spectralType > 6.0)
    {
        starColor = vec3(0.9, 1.0, 1.0) * intensity;
    }
    // B
    else if (spectralType > 5.0)
    {
        starColor = vec3(1.0, 1.0, 1.0) * intensity;
    }
    // A
    else if (spectralType > 4.0)
    {
        starColor = vec3(1.0, 1.0, 1.0) * intensity;
    }
    // F
    else if (spectralType > 3.0)
    {
        starColor = vec3(1.0, 1.0, 1.0) * intensity;
    }
    // G
    else if (spectralType > 2.0)
    {
        starColor = vec3(1.0, 1.0, 1.0) * intensity;
    }
    // K
    else if (spectralType > 1.0)
    {
        starColor = vec3(1.0, 1.0, 1.0) * intensity;
    }
    // M
    else
    {
        starColor = vec3(1.0, 1.0, 1.0) * intensity;
    }
    */
    gl_Position = modelViewProjection * vec4(position, 1.0);
    gl_PointSize = 4.0;

    starColor = vec3(15.0);
}