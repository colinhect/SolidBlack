namespace hect
{

///
/// Renders debug information.
class DebugRenderingSystem :
    public EntitySystem
{
public:

    ///
    /// Constructs a debug rendering system.
    DebugRenderingSystem();

    ///
    /// Renders a wireframe box.
    ///
    /// \param position The center position of the box.
    /// \param scale The scale of the box.
    /// \param color The color of the box.
    void renderWireframeBox(const Vector3<>& position, const Vector3<>& scale, const Vector4<>& color);

    ///
    /// Draws debug information for all visible renderables.
    ///
    /// \param camera The camera to render from.
    /// \param gpu The GPU.
    /// \param target The target to render to.
    void renderAll(Camera& camera, Gpu& gpu, RenderTarget& target);

private:
    struct BoxTask
    {
        Vector3<> position;
        Vector3<> scale;
        Vector4<> color;
    };
    void _renderBoxTask(const BoxTask& task, Camera& camera, Gpu& gpu);

    void _buildBoxMesh();
    void _buildBoxShader();

    std::vector<BoxTask> _boxTasks;

    Mesh::Ref _boxMesh;
    Shader::Ref _boxShader;
};

}