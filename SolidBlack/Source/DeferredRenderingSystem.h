#pragma once

#include <Hect.h>
using namespace hect;

class DeferredRenderingSystem :
    public RenderingSystem
{
public:
    DeferredRenderingSystem(Renderer& renderer, AssetCache& assetCache, const DataValue& settings);

    void addMesh(Mesh& mesh, const Material& material, const Transform& transform);
    void renderAll(Camera& camera, RenderTarget& target);

    double gamma() const;
    void setGamma(double gamma);

    double exposure() const;
    void setExposure(double exposure);

private:
    struct MeshTask
    {
        Mesh* mesh;
        const Pass* pass;
        const Transform* transform;
    };
    void _renderMeshTask(const MeshTask& task, Camera& camera, const RenderTarget& target);

    std::vector<MeshTask> _meshTasks;

    std::unique_ptr<FrameBuffer> _frameBuffer;

    Shader::Ref _compositorShader;
    Mesh::Ref _windowMesh;

    const Uniform* _oneOverGammaUniform;
    const Uniform* _exposureUniform;

    double _gamma;
    double _exposure;
};