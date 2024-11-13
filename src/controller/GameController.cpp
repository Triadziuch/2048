#include "GameController.h"

// = = = = = Initialization functions  = = = = = //
void GameController::initVariables()
{
	srand(static_cast<unsigned>(time(nullptr)));
	this->_eventManager = new CMDEventManager();
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
			this->isGameOver = true;
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
			this->_gameModel->endMerge();
			this->_gameView->syncMatrix(this->_gameModel->getMatrix());
			this->_gameView->updateScore(this->_gameModel->getScore(), this->_gameModel->getBestScore());

			if (this->isGameOver)
				this->_gameView->startGameOver();

			this->_gameView->render();
		return false;
		});
}

void GameController::displayLeaderboard()
{
	this->exitCode = ExitCode::LEADERBOARD;
	this->isEnd = true;
}

void GameController::resetGame()
{
	this->isGameOver = false;
	this->_gameModel->prepareLeaderboard();
	this->_viewHandler->getView<GameViewCMD>("game_cmd")->reset();
	this->_gameModel->clearBoard();
	this->_gameView->syncMatrix(this->_gameModel->getMatrix());
	this->_gameView->updateScore(this->_gameModel->getScore(), this->_gameModel->getBestScore());
}



// = = = = = Public functions  = = = = = //
const ExitCode GameController::run()
{
	this->exitCode = ExitCode::EXIT;
	this->isEnd = false;

	_gameView->openWindow();
	_gameView->syncMatrix(this->_gameModel->getMatrix());
	this->_gameView->updateScore(this->_gameModel->getScore(), this->_gameModel->getBestScore());
	this->render();
	
	if (isGameOver)
		this->_gameView->endGameOver();

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
		this->_gameView->updateSpawn(dt);
		this->render();
	}

	if (isGameOver && !isSpawning && !isMoving) {
		this->_gameView->updateGameOver(dt);
		this->render();
	}
}

const bool& GameController::getIsMoving()
{
	return isMoving;
}

const bool GameController::getIsGameOver()
{
	return isGameOver;
}

// = = = = = Render functions  = = = = = //
void GameController::render()
{
	this->_gameView->render();
}