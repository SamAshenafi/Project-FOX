// Item.h
#pragma once

#include <string>


class Item{

    private:
        std::string name;
        int count;
        long itemId;
        int damage;
        std::string sprite;

    public:


        Item(std::string name, int count, long itemId, int damage, std::string sprite);
        std::string getItemName() const;
        int getItemCount() const;
        long getItemId() const;
        int getItemDamage() const;
        std::string getSprite() const;
};
