#pragma once

class EntityIdTranslator
{
public:
    EntityIdTranslator();

    void set(Entity::Id serverEntityId, Entity::Id clientEntityId);
    
    Entity::Id serverToClient(Entity::Id entityId);
    Entity::Id clientToServer(Entity::Id entityId);

private:
    std::vector<Entity::Id> _serverToClient;
    std::vector<Entity::Id> _clientToServer;
};