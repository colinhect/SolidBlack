#include "SolidBlack.h"

ServerLogicLayer::ServerLogicLayer(AssetCache& assetCache) :
    _server(),
    _scene(),
    _proxySystem(_scene, assetCache, _server.socket())
{
    _server.addListener(*this);

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

void ServerLogicLayer::fixedUpdate(double timeStep)
{
    timeStep;

    _server.refresh();
    _scene.refresh();
}

void ServerLogicLayer::receivePacket(const Player& player, PacketType type, PacketReadStream& stream)
{
    switch (type)
    {
    case PacketType::Authorization:
        _proxySystem.createAll(player.peer);
        break;
    }
}