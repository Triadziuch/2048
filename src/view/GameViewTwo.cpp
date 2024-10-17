#include <iostream>
#include "GameViewTwo.h"

GameViewTwo::GameViewTwo() {
    this->registerObserver("update_game", [&] () {
        std::cout << "[GameViewTwo] Self Observer \"update_game\" triggered." << std::endl;
        return (true);
    });
}

const std::string & GameViewTwo::getViewPath() const {
    return ("");
}

void GameViewTwo::addGame(GameModel &gameModel) {
    std::cout << "[GameViewTwo] Added new game to the view." << std::endl;
    std::cout << "[GameViewTwo] id: " << gameModel.getId() << std::endl;
    std::cout << "[GameViewTwo] name: " << gameModel.getName() << std::endl;
    std::cout << std::endl;

    gameModel.connect([&]() {
        std::cout << "[GameViewTwo] Game Model Updated, view is applying changes." << std::endl;
        this->notify();
        return (false);
    });
}