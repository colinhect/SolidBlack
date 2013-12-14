#include "SolidBlack.h"

const std::string& Broadcast::clientEntity() const
{
    return _clientEntity;
}

void Broadcast::setClientEntity(const std::string& clientEntity)
{
    _clientEntity = clientEntity;
}

void BroadcastSerializer::save(const Broadcast& broadcast, DataWriter& writer) const
{
    writer.writeString("clientEntity", broadcast.clientEntity());
}

void BroadcastSerializer::load(Broadcast& broadcast, DataReader& reader, AssetCache& assetCache) const
{
    assetCache;

    if (reader.hasMember("clientEntity"))
    {
        std::string clientEntity = reader.readString("clientEntity");
        broadcast.setClientEntity(clientEntity);
    }
}