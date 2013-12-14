#pragma once

class Proxy :
    public Component<Proxy>
{
public:
    const std::string& entity() const;
    void setEntity(const std::string& entity);

private:
    std::string _entity;
};

class ProxySerializer :
    public ComponentSerializer<Proxy>
{
public:
    void save(const Proxy& broadcast, DataWriter& writer) const;
    void load(Proxy& broadcast, DataReader& reader, AssetCache& assetCache) const;
};