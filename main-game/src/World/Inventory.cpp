#include "Inventory.h"
#include <iostream>

void Inventory::AddItem(const std::string& itemId) {
    items[itemId]++;
}

void Inventory::UseItem(const std::string& itemId) {
    auto it = items.find(itemId);
    if (it != items.end() && it->second > 0) {
        const auto& itemProperties = ItemAssets::items.at(itemId);
        switch (itemProperties.type) {
            case ItemType::HEALING:
                std::cout << "Healing with " << itemProperties.id << " for " << itemProperties.value << " HP." << std::endl;
                break;
            case ItemType::DAMAGE:
                std::cout << "Attacking with " << itemProperties.id << " for " << itemProperties.value << " damage." << std::endl;
                break;
            case ItemType::NEUTRAL:
                std::cout << "Using " << itemProperties.id << " which is a neutral item." << std::endl;
                break;
        }
        it->second--;
    } else {
        std::cout << "Item not found in inventory." << std::endl;
    }
}

