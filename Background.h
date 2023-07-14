#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>

using namespace std;

class Background {
private:
	// Background variables
	sf::Color		color_background				= sf::Color(250, 248, 239);
	sf::Texture		texture_playground;
	sf::Sprite		sprite_playground;
	const float		playground_top_bottom_space		= 100.f;

public:
	Background(sf::Vector2f window_size_);
	virtual ~Background();

	void render (sf::RenderTarget& target);
};