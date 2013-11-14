#include "ClientState.h"

ClientState::ClientState(Engine& engine) :
    State(engine, 1.0 / 60.0),
    _socket(1, 2)
{
    _connection = _socket.connect(IpAddress::localAddress(), 6006);
}

ClientState::~ClientState()
{
    if (_connection.state() == Connection::Connected)
    {
        LOG_INFO("Disconnecting");
        _socket.disconnect(_connection);
    }
}

void ClientState::update(double timeStep)
{
    Socket::Event event;
    while (_socket.pollEvent(event))
    {
        Connection connection = event.connection;
        std::string address = connection.address().toString();
        Connection::SocketId incomingSocketId = connection.incomingSocketId();
        Connection::SocketId outgoingSocketId = connection.outgoingSocketId();

        switch (event.type)
        {
        case Socket::Event::Connect:
            LOG_INFO(format("[in %d out %d] Connect (%s)", incomingSocketId, outgoingSocketId, address.c_str()));
            break;
        case Socket::Event::Disconnect:
            LOG_INFO(format("[in %d out %d] Disconnect (%s)", incomingSocketId, outgoingSocketId, address.c_str()));
            break;
        }
    }
}

void ClientState::notifyKeyboardEvent(const Keyboard::Event& event)
{
    if (event.type != Keyboard::Event::KeyDown)
    {
        return;
    }

    if (event.key == Keyboard::Esc)
    {
        setActive(false);
    }
}