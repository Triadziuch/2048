#include "Playground.h"

Playground::Playground(const sf::Vector2f& windowSize)
{
	m_tileMatrix = new TileMatrixModel();
	m_tileMatrix->spawn(2);
}

Playground::~Playground()
{
	delete m_tileMatrix;
}

void Playground::update(float dt)
{
	m_tileMatrix->update(dt);
	updateScore();

	if (m_tileMatrix->getIsGameOver()) {
		if (!m_isGameOver) {
			m_isGameOver = true;
		}
	}
}

void Playground::updateScore()
{
	const int added_m_score = m_tileMatrix->getAddedScore();
	m_tileMatrix->setAddedScore(0);
	m_score += added_m_score;
}

void Playground::move(const sf::Keyboard::Key key)
{
	if (m_tileMatrix->getIsMoving()) return;

	switch (key)
	{
		case sf::Keyboard::Key::Up:
		case sf::Keyboard::Key::W:
			m_tileMatrix->moveUp();
			break;
		case sf::Keyboard::Key::Down:
		case sf::Keyboard::Key::S:
			m_tileMatrix->moveDown();
			break;
		case sf::Keyboard::Key::Left:
		case sf::Keyboard::Key::A:
			m_tileMatrix->moveLeft();
			break;
		case sf::Keyboard::Key::Right:
		case sf::Keyboard::Key::D:
			m_tileMatrix->moveRight();
			break;
	}
}

void Playground::clearBoard()
{
	m_isGameOver = false;
	m_tileMatrix->clearBoard();
	m_tileMatrix->spawn(2);
}