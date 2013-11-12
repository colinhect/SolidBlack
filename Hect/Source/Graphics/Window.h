namespace hect
{

///
/// The OS window the engine is rendering to.
class Window :
    public RenderTarget,
    public Uncopyable
{
    friend class Engine;
public:

    ///
    /// \copydoc RenderTarget::bind()
    void bind(Gpu* gpu);

private:
    Window() { }
};

}