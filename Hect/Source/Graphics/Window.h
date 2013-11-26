#pragma once

namespace hect
{

class InputSystem;

///
/// The window that the engine is rendering to.
///
/// \remarks In most cases the window represents the native OS window.
class Window :
    public RenderTarget,
    public Uncopyable
{
public:
    Window(const std::string& title, const DataValue& settings);
    ~Window();

    bool pollEvents(InputSystem& inputSystem);

    void swapBuffers();

    ///
    /// \copydoc RenderTarget::bind()
    void bind(Renderer* renderer);

    static void showFatalError(const std::string& message);

private:
    Vector2<int> _cursorPosition();

    void* _sfmlWindow;

    Vector2<int> _lastCursorPosition;
};

}