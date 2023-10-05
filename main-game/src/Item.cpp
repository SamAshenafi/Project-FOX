#include "Item.h"

Item::Item(std::string name, int count, long itemId, int damage, std::string sprite)
    : name(name), count(count), itemId(itemId), damage(damage), sprite(sprite)
{
}

std::string Item::getItemName() const{
    return name;
}

int Item::getItemCount() const{
    return count;
}

long Item::getItemId() const{
    return itemId;
}

int Item::getItemDamage() const{
    return damage;
}

std::string Item::getSprite() const{
    return sprite;
}
