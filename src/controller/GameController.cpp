#include "GameController.h"

// = = = = = Initialization functions  = = = = = //
void GameController::initVariables()
{
	srand(static_cast<unsigned>(time(nullptr)));
	this->isGraphic = true;
	this->_eventManager = new GraphicEventManager();
}



// = = = = = Constructors / Destructors  = = = = = //
GameController::GameController() {
	initVariables();
}

GameController::~GameController() {
}



// = = = = = Model and View handling  = = = = = //
void GameController::setModelHandler(std::shared_ptr<ModelHandler> modelHandler) {
	printf("Game Model has been set.\n");

	this->_modelHandler = modelHandler;
	this->_gameModel = this->_modelHandler->getModel<GameModel>("game");
	this->_gameModel->connect([&]() {
		std::cout << "[GameController] GameModel has been updated." << std::endl;
		std::cout << std::endl;
		return false;
		});
}

void GameController::setViewHandler(std::shared_ptr<ViewHandler> viewHandler) {
	printf("Game View has been set.\n");
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
			printf("[GameController] GameModel has informed about game over.\n");
		return false;
		});

	this->_gameModel->connect("GAME_WON", [&]() {
			printf("[GameController] GameModel has informed about winning a game.\n");
		return false;
		});

	// CMD View
	this->_gameView = this->_viewHandler->getView<GameViewCMD>("game_cmd");
	this->_gameView->connect("started_move", [&]() {
		this->_gameView->endSpawn();
		isMoving = true;
		return (false);
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
		return false;
		});

	// Graphic View
	this->_gameView = this->_viewHandler->getView<GameViewGraphic>("game_graphic");
	this->_gameView->connect("started_move", [&]() {
			this->_gameView->endSpawn();
			isMoving = true;
		return (false);
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
		return false;
		});
}

void GameController::switchView()
{
	printf("[GameController] Switched view\n");
	printf("Graphic: %d\n", this->isGraphic);
	if (isGraphic) {
		this->_gameView->closeWindow();
		this->_gameView = this->_viewHandler->getView<GameViewCMD>("game_cmd");
		delete _eventManager;
		this->_eventManager = new CMDEventManager();
	}
		
	else {
		this->_gameView->closeWindow();
		this->_gameView = this->_viewHandler->getView<GameViewGraphic>("game_graphic");
		delete _eventManager;
		this->_eventManager = new GraphicEventManager();
		this->_gameView->openWindow();
	}
		
	this->isGraphic = !this->isGraphic;

	this->_gameView->syncMatrix(this->_gameModel->getMatrix());
	this->render();
}



// = = = = = Public functions  = = = = = //
const std::string GameController::run()
{
	_gameView->syncMatrix(this->_gameModel->getMatrix());
	this->render();

	return this->gameLoop();
}

void GameController::close()
{
	this->_gameView->closeWindow();
	this->isEnd = true;
}

const std::string GameController::gameLoop()
{
	while (!isEnd) {
		update();
	}

	return "EXIT";
}



// = = = = = Update functions  = = = = = //
void GameController::update()
{
	dt = dt_clock.restart().asSeconds();

	_eventManager->handleEvents(_gameModel, this, _gameView->getWindow());

	if (isMoving) {
		this->_gameView->updateMove(dt);
		this->render();
	}

	if (isSpawning) {
		this->_gameView->updateSpawning(dt);
		this->render();
	}

	/*if (isGraphic) {
		updatePollEventsGraphic();

		if (isMoving) {
			this->_gameView->updateMove(dt);
			this->render();
		}

		if (isSpawning) {
			this->_gameView->updateSpawning(dt);
			this->render();
		}
	}
	else {
		updatePollEventsCMD();

		if (isMoving) {
			this->_gameView->updateMove(dt);
			this->render();
		}

		if (isSpawning) {
			this->_gameView->updateSpawning(dt);
			this->render();
		}
	}*/

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

void GameController::updatePollEventsGraphic()
{
	//sf::Event ev;

	//if (window->pollEvent(ev)) {

	//	if ((ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) || (ev.type == sf::Event::Closed)) {
	//		this->window->close();
	//		this->isEnd = true;
	//	}
	//		

	//	if (!isEnd) {
	//		if (!isGameOver && !isMoving)
	//			

	//		/*if (playground->getNewGameButton().contains(mouse_pos_view)) {
	//			if (cursor_type != sf::StandardCursor::HAND) {
	//				cursor_type = sf::StandardCursor::HAND;
	//				sf::StandardCursor Cursor(sf::StandardCursor::HAND);
	//				Cursor.set(window->getSystemHandle());
	//			}

	//			if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left) {
	//				playground->clearBoard();
	//				isGameOver = false;
	//			}
	//		}
	//		else {
	//			if (cursor_type != sf::StandardCursor::NORMAL) {
	//				cursor_type = sf::StandardCursor::NORMAL;
	//				sf::StandardCursor Cursor(sf::StandardCursor::NORMAL);
	//				Cursor.set(window->getSystemHandle());
	//			}
	//		}*/
	//	}
	//}
}

void GameController::updatePollEventsCMD()
{
	/*char input;
	std::cin >> input;

	switch (input) {
	case 'a': model.move(sf::Keyboard::A); break;
	case 'd': model.move(sf::Keyboard::D); break;
	case 'w': model.move(sf::Keyboard::W); break;
	case 's': model.move(sf::Keyboard::S); break;
	case 'c': this->switchView(); break;
	}*/
}



// = = = = = Render functions  = = = = = //
void GameController::render()
{
	this->_gameView->render();
}