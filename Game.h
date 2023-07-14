#include "Background.h"

class Game 
{
private:
	// Window variables
	sf::RenderWindow* window;

	// is variables
	bool isEnd;

	// Clock variables
	sf::Clock dt_clock;
	float dt;

	// Background color
	sf::Color color_background;

	// Initialization functions 
	void initWindow();
	void initVariables();

public:
	// Constructors / Destructors
	Game();
	virtual ~Game();

	// Run functions
	void run();
	
	// Update functions
	void update();
	void updatePollEvents();

	// Rendering the game
	void render();
};