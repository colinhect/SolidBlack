{
    "modules" :
    [
        "DeferredShading/DirectionalLight.frag",
        "DeferredShading/Screen.vert"
    ],
    "uniforms" :
    {
        "color" :
        {
            "type" : "Vector3"
        },
        "direction" :
        {
            "type" : "Vector3"
        },
        "colorTexture" :
        {
            "type" : "Texture",
            "defaultValue" : 0
        },
        "normalTexture" :
        {
            "type" : "Texture",
            "defaultValue" : 1
        },
        "view" :
        {
            "type" : "Matrix4"
        }
    }
}