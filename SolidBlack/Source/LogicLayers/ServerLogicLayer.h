#pragma once

class ServerLogicLayer :
    public LogicLayer,
    public Uncopyable
{
public:
    ServerLogicLayer(AssetCache& assetCache);

    void fixedUpdate(double timeStep);

private:
    Server _server;
};