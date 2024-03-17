#pragma once
#include <iostream>
#include "MovementManager/MovementManager.h"
#include "Tile.h"
#include "AssetManager.h"

struct MoveTile {
	sf::Vector2i m_newPos, m_oldPos;
	bool m_merge;

	MoveTile(sf::Vector2i new_pos, sf::Vector2i old_pos, bool merge = false): m_newPos{ new_pos }, m_oldPos{ old_pos }, m_merge{ merge } {}

	const sf::Vector2i& getNewPos() const { return m_newPos; }
	const sf::Vector2i& getOldPos() const { return m_oldPos; }
};

class TileMatrix {
private:
	// Private variables
	const int matrixwidth = 4, matrixheight = 4;

	const float* m_scale;
	const float* m_outerEdgeWidth;
	const float* m_innerEdgeWidth;
	const float* m_tileWidth;

	sf::Vector2f		m_playgroundPosition;
	Tile*				matrix[4][4];
	sf::Texture*		m_textures[12];
	
	float m_timeMoving = 0.f;
	const float m_timeMovingMax = 0.2f;
	
	float m_timeMerging = 0.f;
	const float m_timeMergingMax = 0.25f;


	std::vector <MoveTile*>	move_tile_instructions;
	std::vector <Tile*>	    merge_tile_instructions;
	
	int					m_addedScore = 0;
	unsigned			m_tiles = 0;

	bool m_isMoving{}, m_isMerging{}, m_isGameOver{};
	bool m_mergedTiles{};

	// Movement manager
	MovementManager* m_movementManager;
	MovementContainer* m_movementContainer;

	// Initialize textures
	void initTextures();
	int findID(int type_);
	sf::Vector2f calculateTilePos(int x, int y);

	int findFreeLeft(int x, int y);
	int findFreeRight(int x, int y);
	int findFreeUp(int x, int y);
	int findFreeDown(int x, int y);

	int mergeLeft(int x, int y);
	int mergeRight(int x, int y);
	int mergeUp(int x, int y);
	int mergeDown(int x, int y);

	bool willBeOccupied(int x, int y);

public:
	

	// Constructors / Destructors
	TileMatrix(float *scale_, float *outer_, float *inner_, float *tile_width_, sf::Vector2f playground_pos_);
	virtual ~TileMatrix();

	// Update functions
	void update(float dt);
	void updateMove(float dt);
	void updateMerge(float dt);
	void endMerge();

	// Move functions
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void addMoveInstructions(sf::Vector2i new_pos_, sf::Vector2i old_pos_, int distance_);

	// Tile manipulation functions
	void spawn(unsigned amount_ = 1);
	void addTile(sf::Vector2i pos_, int type_ = 2);
	void clearBoard();
	bool isGameOver();

	// Accessors
	const bool getIsMoving() const { return m_isMoving; }
	const bool getIsGameOver() const { return m_isGameOver; }
	const int getAddedScore() const { return m_addedScore; }

	void setAddedScore(int score) { m_addedScore = score; }

	// Rendering tiles
	void render(sf::RenderTarget& target);
};