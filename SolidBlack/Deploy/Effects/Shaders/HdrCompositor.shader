{
    "modules" :
    [
        "Shaders/HdrCompositor.frag",
        "Shaders/HdrCompositor.vert"
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