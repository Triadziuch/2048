#include "Game.h"

// Initialization functions 
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->WINDOW_WIDTH, this->WINDOW_HEIGHT), this->WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(this->FRAMERATE);
	this->window->setVerticalSyncEnabled(this->VERTICAL_SYNC);
}

void Game::initVariables()
{
	srand(static_cast<unsigned>(time(nullptr)));
	this->playground = new Playground({ static_cast<float>(this->WINDOW_WIDTH), static_cast<float>(this->WINDOW_HEIGHT) });
}

// Constructors / Destructors
Game::Game()
{
	this->initWindow();
	this->initVariables();
}

Game::~Game()
{
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

	this->updatePollEvents();
	if (!this->isEnd) {
	}
}

void Game::updatePollEvents()
{
	sf::Event ev;

	if (this->window->pollEvent(ev)) {

		// Zamykanie okna
		if ((ev.Event::type == sf::Event::Closed) || (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape)) {
			this->window->close();
		}
				
		if (!this->isEnd) {
			if (ev.type == sf::Event::KeyPressed) {

			}
		}
	}
}

// Render functions
void Game::render() {
	// Drawing background
	this->playground->render(*this->window);

	// Displaying frame
	this->window->display();
}