//
// Created by Richard Skarbez on 5/7/23.
//

#include "Character.h"

Character::Character(const std::string &n, const std::string &d) : GameObject(n, d) {}

void Character::addItem(std::shared_ptr<Item> item) {
    inventory.push_back(std::move(item));
}

void Character::removeItem(const std::string& name) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == name) {
            inventory.erase(it);
            return;
        }
    }
}

std::shared_ptr<Item> Character::getItem(const std::string& name) {
    for (const auto& item : inventory) {
        if (item->getName() == name) {
            return item;
        }
    }
    return nullptr;
}

std::shared_ptr<Item> Character::retrieveItem(const std::string& name) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == name) {
            auto item = *it;
            inventory.erase(it);
            return item;
        }
    }
    return nullptr;
}

const std::vector<std::shared_ptr<Item>>& Character::getInventory() const {
    return inventory;
}
