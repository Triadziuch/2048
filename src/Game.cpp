#include "Game.h"

// Initialization functions 
void Game::initWindow()
{

	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);
	
	sf::Image icon;
	icon.loadFromFile("bin/Textures/appicon.png");
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	//window->setFramerateLimit(FRAMERATE);
	//window->setVerticalSyncEnabled(VERTICAL_SYNC);
}

void Game::initVariables()
{
	srand(static_cast<unsigned>(time(nullptr)));
	playground = new Playground({ static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT) });
}

void Game::initAssets()
{
	for(int i = 1; i < 13; i++)
		AssetManager::GetTexture("bin/Textures/" + to_string(static_cast<int>(pow(2, i))) + ".png");
	AssetManager::GetTexture("bin/Textures/button_newgame.png");
	AssetManager::GetTexture("bin/Textures/button_score.png");
	AssetManager::GetTexture("bin/Textures/tiles.png");
}

// Constructors / Destructors
Game::Game()
{
	initWindow();
	initVariables();
	initAssets();
}

Game::~Game()
{
	playground->~Playground();
	delete window;
}

// Run functions
void Game::run()
{
	while (window->isOpen()) {
		update();
		render();
	}
}

// Update functions
void Game::update() {
	dt = dt_clock.restart().asSeconds();

	
	if (!isEnd) {
		playground->update(dt);
		if (!isGameOver) {
			updateMousePositions();
			updatePollEvents();
			updateGameOver();
		}
		else {
			updateMousePositions();
			updatePollEvents();
		}
	}
}

void Game::updateMousePositions()
{
	mouse_pos_window = sf::Mouse::getPosition(*window);
	mouse_pos_view = window->mapPixelToCoords(mouse_pos_window);
}

void Game::updatePollEvents()
{
	sf::Event ev;

	if (window->pollEvent(ev)) {

		if ((ev.Event::type == sf::Event::Closed) || (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape)) 
			window->close();
				
		if (!isEnd) {
			if (!isGameOver) 
				if (ev.type == sf::Event::KeyPressed) 
					playground->move(ev.key.code);

			
			if (playground->getNewGameButton().contains(mouse_pos_view)) {
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
			}
		}
	}
}

void Game::updateGameOver()
{
	isGameOver = playground->getIsGameOver();
}

// Render functions
void Game::render() {

	playground->render(*window);
	window->display();
}