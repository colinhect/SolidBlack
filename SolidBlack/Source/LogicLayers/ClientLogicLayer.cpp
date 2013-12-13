#include "SolidBlack.h"

ClientLogicLayer::ClientLogicLayer(IpAddress serverAddress, Port port) :
    _client(serverAddress, port)
{
}

void ClientLogicLayer::fixedUpdate(double timeStep)
{
    _client.update();
}