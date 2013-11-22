#pragma once

namespace hect
{

class RenderingSystem;
class DebugRenderingSystem;

///
/// A component that can enqueue rendering tasks to a job.
class Renderable :
    public Component<Renderable>
{
public:

    ///
    /// Renders the component.
    ///
    /// \param camera The camera to render from.
    /// \param renderingSystem The rendering system.
    virtual void render(const Camera& camera, RenderingSystem& renderingSystem) { }

    ///
    /// Renders debug data of the component.
    ///
    /// \param camera The camera to render from.
    /// \param renderingSystem The rendering system.
    virtual void renderDebug(const Camera& camera, DebugRenderingSystem& renderingSystem) { }
};

}