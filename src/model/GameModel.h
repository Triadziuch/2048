#pragma once

#include <string>
#include <functional>
#include <list>
#include "BaseModel.h"
#include "../TileMatrixModel.h"

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
    void endMove();
    void endMerge();

    TileModel* const (&getMatrix() const)[4][4];
    const std::vector<MoveInstructions*>& getMoveInstructions() const;
    const std::vector<SpawnInstruction*>& getSpawnInstructions() const;
    const std::vector<MergeInstruction*>& getMergeInstructions() const;
    void clearBoard();
};