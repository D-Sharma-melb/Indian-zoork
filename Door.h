#ifndef ZOORK_DOOR_H
#define ZOORK_DOOR_H

#include "Passage.h"
#include <string>

class Door : public Passage {
public:
    Door(const std::string &n, const std::string &d, Room* from, Room* to, const std::string &reqItem);

    Door(const std::string &n, const std::string &d, std::shared_ptr<Command> c, Room* from, Room* to, const std::string &reqItem);

    bool canEnter(Player* player) const override;

    const std::string& getRequiredItem() const;

private:
    std::string requiredItem;
};

#endif //ZOORK_DOOR_H
