#include "IEventManager.h"
#include "src/model/GameModel.h"
#include "src/controller/GameController.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESCAPE 27

bool IEventManager::isUpPressed = false;
bool IEventManager::isDownPressed = false;
bool IEventManager::isLeftPressed = false;
bool IEventManager::isRightPressed = false;
bool IEventManager::isCPressed = false;
bool IEventManager::isEscapePressed = false;

void GraphicEventManager::handleEvents(std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const
{
	sf::Event ev;

	if (window->pollEvent(ev)) {

		if ((ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) || (ev.type == sf::Event::Closed)) {
			controller->close();
		}

		if (ev.type == sf::Event::KeyPressed) {

			if (!controller->getIsMoving())
				model->move(ev.key.code);

			if (ev.key.code == sf::Keyboard::C) {
				isCPressed = true;
				controller->switchView();
			}
		}
	}
}

void CMDEventManager::handleEvents(std::shared_ptr<GameModel> model, GameController* controller, sf::RenderWindow* window) const
{
	//OutputDebugString(L"Rozpoczynam sprawdzanie wartoœci zwracanych przez _getch()... Wciœnij 'q', aby zakoñczyæ.\n");

	//while (true) {
	//	if (_kbhit()) {  // Sprawdzenie, czy klawisz jest dostêpny
	//		int value = _getch();

	//		// Tworzenie tekstu diagnostycznego
	//		std::wstring message = L"Zwrócona wartoœæ: " + std::to_wstring(value) + L"\n";
	//		OutputDebugString(message.c_str());

	//		// Jeœli u¿ytkownik wciœnie 'q' lub 'Q', przerywamy pêtlê diagnostyczn¹
	//		if (value == 'q' || value == 'Q') {
	//			OutputDebugString(L"Przerywanie diagnostyki.\n");
	//			break;
	//		}
	//	}
	//	// Krótkie opóŸnienie, aby unikn¹æ nadmiernej iloœci wywo³añ
	//	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//}

	OutputDebugString(L"Wejœcie do handleEvents()\n");

	

	// Sprawdzamy stan klawiszy
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (!isUpPressed)
		{
			model->move(sf::Keyboard::W);
			isUpPressed = true;
		}
	}
	else
	{
		isUpPressed = false;
	}

	// Analogicznie dla pozosta³ych klawiszy
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (!isDownPressed)
		{
			model->move(sf::Keyboard::S);
			isDownPressed = true;
		}
	}
	else
	{
		isDownPressed = false;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (!isLeftPressed)
		{
			model->move(sf::Keyboard::A);
			isLeftPressed = true;
		}
	}
	else
	{
		isLeftPressed = false;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (!isRightPressed)
		{
			model->move(sf::Keyboard::D);
			isRightPressed = true;
		}
	}
	else
	{
		isRightPressed = false;
	}

	if (GetAsyncKeyState('C') & 0x8000)
	{
		if (!isCPressed)
		{
			controller->switchView();
			isCPressed = true;
		}
	}
	else
	{
		isCPressed = false;
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		if (!isEscapePressed)
		{
			controller->close();
			isEscapePressed = true;
		}
	}
	else
	{
		isEscapePressed = false;
	}
	/*int input = 0;
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
	}*/

	//if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
	//	// Jeœli klawisz ESC jest wciœniêty
	//	controller->close();
	//	return;
	//}

	//if (GetAsyncKeyState('H') & 0x8000) {
	//	controller->switchView();
	//	return;
	//}

	//// Obs³uga klawiszy strza³ek za pomoc¹ kodów wirtualnych:
	//if (GetAsyncKeyState(VK_UP) & 0x8000) {
	//	model->move(sf::Keyboard::W);
	//	OutputDebugString(L"W\n");
	//	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	//}
	//else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
	//	model->move(sf::Keyboard::S);
	//	OutputDebugString(L"S\n");
	//	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	//}
	//else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
	//	model->move(sf::Keyboard::A);
	//	OutputDebugString(L"A\n");
	//	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	//}
	//else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
	//	model->move(sf::Keyboard::D);
	//	OutputDebugString(L"D\n");
	//	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	//}

	//static std::unordered_map<int, bool> previousKeyState = {
	//	{VK_ESCAPE, false},
	//	{'H', false},
	//	{VK_UP, false},
	//	{VK_DOWN, false},
	//	{VK_LEFT, false},
	//	{VK_RIGHT, false}
	//};

	//// Helper to check if key state has changed from "not pressed" to "pressed"
	//auto isKeyPressed = [](int key) -> bool {
	//	return (GetAsyncKeyState(key) & 0x8000) != 0;
	//	};

	//if (isKeyPressed(VK_ESCAPE) && !previousKeyState[VK_ESCAPE]) {
	//	controller->close();
	//	previousKeyState[VK_ESCAPE] = true; // Zapisanie stanu
	//	return;
	//}
	//else if (!isKeyPressed(VK_ESCAPE)) {
	//	previousKeyState[VK_ESCAPE] = false; // Klawisz zwolniony
	//}

	//if (isKeyPressed('H') && !previousKeyState['H']) {
	//	controller->switchView();
	//	previousKeyState['H'] = true;
	//	return;
	//}
	//else if (!isKeyPressed('H')) {
	//	previousKeyState['H'] = false;
	//}

	//if (isKeyPressed(VK_UP) && !previousKeyState[VK_UP]) {
	//	model->move(sf::Keyboard::W);
	//	OutputDebugString(L"W\n");
	//	previousKeyState[VK_UP] = true;
	//}
	//else if (!isKeyPressed(VK_UP)) {
	//	previousKeyState[VK_UP] = false;
	//}

	//if (isKeyPressed(VK_DOWN) && !previousKeyState[VK_DOWN]) {
	//	model->move(sf::Keyboard::S);
	//	OutputDebugString(L"S\n");
	//	previousKeyState[VK_DOWN] = true;
	//}
	//else if (!isKeyPressed(VK_DOWN)) {
	//	previousKeyState[VK_DOWN] = false;
	//}

	//if (isKeyPressed(VK_LEFT) && !previousKeyState[VK_LEFT]) {
	//	model->move(sf::Keyboard::A);
	//	OutputDebugString(L"A\n");
	//	previousKeyState[VK_LEFT] = true;
	//}
	//else if (!isKeyPressed(VK_LEFT)) {
	//	previousKeyState[VK_LEFT] = false;
	//}

	//if (isKeyPressed(VK_RIGHT) && !previousKeyState[VK_RIGHT]) {
	//	model->move(sf::Keyboard::D);
	//	OutputDebugString(L"D\n");
	//	previousKeyState[VK_RIGHT] = true;
	//}
	//else if (!isKeyPressed(VK_RIGHT)) {
	//	previousKeyState[VK_RIGHT] = false;
	//}
}