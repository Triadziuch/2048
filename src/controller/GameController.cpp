#include "GameController.h"

// Initialization functions 
void GameController::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);

	sf::Image icon;
	icon.loadFromFile("assets/Textures/appicon.png");
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void GameController::initVariables()
{
	srand(static_cast<unsigned>(time(nullptr)));
}



// Constructors / Destructors
GameController::GameController() {
	initWindow();
	initVariables();
}

GameController::~GameController() {
	delete window;
}



// Model and View handling
void GameController::setModelHandler(std::shared_ptr<ModelHandler> modelHandler) {
	printf("Game Model has been set.\n");

	this->_modelHandler = modelHandler;
	this->_gameModel = this->_modelHandler->getModel<GameModel>("game");
	this->_gameModel->connect([&]() {
		std::cout << "[GameController] GameModel has been updated." << std::endl;
		//std::cout << "[GameController] GameModel id: " << this->_gameModel->getId() << std::endl;
		//std::cout << "[GameController] GameModel name: " << this->_gameModel->getName() << std::endl;
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
		_gameView->syncMoveInstructions(this->_gameModel->getMoveInstructions());
		_gameView->startMove();
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

	this->_gameView = this->_viewHandler->getView<GameView>("game_1");
	this->_gameView->connect("started_move", [&]() {
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



// Public funcitons
const std::string GameController::run()
{
	_gameView->syncMatrix(this->_gameModel->getMatrix());
	this->render();

	return this->gameLoop();
}

const std::string GameController::gameLoop()
{
	while (window->isOpen()) {
		update();
	}

	return "EXIT";
}



// Update functions
void GameController::update()
{
	dt = dt_clock.restart().asSeconds();

	if (!isEnd) {
		updatePollEvents();
		
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
}

void GameController::updatePollEvents()
{
	sf::Event ev;

	if (window->pollEvent(ev)) {

		if ((ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) || (ev.type == sf::Event::Closed))
			window->close();

		if (!isEnd) {
			if (!isGameOver && !isMoving)
				if (ev.type == sf::Event::KeyPressed) {
					if (isSpawning)
						_gameView->endSpawn();

					_gameModel->move(ev.key.code);
				}

			/*if (playground->getNewGameButton().contains(mouse_pos_view)) {
				if (cursor_type != sf::StandardCursor::HAND) {
					cursor_type = sf::StandardCursor::HAND;
					sf::StandardCursor Cursor(sf::StandardCursor::HAND);
					Cursor.set(window->getSystemHandle());
				}

				if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left) {
					playground->clearBoard();
					isGameOver = false;
				}
			}
			else {
				if (cursor_type != sf::StandardCursor::NORMAL) {
					cursor_type = sf::StandardCursor::NORMAL;
					sf::StandardCursor Cursor(sf::StandardCursor::NORMAL);
					Cursor.set(window->getSystemHandle());
				}
			}*/
		}
	}
}



// Render function
void GameController::render()
{
	this->_gameView->render(*window);
	this->window->display();
}