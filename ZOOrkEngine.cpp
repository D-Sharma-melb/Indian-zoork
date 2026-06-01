//
// Created by Richard Skarbez on 5/7/23.
//

#include "ZOOrkEngine.h"

#include <algorithm>
#include <utility>
#include <memory>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        if (words.empty()) {
            continue;
        }
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go") {
            handleGoCommand(arguments);
        } else if ((command == "look") || (command == "inspect")) {
            handleLookCommand(arguments);
        } else if ((command == "take") || (command == "get")) {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        } else if (command == "use") {
            handleUseCommand(arguments);
        } else if (command == "quit") {
            handleQuitCommand(arguments);
        } else {
            std::cout << "I don't understand that command.\n";
        }
    }
}

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Go where?\n";
        return;
    }

    std::string direction;
    if (arguments[0] == "n" || arguments[0] == "north") {
        direction = "north";
    } else if (arguments[0] == "s" || arguments[0] == "south") {
        direction = "south";
    } else if (arguments[0] == "e" || arguments[0] == "east") {
        direction = "east";
    } else if (arguments[0] == "w" || arguments[0] == "west") {
        direction = "west";
    } else if (arguments[0] == "u" || arguments[0] == "up") {
        direction = "up";
    } else if (arguments[0] == "d" || arguments[0] == "down") {
        direction = "down";
    } else if (arguments[0] == "i" || arguments[0] == "in") {
        direction = "in";
    } else if (arguments[0] == "o" || arguments[0] == "out") {
        direction = "out";
    }
     else {
        direction = arguments[0];
    }

    Room* currentRoom = player->getCurrentRoom();
    auto passage = currentRoom->getPassage(direction);
    
    if (passage->canEnter(player)) {
        player->setCurrentRoom(passage->getTo());
        passage->enter();
    }
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << player->getCurrentRoom()->getDescription() << "\n";
        
        auto roomItems = player->getCurrentRoom()->getItems();
        if (!roomItems.empty()) {
            std::cout << "You see the following items here:\n";
            for (const auto& item : roomItems) {
                std::cout << "  - " << item->getName() << "\n";
            }
        }

        auto inventory = player->getInventory();
        if (!inventory.empty()) {
            std::cout << "You are carrying:\n";
            for (const auto& item : inventory) {
                std::cout << "  - " << item->getName() << "\n";
            }
        }
    } else {
        std::string target = arguments[0];
        
        // Check if the item is in the room
        auto roomItem = player->getCurrentRoom()->getItem(target);
        if (roomItem) {
            std::cout << roomItem->getDescription() << "\n";
            return;
        }

        // Check if the item is in the player's inventory
        auto inventoryItem = player->getItem(target);
        if (inventoryItem) {
            std::cout << inventoryItem->getDescription() << "\n";
            return;
        }

        std::cout << "You don't see a " << target << " here.\n";
    }
}

void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Take what?\n";
        return;
    }

    std::string target = arguments[0];
    auto item = player->getCurrentRoom()->retrieveItem(target);

    if (item) {
        player->addItem(item);
        std::cout << "You took the " << target << ".\n";
    } else {
        std::cout << "You don't see a " << target << " here.\n";
    }
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Drop what?\n";
        return;
    }

    std::string target = arguments[0];
    auto item = player->retrieveItem(target);

    if (item) {
        player->getCurrentRoom()->addItem(item);
        std::cout << "You dropped the " << target << ".\n";
    } else {
        std::cout << "You do not have a " << target << ".\n";
    }
}

void ZOOrkEngine::handleUseCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Use what?\n";
        return;
    }

    std::string target = arguments[0];
    auto item = player->getItem(target);

    if (!item) {
        std::cout << "You don't have a " << target << " to use right now.\n";
        return;
    }

    if (target == "bamboo-pole") {
        if (player->getCurrentRoom()->getName() == "lotus-pool") {
            auto upPassage = player->getCurrentRoom()->getPassage("up");
            if (upPassage) {
                auto treeRoom = upPassage->getTo();
                if (treeRoom) {
                    auto keyItem = treeRoom->retrieveItem("bronze-key");
                    if (keyItem) {
                        player->getCurrentRoom()->addItem(keyItem);
                        std::cout << "You use the bamboo pole to swat at the branches above. A heavy bronze key is knocked loose and falls to the ground!\n";
                        return;
                    } else {
                        std::cout << "You swat at the branches above, but nothing falls down.\n";
                        return;
                    }
                }
            }
        }
        std::cout << "You wave the bamboo pole around. Nothing much happens here.\n";
    } else {
        // Fallback to the item's own use command if it has one
        item->use();
    }
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}
