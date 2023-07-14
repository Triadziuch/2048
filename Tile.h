#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>
#include <utility>

using namespace std;

struct Tile {
private:
	sf::Sprite		sprite_tile;
	int				type			= 2;

	void center_origin();
public:
	// Constructors / Destructors
	Tile() {}
	Tile(int type_, sf::Texture* texture_tile_, float *scale_);
	virtual ~Tile() {};

	// Mutators
	void setScale(float scale_)				{ this->sprite_tile.setScale(scale_, scale_); }
	void setTexture(sf::Texture* texture_)  { this->sprite_tile.setTexture(*texture_); this->center_origin(); }
	void setPosition(sf::Vector2f pos_)		{ this->sprite_tile.setPosition(pos_); }
	void setType(int type_)					{ this->type = type_; }

	// Accessors
	const int& getType() const { return this->type; }

	// Rendering tile
	void render(sf::RenderTarget& target);
};