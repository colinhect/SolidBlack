#pragma once

namespace hect
{

///
/// Renders renderables.
class RenderingSystem :
    public System
{
public:

    ///
    /// Constructs a rendering system.
    RenderingSystem();

    ///
    /// Renders a mesh.
    ///
    /// \param mesh The mesh to render.
    /// \param material The material to render the mesh using.
    /// \param transform The global transformation of the mesh.
    virtual void renderMesh(Mesh& mesh, const Material& material, const Transform& transform);

    ///
    /// Draws all visible renderables.
    ///
    /// \param camera The camera to render from.
    /// \param renderer The renderer.
    /// \param target The render target.
    virtual void renderAll(Camera& camera, Renderer& renderer, RenderTarget& target);

private:
    struct MeshTask
    {
        Mesh* mesh;
        const Pass* pass;
        const Transform* transform;
    };
    void _renderMeshTask(const MeshTask& task, Camera& camera, Renderer& renderer, const RenderTarget& target);

    std::vector<MeshTask> _meshTasks;
};

}