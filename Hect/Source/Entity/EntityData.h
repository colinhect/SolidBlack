#pragma once

namespace hect
{

class EntityData
{
public:
    bool isActivated() const;
    void setActivated(bool activated);

    bool isDestroyed() const;
    void setDestroyed(bool destroyed);
    
    bool isNull() const;
    void setNull(bool null);

    bool hasComponent(ComponentTypeId type) const;
    void setHasComponent(ComponentTypeId type, bool value);

private:
    std::bitset<64> _bitset;
};

}