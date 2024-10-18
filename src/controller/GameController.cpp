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
			if (!isGameOver)
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
			std::cout << "[GameController]	Updating the GameViewTwo" << std::endl;
			std::cout << std::endl;
			this->_viewHandler->getView<GameViewTwo>("game_2")->notify("update_game");
		return (false);
	});

	this->_gameModel->connect("TILE_SPAWN", [&]() {
			printf("[GameController] GameModel spawned new tile.");
		return false;
		});

	this->_gameModel->connect("STARTED_MOVE", [&]() {
			printf("[GameController] GameModel has started move.");
		return false;
		});

	this->_gameModel->connect("STARTED_MERGE", [&]() {
			printf("[GameController] GameModel has started merge.");
		return false;
		});

	this->_gameModel->connect("GAME_OVER", [&]() {
			printf("[GameController] GameModel has informed about game over.");
		return false;
		});

	this->_gameView = this->_viewHandler->getView<GameView>("game_1");
	this->_gameView->connect("form_submit", [&] () {
		std::cout << "[GameController] Game 1 View Form has been submit." << std::endl;
		const auto &form = this->_gameView->getForm();
		std::cout << "[GameController] Game Form name: " << form.name << std::endl;
		std::cout << "[GameController] Game Form age: " << std::to_string(form.age) << std::endl;
		std::cout << std::endl;
		//this->_gameModel->setName(form.name);
		//this->_gameModel->setId(std::to_string(form.age)); // yes id != age, but it's just an example !
        return (false);
    });
}