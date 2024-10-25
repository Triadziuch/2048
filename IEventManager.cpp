#include "IEventManager.h"
#include "src/model/GameModel.h"
#include "src/controller/GameController.h"

GraphicEventManager::GraphicEventManager()
{
}

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

CMDEventManager::CMDEventManager()
{
}

void CMDEventManager::handleEvents(std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const
{
	char input;
	std::cin >> input;

	switch (input) {
	case 'a': model->move(sf::Keyboard::A); break;
	case 'd': model->move(sf::Keyboard::D); break;
	case 'w': model->move(sf::Keyboard::W); break;
	case 's': model->move(sf::Keyboard::S); break;
	case 'c': controller->switchView(); break;
	}
}