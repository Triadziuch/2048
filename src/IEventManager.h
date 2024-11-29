#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <conio.h>

class GameModel;
class ViewModel;
class LeaderboardModel;
class GameController;
class LeaderboardController;

class IEventManager {
protected:
	// Flagi stanu klawiszy
	static std::unordered_map<int, bool> previousKeyState;

public:
	virtual void handleEvent(sf::Event* event, std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const = 0;
	virtual void handleEvents(std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const = 0;

	virtual void handleEvent(sf::Event* event, std::shared_ptr<LeaderboardModel> model, LeaderboardController* controller, sf::RenderWindow* window) const = 0;
	virtual void handleEvents(std::shared_ptr<LeaderboardModel> model, LeaderboardController* controller, sf::RenderWindow* window) const = 0;
};

class GraphicEventManager : public IEventManager {
public:
	void handleEvent(sf::Event* event, std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const override;
	void handleEvents(std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const override;

	void handleEvent(sf::Event* event, std::shared_ptr<LeaderboardModel> model, LeaderboardController* controller, sf::RenderWindow* window) const override;
	void handleEvents(std::shared_ptr<LeaderboardModel> model, LeaderboardController* controller, sf::RenderWindow* window) const override;
};

class CMDEventManager : public IEventManager {
public:
	void handleEvent(sf::Event* event, std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const override;
	void handleEvents(std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const override;

	void handleEvent(sf::Event* event, std::shared_ptr<LeaderboardModel> model, LeaderboardController* controller, sf::RenderWindow* window) const override;
	void handleEvents(std::shared_ptr<LeaderboardModel> model, LeaderboardController* controller, sf::RenderWindow* window) const override;
};