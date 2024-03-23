#pragma once
#include <iostream>
#include "MovementManager/MovementManager.h"
#include "Tile.h"
#include "AssetManager.h"

struct MoveInstructions {
	sf::Vector2i m_newPos, m_oldPos;
	bool m_merge;

	MoveInstructions(sf::Vector2i new_pos, sf::Vector2i old_pos, bool merge = false): m_newPos{ new_pos }, m_oldPos{ old_pos }, m_merge{ merge } {}

	const sf::Vector2i& getNewPos() const { return m_newPos; }
	const sf::Vector2i& getOldPos() const { return m_oldPos; }
};

class TileMatrix {
private:
	// Private variables
	constexpr static int m_matrixWidth = 4, m_matrixHeight = 4, m_maxTiles = m_matrixWidth * m_matrixHeight, m_maxType = 4096;
	const float* m_scale{}, * m_outerEdgeWidth{}, * m_innerEdgeWidth{}, * m_tileWidth{};

	Tile* m_matrix[4][4]{ {} };
	sf::Texture* m_textures[12]{};
	sf::Vector2f m_playgroundPosition{};

	const float m_timeSpawningMax = 0.2f;

	float m_timeMoving = 0.f;
	const float m_timeMovingMax = 0.2f;
	
	float m_timeMerging = 0.f;
	const float m_timeMergingMax = 0.2f;

	std::vector <MoveInstructions*>	m_moveInstructions;
	std::vector <Tile*> m_tilesToMerge;
	
	int m_addedScore{};
	unsigned m_tiles{};

	bool m_isGameOver{}, m_isWin{}, m_mergedTiles{};

	// Movement manager
	MovementManager* m_movementManager;
	MovementContainer* m_movementContainer;

	// Initialize textures
	void initTextures();
	int findID(int type) const;
	sf::Vector2f calculateTilePos(const sf::Vector2i& pos) const;
	void checkWin(const Tile& tile);

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
	TileMatrix(const float *scale, const float *outer, const float *inner, const float *tileWidth, const sf::Vector2f& playgroundPos);
	virtual ~TileMatrix();

	// Update functions
	void update(float dt);
	void updateMove(float dt);
	void updateMerge(float dt);

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

	// Rendering tiles
	void render(sf::RenderTarget& target);
};