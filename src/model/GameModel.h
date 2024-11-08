#pragma once
#include <string>
#include <functional>
#include <list>
#include "BaseModel.h"
#include "../TileMatrixModel.h"

class LeaderboardModel;
enum class LeaderboardMode;

class GameModel : public BaseModel {
private:
    TileMatrixModel* m_tileMatrix;
    std::shared_ptr<LeaderboardModel> m_leaderboardModel;

    int m_score{}, m_bestScore{ 212 };

public:
    // Constructors / Destructors
    GameModel(std::shared_ptr<LeaderboardModel> leaderboardModel);
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
    const int& getScore() const;
    const int& getBestScore() const;

    void setLeaderboardMode(LeaderboardMode mode);
};