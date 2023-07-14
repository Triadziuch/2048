#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>

using namespace std;

class Playground {
private:
	// Background variables
	sf::Color		color_background				= sf::Color(250, 248, 239);
	sf::Texture		texture_playground;
	sf::Sprite		sprite_playground;
	const float		playground_top_bottom_space		= 100.f;
	float			outer_edge_width				= 37.f;
	float			inner_edge_width				= 36.f;
	float			tile_width						= 215.f;

public:
	Playground(sf::Vector2f window_size_);
	virtual ~Playground();

	// Accessors
	const float& getOuterEdgeWidth() const { return this->outer_edge_width; }
	const float& getInnerEdgeWidth() const { return this->inner_edge_width; }
	const float& getTileWidth()		 const { return this->tile_width; }

	void render (sf::RenderTarget& target);
};