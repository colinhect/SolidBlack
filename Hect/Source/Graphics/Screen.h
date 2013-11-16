#pragma once

namespace hect
{

///
/// The screen that the engine is rendering to.
///
/// \remarks In most cases the screen represents the native OS window.
class Screen :
    public RenderTarget,
    public Uncopyable
{
    friend class Engine;
public:

    ///
    /// \copydoc RenderTarget::bind()
    void bind(Gpu* gpu);

private:
    Screen() { }
};

}