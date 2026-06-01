#include "Door.h"
#include "Player.h"
#include <iostream>

Door::Door(const std::string &n, const std::string &d, Room* from, Room* to, const std::string &reqItem)
    : Passage(n, d, from, to), requiredItem(reqItem) {}

Door::Door(const std::string &n, const std::string &d, std::shared_ptr<Command> c, Room* from, Room* to, const std::string &reqItem)
    : Passage(n, d, std::move(c), from, to), requiredItem(reqItem) {}

bool Door::canEnter(Player* player) const {
    if (player->getItem(requiredItem)) {
        return true;
    } else {
        std::cout << "The " << getName() << " is locked! You need a " << requiredItem << " to open it.\n";
        return false;
    }
}

const std::string& Door::getRequiredItem() const {
    return requiredItem;
}
