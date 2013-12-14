#pragma once

class ClientLogicLayer :
    public LogicLayer,
    public Uncopyable
{
public:
    ClientLogicLayer(IpAddress serverAddress, Port port);
    ~ClientLogicLayer();
    
    void fixedUpdate(double timeStep);
    void frameUpdate(double delta);

private:
    void _receivePacketEvent(SocketEvent& event);
    void _sendAuthorization();

    Socket _socket;
    Peer _server;
};