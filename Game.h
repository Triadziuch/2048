#include "Playground.h"

class Game 
{
private:
	// Window variables
	const string			WINDOW_TITLE		= "2048";
	const unsigned int		WINDOW_WIDTH		= 1280;
	const unsigned int		WINDOW_HEIGHT		= 720;
	const unsigned int		FRAMERATE			= 60;
	const bool				VERTICAL_SYNC		= true;
	sf::RenderWindow*		window;

	// Other variables
	bool				isEnd			= false;
	Playground*			playground;

	// Clock variables
	sf::Clock dt_clock;
	float dt;

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