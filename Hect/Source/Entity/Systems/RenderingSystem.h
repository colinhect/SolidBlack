#pragma once

namespace hect
{

///
/// Abstract system interface for rendering renderable components.
class RenderingSystem :
    public System
{
public:

    ///
    /// Constructs a rendering system given a renderer.
    ///
    /// \param renderer The renderer.
    RenderingSystem(Renderer& renderer);
    
    ///
    /// Adds a mesh to be rendered next frame.
    ///
    /// \param mesh The mesh to render.
    /// \param material The material to render the mesh using.
    /// \param transform The global transformation of the mesh.
    virtual void addMesh(Mesh& mesh, const Material& material, const Transform& transform) { }

    ///
    /// Adds a directional light to be rendered next frame.
    ///
    /// \param light The directional light.
    virtual void addDirectionalLight(DirectionalLight& light) { }

    ///
    /// Draws all visible renderables.
    ///
    /// \param camera The camera to render from.
    /// \param renderer The renderer.
    /// \param target The render target.
    virtual void renderAll(Camera& camera, RenderTarget& target) = 0;

protected:

    ///
    /// Renders a mesh.
    ///
    /// \param mesh The mesh to render.
    /// \param pass The pass the render the mesh with.
    /// \param transform The global transform of the mesh.
    /// \param camera The camera.
    /// \param target The render target.
    void renderMesh(Mesh& mesh, const Pass& pass, const Transform& transform, Camera& camera, const RenderTarget& target);

    ///
    /// Returns the renderer.
    Renderer& renderer();

private:
    Renderer* _renderer;
};

}