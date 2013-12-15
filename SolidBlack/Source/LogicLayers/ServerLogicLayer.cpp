#include "SolidBlack.h"

ServerLogicLayer::ServerLogicLayer(AssetCache& assetCache)
{
    _bubbles.push_back(ServerBubble::Ref(new ServerBubble(_server, assetCache)));
}

void ServerLogicLayer::fixedUpdate(double timeStep)
{
    timeStep;

    for (const ServerBubble::Ref& bubble : _bubbles)
    {
        bubble->fixedUpdate(timeStep);
    }

    _server.refresh();
}