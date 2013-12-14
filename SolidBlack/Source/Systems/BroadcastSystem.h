#pragma once

class BroadcastSystem :
    public System
{
public:
    BroadcastSystem(Scene& scene);

    bool includesEntity(const Entity& entity) const;

    void addEntity(Entity& entity);
    void removeEntity(Entity& entity);

private:
    Scene* _scene;
};