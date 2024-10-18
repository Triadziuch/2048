#pragma once

#include "../TileMatrixModel.h"
#include "GUI.h"
#include "event/EventObserver.h"

using namespace std;

class Playground : public EventObserver {
private:
	// Background variables
	bool m_isGameOver{ false };

	int m_score{};
	TileMatrixModel* m_tileMatrix{};

public:
	// Constructors / Destructors
	Playground(const sf::Vector2f& windowSize);
	virtual ~Playground();

	void update(float dt);
	void updateScore();

	void move(const sf::Keyboard::Key key);
	void clearBoard();
};