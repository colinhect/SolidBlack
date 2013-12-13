#pragma once

class ClientLogicLayer :
    public LogicLayer,
    public Uncopyable
{
public:
    ClientLogicLayer(IpAddress serverAddress, Port port);

    void fixedUpdate(double timeStep);

private:
    Client _client;
};