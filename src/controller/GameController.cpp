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

const std::string GameController::run()
{
	printf("RUN\n");
	return this->gameLoop();
}

const std::string GameController::gameLoop()
{
	while (window->isOpen()) {
		update();
		render();
	}

	return "EXIT";
}

void GameController::update()
{
	dt = dt_clock.restart().asSeconds();

	if (!isEnd) {
		updatePollEvents();
		
		if (isMoving) {
			this->_gameView->updateMove(dt);
			this->_gameView->render(*window);
			this->window->display();
		}

		if (isSpawning) {
			this->_gameView->updateSpawning(dt);
			this->_gameView->render(*window);
			this->window->display();
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

		if ((ev.Event::type == sf::Event::Closed) || (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape))
			window->close();

		if (!isEnd) {
			if (!isGameOver && !isMoving && !isSpawning)
				if (ev.type == sf::Event::KeyPressed) {
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

void GameController::render()
{
}

void GameController::setModelHandler(std::shared_ptr<ModelHandler> modelHandler) {
	printf("Game Model has been set.\n");

	this->_modelHandler = modelHandler;
	this->_gameModel = this->_modelHandler->getModel<GameModel>("game");
	this->_gameModel->connect([&] () {
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
	this->_gameModel->connect([&] () {
			std::cout << "[GameController]	GameModel has been updated" << std::endl;
			std::cout << "[GameController]	Updating the GameView" << std::endl;
			std::cout << std::endl;
			_gameView->notify("update_game");
		return (false);
	});

	this->_gameModel->connect("STARTED_MOVE", [&]() {
			printf("[GameController] GameModel has started move.\n");
			_gameView->syncMatrix(this->_gameModel->getMatrix());
			_gameView->syncMoveInstructions(this->_gameModel->getMoveInstructions());
			_gameView->startMove();
			//_gameView->render(*window);
			//window->display();
		return false;
		});

	this->_gameModel->connect("STARTED_SPAWN", [&]() {
		printf("[GameController] GameModel has started spawning new tile.\n");
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
	this->_gameView->connect("started_move", [&] () {
		std::cout << "[GameController] GameView has started move animation." << std::endl;
		isMoving = true;
		return (false);
		});

	this->_gameView->connect("finished_move", [&]() {
		std::cout << "[GameController] GameView has finished move animation." << std::endl;
		isMoving = false;
		this->_gameModel->endMove();
		return (false);
		});

	this->_gameView->connect("started_spawning", [&]() {
		std::cout << "[GameController] GameView has started spawn animation." << std::endl;
		isSpawning = true;
		return (false);
		});

	this->_gameView->connect("finished_spawning", [&]() {
		std::cout << "[GameController] GameView has finished spawn animation." << std::endl;
		isSpawning = false;
		this->_gameModel->endMerge();
		return (false);
		});
}