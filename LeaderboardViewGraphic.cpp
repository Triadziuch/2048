#include "LeaderboardViewGraphic.h"

void LeaderboardViewGraphic::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);

	sf::Image icon;
	icon.loadFromFile("assets/Textures/appicon.png");
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void LeaderboardViewGraphic::initVariables()
{
	// Playground sprite initialization
	m_texture = &AssetManager::GetTexture("assets/Textures/playground.png");
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2.f,
		m_sprite.getPosition().y + m_sprite.getGlobalBounds().height / 2.f);
	m_sprite.setPosition(windowSize / 2.f);
	m_scale = (windowSize.y - m_playgroundPadding * 2) / m_sprite.getGlobalBounds().height;
	m_sprite.setScale(m_scale, m_scale);

	m_movementManager = new MovementManager();
	m_movementContainer = MovementContainer::getInstance();

	sf::Vector2f playground_pos = m_sprite.getPosition();
	playground_pos.x -= m_sprite.getLocalBounds().width / 4.f;
	playground_pos.y -= m_sprite.getLocalBounds().height / 4.f;
	m_playgroundPosition = playground_pos;
}

void LeaderboardViewGraphic::initAssets()
{
}

void LeaderboardViewGraphic::initAnimations()
{
}

LeaderboardViewGraphic::LeaderboardViewGraphic()
{
	initAssets();
	initVariables();
	initAnimations();
}

const std::string& LeaderboardViewGraphic::getViewPath() const
{
	return "leaderboardViewGraphic";
}

void LeaderboardViewGraphic::updateContent()
{

}


void LeaderboardViewGraphic::openWindow()
{
	if (this->window == nullptr)
		initWindow();
}

void LeaderboardViewGraphic::closeWindow()
{
	this->window->close();
	delete this->window;
	this->window = nullptr;
}

void LeaderboardViewGraphic::initRenderer()
{
}

void LeaderboardViewGraphic::deleteRenderer()
{
}

void LeaderboardViewGraphic::setLeaderboardEntries(std::vector<LeaderboardEntry*>& v_leaderboardEntries)
{
	this->v_leaderboardEntries = &v_leaderboardEntries;
	this->updateContent();
}

void LeaderboardViewGraphic::setScore(int score)
{
}

void LeaderboardViewGraphic::setMode(LeaderboardMode mode)
{
}

LeaderboardEntry LeaderboardViewGraphic::getEntry()
{
	return LeaderboardEntry();
}

sf::RenderWindow* LeaderboardViewGraphic::getWindow()
{
	return window;
}

void LeaderboardViewGraphic::render()
{
	if (window) {
		window->clear(m_backgroundColor);
		window->draw(m_sprite);
		window->display();
	}
}
