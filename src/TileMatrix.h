#include "Tile.h"
#include "MovementManager/MovementManager.h"
#include "AssetManager.h"

struct MoveTile {
	sf::Vector2i m_newPos, m_oldPos;
	bool m_merge;

	MoveTile(sf::Vector2i new_pos, sf::Vector2i old_pos, bool merge = false): m_newPos{ new_pos }, m_oldPos{ old_pos }, m_merge{ merge } {}

	const sf::Vector2i& getNewPos() const { return this->m_newPos; }
	const sf::Vector2i& getOldPos() const { return this->m_oldPos; }
};

class TileMatrix {
private:
	// Variables
	const int			maxtype		 = 4096;
	const int			matrixwidth	 = 4;
	const int			matrixheight	 = 4;
	float*				scale;
	float*				outer_edge;
	float*				inner_edge;
	float*				tile_width;
	sf::Vector2f		playground_pos;
	Tile*				matrix[4][4];
	vector <Tile*>		spawning_tiles;
	sf::Texture*		textures[12];
	float				time_to_move = 0.2f;
	float				current_move_time = 0.f;
	float				time_to_merge = 0.25f;
	float				current_merge_time = 0.f;
	vector <MoveTile*>	move_tile_instructions;
	vector <Tile*>	    merge_tile_instructions;
	bool				do_move, m_isMerging{};
	int					added_score = 0;
	unsigned			tiles = 0;

	ScalingRoutine* scaling_routine;
	ScalingRoutine* merge_routine;

	// Movement manager
	MovementContainer* movement_container;
	MovementManager* movement_manager;

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
	bool				GAMEOVER_FLAG	= false;
	bool				MERGE_FLAG		= false;
	bool				MOVE_FLAG		= false;

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
	bool& getIsMoving()				{ return this->do_move; }
	int getAddedScore()				{ return this->added_score; }

	// Mutators
	void setAddedScore(int value_)  { this->added_score = value_; }

	// Rendering tiles
	void render(sf::RenderTarget& target);
};