// Inventory.h
#pragma once
#include <string>
#include <vector>

class Inventory {
  public:
    // TODO: better constructor for the added data members
    Inventory();

    int gold = 0;
    // TODO: add more stuffs here like unlocked equipments, consumables, etc.

    std::vector<std::string> items;
    // NOTE: for item, we can just use id instead of making a new class
    // it will look like "1-Healing_potion"
    // 1 is the count (how many of that item)
    // after the dash(-) is the item name
    // TODO: have a helper parse function for parsing item id
    // TODO: have a helper parse function for item name (get rid of the underscore(_))
};

