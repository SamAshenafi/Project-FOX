#ifndef INVENTORY_H
#define INVENTORY_H

#include "ItemAssets.h"  // Updated to include the correct header file for ItemAssets
#include <string>
#include <unordered_map>

// Inventory class to manage items and quantities
class Inventory {
private:
    std::unordered_map<std::string, int> items; // Map of item IDs to quantities

public:
    void AddItem(const std::string& itemId);
    void UseItem(const std::string& itemId);
    const std::unordered_map<std::string, int>& GetItems() const {
        return items;
    }
};

#endif // INVENTORY_H
