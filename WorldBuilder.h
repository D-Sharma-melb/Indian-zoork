#ifndef ZOORK_WORLDBUILDER_H
#define ZOORK_WORLDBUILDER_H

#include "Room.h"
#include <memory>
#include <vector>

class WorldBuilder {
public:
    static std::shared_ptr<Room> buildWorld();
private:
    static std::vector<std::shared_ptr<Room>> rooms;
};

#endif //ZOORK_WORLDBUILDER_H