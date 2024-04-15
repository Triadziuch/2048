#pragma once
#include "GUI.h"

using namespace std;

void GUI::center_origin(sf::Sprite& sprite)
{
	sprite.setOrigin(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2.f,
					 sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2.f);
}

void GUI::justifyHorizontal(const sf::FloatRect& button, sf::Text& text)
{
	text.setOrigin(0.f, 0.f);
	text.setPosition(button.left + (button.width - text.getGlobalBounds().width) / 2.f, text.getPosition().y);
}

void GUI::saveBestScore()
{
	ofstream file;
	file.open(m_bestScoreFilename, ios::out);

	if (file.good())
		file << to_string(m_bestScore);

	file.close();
}

void GUI::updateGameOver(const float dt)
{
	if (m_gameOverTime < m_gameOverTimeMax) {
		m_gameOverTime += dt;
		m_gameOverText.setFillColor(sf::Color(250, 248, 239, 255 * m_gameOverTime / m_gameOverTimeMax));
	}
}

void GUI::startGameOver()
{
	m_gameOverTime = 0.f;
	m_isGameOver = true;
}

void GUI::stopGameOver()
{
	m_isGameOver = false;
}

void GUI::loadBestScore()
{
	fstream file;
	file.open(m_bestScoreFilename);

	if (file.good()) {
		string bestScoreString;
		stringstream ss_best_score;
		int int_best_score;
		file >> bestScoreString;
		ss_best_score << bestScoreString;
		ss_best_score >> int_best_score;
		m_bestScore = int_best_score;
	}

	file.close();
}

GUI::GUI(sf::Vector2f windowSize, sf::FloatRect playgroundRect) : m_windowSize(windowSize), m_playgroundRect(playgroundRect)
{
	loadBestScore();
	initSprites();
	initText();
}

void GUI::setScore(int value_)
{
	m_score = value_;

	const float old_width = m_scoreText.getGlobalBounds().width;
	m_scoreText.setString(to_string(m_score));
	const float new_width = m_scoreText.getGlobalBounds().width;

	if (old_width != new_width)
		m_scoreText.move((old_width - new_width) / 2.f, 0.f);

	if (m_bestScore < m_score) {
		sf::Vector2f old_pos = m_bestScoreText.getPosition();
		m_bestScore = m_score;
		m_bestScoreText = m_scoreText;
		m_bestScoreText.setPosition(old_pos);

		if (old_width != new_width)
			m_bestScoreText.move((old_width - new_width) / 2.f, 0.f);
	}
}

GUI::~GUI()
{
	saveBestScore();
}

void GUI::initText()
{
	m_font = &AssetManager::GetFont("assets/Fonts/ClearSans-Bold.ttf");
	if (!m_font)
		printf("Couldn't load m_font: assets/Fonts/ClearSans-Bold.ttf\n");

	m_newGameText.setFont(*m_font);
	m_bestScoreHeaderText.setFont(*m_font);
	m_scoreHeaderText.setFont(*m_font);
	m_titleText.setFont(*m_font);
	m_gameOverText.setFont(*m_font);

	m_newGameText.setCharacterSize(m_newGameSize);
	m_bestScoreHeaderText.setCharacterSize(m_bestScoreSize);
	m_scoreHeaderText.setCharacterSize(m_scoreSize);
	m_titleText.setCharacterSize(m_titleSize);
	m_gameOverText.setCharacterSize(m_gameOverSize);

	m_newGameText.setFillColor(sf::Color::White);
	m_bestScoreHeaderText.setFillColor(m_scoreColor);
	m_scoreHeaderText.setFillColor(m_scoreColor);
	m_titleText.setFillColor(m_titleColor);
	m_gameOverText.setFillColor(m_gameOverColor);

	m_newGameText.setString(m_newGameString);
	m_bestScoreHeaderText.setString(m_bestScoreString);
	m_scoreHeaderText.setString(m_scoreString);
	m_titleText.setString(m_titleString);
	m_gameOverText.setString(m_gameOverString);

	m_gameOverText.setFillColor(m_titleColor);

	m_newGameText.setOrigin(m_newGameText.getLocalBounds().left + m_newGameText.getGlobalBounds().width / 2.f, m_newGameText.getLocalBounds().top + m_newGameText.getGlobalBounds().height / 2.f);
	m_bestScoreHeaderText.setOrigin(m_bestScoreHeaderText.getLocalBounds().left + m_bestScoreHeaderText.getGlobalBounds().width / 2.f, m_bestScoreHeaderText.getLocalBounds().top + m_bestScoreHeaderText.getGlobalBounds().height / 2.f);
	m_scoreHeaderText.setOrigin(m_scoreHeaderText.getLocalBounds().left + m_scoreHeaderText.getGlobalBounds().width / 2.f, m_scoreHeaderText.getLocalBounds().top + m_scoreHeaderText.getGlobalBounds().height / 2.f);
	m_gameOverText.setOrigin(m_gameOverText.getLocalBounds().left + m_gameOverText.getGlobalBounds().width / 2.f, m_gameOverText.getLocalBounds().top + m_gameOverText.getGlobalBounds().height / 2.f);

	m_newGameText.setPosition(m_newGameButtonSprite.getGlobalBounds().left + m_newGameButtonSprite.getGlobalBounds().width / 2.f, m_newGameButtonSprite.getGlobalBounds().top + m_newGameButtonSprite.getGlobalBounds().height / 2.f);
	m_bestScoreHeaderText.setPosition(m_bestScoreButtonSprite.getGlobalBounds().left + m_bestScoreButtonSprite.getGlobalBounds().width / 2.f, m_bestScoreButtonSprite.getGlobalBounds().top + m_bestScoreHeaderText.getGlobalBounds().height * 2);
	m_scoreHeaderText.setPosition(m_scoreButtonSprite.getGlobalBounds().left + m_scoreButtonSprite.getGlobalBounds().width / 2.f, m_scoreButtonSprite.getGlobalBounds().top + m_scoreHeaderText.getGlobalBounds().height * 2);
	m_titleText.setPosition(m_playgroundRect.left, m_playgroundRect.top - m_titleText.getGlobalBounds().height * 1.75f);
	m_gameOverText.setPosition(m_playgroundRect.left + m_playgroundRect.width / 2.f, m_playgroundRect.top + m_playgroundRect.height / 2.f);

	m_scoreText.setFont(*m_font);
	m_bestScoreText.setFont(*m_font);

	m_scoreText.setCharacterSize(20);
	m_bestScoreText.setCharacterSize(20);

	m_scoreText.setFillColor(sf::Color::White);
	m_bestScoreText.setFillColor(sf::Color::White);

	m_scoreText.setString(to_string(m_score));
	m_bestScoreText.setString(to_string(m_bestScore));

	m_scoreText.setOrigin(m_scoreText.getLocalBounds().left + m_scoreText.getGlobalBounds().width / 2.f, m_scoreText.getLocalBounds().top + m_scoreText.getGlobalBounds().height / 2.f);
	m_bestScoreText.setOrigin(m_bestScoreText.getLocalBounds().left + m_bestScoreText.getGlobalBounds().width / 2.f, m_bestScoreText.getLocalBounds().top + m_bestScoreText.getGlobalBounds().height / 2.f);

	m_scoreText.setPosition(m_scoreHeaderText.getPosition().x, m_scoreHeaderText.getGlobalBounds().top + m_scoreHeaderText.getGlobalBounds().height + 15.f);
	m_bestScoreText.setPosition(m_bestScoreHeaderText.getPosition().x, m_bestScoreHeaderText.getGlobalBounds().top + m_bestScoreHeaderText.getGlobalBounds().height + 15.f);
}

void GUI::initSprites()
{
	m_newGameTexture = &AssetManager::GetTexture("assets/Textures/button_newgame.png");
	if (!m_newGameTexture)
		printf("Couldn't load texture: assets//Textures/button_newgame.png\n");

	m_scoreTexture = &AssetManager::GetTexture("assets/Textures/button_score.png");
	if (!m_scoreTexture)
		printf("Couldn't load texture: assets//Textures/button_score.png\n");

	m_newGameButtonSprite.setTexture(*m_newGameTexture);
	m_bestScoreButtonSprite.setTexture(*m_scoreTexture);
	m_scoreButtonSprite.setTexture(*m_scoreTexture);

	m_newGameButtonSprite.setScale(m_scale, m_scale);
	m_bestScoreButtonSprite.setScale(m_scale, m_scale);
	m_scoreButtonSprite.setScale(m_scale, m_scale);

	m_newGameButtonSprite.setPosition(m_windowSize.x - m_newGameButtonSprite.getGlobalBounds().width * 1.25f, m_playgroundRect.top + m_newGameButtonSprite.getGlobalBounds().height / 4.f );
	m_bestScoreButtonSprite.setPosition(m_newGameButtonSprite.getPosition().x + m_newGameButtonSprite.getGlobalBounds().width - m_bestScoreButtonSprite.getGlobalBounds().width, m_playgroundRect.top - m_newGameButtonSprite.getGlobalBounds().height / 4.f - m_bestScoreButtonSprite.getGlobalBounds().height);
	m_scoreButtonSprite.setPosition(m_bestScoreButtonSprite.getPosition().x - m_scoreButtonSprite.getGlobalBounds().width - 10.f, m_bestScoreButtonSprite.getPosition().y);
}


void GUI::addScore(int value_) {
	m_score += value_;
	
	float old_width = m_scoreText.getGlobalBounds().width;
	m_scoreText.setString(to_string(m_score));
	float new_width = m_scoreText.getGlobalBounds().width;
	
	if (old_width != new_width)
		m_scoreText.move((old_width - new_width) / 2.f, 0.f);

	if (m_bestScore < m_score) {
		m_bestScore = m_score;
		m_bestScoreText.setString(to_string(m_bestScore));
		justifyHorizontal(m_bestScoreButtonSprite.getGlobalBounds(), m_bestScoreText);
		m_bestScoreText.setPosition(m_bestScoreText.getPosition().x, m_scoreText.getPosition().y - m_scoreText.getOrigin().y);
	}
}

void GUI::render(sf::RenderTarget& target)
{
	// Drawing buttons
	target.draw(m_newGameButtonSprite);
	target.draw(m_bestScoreButtonSprite);
	target.draw(m_scoreButtonSprite);

	// Drawing text
	target.draw(m_newGameText);
	target.draw(m_bestScoreHeaderText);
	target.draw(m_scoreHeaderText);
	target.draw(m_titleText);

	// Drawing score
	target.draw(m_bestScoreText);
	target.draw(m_scoreText);

	// Drawing game over
	if (m_isGameOver)
		target.draw(m_gameOverText);
}
