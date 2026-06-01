#include "WorldBuilder.h"
#include "Passage.h"
#include "Item.h"
#include "Door.h"

std::vector<std::shared_ptr<Room>> WorldBuilder::rooms;

std::shared_ptr<Room> WorldBuilder::buildWorld() {
    rooms.clear();

    std::shared_ptr<Room> start = std::make_shared<Room>("main-gate",
                           "You are standing before the magnificent sandstone Sun Gate of an ancient Rajasthani palace. The desert heat surrounds you.\n");
    rooms.push_back(start);

    std::shared_ptr<Room> courtyard_south = std::make_shared<Room>("courtyard-south",
                                    "You are in the southern end of the massive Jaleb Chowk courtyard. Giant elephant mounting platforms stand empty.\n");
    rooms.push_back(courtyard_south);

    std::shared_ptr<Room> courtyard_north = std::make_shared<Room>("courtyard-north",
                                  "You are in the northern end of the courtyard. The old guards' armory is locked tight.\n");
    rooms.push_back(courtyard_north);

    std::shared_ptr<Room> palace_entrance = std::make_shared<Room>("lion-gate",
                                  "You are at the Lion Gate, the ornate entrance to the inner palace corridors. A path leads east to the royal gardens. One of the heavy brass-studded wooden doors is slightly ajar.\n");
    rooms.push_back(palace_entrance);

    std::shared_ptr<Room> garden_path = std::make_shared<Room>("garden-path",
                                  "A stone pathway winds through a beautifully symmetrical Mughal-style garden. The scent of jasmine fills the air, heading east towards water.\n");
    rooms.push_back(garden_path);

    std::shared_ptr<Room> lotus_pool = std::make_shared<Room>("lotus-pool",
                                  "You are at a serene marble courtyard framing a tranquil pool filled with blooming pink lotus flowers. A massive, ancient banyan tree grows nearby.\n");
    rooms.push_back(lotus_pool);

    std::shared_ptr<Room> up_banyan_tree = std::make_shared<Room>("up-banyan-tree",
                                  "You are nestled high among the thick, hanging aerial roots of the banyan tree. You have a sprawling view of the Aravalli hills.\n");
    rooms.push_back(up_banyan_tree);

    std::shared_ptr<Room> diwan_i_aam = std::make_shared<Room>("diwan-i-aam",
                                  "You are inside the Diwan-i-Aam, the Hall of Public Audience. Its massive red sandstone columns line the pavilion. The private royal chambers lie to the west.\n");
    rooms.push_back(diwan_i_aam);

    std::shared_ptr<Room> sheesh_mahal = std::make_shared<Room>("sheesh-mahal",
                                  "You are in the breathtaking Sheesh Mahal, the Palace of Mirrors. The walls and ceiling glitter with thousands of tiny glass mosaic pieces. A narrow spiral staircase leads up.\n");
    rooms.push_back(sheesh_mahal);

    std::shared_ptr<Room> palace_roof = std::make_shared<Room>("palace-roof",
                                  "You are on the sun-baked terrace of the palace. The sweeping view overlooks the desert valley and a shimmering lake below.\n");
    rooms.push_back(palace_roof);

    // Connect the paths to/around the palace
    Passage::createBasicPassage(start.get(), courtyard_south.get(), "south", true);
    Passage::createBasicPassage(start.get(), courtyard_north.get(), "north", true);
    Passage::createBasicPassage(courtyard_south.get(), palace_entrance.get(), "east", true);
    Passage::createBasicPassage(courtyard_north.get(), palace_entrance.get(), "east", true);

    // Garden connections
    Passage::createBasicPassage(palace_entrance.get(), garden_path.get(), "east", true);
    Passage::createBasicPassage(garden_path.get(), lotus_pool.get(), "east", true);
    Passage::createBasicPassage(lotus_pool.get(), up_banyan_tree.get(), "up", true);

    // Inside the palace (Entering via the ajar door using "in")
    Passage::createBasicPassage(palace_entrance.get(), diwan_i_aam.get(), "in", true);
    
    // locked door from Diwan-i-Aam to Sheesh Mahal
    auto door_to_sheesh = std::make_shared<Door>("door-to-sheesh", "A beautiful ivory-inlaid door, firmly locked.", diwan_i_aam.get(), sheesh_mahal.get(), "bronze-key");
    diwan_i_aam->addPassage("west", door_to_sheesh);
    auto door_from_sheesh = std::make_shared<Door>("door-from-sheesh", "A beautiful ivory-inlaid door, firmly locked.", sheesh_mahal.get(), diwan_i_aam.get(), "bronze-key");
    sheesh_mahal->addPassage("east", door_from_sheesh);

    Passage::createBasicPassage(sheesh_mahal.get(), palace_roof.get(), "up", true);

    // CREATE AND PLACE PUZZLE ITEMS
    auto bamboo_pole = std::make_shared<Item>("bamboo-pole", "A long, sturdy bamboo pole, perhaps once used by gardeners.");
    garden_path->addItem(bamboo_pole);

    auto brass_bowl = std::make_shared<Item>("brass-bowl", "An intricately carved antique brass bowl.");
    sheesh_mahal->addItem(brass_bowl);

    // For now, the key is just sitting up in the tree 
    auto bronze_key = std::make_shared<Item>("bronze-key", "A heavy, ornate bronze key. It looks like it fits the lock on the Sun Gate.");
    up_banyan_tree->addItem(bronze_key);

    return start;
}