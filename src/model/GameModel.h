#pragma once

#include <string>
#include <functional>
#include <list>
#include "BaseModel.h"
#include "../Playground.h"

class GameModel : public BaseModel {
private:
    // Background variables
    bool m_isGameOver{ false };

    int m_score{};
    TileMatrixModel* m_tileMatrix{};

public:
    GameModel();

    void update(float dt);
    void updateScore();

    void move(const sf::Keyboard::Key key);
    void clearBoard();
};