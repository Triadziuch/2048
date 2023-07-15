#include "Tile.h"

struct MoveTile {
	int distance;
	sf::Vector2i new_pos, old_pos;
	float pixel_distance, move_speed;

	MoveTile(int distance_, float pixel_distance_, float move_speed_, sf::Vector2i new_pos_, sf::Vector2i old_pos_) {
		this->distance = distance_;
		this->pixel_distance = pixel_distance_;
		this->move_speed = move_speed_;
		this->new_pos = new_pos_;
		this->old_pos = old_pos_;
	}
};

class TileMatrix {
private:
	// Variables
	const int			max_type		 = 4996;
	const int			matrix_width	 = 4;
	const int			matrix_height	 = 4;
	float*				scale;
	float*				outer_edge;
	float*				inner_edge;
	float*				tile_width;
	sf::Vector2f		playground_pos;
	Tile*				matrix[4][4];
	sf::Texture			textures[4];
	int					frames_to_move = 10;
	int					current_moved_frames = 0;
	vector <MoveTile*>	move_tile_instructions;
	bool				do_move;

	// Initialize textures
	void initTextures();
	int findID(int type_);
	sf::Vector2f calculateTilePos(int x_, int y_);

	int findFreeLeft(int x_, int y_);
	int findFreeRight(int x_, int y_);
	int findFreeUp(int x_, int y_);
	int findFreeDown(int x_, int y_);
	bool willBeOccupied(int x_, int y_);

public:
	// Constructors / Destructors
	TileMatrix(float *scale_, float *outer_, float *inner_, float *tile_width_, sf::Vector2f playground_pos_);
	virtual ~TileMatrix();

	void update(float dt);
	void updateMove();

	// Functions
	void addTile(int x_, int y_, int type_ = 2);
	void addMoveInstructions(sf::Vector2i new_pos_, sf::Vector2i old_pos_, int distance_);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	// Accessors
	bool& getIsMoving() { return this->do_move; }

	// Rendering tiles
	void render(sf::RenderTarget& target);
};