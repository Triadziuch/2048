#pragma once
#include <iostream>
#include "src/MovementManager/MovementManager.h"
#include "TileModel.h"
#include "src/AssetManager.h"
#include "src/event/EventObserver.h"
#include "src/model/BaseModel.h"

struct MoveInstructions {
	sf::Vector2i m_newPos, m_oldPos;
	bool m_merge;

	MoveInstructions(sf::Vector2i new_pos, sf::Vector2i old_pos, bool merge = false) : m_newPos{ new_pos }, m_oldPos{ old_pos }, m_merge{ merge } {}

	const sf::Vector2i& getNewPos() const { return m_newPos; }
	const sf::Vector2i& getOldPos() const { return m_oldPos; }
};

class TileMatrixModel : public BaseModel {
private:
	// Private variables
	constexpr static int m_matrixWidth = 4, m_matrixHeight = 4, m_maxTiles = m_matrixWidth * m_matrixHeight, m_maxType = 16384;

	TileModel* m_matrix[4][4]{ {} };

	std::vector <MoveInstructions*>	m_moveInstructions;
	std::vector <TileModel*> m_tilesToMerge;

	int m_addedScore{};
	unsigned m_tiles{};

	bool m_isGameOver{}, m_isWin{}, m_mergedTiles{};

	// Initialize textures
	int findID(int type) const;
	void checkWin(const TileModel& tile);

	int findFreeLeft(const sf::Vector2i& pos);
	int findFreeRight(const sf::Vector2i& pos);
	int findFreeUp(const sf::Vector2i& pos);
	int findFreeDown(const sf::Vector2i& pos);

	int mergeLeft(const sf::Vector2i& pos);
	int mergeRight(const sf::Vector2i& pos);
	int mergeUp(const sf::Vector2i& pos);
	int mergeDown(const sf::Vector2i& pos);

	bool willBeOccupied(const sf::Vector2i& pos) const;

	void endMove();
	void endMerge();

public:
	enum Tstate { IDLE, MOVING, MERGING };
	Tstate m_state{ IDLE };

	// Constructors / Destructors
	TileMatrixModel();
	virtual ~TileMatrixModel();

	// Update functions
	void update(float dt);

	// Move functions
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void addMoveInstructions(const sf::Vector2i& newPos, const sf::Vector2i& oldPos);

	// Tile manipulation functions
	void spawn(const int amount = 1);
	void addTile(const sf::Vector2i& pos, const int type = 2);
	void clearBoard();
	bool isGameOver();

	// Accessors / Mutators
	bool getIsMoving() const;

	bool getIsGameOver() const;
	int getAddedScore() const;

	void setAddedScore(const int score);
};