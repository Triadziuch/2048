#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include "src/AssetManager.h"

class GameViewGUI {
private:
	int m_score{}, m_bestScore{};
	float m_scale{ 0.25f };

	float m_gameOverTime{};
	const float m_gameOverTimeMax{ 0.5f };

	bool m_isGameOver{};

	const std::string m_newGameString{ "New Game" }, m_leaderboardString{ "Leaderboard" }, m_bestScoreString{ "BEST" }, m_scoreString{ "SCORE" },
		m_titleString{ "2048" }, m_gameOverString{ "Game over!" }, m_gameOverPressKeyString{ "Press any key to continue..." };
	const std::string m_bestScoreFilename{ "assets/best_score.txt" };

	sf::Font* m_font;
	sf::Text m_newGameText, m_leaderboardText, m_bestScoreHeaderText, m_scoreHeaderText,
		m_titleText, m_scoreText, m_bestScoreText, m_gameOverText, m_gameOverPressKeyText;

	const unsigned m_newGameSize{ 20u }, m_bestScoreSize{ 12u }, m_scoreSize{ 12u }, m_titleSize{ 64u }, m_gameOverSize{ 60u };
	sf::Sprite m_newGameButtonSprite, m_leaderboardButtonSprite, m_bestScoreButtonSprite, m_scoreButtonSprite;

	sf::Texture* m_newGameTexture, * m_scoreTexture;
	sf::Color m_titleColor{ 119, 110, 101 }, m_newGameColor{ 249, 246, 242 }, m_scoreColor{ 238, 228, 218 }, m_gameOverColor{ 110, 100, 90 };

	sf::Vector2f m_windowSize;
	sf::FloatRect m_playgroundRect;

	void initText();
	void initSprites();
	void center_origin(sf::Sprite& sprite);
	void justifyHorizontal(const sf::FloatRect& button, sf::Text& text);

public:
	// Constructors / Destructors
	GameViewGUI(sf::Vector2f windowSize, sf::FloatRect playgroundRect);
	virtual ~GameViewGUI();


	bool updateGameOver(const float dt);

	void startGameOver();
	void stopGameOver();

	// Mutators
	void setScore(int value);
	void setBestScore(int value);
	void addScore(int value);

	// Accessors
	sf::FloatRect getNewGameButton() { return m_newGameButtonSprite.getGlobalBounds(); }
	sf::FloatRect getLeaderboardButton() { return m_leaderboardButtonSprite.getGlobalBounds(); }

	// Render GUI
	void render(sf::RenderTarget& target);
};