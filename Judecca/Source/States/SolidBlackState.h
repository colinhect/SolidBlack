#pragma once

#include <Hect.h>

using namespace hect;

class SolidBlackState :
    public State,
    public Keyboard::Listener
{
public:
    SolidBlackState(Engine& engine);

    virtual void begin();
    virtual void end();

    virtual void update(double timeStep);
    void render(double delta);

    void notifyKeyboardEvent(const Keyboard::Event& event);

protected:
    AssetCache& assetCache();
    Scene& galaxyScene();

    unsigned debugLevel() const;

private:
    AssetCache _assetCache;
    Scene _galaxyScene;

    CameraSystem _cameraSystem;
    RenderingSystem _renderingSystem;
    DebugRenderingSystem _debugRenderingSystem;

    std::unique_ptr<FrameBuffer> _frameBuffer;

    Shader::Ref _hdrCompositorShader;
    Mesh::Ref _screenMesh;

    const Shader::Parameter* _oneOverGammaParameter;
    const Shader::Parameter* _exposureParameter;

    double _gamma;
    double _exposure;

    unsigned _debugLevel;
};