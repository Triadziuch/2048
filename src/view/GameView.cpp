#include <iostream>
#include "GameView.h"

void GameView::initAssets()
{
    for (int i = 1; i < 13; i++)
        AssetManager::GetTexture("assets/Textures/" + std::to_string(static_cast<int>(pow(2, i))) + ".png");
    AssetManager::GetTexture("assets/Textures/button_newgame.png");
    AssetManager::GetTexture("assets/Textures/button_score.png");

	// Playground initialization
	m_texture = &AssetManager::GetTexture("assets/Textures/playground.png");
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
	m_tileMatrix->spawn(2);
	m_gui = new GUI(windowSize, m_sprite.getGlobalBounds());
}

GameView::GameView() {
    initAssets();
}

GameView::~GameView()
{
	delete m_gui;
	delete m_tileMatrix;
}

void GameView::onFormSubmit() {
    std::cout << "[GameView] form has been submitted." << std::endl;
    this->notify("form_submit");
}

const std::string & GameView::getViewPath() const {
    return ("game.html");
}

const StudentForm & GameView::getForm() const {
    return StudentForm();
}

StudentForm::StudentForm() {
    this->name = "No Name";
    this->age = -1;
}