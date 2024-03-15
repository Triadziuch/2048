#include "Playground.h"
#include "StandardCursor.h"
#include "AssetManager.h"
#include "math.h"

class Game 
{
private:
	// Window variables
	const string				WINDOW_TITLE		= "2048";
	const unsigned int			WINDOW_WIDTH		= 1280;
	const unsigned int			WINDOW_HEIGHT		= 720;
	const unsigned int			FRAMERATE			= 60;
	const bool					VERTICAL_SYNC		= true;
	sf::StandardCursor::TYPE	cursor_type = sf::StandardCursor::NORMAL;
	sf::Vector2i				mouse_pos_window;
	sf::Vector2f				mouse_pos_view;
	sf::RenderWindow*			window;

	// Other variables
	bool				isEnd			= false;
	bool				isGameOver		= false;
	Playground*			playground;
	AssetManager manager;

	// Clock variables
	sf::Clock dt_clock;
	float dt;

	// Initialization functions 
	void initWindow();
	void initVariables();
	void initAssets();

public:
	// Constructors / Destructors
	Game();
	virtual ~Game();

	// Run functions
	void run();
	
	// Update functions
	void update();
	void updateMousePositions();
	void updatePollEvents();
	void updateGameOver();

	// Rendering the game
	void render();
};