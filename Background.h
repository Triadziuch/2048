#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>

class Background {
private:
	// Background variables



public:
	Background();
	virtual ~Background();

	void render (sf::RenderTarget& target);
};