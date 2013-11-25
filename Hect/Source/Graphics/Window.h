#pragma once

namespace hect
{

class Input;

///
/// The window that the engine is rendering to.
///
/// \remarks In most cases the window represents the native OS window.
class Window :
    public RenderTarget,
    public Uncopyable
{
public:
    Window(const std::string& title, Input& input, const DataValue& settings);
    ~Window();

    bool pollEvents();

    void swapBuffers();

    ///
    /// \copydoc RenderTarget::bind()
    void bind(Gpu* gpu);

private:
    Vector2<int> _cursorPosition();

    Input* _input;
    void* _sfmlWindow;

    Vector2<int> _lastCursorPosition;
};

}