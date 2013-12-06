{
    "modules" :
    [
        "DeferredShading/Diffuse.frag",
        "DeferredShading/Diffuse.vert"
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
        "modelView" :
        {
            "binding" : "ModelViewMatrix"
        },
        "modelViewProjection" :
        {
            "binding" : "ModelViewProjectionMatrix"
        }
    }
}