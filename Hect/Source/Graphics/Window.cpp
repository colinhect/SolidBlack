#include "Hect.h"

using namespace hect;

#include <SFML/Graphics.hpp>

#ifdef HECT_WINDOWS
#include <Windows.h>
#endif

// Default video mode values
const unsigned _defaultWidth = 256;
const unsigned _defaultHeight = 256;
const unsigned _defaultBitsPerPixel = 32;

// Translates an SFML mouse event to an internal mouse event.
MouseEvent _translateMouseEvent(const sf::Event& event, const Vector2<int>& cursorPosition, const Vector2<int>& lastCursorPosition)
{
    MouseEvent mouseEvent;

    switch (event.type)
    {
    case sf::Event::MouseMoved:
    {
        mouseEvent.type = MouseEventType::Movement;
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
            MouseEventType::ButtonDown :
            MouseEventType::ButtonUp;
        mouseEvent.button = (MouseButton)event.mouseButton.button;
    }
    break;
    case sf::Event::MouseWheelMoved:
    {
        mouseEvent.type =
            event.mouseWheel.delta < 0 ?
            MouseEventType::ScrollDown :
            MouseEventType::ScrollUp;
    }
    break;
    }

    // Get the position and movement of the cursor
    mouseEvent.cursorPosition = cursorPosition;
    mouseEvent.cursorMovement = mouseEvent.cursorPosition - lastCursorPosition;

    return mouseEvent;
}

// Translates an SFML keyboard event to an internal keyboard event.
KeyboardEvent _translateKeyboardEvent(const sf::Event& event)
{
    KeyboardEvent keyboardEvent;

    switch (event.type)
    {
    case sf::Event::KeyPressed:
    case sf::Event::KeyReleased:
    {
        keyboardEvent.type =
            event.type == sf::Event::KeyPressed ?
            KeyboardEventType::KeyDown :
            KeyboardEventType::KeyUp;
        keyboardEvent.key = (Key)event.key.code;
    }
    break;
    }

    return keyboardEvent;
}

Window::Window(const std::string& title, const DataValue& settings) :
    _sfmlWindow(nullptr)
{
    // Create the default video mode
    sf::VideoMode videoMode;
    videoMode.width = _defaultWidth;
    videoMode.height = _defaultHeight;
    videoMode.bitsPerPixel = _defaultBitsPerPixel;

    // Create the default style
    unsigned style = sf::Style::Titlebar | sf::Style::Close;

    // Video mode settings
    const DataValue& videoModeValue = settings["videoMode"];
    videoMode.width = videoModeValue["width"].or(_defaultWidth).asUnsigned();
    videoMode.height = videoModeValue["height"].or(_defaultHeight).asUnsigned();
    videoMode.bitsPerPixel = videoModeValue["bitsPerPixel"].or(_defaultBitsPerPixel).asUnsigned();
    if (videoModeValue["fullwindow"].asBool())
    {
        style |= sf::Style::Fullscreen;
    }

    // Create the window
    _sfmlWindow = new sf::Window(videoMode, title, style);

    setWidth(videoMode.width);
    setHeight(videoMode.height);
}

Window::~Window()
{
    if (_sfmlWindow)
    {
        ((sf::Window*)_sfmlWindow)->close();
        delete (sf::Window*)_sfmlWindow;
    }
}

void Window::bind(Renderer* renderer)
{
    renderer->bindWindow(*this);
}

bool Window::pollEvents(InputSystem& inputSystem)
{
    static bool cursorVisible = true;

    Mouse& mouse = inputSystem.mouse();
    Keyboard& keyboard = inputSystem.keyboard();

    sf::Vector2u windowSize = ((sf::Window*)_sfmlWindow)->getSize();
    sf::Vector2i windowCenter(windowSize.x / 2, windowSize.y / 2);

    // Occurs the first time pollEvents() is called after the mouse is locked
    if (mouse.isCursorLocked() && cursorVisible)
    {
        // Hide the cursor
        ((sf::Window*)_sfmlWindow)->setMouseCursorVisible(false);
        cursorVisible = false;

        // Move cursor to center of window
        sf::Mouse::setPosition(windowCenter, *((sf::Window*)_sfmlWindow));
        _lastCursorPosition = _cursorPosition();
    }

    // Occurs the first time pollEvents() is called after the mouse is unlocked
    else if (!mouse.isCursorLocked() && !cursorVisible)
    {
        // Show the cursor
        ((sf::Window*)_sfmlWindow)->setMouseCursorVisible(true);
        cursorVisible = true;

        // Move cursor to center of window
        sf::Mouse::setPosition(windowCenter, *((sf::Window*)_sfmlWindow));
        _lastCursorPosition = _cursorPosition();
    }

    // Poll all pending events and translate/dispatch to the proper systems
    sf::Event event;
    while (((sf::Window*)_sfmlWindow)->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            ((sf::Window*)_sfmlWindow)->close();
            break;
        case sf::Event::MouseMoved:
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        case sf::Event::MouseWheelMoved:
            inputSystem._enqueueEvent(_translateMouseEvent(event, _cursorPosition(), _lastCursorPosition));
            break;
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
            inputSystem._enqueueEvent(_translateKeyboardEvent(event));
            break;
        }
    }

    inputSystem._dispatchEvents();

    // If the cursor is locked then move it back to the center of the window
    if (mouse.isCursorLocked())
    {
        if (sf::Mouse::getPosition(*((sf::Window*)_sfmlWindow)) != windowCenter)
        {
            sf::Mouse::setPosition(windowCenter, *((sf::Window*)_sfmlWindow));
        }
    }

    // Save the current cursor position as the last current position in order to
    // compute the relative cursor movements
    _lastCursorPosition = _cursorPosition();

    return ((sf::Window*)_sfmlWindow)->isOpen();
}

void Window::swapBuffers()
{
    ((sf::Window*)_sfmlWindow)->display();
}

Vector2<int> Window::_cursorPosition()
{
    sf::Vector2i position = sf::Mouse::getPosition(*((sf::Window*)_sfmlWindow));
    return Vector2<int>(position.x, ((sf::Window*)_sfmlWindow)->getSize().y - position.y);
}

void Window::showFatalError(const std::string& message)
{
#ifdef HECT_WINDOWS
    MessageBoxA(NULL, message.c_str(), "Fatal Error", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#endif
}