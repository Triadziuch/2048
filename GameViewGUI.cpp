#pragma once
#include "GameViewGUI.h"
#include "Windows.h"


// = = = = = = Initialization functions = = = = = = //
void GameViewGUI::initText()
{
	m_font = &AssetManager::GetFont("assets/Fonts/ClearSans-Bold.ttf");
	if (!m_font)
		printf("Couldn't load m_font: assets/Fonts/ClearSans-Bold.ttf\n");

	m_newGameText.setFont(*m_font);
	m_leaderboardText.setFont(*m_font);
	m_bestScoreHeaderText.setFont(*m_font);
	m_scoreHeaderText.setFont(*m_font);
	m_titleText.setFont(*m_font);
	m_gameOverText.setFont(*m_font);
	m_gameOverPressKeyText.setFont(*m_font);

	m_newGameText.setCharacterSize(m_newGameSize);
	m_leaderboardText.setCharacterSize(m_newGameSize);
	m_bestScoreHeaderText.setCharacterSize(m_bestScoreSize);
	m_scoreHeaderText.setCharacterSize(m_scoreSize);
	m_titleText.setCharacterSize(m_titleSize);
	m_gameOverText.setCharacterSize(m_gameOverSize);
	m_gameOverPressKeyText.setCharacterSize(m_gameOverSize / 2U);

	m_newGameText.setFillColor(sf::Color::White);
	m_leaderboardText.setFillColor(sf::Color::White);
	m_bestScoreHeaderText.setFillColor(m_scoreColor);
	m_scoreHeaderText.setFillColor(m_scoreColor);
	m_titleText.setFillColor(m_titleColor);
	m_gameOverText.setFillColor(m_gameOverColor);
	m_gameOverPressKeyText.setFillColor(m_gameOverColor);

	m_newGameText.setString(m_newGameString);
	m_leaderboardText.setString(m_leaderboardString);
	m_bestScoreHeaderText.setString(m_bestScoreString);
	m_scoreHeaderText.setString(m_scoreString);
	m_titleText.setString(m_titleString);
	m_gameOverText.setString(m_gameOverString);
	m_gameOverPressKeyText.setString(m_gameOverPressKeyString);

	m_gameOverText.setFillColor(m_titleColor);
	m_gameOverPressKeyText.setFillColor(m_titleColor);

	m_newGameText.setOrigin(m_newGameText.getLocalBounds().left + m_newGameText.getGlobalBounds().width / 2.f, m_newGameText.getLocalBounds().top + m_newGameText.getGlobalBounds().height / 2.f);
	m_leaderboardText.setOrigin(m_leaderboardText.getLocalBounds().left + m_leaderboardText.getGlobalBounds().width / 2.f, m_leaderboardText.getLocalBounds().top + m_leaderboardText.getGlobalBounds().height / 2.f);
	m_bestScoreHeaderText.setOrigin(m_bestScoreHeaderText.getLocalBounds().left + m_bestScoreHeaderText.getGlobalBounds().width / 2.f, m_bestScoreHeaderText.getLocalBounds().top + m_bestScoreHeaderText.getGlobalBounds().height / 2.f);
	m_scoreHeaderText.setOrigin(m_scoreHeaderText.getLocalBounds().left + m_scoreHeaderText.getGlobalBounds().width / 2.f, m_scoreHeaderText.getLocalBounds().top + m_scoreHeaderText.getGlobalBounds().height / 2.f);
	m_gameOverText.setOrigin(m_gameOverText.getLocalBounds().left + m_gameOverText.getGlobalBounds().width / 2.f, m_gameOverText.getLocalBounds().top + m_gameOverText.getGlobalBounds().height / 2.f);
	m_gameOverPressKeyText.setOrigin(m_gameOverPressKeyText.getLocalBounds().left + m_gameOverPressKeyText.getGlobalBounds().width / 2.f, m_gameOverPressKeyText.getLocalBounds().top + m_gameOverPressKeyText.getGlobalBounds().height / 2.f);

	m_newGameText.setPosition(m_newGameButtonSprite.getGlobalBounds().left + m_newGameButtonSprite.getGlobalBounds().width / 2.f, m_newGameButtonSprite.getGlobalBounds().top + m_newGameButtonSprite.getGlobalBounds().height / 2.f);
	m_leaderboardText.setPosition((int)(m_leaderboardButtonSprite.getGlobalBounds().left + m_leaderboardButtonSprite.getGlobalBounds().width / 2.f), (int)(m_leaderboardButtonSprite.getGlobalBounds().top + m_leaderboardButtonSprite.getGlobalBounds().height / 2.f));
	m_bestScoreHeaderText.setPosition(m_bestScoreButtonSprite.getGlobalBounds().left + m_bestScoreButtonSprite.getGlobalBounds().width / 2.f, m_bestScoreButtonSprite.getGlobalBounds().top + m_bestScoreHeaderText.getGlobalBounds().height * 2);
	m_scoreHeaderText.setPosition(m_scoreButtonSprite.getGlobalBounds().left + m_scoreButtonSprite.getGlobalBounds().width / 2.f, m_scoreButtonSprite.getGlobalBounds().top + m_scoreHeaderText.getGlobalBounds().height * 2);
	m_titleText.setPosition(m_playgroundRect.left, m_playgroundRect.top - m_titleText.getGlobalBounds().height * 1.75f);
	m_gameOverText.setPosition(m_playgroundRect.left + m_playgroundRect.width / 2.f, m_playgroundRect.top + m_playgroundRect.height / 2.f - m_gameOverText.getGlobalBounds().height);
	m_gameOverPressKeyText.setPosition(m_playgroundRect.left + m_playgroundRect.width / 2.f, m_playgroundRect.top + m_playgroundRect.height / 2.f + m_gameOverPressKeyText.getGlobalBounds().height);

	m_scoreText.setFont(*m_font);
	m_bestScoreText.setFont(*m_font);

	m_scoreText.setCharacterSize(20);
	m_bestScoreText.setCharacterSize(20);

	m_scoreText.setFillColor(sf::Color::White);
	m_bestScoreText.setFillColor(sf::Color::White);

	m_scoreText.setString(std::to_string(m_score));
	m_bestScoreText.setString(std::to_string(m_bestScore));

	m_scoreText.setOrigin(m_scoreText.getLocalBounds().left + m_scoreText.getGlobalBounds().width / 2.f, m_scoreText.getLocalBounds().top + m_scoreText.getGlobalBounds().height / 2.f);
	m_bestScoreText.setOrigin(m_bestScoreText.getLocalBounds().left + m_bestScoreText.getGlobalBounds().width / 2.f, m_bestScoreText.getLocalBounds().top + m_bestScoreText.getGlobalBounds().height / 2.f);

	m_scoreText.setPosition(m_scoreHeaderText.getPosition().x, m_scoreHeaderText.getGlobalBounds().top + m_scoreHeaderText.getGlobalBounds().height + 15.f);
	m_bestScoreText.setPosition(m_bestScoreHeaderText.getPosition().x, m_bestScoreHeaderText.getGlobalBounds().top + m_bestScoreHeaderText.getGlobalBounds().height + 15.f);

	std::wstring newGameTextPosition = std::to_wstring(m_newGameText.getPosition().x) + L" " + std::to_wstring(m_newGameText.getPosition().y);
	std::wstring leaderboardTextPosition = std::to_wstring(m_leaderboardText.getPosition().x) + L" " + std::to_wstring(m_leaderboardText.getPosition().y);
	std::wstring bestScoreHeaderTextPosition = std::to_wstring(m_bestScoreHeaderText.getPosition().x) + L" " + std::to_wstring(m_bestScoreHeaderText.getPosition().y);
	std::wstring scoreHeaderTextPosition = std::to_wstring(m_scoreHeaderText.getPosition().x) + L" " + std::to_wstring(m_scoreHeaderText.getPosition().y);
	std::wstring titleTextPosition = std::to_wstring(m_titleText.getPosition().x) + L" " + std::to_wstring(m_titleText.getPosition().y);
	std::wstring gameOverTextPosition = std::to_wstring(m_gameOverText.getPosition().x) + L" " + std::to_wstring(m_gameOverText.getPosition().y);
	std::wstring gameOverPressKeyTextPosition = std::to_wstring(m_gameOverPressKeyText.getPosition().x) + L" " + std::to_wstring(m_gameOverPressKeyText.getPosition().y);
	std::wstring scoreTextPosition = std::to_wstring(m_scoreText.getPosition().x) + L" " + std::to_wstring(m_scoreText.getPosition().y);
	std::wstring bestScoreTextPosition = std::to_wstring(m_bestScoreText.getPosition().x) + L" " + std::to_wstring(m_bestScoreText.getPosition().y);
}

void GameViewGUI::initSprites()
{
	m_newGameTexture = &AssetManager::GetTexture("assets/Textures/button_newgame.png");
	if (!m_newGameTexture)
		printf("Couldn't load texture: assets//Textures/button_newgame.png\n");

	m_scoreTexture = &AssetManager::GetTexture("assets/Textures/button_score.png");
	if (!m_scoreTexture)
		printf("Couldn't load texture: assets//Textures/button_score.png\n");

	m_newGameButtonSprite.setTexture(*m_newGameTexture);
	m_leaderboardButtonSprite.setTexture(*m_newGameTexture);
	m_bestScoreButtonSprite.setTexture(*m_scoreTexture);
	m_scoreButtonSprite.setTexture(*m_scoreTexture);

	m_newGameButtonSprite.setScale(m_scale, m_scale);
	m_leaderboardButtonSprite.setScale((m_scale + 0.05f), m_scale);
	m_bestScoreButtonSprite.setScale(m_scale, m_scale);
	m_scoreButtonSprite.setScale(m_scale, m_scale);

	m_leaderboardButtonSprite.setPosition(m_windowSize.x - m_leaderboardButtonSprite.getGlobalBounds().width * 1.25f, m_playgroundRect.top + m_leaderboardButtonSprite.getGlobalBounds().height / 4.f);
	m_newGameButtonSprite.setPosition(m_leaderboardButtonSprite.getPosition().x + (m_leaderboardButtonSprite.getGlobalBounds().width - m_newGameButtonSprite.getGlobalBounds().width), m_leaderboardButtonSprite.getGlobalBounds().top + m_leaderboardButtonSprite.getGlobalBounds().height + m_leaderboardButtonSprite.getGlobalBounds().height / 4.f);
	m_bestScoreButtonSprite.setPosition(m_leaderboardButtonSprite.getPosition().x + m_leaderboardButtonSprite.getGlobalBounds().width - m_bestScoreButtonSprite.getGlobalBounds().width, m_playgroundRect.top - m_leaderboardButtonSprite.getGlobalBounds().height / 4.f - m_bestScoreButtonSprite.getGlobalBounds().height);
	m_scoreButtonSprite.setPosition(m_bestScoreButtonSprite.getPosition().x - m_scoreButtonSprite.getGlobalBounds().width - 10.f, m_bestScoreButtonSprite.getPosition().y);

	std::wstring leadebroardButtonPosition = std::to_wstring(m_leaderboardButtonSprite.getPosition().x) + L" " + std::to_wstring(m_leaderboardButtonSprite.getPosition().y);
	std::wstring newGameButtonPosition = std::to_wstring(m_newGameButtonSprite.getPosition().x) + L" " + std::to_wstring(m_newGameButtonSprite.getPosition().y);
	std::wstring bestScoreButtonPosition = std::to_wstring(m_bestScoreButtonSprite.getPosition().x) + L" " + std::to_wstring(m_bestScoreButtonSprite.getPosition().y);
	std::wstring scoreButtonPosition = std::to_wstring(m_scoreButtonSprite.getPosition().x) + L" " + std::to_wstring(m_scoreButtonSprite.getPosition().y);
}



// = = = = = = Utility functions = = = = = = //
void GameViewGUI::center_origin(sf::Sprite& sprite)
{
	sprite.setOrigin(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2.f,
					 sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2.f);
}

void GameViewGUI::justifyHorizontal(const sf::FloatRect& button, sf::Text& text)
{
	text.setOrigin(0.f, 0.f);
	text.setPosition(button.left + (button.width - text.getGlobalBounds().width) / 2.f, text.getPosition().y);
}



// = = = = = = Constructors / Destructors = = = = = = //
GameViewGUI::GameViewGUI(sf::Vector2f windowSize, sf::FloatRect playgroundRect) : m_windowSize(windowSize), m_playgroundRect(playgroundRect)
{
	initSprites();
	initText();
}

GameViewGUI::~GameViewGUI() {}



// = = = = = = Update functions = = = = = = //
bool GameViewGUI::updateGameOver(const float dt)
{
	m_gameOverTime += dt;

	if (m_gameOverTime < m_gameOverTimeMax) {

		m_gameOverText.setFillColor(sf::Color(250, 248, 239, 255 * m_gameOverTime / m_gameOverTimeMax));
		return false;
	}
	else if (m_gameOverTime < m_gameOverTimeMax * 2.f) {
		return false;
	}
	else if (m_gameOverTime < m_gameOverTimeMax * 3.f) {
		m_gameOverPressKeyText.setFillColor(sf::Color(250, 248, 239, 255 * (m_gameOverTime - 2.f * m_gameOverTimeMax) / m_gameOverTimeMax ));
		return false;
	}
	else {
		m_gameOverText.setFillColor(sf::Color(250, 248, 239, 255));
		m_gameOverPressKeyText.setFillColor(sf::Color(250, 248, 239, 255));
	}

	return true;
}



// = = = = = = Public functions = = = = = = //
void GameViewGUI::startGameOver()
{
	m_gameOverTime = 0.f;
	m_isGameOver = true;
}

void GameViewGUI::stopGameOver()
{
	m_isGameOver = false;
}



// = = = = = = Accessors / Mutators = = = = = = //
sf::FloatRect GameViewGUI::getNewGameButton()
{
	return m_newGameButtonSprite.getGlobalBounds();
}

sf::FloatRect GameViewGUI::getLeaderboardButton()
{
	return m_leaderboardButtonSprite.getGlobalBounds();
}

void GameViewGUI::setScore(int score)
{
	m_score = score;

	const float old_width = m_scoreText.getGlobalBounds().width;
	m_scoreText.setString(std::to_string(m_score));
	const float new_width = m_scoreText.getGlobalBounds().width;

	if (old_width != new_width)
		m_scoreText.move((old_width - new_width) / 2.f, 0.f);
}

void GameViewGUI::setBestScore(int value)
{
	this->m_bestScore = value;
	m_bestScoreText.setString(std::to_string(m_bestScore));
	m_bestScoreText.setOrigin(m_bestScoreText.getLocalBounds().left + m_bestScoreText.getGlobalBounds().width / 2.f, m_bestScoreText.getLocalBounds().top + m_bestScoreText.getGlobalBounds().height / 2.f);
	m_bestScoreText.setPosition(m_bestScoreHeaderText.getPosition().x, m_bestScoreHeaderText.getGlobalBounds().top + m_bestScoreHeaderText.getGlobalBounds().height + 15.f);
}

void GameViewGUI::addScore(int value_) {
	m_score += value_;

	float old_width = m_scoreText.getGlobalBounds().width;
	m_scoreText.setString(std::to_string(m_score));
	float new_width = m_scoreText.getGlobalBounds().width;

	if (old_width != new_width)
		m_scoreText.move((old_width - new_width) / 2.f, 0.f);

	if (m_bestScore < m_score) {
		m_bestScore = m_score;
		m_bestScoreText.setString(std::to_string(m_bestScore));
		justifyHorizontal(m_bestScoreButtonSprite.getGlobalBounds(), m_bestScoreText);
		m_bestScoreText.setPosition(m_bestScoreText.getPosition().x, m_scoreText.getPosition().y - m_scoreText.getOrigin().y);
	}
}



// = = = = = = Render functions = = = = = = //
void GameViewGUI::render(sf::RenderTarget& target)
{
	// Drawing buttons
	target.draw(m_newGameButtonSprite);
	target.draw(m_leaderboardButtonSprite);
	target.draw(m_bestScoreButtonSprite);
	target.draw(m_scoreButtonSprite);

	// Drawing text
	target.draw(m_newGameText);
	target.draw(m_leaderboardText);
	target.draw(m_bestScoreHeaderText);
	target.draw(m_scoreHeaderText);
	target.draw(m_titleText);

	// Drawing score
	target.draw(m_bestScoreText);
	target.draw(m_scoreText);

	// Drawing game over
	if (m_isGameOver) {
		target.draw(m_gameOverText);

		if (m_gameOverTime > m_gameOverTimeMax * 2.f)
			target.draw(m_gameOverPressKeyText);
	}
		
}
