//
// Created by Richard Skarbez on 5/7/23.
//

#include "NullPassage.h"
#include "Room.h"

#include <utility>
#include <memory>


Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

void Room::addItem(std::shared_ptr<Item> item) {
    items.push_back(std::move(item));
}

void Room::removeItem(const std::string& name) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getName() == name) {
            items.erase(it);
            return;
        }
    }
}

std::shared_ptr<Item> Room::getItem(const std::string& name) {
    for (const auto& item : items) {
        if (item->getName() == name) {
            return item;
        }
    }
    return nullptr;
}

std::shared_ptr<Item> Room::retrieveItem(const std::string& name) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getName() == name) {
            auto item = *it;
            items.erase(it);
            return item;
        }
    }
    return nullptr;
}

const std::vector<std::shared_ptr<Item>>& Room::getItems() const {
    return items;
}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction) {
    if (passageMap.count(direction) > 0) {
        passageMap.erase(direction);
    }
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    if (passageMap.count(direction) > 0) {
        return passageMap[direction];
    } else {
        std::cout << "It is impossible to go " << direction << "!\n";
        return std::make_shared<NullPassage>(this);
    }
}