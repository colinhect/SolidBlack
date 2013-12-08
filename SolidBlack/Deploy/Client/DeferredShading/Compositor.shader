{
    "modules" :
    [
        "DeferredShading/Compositor.frag",
        "DeferredShading/Screen.vert"
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
        "colorBuffer" :
        {
            "type" : "Texture",
            "defaultValue" : 0
        },
        "lightingBuffer" :
        {
            "type" : "Texture",
            "defaultValue" : 1
        }
    }
}