#include "RoomDefaultEnterCommand.h"
#include "WorldBuilder.h"
#include "ZOOrkEngine.h"
#include <memory>

int main() {
    std::shared_ptr<Room> start = WorldBuilder::buildWorld();

    ZOOrkEngine zoork(start);

    zoork.run();

    return 0;
}
