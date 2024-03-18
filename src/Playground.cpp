#include "Playground.h"

Playground::Playground(const sf::Vector2f& windowSize)
{
	// Playground initialization
	m_texture = &AssetManager::GetTexture("Textures/playground.png");
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2.f,
									  m_sprite.getPosition().y + m_sprite.getGlobalBounds().height / 2.f);
	m_sprite.setPosition(windowSize / 2.f);
	m_scale = (windowSize.y - m_playgroundPadding * 2) / m_sprite.getGlobalBounds().height;
	m_sprite.setScale(m_scale, m_scale);

	m_innerEdgeWidth *= m_scale;
	m_outerEdgeWidth *= m_scale;
	m_tileWidth *= m_scale;

	sf::Vector2f playground_pos = m_sprite.getPosition();
	playground_pos.x -= m_sprite.getLocalBounds().width / 4.f;
	playground_pos.y -= m_sprite.getLocalBounds().height / 4.f;
	m_tileMatrix = new TileMatrix(&m_scale, &m_outerEdgeWidth, &m_innerEdgeWidth, &m_tileWidth, playground_pos);
	/*m_tileMatrix->addTile({ 0, 0 }, 4096);
	m_tileMatrix->addTile({ 1, 0 }, 2048);
	m_tileMatrix->addTile({ 2, 0 }, 1024);
	m_tileMatrix->addTile({ 3, 0 }, 512);
	m_tileMatrix->addTile({ 0, 1 }, 256);
	m_tileMatrix->addTile({ 0, 2 }, 128);*/
	m_tileMatrix->spawn(2);
	m_gui = new GUI(windowSize, m_sprite.getGlobalBounds());
}

Playground::~Playground()
{
	delete m_gui;
	delete m_tileMatrix;
}

void Playground::update(float dt)
{
	m_tileMatrix->update(dt);
	updateScore();

	if (m_tileMatrix->getIsGameOver()) {
		if (!m_isGameOver) {
			m_isGameOver = true;
			m_gui->startGameOver();
			m_gui->saveBestScore();
		}

		m_gui->updateGameOver(dt);
	}
}

void Playground::updateScore()
{
	const int added_m_score = m_tileMatrix->getAddedScore();
	m_tileMatrix->setAddedScore(0);
	m_score += added_m_score;
	m_gui->addScore(added_m_score);
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
	m_gui->stopGameOver();
	m_gui->saveBestScore();
	m_gui->setScore(0);
	m_tileMatrix->clearBoard();
	m_tileMatrix->spawn();
}

void Playground::render(sf::RenderTarget& target)
{
	target.clear(m_backgroundColor);
	target.draw(m_sprite);
	m_tileMatrix->render(target);
	m_gui->render(target);
}
