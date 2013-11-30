#pragma once

namespace hect
{

class EntityAttributes
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

    bool contains(const EntityAttributes& attributes) const;

private:
    std::bitset<64> _bitset;
};

}