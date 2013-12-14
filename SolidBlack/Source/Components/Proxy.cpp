#include "SolidBlack.h"

const std::string& Proxy::entity() const
{
    return _entity;
}

void Proxy::setEntity(const std::string& entity)
{
    _entity = entity;
}

void ProxySerializer::save(const Proxy& proxy, DataWriter& writer) const
{
    writer.writeString("entity", proxy.entity());
}

void ProxySerializer::load(Proxy& proxy, DataReader& reader, AssetCache& assetCache) const
{
    assetCache;

    if (reader.hasMember("entity"))
    {
        std::string entity = reader.readString("entity");
        proxy.setEntity(entity);
    }
}