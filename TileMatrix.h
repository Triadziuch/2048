#include "Tile.h"

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

	// Initialize textures
	void initTextures();
	int findID(int type_);
	sf::Vector2f calculateTilePos(int x_, int y_);
	int findFreeLeft(int x_, int y_);
	int findFreeRight(int x_, int y_);
	int findFreeUp(int x_, int y_);
	int findFreeDown(int x_, int y_);
public:
	// Constructors / Destructors
	TileMatrix(float *scale_, float *outer_, float *inner_, float *tile_width_, sf::Vector2f playground_pos_);
	virtual ~TileMatrix();

	// Functions
	void addTile(int x_, int y_, int type_ = 2);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	// Rendering tiles
	void render(sf::RenderTarget& target);
};