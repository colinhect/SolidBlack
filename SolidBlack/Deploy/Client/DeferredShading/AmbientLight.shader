{
    "modules" :
    [
        "DeferredShading/AmbientLight.frag",
        "DeferredShading/Screen.vert"
    ],
    "uniforms" :
    {
        "color" :
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
        }
    }
}