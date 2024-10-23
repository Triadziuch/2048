#pragma once

#include <string>
#include "../model/GameModel.h"
#include "../view/GameView.h"
#include "../view/GameViewTwo.h"
#include "../view/ViewHandler.h"
#include "IBaseController.h"
#include "../StandardCursor.h"

class GameController : public IBaseController {
private:
	// MVC Model and View variables
	std::shared_ptr<ModelHandler> _modelHandler;
	std::shared_ptr<ViewHandler> _viewHandler;
	std::shared_ptr<GameModel> _gameModel;
	std::shared_ptr<GameView> _gameView;

	// Window variables
	const std::string WINDOW_TITLE = "2048";
	const unsigned int FRAMERATE = 60;
	const unsigned int WINDOW_WIDTH = 1280;
	const unsigned int WINDOW_HEIGHT = 720;
	const bool VERTICAL_SYNC = true;
	sf::StandardCursor::TYPE cursor_type = sf::StandardCursor::NORMAL;
	sf::Vector2i mouse_pos_window;
	sf::Vector2f mouse_pos_view;
	sf::RenderWindow* window;

	// Clock variables
	sf::Clock dt_clock;
	float dt;

	// Is Variables
	bool isMoving = false;
	bool isSpawning = false;
	bool isEnd = false;
	bool isGameOver = false;

	// Initialization functions 
	void initWindow();
	void initVariables();

public:

	// Constructors / Destructors
	GameController();
	~GameController();

	// Model and View handling
	void setModelHandler(std::shared_ptr<ModelHandler> modelHandler) override;
	void setViewHandler(std::shared_ptr<ViewHandler> viewHandler) override;

	// Public funcitons
	const std::string run() override;
	const std::string gameLoop();

	// Update functions
	void update();
	void updatePollEvents();
	
	// Render function
	void render();
};