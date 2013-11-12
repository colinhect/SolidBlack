namespace hect
{

class RenderingSystem;
class DebugRenderingSystem;

///
/// A component that can enqueue rendering tasks to a job.
class Renderable :
    public EntityComponent<Renderable>
{
public:

    ///
    /// Renders the component.
    ///
    /// \param camera The camera to render from.
    /// \param renderingSystem The rendering system.
    virtual void render(Camera& camera, RenderingSystem& renderingSystem) { }

    ///
    /// Renders debug data of the component.
    ///
    /// \param camera The camera to render from.
    /// \param renderingSystem The rendering system.
    virtual void renderDebug(Camera& camera, DebugRenderingSystem& renderingSystem) { }
};

}