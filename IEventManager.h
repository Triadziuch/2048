#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <conio.h>

class GameModel;
class GameController;

class IEventManager {
public:
	virtual void handleEvents(std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const = 0;
};

class GraphicEventManager : public IEventManager {
public:
	void handleEvents(std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const override;
};

class CMDEventManager : public IEventManager {
public:
	void handleEvents(std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const override;
};