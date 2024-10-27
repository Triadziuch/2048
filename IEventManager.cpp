#include "IEventManager.h"
#include "src/model/GameModel.h"
#include "src/controller/GameController.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESCAPE 27

void GraphicEventManager::handleEvents(std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const
{
	sf::Event ev;

	if (window->pollEvent(ev)) {

		if ((ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) || (ev.type == sf::Event::Closed)) {
			controller->close();
		}

		if (ev.type == sf::Event::KeyPressed) {
			model->move(ev.key.code);

			if (ev.key.code == sf::Keyboard::C) {
				controller->switchView();
			}
		}
	}
}

void CMDEventManager::handleEvents(std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const
{
	int input = 0;
	input = _getch();

	if (input == 0 || input == 224) {
		input = _getch();

		switch (input) {
		case KEY_UP:    model->move(sf::Keyboard::W); break;
		case KEY_DOWN:  model->move(sf::Keyboard::S); break;
		case KEY_LEFT:  model->move(sf::Keyboard::A); break;
		case KEY_RIGHT: model->move(sf::Keyboard::D); break;
		}
	}
	switch (input) {
	case 'c':
	case 'C':
		controller->switchView();
		break;
	case KEY_ESCAPE:
		controller->close();
		break;
	}
}