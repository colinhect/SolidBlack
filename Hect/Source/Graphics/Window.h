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

    ///
    /// Shows a fatal error.
    ///
    /// \param message The error message to show.
    static void showFatalError(const std::string& message);

    ///
    /// Constructs a window given a title and the settings.
    ///
    /// \param title The window title.
    /// \param settings The settings.
    Window(const std::string& title, const DataValue& settings);
    
    ///
    /// Closes the window.
    ~Window();

    ///
    /// Polls events from the window and redirects them to an input system.
    ///
    /// \param inputSystem The input system to redirect the window input events
    /// to.
    ///
    /// \returns True if the window has not received a close event; false
    /// otherwise.
    bool pollEvents(InputSystem& inputSystem);

    ///
    /// Swaps the back buffer.
    void swapBuffers();

    ///
    /// \copydoc RenderTarget::bind()
    void bind(Renderer* renderer);

private:
    Vector2<int> _cursorPosition();

    void* _sfmlWindow;

    Vector2<int> _lastCursorPosition;
};

}