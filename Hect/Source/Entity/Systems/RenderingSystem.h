#pragma once

namespace hect
{

///
/// Renders renderables.
class RenderingSystem :
    public EntitySystem
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
    void renderMesh(Mesh& mesh, const Material& material, const Transform& transform);

    ///
    /// Draws all visible renderables.
    ///
    /// \param camera The camera to render from.
    /// \param gpu The GPU.
    /// \param target The render target (for referencing size only).
    void renderAll(Camera& camera, Gpu& gpu, const RenderTarget& target);

private:
    struct MeshTask
    {
        Mesh* mesh;
        const Pass* pass;
        const Transform* transform;
    };
    void _renderMeshTask(const MeshTask& task, Camera& camera, Gpu& gpu, const RenderTarget& target);

    std::vector<MeshTask> _meshTasks;
};

}