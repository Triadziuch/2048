#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <sstream>
#include <fstream>

class GUI {
private:
	int m_score{}, m_bestScore{};
	float m_scale{ 0.25f };

	float m_gameOverTime{};
	const float m_gameOverTimeMax{ 0.5f };

	bool m_isGameOver{};

	const std::string m_newGameString{ "New Game" }, m_bestScoreString{ "BEST" }, m_scoreString{ "SCORE" },
					  m_titleString{ "2048" }, m_gameOverString{ "Game over!" };
	const std::string m_bestScoreFilename{ "best_score.txt" };

	sf::Font m_font;
	sf::Text m_newGameText, m_bestScoreHeaderText, m_scoreHeaderText,
			 m_titleText, m_scoreText, m_bestScoreText, m_gameOverText;

	const unsigned m_newGameSize{ 20u }, m_bestScoreSize{ 12u }, m_scoreSize{ 12u }, m_titleSize{ 64u }, m_gameOverSize{ 60u };
	sf::Sprite m_newGameButtonSprite, m_bestScoreButtonSprite, m_scoreButtonSprite;

	sf::Texture m_newGameTexture, m_scoreTexture;
	sf::Color m_titleColor{ 119, 110, 101 }, m_newGameColor{ 249, 246, 242 }, m_scoreColor{ 238, 228, 218 }, m_gameOverColor{ 110, 100, 90 };

	sf::Vector2f m_windowSize;
	sf::FloatRect m_playgroundRect;

	void initText();
	void initSprites();
	void center_origin(sf::Sprite &sprite);
	void justifyHorizontal(const sf::FloatRect& button, sf::Text& text);

public:
	// Constructors / Destructors
	GUI(sf::Vector2f windowSize, sf::FloatRect playgroundRect);
	virtual ~GUI();

	// Functions
	void loadBestScore();
	void saveBestScore();

	void updateGameOver(const float dt);

	void startGameOver();
	void stopGameOver();
	
	// Mutators
	void setScore(int value_);
	void addScore(int value_);

	// Accessors
	sf::FloatRect getNewGameButton() { return m_newGameButtonSprite.getGlobalBounds(); }

	// Render GUI
	void render(sf::RenderTarget& target);
};