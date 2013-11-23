{
    "modules" :
    [
        "Shaders/Diffuse.frag",
        "Shaders/Diffuse.vert"
    ],
    "uniforms" :
    {
        "diffuseTexture" :
        {
            "type" : "Texture",
            "defaultValue" : 0
        },
        "diffuseIntensityRange" :
        {
            "type" : "Vector2",
            "defaultValue" : [ 0, 1 ]
        },
        "modelViewProjection" :
        {
            "binding" : "ModelViewProjectionMatrix"
        }
    }
}