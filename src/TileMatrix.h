#include "Tile.h"

struct MoveTile {
	int distance;
	sf::Vector2i new_pos, old_pos;
	float pixel_distance, move_speed;
	bool merge;

	MoveTile(int distance_, float pixel_distance_, float move_speed_, sf::Vector2i new_pos_, sf::Vector2i old_pos_, bool merge_ = false) {
		this->distance = distance_;
		this->pixel_distance = pixel_distance_;
		this->move_speed = move_speed_;
		this->new_pos = new_pos_;
		this->old_pos = old_pos_;
		this->merge = merge_;
	}
};

class TileMatrix {
private:
	// Variables
	const int			max_type		 = 4096;
	const int			matrix_width	 = 4;
	const int			matrix_height	 = 4;
	float*				scale;
	float*				outer_edge;
	float*				inner_edge;
	float*				tile_width;
	sf::Vector2f		playground_pos;
	Tile*				matrix[4][4];
	vector <Tile*>		spawning_tiles;
	sf::Texture			textures[12];
	int					frames_to_move = 10;
	int					current_moved_frames = 0;
	vector <MoveTile*>	move_tile_instructions;
	bool				do_move;
	int					added_score = 0;
	unsigned			tiles = 0;

	// Initialize textures
	void initTextures();
	int findID(int type_);
	sf::Vector2f calculateTilePos(int x_, int y_);

	int findFreeLeft(int x_, int y_);
	int findFreeRight(int x_, int y_);
	int findFreeUp(int x_, int y_);
	int findFreeDown(int x_, int y_);

	int mergeLeft(int x_, int y_);
	int mergeRight(int x_, int y_);
	int mergeUp(int x_, int y_);
	int mergeDown(int x_, int y_);

	bool willBeOccupied(int x_, int y_);

	

public:
	bool				GAMEOVER_FLAG	= false;
	bool				MERGE_FLAG		= false;
	bool				MOVE_FLAG		= false;

	// Constructors / Destructors
	TileMatrix(float *scale_, float *outer_, float *inner_, float *tile_width_, sf::Vector2f playground_pos_);
	virtual ~TileMatrix();

	// Update functions
	void update(float dt);
	void updateMove();

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