// Item.h
#pragma once

#include <string>


class Item{
  public:


    Item(
        std::string name,
        int count,
        long id,
        int damage

        );


    std::string getItemName(Item item);
    int getItemCount(Item item);
    long getItemId(Item item);
    int getItemDamage(Item item);
};
