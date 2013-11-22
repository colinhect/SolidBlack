{
    "modules" :
    [
        "Shaders/Compositor.frag",
        "Shaders/Compositor.vert"
    ],
    "uniforms" :
    {
        "exposure" :
        {
            "type" : "Float",
            "defaultValue" : 0.0015
        },
        "oneOverGamma" :
        {
            "type" : "Float",
            "defaultValue" : 0.4545
        },
        "sourceTexture" :
        {
            "type" : "Texture",
            "defaultValue" : 0
        }
    }
}