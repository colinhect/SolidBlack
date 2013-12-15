#include "SolidBlack.h"

ServerBubble::ServerBubble(Server& server, AssetCache& assetCache) :
    _server(&server),
    _assetCache(&assetCache),
    _proxySystem(assetCache, server.socket())
{
    server.addListener(*this);

    _scene.registerComponent<DebugCamera, DebugCameraSerializer>("DebugCamera");
    _scene.registerComponent<Proxy, ProxySerializer>("Proxy");

    _scene.addSystem(_proxySystem);
    _scene.addSystem(_physicsSystem);

    {
        DataValue::Ref sceneValue = assetCache.get<DataValue>("Test.scene");
        _scene.load(*sceneValue, assetCache);
    }

    _scene.refresh();
}

ServerBubble::~ServerBubble()
{
    _server->removeListener(*this);
}

void ServerBubble::fixedUpdate(double timeStep)
{
    timeStep;

    _scene.refresh();
}

void ServerBubble::receivePacket(const Player& player, PacketType type, PacketReadStream& stream)
{
    stream;

    switch (type)
    {
    case PacketType::Authorization:
        _proxySystem.createAll(player.peer);
        break;
    }
}