#pragma once
#include "LeaderboardViewGUI.h"

// = = = = = Initialization functions  = = = = = //
void LeaderboardViewGUI::initText()
{
	m_font = &AssetManager::GetFont("assets/Fonts/ClearSans-Bold.ttf");
	if (!m_font)
		printf("Couldn't load m_font: assets/Fonts/ClearSans-Bold.ttf\n");

	m_returnText.setFont(*m_font);
	m_leaderboardText.setFont(*m_font);
	m_bestScoreHeaderText.setFont(*m_font);
	m_scoreHeaderText.setFont(*m_font);
	m_congratulationsText.setFont(*m_font);

	m_returnText.setCharacterSize(m_returnSize);
	m_leaderboardText.setCharacterSize(m_leaderboardSize);
	m_bestScoreHeaderText.setCharacterSize(m_bestScoreSize);
	m_scoreHeaderText.setCharacterSize(m_scoreSize);
	m_congratulationsText.setCharacterSize(m_congratulationsSize);

	m_returnText.setFillColor(m_returnColor);
	m_leaderboardText.setFillColor(m_leaderboardColor);
	m_bestScoreHeaderText.setFillColor(m_scoreColor);
	m_scoreHeaderText.setFillColor(m_scoreColor);
	m_congratulationsText.setFillColor(m_leaderboardColor);

	m_returnText.setString(m_returnString);
	m_leaderboardText.setString(m_leaderboardString);
	m_bestScoreHeaderText.setString(m_bestScoreString);
	m_scoreHeaderText.setString(m_scoreString);
	m_congratulationsText.setString(m_congratulationsString);


	m_returnText.setOrigin((int)(m_returnText.getLocalBounds().left + m_returnText.getGlobalBounds().width / 2.f), (int)(m_returnText.getLocalBounds().top + m_returnText.getGlobalBounds().height / 2.f));
	m_leaderboardText.setOrigin(m_leaderboardText.getLocalBounds().left + m_leaderboardText.getGlobalBounds().width / 2.f, m_leaderboardText.getLocalBounds().top + m_leaderboardText.getGlobalBounds().height / 2.f);
	m_bestScoreHeaderText.setOrigin(m_bestScoreHeaderText.getLocalBounds().left + m_bestScoreHeaderText.getGlobalBounds().width / 2.f, m_bestScoreHeaderText.getLocalBounds().top + m_bestScoreHeaderText.getGlobalBounds().height / 2.f);
	m_scoreHeaderText.setOrigin(m_scoreHeaderText.getLocalBounds().left + m_scoreHeaderText.getGlobalBounds().width / 2.f, m_scoreHeaderText.getLocalBounds().top + m_scoreHeaderText.getGlobalBounds().height / 2.f);
	m_congratulationsText.setOrigin((int)(m_congratulationsText.getLocalBounds().left + m_congratulationsText.getGlobalBounds().width / 2.f), (int)(m_congratulationsText.getLocalBounds().top + m_congratulationsText.getGlobalBounds().height / 2.f));

	m_returnText.setPosition((int)(m_returnButtonSprite.getGlobalBounds().left + m_returnButtonSprite.getGlobalBounds().width / 2.f), (int)(m_returnButtonSprite.getGlobalBounds().top + m_returnButtonSprite.getGlobalBounds().height / 2.f));
	m_leaderboardText.setPosition(m_windowSize.x / 2.f, 75.f);
	m_bestScoreHeaderText.setPosition(m_bestScoreButtonSprite.getGlobalBounds().left + m_bestScoreButtonSprite.getGlobalBounds().width / 2.f, m_bestScoreButtonSprite.getGlobalBounds().top + m_bestScoreHeaderText.getGlobalBounds().height * 2);
	m_scoreHeaderText.setPosition(m_scoreButtonSprite.getGlobalBounds().left + m_scoreButtonSprite.getGlobalBounds().width / 2.f, m_scoreButtonSprite.getGlobalBounds().top + m_scoreHeaderText.getGlobalBounds().height * 2);
	m_congratulationsText.setPosition((int)(m_windowSize.x / 2.f), (int)(m_windowSize.y / 2.f));

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
}

void LeaderboardViewGUI::initSprites()
{
	m_returnTexture = &AssetManager::GetTexture("assets/Textures/button_newgame.png");
	if (!m_returnTexture)
		printf("Couldn't load texture: assets//Textures/button_newgame.png\n");

	m_scoreTexture = &AssetManager::GetTexture("assets/Textures/button_score.png");
	if (!m_scoreTexture)
		printf("Couldn't load texture: assets//Textures/button_score.png\n");

	m_returnButtonSprite.setTexture(*m_returnTexture);
	m_bestScoreButtonSprite.setTexture(*m_scoreTexture);
	m_scoreButtonSprite.setTexture(*m_scoreTexture);

	m_returnButtonSprite.setScale((m_scale * 1.3f), m_scale);
	m_bestScoreButtonSprite.setScale(m_scale, m_scale);
	m_scoreButtonSprite.setScale(m_scale, m_scale);

	m_bestScoreButtonSprite.setPosition(sf::Vector2f(1130.f, 35.f));
	m_scoreButtonSprite.setPosition(1009.3f, 35.f);
	m_returnButtonSprite.setPosition(m_bestScoreButtonSprite.getGlobalBounds().left + (m_bestScoreButtonSprite.getGlobalBounds().width - m_returnButtonSprite.getGlobalBounds().width), m_bestScoreButtonSprite.getGlobalBounds().top + m_bestScoreButtonSprite.getGlobalBounds().height + m_returnButtonSprite.getGlobalBounds().height / 2.f);
}



// = = = = = Utility functions  = = = = = //
void LeaderboardViewGUI::center_origin(sf::Sprite& sprite)
{
	sprite.setOrigin(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2.f,
	                 sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2.f);
}

void LeaderboardViewGUI::justifyHorizontal(const sf::FloatRect& button, sf::Text& text)
{
	text.setOrigin(0.f, 0.f);
	text.setPosition(button.left + (button.width - text.getGlobalBounds().width) / 2.f, text.getPosition().y);
}



// = = = = = Constructors / Destructors  = = = = = //
LeaderboardViewGUI::LeaderboardViewGUI(sf::Vector2f windowSize) : m_windowSize(windowSize)
{
	initSprites();
	initText();
}

LeaderboardViewGUI::~LeaderboardViewGUI()
{
	if (m_leaderboard)
		delete m_leaderboard;
}



// = = = = = Update functions  = = = = = //
void LeaderboardViewGUI::update()
{
	if (cursor_clock.getElapsedTime() >= sf::seconds(0.5f)) {
		show_cursor = !show_cursor;
		cursor_clock.restart();
	}
}


// = = = = = Mutators  = = = = = //
void LeaderboardViewGUI::setMode(LeaderboardMode mode)
{
	this->mode = mode;
	if (this->mode == LeaderboardMode::VIEW) {
		m_congratulationsText.setString(m_congratulationsString);
		m_congratulationsText.setOrigin((int)(m_congratulationsText.getLocalBounds().left + m_congratulationsText.getGlobalBounds().width / 2.f), (int)(m_congratulationsText.getLocalBounds().top + m_congratulationsText.getGlobalBounds().height / 2.f));
		m_congratulationsText.setPosition((int)(m_windowSize.x / 2.f), (int)(m_windowSize.y / 2.f));
	}
}

void LeaderboardViewGUI::setScore(int score)
{
	m_score = score;

	const float old_width = m_scoreText.getGlobalBounds().width;
	m_scoreText.setString(std::to_string(m_score));
	const float new_width = m_scoreText.getGlobalBounds().width;

	if (old_width != new_width)
		m_scoreText.move((old_width - new_width) / 2.f, 0.f);
}

void LeaderboardViewGUI::setName(std::string name)
{
	this->m_congratulationsText.setString(m_congratulationsString + name);
	this->m_congratulationsText.setOrigin((int)(m_congratulationsText.getLocalBounds().left + m_congratulationsText.getGlobalBounds().width / 2.f), (int)(m_congratulationsText.getLocalBounds().top + m_congratulationsText.getGlobalBounds().height / 2.f));
	this->m_congratulationsText.setPosition((int)(m_windowSize.x / 2.f), (int)(m_windowSize.y / 2.f));
}

void LeaderboardViewGUI::setLeaderboard(std::vector<LeaderboardEntry*> entries)
{
	if (m_leaderboard)
		delete m_leaderboard;
	m_leaderboard = new Leaderboard(entries);
	m_leaderboard->setPosition(m_windowSize.x / 2.f, m_leaderboardText.getGlobalBounds().top + m_leaderboardText.getGlobalBounds().height + 30.f);
	this->m_bestScore = entries[0]->score;
	this->m_bestScoreText.setString(std::to_string(this->m_bestScore));
	this->m_bestScoreText.setOrigin(m_bestScoreText.getLocalBounds().left + m_bestScoreText.getGlobalBounds().width / 2.f, m_bestScoreText.getLocalBounds().top + m_bestScoreText.getGlobalBounds().height / 2.f);
	this->m_bestScoreText.setPosition(m_bestScoreHeaderText.getPosition().x, m_bestScoreHeaderText.getGlobalBounds().top + m_bestScoreHeaderText.getGlobalBounds().height + 15.f);
}



// = = = = = Accessors  = = = = = //
sf::FloatRect LeaderboardViewGUI::getReturnButton()
{
	return m_returnButtonSprite.getGlobalBounds();
}

sf::FloatRect LeaderboardViewGUI::getEnteredNameRect()
{
	return m_congratulationsText.getGlobalBounds();
}



// = = = = = Render functions  = = = = = //
void LeaderboardViewGUI::render(sf::RenderTarget& target)
{
	if (mode == LeaderboardMode::VIEW) {
		// Drawing buttons
		target.draw(m_returnButtonSprite);
		target.draw(m_bestScoreButtonSprite);
		target.draw(m_scoreButtonSprite);

		// Drawing text
		target.draw(m_returnText);
		target.draw(m_leaderboardText);
		target.draw(m_bestScoreHeaderText);
		target.draw(m_scoreHeaderText);

		// Drawing score
		target.draw(m_bestScoreText);
		target.draw(m_scoreText);

		if (m_leaderboard)
			m_leaderboard->render(target);
	}
	else {
		target.draw(m_congratulationsText);
	}
}
