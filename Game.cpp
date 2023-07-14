#include "Game.h"

// Initialization functions 
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "2048", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initVariables()
{
	srand(static_cast<unsigned>(time(nullptr)));
	this->isEnd = false;
	this->color_background = sf::Color(250, 248, 239);

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

	this->window->clear(this->color_background);

	// Displaying frame
	this->window->display();
}