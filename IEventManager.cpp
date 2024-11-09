#include "IEventManager.h"
#include "src/model/GameModel.h"
#include "src/controller/GameController.h"
#include "LeaderboardModel.h"
#include "LeaderboardController.h"

std::unordered_map<int, bool> IEventManager::previousKeyState = {
	{ VK_UP, false },
	{ VK_DOWN, false },
	{ VK_LEFT, false },
	{ VK_RIGHT, false },
	{ 'C', false },
	{ VK_ESCAPE, false },
	{ 'L', false },
	{ 'V', false }
};

void GraphicEventManager::handleEvents(std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const
{
	auto isKeyPressed = [](int key) -> bool {
		return (GetAsyncKeyState(key) & 0x8000) != 0;
		};

	sf::Event ev;

	if (window->pollEvent(ev)) {

		if ((ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) || (ev.type == sf::Event::Closed)) {
			controller->close();
		}

		if (ev.type == sf::Event::KeyPressed) {

			if (controller->getIsGameOver())
				controller->resetGame();
			else {
				if (!controller->getIsMoving())
					model->move(ev.key.code);

				if (ev.key.code == sf::Keyboard::C) {
					previousKeyState['C'] = true;
					controller->switchView();
				}
			}
		}
	}
}

void GraphicEventManager::handleEvents(std::shared_ptr<LeaderboardModel> model, LeaderboardController* controller, sf::RenderWindow* window) const
{
	auto isKeyPressed = [](int key) -> bool {
		return (GetAsyncKeyState(key) & 0x8000) != 0;
		};

	sf::Event ev;

	if (window->pollEvent(ev)) {

		if ((ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) || (ev.type == sf::Event::Closed)) {
			controller->close();
		}

		if (ev.type == sf::Event::KeyPressed) {

			if (ev.key.code == sf::Keyboard::C) {
				previousKeyState['C'] = true;
				controller->switchView();
			}
		}
	}
}

void CMDEventManager::handleEvents(std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const
{
	auto isKeyPressed = [](int key) -> bool {
		return (GetAsyncKeyState(key) & 0x8000) != 0;
		};

	if (isKeyPressed(VK_ESCAPE) && !previousKeyState[VK_ESCAPE]) {
		controller->close();
		previousKeyState[VK_ESCAPE] = true;
		return;
	}
	else if (!isKeyPressed(VK_ESCAPE)) 
		previousKeyState[VK_ESCAPE] = false;

	if (isKeyPressed('C') && !previousKeyState['C']) {
		if (controller->getIsGameOver() == false)
			controller->switchView();
		previousKeyState['C'] = true;
		return;
	}
	else if (!isKeyPressed('C')) 
		previousKeyState['C'] = false;

	if (isKeyPressed('L') && !previousKeyState['L']) {
		controller->displayLeaderboard(LeaderboardMode::EDIT); // TODO: Do zmienienia na view bo edit bedzie tylko po przegranej
		previousKeyState['L'] = true;
		return;
	}
	else if (!isKeyPressed('L'))
		previousKeyState['L'] = false;
	
	if (isKeyPressed('V') && !previousKeyState['V']) {
		controller->displayLeaderboard(LeaderboardMode::VIEW); // TODO: Do zmienienia na view bo edit bedzie tylko po przegranej
		previousKeyState['V'] = true;
		return;
	}
	else if (!isKeyPressed('V'))
		previousKeyState['V'] = false;

	if (isKeyPressed(VK_UP) && !previousKeyState[VK_UP]) {
		model->move(sf::Keyboard::W);
		previousKeyState[VK_UP] = true;
	}
	else if (!isKeyPressed(VK_UP)) 
		previousKeyState[VK_UP] = false;

	if (isKeyPressed(VK_DOWN) && !previousKeyState[VK_DOWN]) {
		model->move(sf::Keyboard::S);
		previousKeyState[VK_DOWN] = true;
	}
	else if (!isKeyPressed(VK_DOWN)) 
		previousKeyState[VK_DOWN] = false;

	if (isKeyPressed(VK_LEFT) && !previousKeyState[VK_LEFT]) {
		model->move(sf::Keyboard::A);
		previousKeyState[VK_LEFT] = true;
	}
	else if (!isKeyPressed(VK_LEFT)) 
		previousKeyState[VK_LEFT] = false;

	if (isKeyPressed(VK_RIGHT) && !previousKeyState[VK_RIGHT]) {
		model->move(sf::Keyboard::D);
		previousKeyState[VK_RIGHT] = true;
	}
	else if (!isKeyPressed(VK_RIGHT)) 
		previousKeyState[VK_RIGHT] = false;
}

void CMDEventManager::handleEvents(std::shared_ptr<LeaderboardModel> model, LeaderboardController* controller, sf::RenderWindow* window) const
{
	auto isKeyPressed = [](int key) -> bool {
		return (GetAsyncKeyState(key) & 0x8000) != 0;
		};

	if (isKeyPressed(VK_ESCAPE) && !previousKeyState[VK_ESCAPE]) {
		controller->close();
		previousKeyState[VK_ESCAPE] = true;
		return;
	}
	else if (!isKeyPressed(VK_ESCAPE))
		previousKeyState[VK_ESCAPE] = false;

	if (isKeyPressed('C') && !previousKeyState['C']) {
		controller->switchView();
		previousKeyState['C'] = true;
		return;
	}
	else if (!isKeyPressed('C'))
		previousKeyState['C'] = false;

	if (isKeyPressed('L') && !previousKeyState['L']) {
		controller->close(ExitCode::GAME);
		previousKeyState['L'] = true;
		return;
	}
	else if (!isKeyPressed('L'))
		previousKeyState['L'] = false;
}
