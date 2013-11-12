#include "Hect.h"

using namespace hect;

#include <SFML/Graphics.hpp>

#ifdef HECT_WINDOWS
#include <Windows.h>
#endif

// Default video mode values
const unsigned _defaultWidth = 800;
const unsigned _defaultHeight = 600;
const unsigned _defaultBitsPerPixel = 32;

// The SFML window
sf::Window* _sfmlWindow = nullptr;

// The engine instance
Engine* _engine = nullptr;

// Translates an SFML mouse event to an internal mouse event.
Mouse::Event _translateMouseEvent(const sf::Event& event, const Vector2<int>& cursorPosition, const Vector2<int>& lastCursorPosition)
{
    Mouse::Event mouseEvent;

    switch (event.type)
    {
    case sf::Event::MouseMoved:
    {
        mouseEvent.type = Mouse::Event::Movement;
    }
    break;
    case sf::Event::MouseButtonPressed:
    case sf::Event::MouseButtonReleased:
    {

        // Ignore unsupported buttons
        if (event.mouseButton.button >= 3)
        {
            break;
        }

        mouseEvent.type =
            event.type == sf::Event::MouseButtonPressed ?
            Mouse::Event::ButtonDown :
            Mouse::Event::ButtonUp;
        mouseEvent.button = (Mouse::Button)event.mouseButton.button;
    }
    break;
    case sf::Event::MouseWheelMoved:
    {
        mouseEvent.type =
            event.mouseWheel.delta < 0 ?
            Mouse::Event::ScrollDown :
            Mouse::Event::ScrollUp;
    }
    break;
    }

    // Get the position and movement of the cursor
    mouseEvent.cursorPosition = cursorPosition;
    mouseEvent.cursorMovement = mouseEvent.cursorPosition - lastCursorPosition;

    return mouseEvent;
}

// Translates an SFML keyboard event to an internal keyboard event.
Keyboard::Event _translateKeyboardEvent(const sf::Event& event)
{
    Keyboard::Event keyboardEvent;

    switch (event.type)
    {
    case sf::Event::KeyPressed:
    case sf::Event::KeyReleased:
    {
        keyboardEvent.type =
            event.type == sf::Event::KeyPressed ?
            Keyboard::Event::KeyDown :
            Keyboard::Event::KeyUp;
        keyboardEvent.key = (Keyboard::Key)event.key.code;
    }
    break;
    }

    return keyboardEvent;
}

Engine::Engine(const std::string& title, const Path& settingsFile)
{

    // Prevent multiple engine instances
    if (_engine)
    {
        throw Error("Attempt to instantiate multiple engines");
    }
    _engine = this;

    // Add the working directory as readable to the filesystem
    Path workingDirectory = _storage.workingDirectory();
    _storage.addDataSource(workingDirectory);

    // Create the default video mode
    sf::VideoMode videoMode;
    videoMode.width = _defaultWidth;
    videoMode.height = _defaultHeight;
    videoMode.bitsPerPixel = _defaultBitsPerPixel;

    // Create the default style
    unsigned style = sf::Style::Titlebar | sf::Style::Close;

    // Try to load configuration
    try
    {
        LOG_INFO("Loading settings...");

        FileReadStream stream = _storage.openFileForRead(settingsFile);
        _settings = JsonParser().parse(stream);

        // Video mode settings
        const DataValue& videoModeValue = _settings["videoMode"];
        videoMode.width = videoModeValue["width"].or(_defaultWidth).asUnsigned();
        videoMode.height = videoModeValue["height"].or(_defaultHeight).asUnsigned();
        videoMode.bitsPerPixel = videoModeValue["bitsPerPixel"].or(_defaultBitsPerPixel).asUnsigned();
        if (videoModeValue["fullscreen"].asBool())
        {
            style |= sf::Style::Fullscreen;
        }

        // Add data sources
        for (const DataValue& dataSource : _settings["dataSources"])
        {
            LOG_INFO(format("Adding data source '%s'...", dataSource.asString().c_str()));

            _storage.addDataSource(dataSource.asString());
        }
    }
    catch (Error&)
    {
        LOG_ERROR("Failed to load config (using default settings)");
    }

    LOG_INFO("Creating window...");
    LOG_INFO(format("Resolution: %dx%dx%d", videoMode.width, videoMode.height, videoMode.bitsPerPixel));
    LOG_INFO(format("Fullscreen: %s", (style & sf::Style::Fullscreen) == sf::Style::Fullscreen ? "yes" : "no"));

    // Create the window
    _sfmlWindow = new sf::Window(videoMode, title, style);
    _window.setWidth(videoMode.width);
    _window.setHeight(videoMode.height);

    LOG_INFO("Initializing graphics...");

    // Initialize gpu
    _gpu.initialize();

    // Set the last cursor position to avoid a large relative movement on the
    // first movement event
    _lastCursorPosition = _cursorPosition();
}

Engine::~Engine()
{
    if (_sfmlWindow)
    {
        LOG_INFO("Closing window...");

        _sfmlWindow->close();
        delete _sfmlWindow;
    }
    _engine = nullptr;
}

void Engine::execute()
{
    if (_states.empty())
    {
        return;
    }

    TimeSpan timeStep, currentTime, accumulator, delta;
    std::shared_ptr<State> currentState;

    while (_pollEvents())
    {
        // A new state was push on the stack
        if (currentState && !_states.empty() && currentState != _states.top())
        {
            currentState->end();
            currentState = _states.top();
            _states.pop();

            currentState->begin();
            timeStep = TimeSpan::fromSeconds(currentState->timeStep());
            currentTime = elapsedTime();
            accumulator = TimeSpan();
            delta = TimeSpan();
        }

        // We have no current state or the current state is inactive
        else if (!currentState || !currentState->isActive())
        {
            if (_states.empty())
            {
                break;
            }

            currentState = _states.top();
            _states.pop();

            currentState->begin();
            timeStep = TimeSpan::fromSeconds(currentState->timeStep());
            currentTime = elapsedTime();
            accumulator = TimeSpan();
            delta = TimeSpan();
        }

        TimeSpan newTime = elapsedTime();
        TimeSpan deltaTime = newTime - currentTime;
        currentTime = newTime;

        accumulator += deltaTime;
        delta += deltaTime;

        while (accumulator.microseconds() >= timeStep.microseconds())
        {
            currentState->update(timeStep.seconds());
            _input._update(timeStep.seconds());

            delta = TimeSpan();
            accumulator -= timeStep;
        }

        currentState->render(delta.seconds() / timeStep.seconds());
    }
}

void Engine::swapBuffers()
{
    _sfmlWindow->display();
}

Storage& Engine::storage()
{
    return _storage;
}

Input& Engine::input()
{
    return _input;
}

Gpu& Engine::gpu()
{
    return _gpu;
}

Window& Engine::window()
{
    return _window;
}

const DataValue& Engine::settings() const
{
    return _settings;
}

TimeSpan Engine::elapsedTime() const
{
    static sf::Clock clock;
    return TimeSpan::fromMicroseconds(clock.getElapsedTime().asMicroseconds());
}

bool Engine::_pollEvents()
{
    static bool cursorVisible = true;

    Mouse& mouse = _input.mouse();
    Keyboard& keyboard = _input.keyboard();

    sf::Vector2u windowSize = _sfmlWindow->getSize();
    sf::Vector2i windowCenter(windowSize.x / 2, windowSize.y / 2);

    // Occurs the first time pollEvents() is called after the mouse is locked
    if (mouse.isCursorLocked() && cursorVisible)
    {

        // Hide the cursor
        _sfmlWindow->setMouseCursorVisible(false);
        cursorVisible = false;

        // Move cursor to center of window
        sf::Mouse::setPosition(windowCenter, *_sfmlWindow);
        _lastCursorPosition = _cursorPosition();
    }

    // Occurs the first time pollEvents() is called after the mouse is unlocked
    else if (!mouse.isCursorLocked() && !cursorVisible)
    {

        // Show the cursor
        _sfmlWindow->setMouseCursorVisible(true);
        cursorVisible = true;

        // Move cursor to center of window
        sf::Mouse::setPosition(windowCenter, *_sfmlWindow);
        _lastCursorPosition = _cursorPosition();
    }

    // Poll all pending events and translate/dispatch to the proper systems
    sf::Event event;
    while (_sfmlWindow->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            _sfmlWindow->close();
            break;
        case sf::Event::MouseMoved:
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        case sf::Event::MouseWheelMoved:
            _input._enqueueEvent(_translateMouseEvent(event, _cursorPosition(), _lastCursorPosition));
            break;
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
            _input._enqueueEvent(_translateKeyboardEvent(event));
            break;
        }
    }

    _input._dispatchEvents();

    // If the cursor is locked then move it back to the center of the window
    if (mouse.isCursorLocked())
    {
        if (sf::Mouse::getPosition(*_sfmlWindow) != windowCenter)
        {
            sf::Mouse::setPosition(windowCenter, *_sfmlWindow);
        }
    }

    // Save the current cursor position as the last current position in order to
    // compute the relative cursor movements
    _lastCursorPosition = _cursorPosition();

    return _sfmlWindow->isOpen();
}

Vector2<int> Engine::_cursorPosition()
{
    sf::Vector2i position = sf::Mouse::getPosition(*_sfmlWindow);
    return Vector2<int>(position.x, _sfmlWindow->getSize().y - position.y);
}

void Engine::fatalError(const std::string& message)
{
#ifdef HECT_WINDOWS
    MessageBoxA(NULL, message.c_str(), "Fatal Error", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#endif
}