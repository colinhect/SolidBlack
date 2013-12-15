#include "SolidBlack.h"

EntityIdTranslator::EntityIdTranslator() :
    _serverToClient(1024),
    _clientToServer(1024)
{
}

void EntityIdTranslator::set(Entity::Id serverEntityId, Entity::Id clientEntityId)
{
    Entity::Id max = std::max(serverEntityId, clientEntityId);
    if (max > _serverToClient.size())
    {
        _serverToClient.resize(_serverToClient.size() * 2);
        _clientToServer.resize(_clientToServer.size() * 2);
    }
    
    _serverToClient[serverEntityId] = clientEntityId;
    _clientToServer[clientEntityId] = serverEntityId;
}

Entity::Id EntityIdTranslator::serverToClient(Entity::Id entityId)
{
    return _serverToClient[entityId];
}

Entity::Id EntityIdTranslator::clientToServer(Entity::Id entityId)
{
    return _clientToServer[entityId];
}
