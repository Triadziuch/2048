#include "Game.h"

// Initialization functions 
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->WINDOW_WIDTH, this->WINDOW_HEIGHT), this->WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);
	//this->window->setFramerateLimit(this->FRAMERATE);
	//this->window->setVerticalSyncEnabled(this->VERTICAL_SYNC);
}

void Game::initVariables()
{
	srand(static_cast<unsigned>(time(nullptr)));
	this->playground = new Playground({ static_cast<float>(this->WINDOW_WIDTH), static_cast<float>(this->WINDOW_HEIGHT) });
}

void Game::initAssets()
{
	for(int i = 1; i < 13; i++)
		AssetManager::GetTexture("Textures/" + to_string(static_cast<int>(pow(2, i))) + ".png");
	AssetManager::GetTexture("Textures/button_newgame.png");
	AssetManager::GetTexture("Textures/button_score.png");
	AssetManager::GetTexture("Textures/tiles.png");
}

// Constructors / Destructors
Game::Game()
{
	this->initWindow();
	this->initVariables();
	this->initAssets();
}

Game::~Game()
{
	this->playground->~Playground();
	delete this->window;
}

// Run functions
void Game::run()
{
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}
}

// Update functions
void Game::update() {
	dt = dt_clock.restart().asSeconds();

	
	if (!this->isEnd) {
		if (!this->isGameOver) {
			this->updateMousePositions();
			this->updatePollEvents();
			this->playground->update(dt);
			this->updateGameOver();
		}
		else {
			this->updateMousePositions();
			this->updatePollEvents();
		}
	}
}

void Game::updateMousePositions()
{
	this->mouse_pos_window = sf::Mouse::getPosition(*this->window);
	this->mouse_pos_view = this->window->mapPixelToCoords(this->mouse_pos_window);
}

void Game::updatePollEvents()
{
	sf::Event ev;

	if (this->window->pollEvent(ev)) {

		// Zamykanie okna
		if ((ev.Event::type == sf::Event::Closed) || (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape)) 
			this->window->close();
				
		if (!this->isEnd) {
			if (!this->isGameOver) 
				if (ev.type == sf::Event::KeyPressed) 
					this->playground->move(ev.key.code);

			
			if (this->playground->getNewGameButton().contains(this->mouse_pos_view)) {
				if (this->cursor_type != sf::StandardCursor::HAND) {
					this->cursor_type = sf::StandardCursor::HAND;
					sf::StandardCursor Cursor(sf::StandardCursor::HAND);
					Cursor.set(this->window->getSystemHandle());
				}
				
				if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left) {
					this->playground->clearBoard();
					this->isGameOver = false;
				}
			}
			else {
				if (this->cursor_type != sf::StandardCursor::NORMAL) {
					this->cursor_type = sf::StandardCursor::NORMAL;
					sf::StandardCursor Cursor(sf::StandardCursor::NORMAL);
					Cursor.set(this->window->getSystemHandle());
				}
			}
		}
	}
}

void Game::updateGameOver()
{
	this->isGameOver = this->playground->getIsGameOver();
}

// Render functions
void Game::render() {
	// Drawing background
	this->playground->render(*this->window);

	// Displaying frame
	this->window->display();
}