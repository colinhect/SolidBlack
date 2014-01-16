#pragma once

namespace hect
{

///
/// Provides basic rendering.
class BasicRenderSystem :
    public System
{
public:

    ///
    /// Constructs the system given the renderer.
    ///
    /// \param renderer The renderer.
    BasicRenderSystem(Renderer& renderer);

    ///
    /// \copydoc System::includesEntity()
    bool includesEntity(const Entity& entity) const;

    ///
    /// Renders all visible entities.
    ///
    /// \param camera The camera to render from.
    /// \param target The target to render to.
    void renderAll(Camera& camera, RenderTarget& target);

private:
    void _renderMeshPass(const Camera& camera, const RenderTarget& target, const Pass& pass, Mesh& mesh, const Transform& transform);

    Renderer* _renderer;
};

}