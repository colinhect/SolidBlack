#pragma once

namespace hect
{

class State;

///
/// The entry point of a client application.
///
/// \remarks Provides the flow for the states the engine will be in as
/// well as access to fundamental systems of the engine.
///
/// \warning Only one engine can be instantiated at a time.
class Engine :
    public Uncopyable
{
public:

    ///
    /// Constructs an engine given the window title and the path to the
    /// settings file to load.
    ///
    /// \remarks If for any reason the settings file cannot be loaded then
    /// sensible defaults are used.  Similarly, if any specific setting values
    /// are missing or invalid then the sensible default for that setting will
    /// be used.
    ///
    /// \param title The window title.
    /// \param settingsFile The path (in the working directory) to the settings
    /// file.
    ///
    /// \throws Error If an engine is already instantiated.
    Engine(const std::string& title, const Path& settingsFile);

    ///
    /// Closes the engine.
    ~Engine();

    bool pollEvents();

    ///
    /// Swaps the back buffers making the most recently drawn buffer visible
    /// on the screen.
    void swapBuffers();

    ///
    /// Returns access to persistent storage.
    Storage& storage();

    ///
    /// Returns access to input peripherals.
    Input& input();

    ///
    /// Returns access to the graphics processing unit.
    Gpu& gpu();

    ///
    /// Returns the screen.
    Screen& screen();

    ///
    /// Returns the settings loaded during engine initialization.
    const DataValue& settings() const;

    ///
    /// Displays a fatal error message to the user.
    ///
    /// \param message The error message to display.
    static void fatalError(const std::string& message);

private:
    Vector2<int> _cursorPosition();

    Storage _storage;
    Input _input;
    Gpu _gpu;
    Screen _screen;
    DataValue _settings;

    Vector2<int> _lastCursorPosition;
};

}