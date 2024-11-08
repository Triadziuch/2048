#include "GameController.h"

// = = = = = Initialization functions  = = = = = //
void GameController::initVariables()
{
	srand(static_cast<unsigned>(time(nullptr)));
	this->isGraphic = true;
	this->_eventManager = new GraphicEventManager();

	/*HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);*/
}



// = = = = = Constructors / Destructors  = = = = = //
GameController::GameController() {
	initVariables();
}

GameController::~GameController() {}



// = = = = = Model and View handling  = = = = = //
void GameController::setModelHandler(std::shared_ptr<ModelHandler> modelHandler) {
	printDebug("Game Model has been set.");

	this->_modelHandler = modelHandler;
	this->_gameModel = this->_modelHandler->getModel<GameModel>("game");
	this->_gameModel->connect([&]() {
			printDebug("[GameController] GameModel has been updated.");
		return false;
		});
}

void GameController::setViewHandler(std::shared_ptr<ViewHandler> viewHandler) {
	printDebug("Game View has been set.");

	this->_viewHandler = viewHandler;
	this->_gameModel->connect([&]() {
			_gameView->notify("update_game");
		return false;
		});

	this->_gameModel->connect("STARTED_MOVE", [&]() {
			_gameView->syncMatrix(this->_gameModel->getMatrix());
			_gameView->startMove(this->_gameModel->getMoveInstructions());
		return false;
		});

	this->_gameModel->connect("STARTED_SPAWN", [&]() {
			_gameView->syncMatrix(this->_gameModel->getMatrix());
			_gameView->startSpawn(this->_gameModel->getSpawnInstructions());
			_gameView->startMerge(this->_gameModel->getMergeInstructions());
		return false;
		});

	this->_gameModel->connect("GAME_OVER", [&]() {
			printDebug("[GameController] GameModel has informed about game over.");
		return false;
		});

	this->_gameModel->connect("GAME_WON", [&]() {
			printDebug("[GameController] GameModel has informed about winning a game.");
		return false;
		});

	// CMD View
	this->_gameView = this->_viewHandler->getView<GameViewCMD>("game_cmd");
	this->_gameView->updateScore(this->_gameModel->getScore(), this->_gameModel->getBestScore());
	this->_gameView->connect("started_move", [&]() {
			this->_gameModel->endMove();
			this->_gameView->endSpawn();
		return false;
		});

	this->_gameView->connect("finished_move", [&]() {
			isMoving = false;
			this->_gameModel->endMove();
		return false;
		});

	this->_gameView->connect("started_spawning", [&]() {
			isSpawning = true;
		return false;
		});

	this->_gameView->connect("finished_spawning", [&]() {
		isSpawning = false;
		this->_gameModel->endMerge();
		this->_gameView->updateScore(this->_gameModel->getScore(), this->_gameModel->getBestScore());
		_gameView->syncMatrix(this->_gameModel->getMatrix());
		this->_gameView->render();
		return false;
		});

	// Graphic View
	this->_gameView = this->_viewHandler->getView<GameViewGraphic>("game_graphic");
	this->_gameView->updateScore(this->_gameModel->getScore(), this->_gameModel->getBestScore());
	this->_gameView->connect("started_move", [&]() {
			this->_gameView->endSpawn();
			isMoving = true;
		return false;
		});

	this->_gameView->connect("finished_move", [&]() {
			isMoving = false;
			this->_gameModel->endMove();
		return false;
		});

	this->_gameView->connect("started_spawning", [&]() {
			isSpawning = true;
		return false;
		});

	this->_gameView->connect("finished_spawning", [&]() {
			isSpawning = false;
			this->_gameModel->endMerge();
			this->_gameView->updateScore(this->_gameModel->getScore(), this->_gameModel->getBestScore());
		return false;
		});
}

void GameController::switchView()
{
	printDebug("[GameController] Switched view. Graphic: " + this->isGraphic);

	while (isMoving) 
		this->_gameView->updateMove(1.f);

	while (isSpawning) 
		this->_gameView->updateSpawning(1.f);

	this->_gameView->closeWindow();
	delete _eventManager;

	if (isGraphic) {
		this->_gameView = this->_viewHandler->getView<GameViewCMD>("game_cmd");
		this->_eventManager = new CMDEventManager();
	}
	else {
		this->_gameView = this->_viewHandler->getView<GameViewGraphic>("game_graphic");
		this->_eventManager = new GraphicEventManager();
	}

	this->_gameView->openWindow();
	this->isGraphic = !this->isGraphic;
	this->_gameView->syncMatrix(this->_gameModel->getMatrix());
	this->_gameView->updateScore(this->_gameModel->getScore(), this->_gameModel->getBestScore());

	this->render();
}

void GameController::displayLeaderboard(LeaderboardMode mode)
{
	this->_gameModel->setLeaderboardMode(mode);
	this->exitCode = ExitCode::LEADERBOARD;
	this->isEnd = true;
}



// = = = = = Public functions  = = = = = //
const ExitCode GameController::run()
{
	this->exitCode = ExitCode::EXIT;
	this->isEnd = false;

	if (isGraphic) {
		this->switchView();
	}
	else {
		_gameView->openWindow();
		_gameView->syncMatrix(this->_gameModel->getMatrix());
		this->_gameView->updateScore(this->_gameModel->getScore(), this->_gameModel->getBestScore());
		this->render();
	}

	

	return this->gameLoop();
}

void GameController::close()
{
	this->_gameView->closeWindow();
	this->isEnd = true;
	this->exitCode = ExitCode::EXIT;
}

const ExitCode GameController::gameLoop()
{
	while (!isEnd) {
		update();
	}

	if (exitCode != ExitCode::EXIT)
		this->_gameView->deleteRenderer();

	return exitCode;
}



// = = = = = Update functions  = = = = = //
void GameController::update()
{
	dt = dt_clock.restart().asSeconds();

	_eventManager->handleEvents(_gameModel, this, _gameView->getWindow());
	if (isEnd)
		return;

	if (isMoving) {
		this->_gameView->updateMove(dt);
		this->render();
	}

	if (isSpawning) {
		this->_gameView->updateSpawning(dt);
		this->render();
	}

	/*playground->update(dt);
	if (!isGameOver) {
		updateMousePositions();
		updatePollEvents();
		updateGameOver();
	}
	else {
		updateMousePositions();
		updatePollEvents();
	}*/
}

const bool& GameController::getIsMoving()
{
	return isMoving;
}

// = = = = = Render functions  = = = = = //
void GameController::render()
{
	this->_gameView->render();
}