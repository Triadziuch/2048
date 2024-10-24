#pragma once

#include <string>
#include <functional>
#include <list>
#include "BaseModel.h"
#include "../TileMatrixModel.h"

class GameModel : public BaseModel {
private:
    TileMatrixModel* m_tileMatrix{};
    int m_score{};

public:
    // Constructors / Destructors
    GameModel();
    ~GameModel();

    // Public functions
    void updateScore();

    void move(const sf::Keyboard::Key key);
    void endMove();
    void endMerge();
    void clearBoard();

    // Accessors / Mutators
    TileBase* const (&getMatrix() const)[4][4];
    const std::vector<MoveInstruction*>& getMoveInstructions() const;
    const std::vector<SpawnInstruction*>& getSpawnInstructions() const;
    const std::vector<MergeInstruction*>& getMergeInstructions() const;
};