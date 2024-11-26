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
	{ VK_ESCAPE, false },
	{ VK_RETURN, false },
	{ VK_SPACE, false },
	{ VK_SHIFT, false },
	{ VK_CONTROL, false },
	{ VK_MENU, false },
	{ VK_TAB, false },
	{ VK_BACK, false },
	{ VK_INSERT, false },
	{ VK_DELETE, false },
	{ VK_HOME, false },
	{ VK_END, false },
	{ VK_PRIOR, false },
	{ VK_NEXT, false },
	{ VK_F1, false },
	{ VK_F2, false },
	{ VK_F3, false },
	{ VK_F4, false },
	{ VK_F5, false },
	{ VK_F6, false },
	{ VK_F7, false },
	{ VK_F8, false },
	{ VK_F9, false },
	{ VK_F10, false },
	{ VK_F11, false },
	{ VK_F12, false },

	{ 'A', false },
	{ 'B', false },
	{ 'C', false },
	{ 'D', false },
	{ 'E', false },
	{ 'F', false },
	{ 'G', false },
	{ 'H', false },
	{ 'I', false },
	{ 'J', false },
	{ 'K', false },
	{ 'L', false },
	{ 'M', false },
	{ 'N', false },
	{ 'O', false },
	{ 'P', false },
	{ 'Q', false },
	{ 'R', false },
	{ 'S', false },
	{ 'T', false },
	{ 'U', false },
	{ 'V', false },
	{ 'W', false },
	{ 'X', false },
	{ 'Y', false },
	{ 'Z', false },
	{ '0', false },
	{ '1', false },
	{ '2', false },
	{ '3', false },
	{ '4', false },
	{ '5', false },
	{ '6', false },
	{ '7', false },
	{ '8', false },
	{ '9', false },

	{ '!', false },
	{ '"', false },
	{ '#', false },
	{ '$', false },
	{ '%', false },
	{ '&', false },
	{ '\'', false },
	{ '(', false },
	{ ')', false },
	{ '*', false },
	{ '+', false },
	{ ',', false },
	{ '-', false },
	{ '.', false },
	{ '/', false },
	{ ':', false },
	{ ';', false },
	{ '<', false },
	{ '=', false },
	{ '>', false },
	{ '?', false },
	{ '@', false },
	{ '[', false },
	{ '\\', false },
	{ ']', false },
	{ '^', false },
	{ '_', false },
	{ '`', false },
	{ '{', false },
	{ '|', false },
	{ '}', false },
	{ '~', false }
};

void GraphicEventManager::handleEvents(std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const
{
	auto isKeyPressed = [](int key) -> bool {
		return (GetAsyncKeyState(key) & 0x8000) != 0;
		};

	sf::Event ev;

	if (window->pollEvent(ev)) 
		this->handleEvent(&ev, model, controller, window);
}

void GraphicEventManager::handleEvent(sf::Event* event, std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const
{
	if (event == nullptr)
		return;

	if ((event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Escape) || (event->type == sf::Event::Closed)) {
		controller->close();
	}

	if (event->type == sf::Event::KeyPressed && controller->getIsHandlingEvents()) {

		if (controller->getIsGameOver())
			controller->resetGame();
		else {
			if (!controller->getIsMoving())
				model->move(event->key.code);

			if (event->key.code == sf::Keyboard::C) {
				previousKeyState['C'] = true;
				controller->switchView();
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
		controller->switchView();
		previousKeyState['C'] = true;
		return;
	}
	else if (!isKeyPressed('C')) 
		previousKeyState['C'] = false;

	if (isKeyPressed('L') && !previousKeyState['L']) {
		controller->displayLeaderboard(); // TODO: Do zmienienia na view bo edit bedzie tylko po przegranej
		previousKeyState['L'] = true;
		return;
	}
	else if (!isKeyPressed('L'))
		previousKeyState['L'] = false;
	
	if (isKeyPressed('V') && !previousKeyState['V']) {
		controller->displayLeaderboard(); // TODO: Do zmienienia na view bo edit bedzie tylko po przegranej
		previousKeyState['V'] = true;
		return;
	}
	else if (!isKeyPressed('V'))
		previousKeyState['V'] = false;

	if (isKeyPressed('R') && !previousKeyState['R']) {
		controller->resetGame();
		controller->render();
		previousKeyState['R'] = true;
		return;
	}
	else if (!isKeyPressed('R'))
		previousKeyState['R'] = false;

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

	if (isKeyPressed(VK_RETURN) && !previousKeyState[VK_RETURN]) {
		if (controller->getIsGameOver()) {
			controller->resetGame();
			controller->displayLeaderboard();
		}

		previousKeyState[VK_RETURN] = true;
	}
	else if (!isKeyPressed(VK_RETURN))
		previousKeyState[VK_RETURN] = false;
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

	for (int key = 0; key <= 255; ++key) {
		if (previousKeyState.find(key) != previousKeyState.end()) {
			if (isKeyPressed(key) && !previousKeyState[key]) {
				controller->close(ExitCode::GAME);
				previousKeyState[key] = true;
				return;
			}
			else if (!isKeyPressed(key)) {
				previousKeyState[key] = false;
			}
		}
	}
}

void CMDEventManager::handleEvent(sf::Event* event, std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const
{
}
