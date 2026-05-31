//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_CHARACTER_H
#define ZOORK_CHARACTER_H

#include "GameObject.h"
#include "Item.h"
#include <vector>
#include <memory>

class Character : public GameObject {
public:
    Character(const std::string &, const std::string &);

    void addItem(std::shared_ptr<Item> item);
    void removeItem(const std::string& name);
    std::shared_ptr<Item> getItem(const std::string& name);
    std::shared_ptr<Item> retrieveItem(const std::string& name);
    const std::vector<std::shared_ptr<Item>>& getInventory() const;

protected:
    std::vector<std::shared_ptr<Item>> inventory;
//    std::vector<std::string> tags;
//    int health;
//    int attack;
//    int move;
//    int initiative;
};

#endif //ZOORK_CHARACTER_H
