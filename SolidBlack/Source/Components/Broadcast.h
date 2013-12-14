#pragma once

class Broadcast :
    public Component<Broadcast>
{
public:
    const std::string& clientEntity() const;
    void setClientEntity(const std::string& clientEntity);

private:
    std::string _clientEntity;
};

class BroadcastSerializer :
    public ComponentSerializer<Broadcast>
{
public:
    void save(const Broadcast& broadcast, DataWriter& writer) const;
    void load(Broadcast& broadcast, DataReader& reader, AssetCache& assetCache) const;
};