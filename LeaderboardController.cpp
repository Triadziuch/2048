#include "LeaderboardController.h"

void LeaderboardController::initVariables()
{
	srand(static_cast<unsigned>(time(nullptr)));
	this->isGraphic = false;
	this->_eventManager = new CMDEventManager();
}

LeaderboardController::LeaderboardController()
{
	initVariables();
}

LeaderboardController::~LeaderboardController() {}

void LeaderboardController::setModelHandler(std::shared_ptr<ModelHandler> modelHandler)
{
	printDebug("Game Model has been set.");

	this->_modelHandler = modelHandler;
	this->_leaderboardModel = this->_modelHandler->getModel<LeaderboardModel>("leaderboard");
	this->_leaderboardModel->connect([&]() {
		printDebug("[LeaderboardController] LeaderboardModel has been updated.");
		return false;
		});
}

void LeaderboardController::setViewHandler(std::shared_ptr<ViewHandler> viewHandler)
{
	printDebug("Game View has been set.");

	this->_viewHandler = viewHandler;
	this->_leaderboardModel->connect([&]() {
			_leaderboardView->notify("update_game");
		return false;
		});

	this->_leaderboardModel->connect("STARTED_MOVE", [&]() {
		return false;
		});

	this->_leaderboardModel->connect("STARTED_SPAWN", [&]() {
		return false;
		});

	this->_leaderboardModel->connect("GAME_OVER", [&]() {
		return false;
		});

	this->_leaderboardModel->connect("GAME_WON", [&]() {
		return false;
		});

	// Graphic View
	this->_leaderboardView = this->_viewHandler->getView<BaseLeaderboardView>("leaderboard_graphic");
	this->_leaderboardView->connect("entered_name", [&]() {
		return false;
		});

	this->_leaderboardView->connect("finished_move", [&]() {
		return false;
		});

	this->_leaderboardView->connect("started_spawning", [&]() {
		return false;
		});

	this->_leaderboardView->connect("finished_spawning", [&]() {
		return false;
		});

	// CMD View
	this->_leaderboardView = this->_viewHandler->getView<BaseLeaderboardView>("leaderboard_cmd");
	this->_leaderboardView->connect("entered_name", [&]() {
		this->_leaderboardModel->updateLeaderboard(this->_leaderboardView->getEntry());
		this->_leaderboardView->setLeaderboardEntries(this->_leaderboardModel->getLeaderboardEntries());
		this->leaderboardMode = LeaderboardMode::VIEW;
		this->_leaderboardView->render();
		return false;
		});

	this->_leaderboardView->connect("finished_move", [&]() {
		return false;
		});

	this->_leaderboardView->connect("started_spawning", [&]() {
		return false;
		});

	this->_leaderboardView->connect("finished_spawning", [&]() {
		return false;
		});
}

void LeaderboardController::switchView()
{
	printDebug("[GameController] Switched view. Graphic: " + this->isGraphic);

	this->_leaderboardView->closeWindow();
	delete _eventManager;

	if (isGraphic) {
		this->_leaderboardView = this->_viewHandler->getView<LeaderboardViewCMD>("leaderboard_cmd");
		this->_eventManager = new CMDEventManager();
	}
	else {
		this->_leaderboardView = this->_viewHandler->getView<LeaderboardViewGraphic>("leaderboard_graphic");
		this->_eventManager = new GraphicEventManager();
	}

	this->_leaderboardView->openWindow();
	this->isGraphic = !this->isGraphic;
	this->_leaderboardView->setLeaderboardEntries(this->_leaderboardModel->getLeaderboardEntries());

	this->render();
}

const ExitCode LeaderboardController::run()
{
	this->exitCode = ExitCode::EXIT;
	this->isEnd = false;

	if (isGraphic) {
		this->switchView();
	}

	this->_leaderboardView->setLeaderboardEntries(this->_leaderboardModel->getLeaderboardEntries());
	this->_leaderboardView->setMode(this->_leaderboardModel->getMode());
	this->_leaderboardView->setScore(this->_leaderboardModel->getScore());
	this->render();

	return this->gameLoop();
}

void LeaderboardController::close(ExitCode code)
{
	if (code == ExitCode::EXIT)
		this->_leaderboardView->closeWindow();

	this->isEnd = true;
	this->exitCode = code;
}

const ExitCode LeaderboardController::gameLoop()
{
	while (!isEnd) 
		update();

	if (exitCode != ExitCode::EXIT)
		this->_leaderboardView->deleteRenderer();

	return exitCode;
}

void LeaderboardController::update()
{
	_eventManager->handleEvents(_leaderboardModel, this, _leaderboardView->getWindow());

	if (isEnd)
		return;
}

void LeaderboardController::render()
{
	this->_leaderboardView->render();
}
