#pragma once

#include <string>
#include "../view/GameViewGraphic.h"
#include "../view/GameViewCMD.h"
#include "../view/ViewHandler.h"
#include "IBaseController.h"
#include "../IEventManager.h"

class GameController : public IBaseController {
private:
	// MVC Model and View variables
	std::shared_ptr<ModelHandler> _modelHandler;
	std::shared_ptr<ViewHandler> _viewHandler;
	std::shared_ptr<GameModel> _gameModel;
	std::shared_ptr<BaseView> _gameView;
	IEventManager* _eventManager;

	// Clock variables
	sf::Clock dt_clock;
	float dt;

	// Is Variables
	bool isGraphic = true;
	bool isMoving = false;
	bool isSpawning = false;
	bool isEnd = false;
	bool isGameOver = false;

	// Initialization functions 
	void initVariables();

public:
	// Constructors / Destructors
	GameController();
	~GameController();

	// Model and View handling
	void setModelHandler(std::shared_ptr<ModelHandler> modelHandler) override;
	void setViewHandler(std::shared_ptr<ViewHandler> viewHandler) override;
	void switchView();

	// Public funcitons
	const std::string run() override;
	void close();
	const std::string gameLoop();

	// Update functions
	void update();
	
	// Render function
	void render();
};