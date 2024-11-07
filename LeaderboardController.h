#pragma once

#include "src/controller/IBaseController.h"
#include "LeaderboardViewCMD.h"
#include "LeaderboardViewGraphic.h"
#include "src/view/ViewHandler.h"
#include "IEventManager.h"

class LeaderboardController : public IBaseController {
private:
	// MVC Model and View variables
	std::shared_ptr<ModelHandler> _modelHandler;
	std::shared_ptr<ViewHandler> _viewHandler;
	std::shared_ptr<LeaderboardModel> _leaderboardModel;
	std::shared_ptr<BaseLeaderboardView> _leaderboardView;
	IEventManager* _eventManager;

	// Game state Variables
	bool isEnd = false;
	bool isGraphic = false;
	ExitCode exitCode = ExitCode::EXIT;

	// Initialization functions 
	void initVariables();
	
public:
	LeaderboardController();
	~LeaderboardController();

	// Model and View handling
	void setModelHandler(std::shared_ptr<ModelHandler> modelHandler) override;
	void setViewHandler(std::shared_ptr<ViewHandler> viewHandler) override;
	void switchView();

	// Public funcitons
	const ExitCode run() override;
	void close();
	const ExitCode gameLoop();
	void enterName();

	// Update functions
	void update();

	// Render function
	void render();
};