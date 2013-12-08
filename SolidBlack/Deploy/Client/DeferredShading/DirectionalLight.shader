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
        "view" :
        {
            "type" : "Matrix4"
        },
        "normalBuffer" :
        {
            "type" : "Texture",
            "defaultValue" : 0
        }
    }
}