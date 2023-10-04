#include "Item.h"


class Item
{
    private:
        std::string name;
        int count;
        int itemId;
        int damage;
        std::string sprite;
    
    public:
        Item(std::string name, int count, long id, int damage);
        std::string getItemName() const{
            return name;
        }

        int getItemCount() const{
            return count;
        }

        long getItemId() const{
            return itemId;
        }

        int getItemDamage() const{
            return damage;
        }
        std::string getSprite() const{
            return sprite;
        }
};

Item::Item(std::string name, int count, long id, int damage)
    : name(name), count(count), itemId(itemId), damage(damage), sprite(sprite)
{
}



