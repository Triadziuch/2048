#include "Tile.h"

struct MoveTile {
	bool move = false;
	int distance;
	float pixel_distance;
	sf::Vector2i new_pos;
	float move_speed;
};

class TileMatrix {
private:
	// Variables
	const int		max_type		 = 16;
	const int		matrix_width	 = 4;
	const int		matrix_height	 = 4;
	float*			scale;
	float*			outer_edge;
	float*			inner_edge;
	float*			tile_width;
	sf::Vector2f	playground_pos;
	Tile*			matrix[4][4];
	sf::Texture		textures[4];
	int				frames_to_move = 15;
	int				current_moved_frames = 0;
	MoveTile		moveTile[4][4];
	bool			do_move;

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
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	// Accessors
	bool& getIsMoving() { return this->do_move; }

	// Rendering tiles
	void render(sf::RenderTarget& target);
};