#include "SolidBlack.h"

ServerLogicLayer::ServerLogicLayer(AssetCache& assetCache)
{
}

void ServerLogicLayer::fixedUpdate(double timeStep)
{
    _server.update(timeStep);
}