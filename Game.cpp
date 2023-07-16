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
		this->updatePollEvents();
		this->playground->update(dt);
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
				if (!this->playground->getIsMoving()) {
					if (ev.Event::key.code == sf::Keyboard::Up || ev.Event::key.code == sf::Keyboard::W) 
						this->playground->move('U');
					else if (ev.Event::key.code == sf::Keyboard::Down || ev.Event::key.code == sf::Keyboard::S)
						this->playground->move('D');
					else if (ev.Event::key.code == sf::Keyboard::Left || ev.Event::key.code == sf::Keyboard::A)
						this->playground->move('L');
					else if (ev.Event::key.code == sf::Keyboard::Right || ev.Event::key.code == sf::Keyboard::D)
						this->playground->move('R');
				}
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