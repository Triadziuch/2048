#include <string>
#include "GameModel.h"


GameModel::GameModel() : BaseModel() {
	m_tileMatrix = new TileMatrixModel();
	m_tileMatrix->connect([&] () {
		printf("[GameModel]: TileMatrixModel has been updated.\n");
		this->notify();
		});
	m_tileMatrix->spawn(2);

}

void GameModel::update(float dt)
{
	m_tileMatrix->update(dt);
	updateScore();

	if (m_tileMatrix->getIsGameOver()) {
		if (!m_isGameOver) {
			m_isGameOver = true;
		}
	}
}

void GameModel::updateScore()
{
	const int added_m_score = m_tileMatrix->getAddedScore();
	m_tileMatrix->setAddedScore(0);
	m_score += added_m_score;
}

void GameModel::move(const sf::Keyboard::Key key)
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

void GameModel::clearBoard()
{
	m_isGameOver = false;
	m_tileMatrix->clearBoard();
	m_tileMatrix->spawn(2);
}
