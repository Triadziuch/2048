#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include "src/AssetManager.h"

class LeaderboardViewGUI {
private:
	int m_score{}, m_bestScore{};
	float m_scale{ 0.25f };

	float m_gameOverTime{};
	const float m_gameOverTimeMax{ 0.5f };

	bool m_isGameOver{};

	const std::string m_returnString{ "Return to game" }, m_leaderboardString{ "Leaderboard" }, m_bestScoreString{ "BEST" }, m_scoreString{ "SCORE" };
	const std::string m_bestScoreFilename{ "assets/best_score.txt" };

	sf::Font* m_font;
	sf::Text m_returnText, m_leaderboardText, m_bestScoreHeaderText, m_scoreHeaderText, m_scoreText, m_bestScoreText;

	const unsigned m_returnSize{ 20u }, m_bestScoreSize{ 12u }, m_scoreSize{ 12u }, m_leaderboardSize{ 64u };
	sf::Sprite m_returnButtonSprite, m_bestScoreButtonSprite, m_scoreButtonSprite;

	sf::Texture* m_returnTexture, * m_scoreTexture;
	sf::Color m_leaderboardColor{ 119, 110, 101 }, m_returnColor{ 249, 246, 242 }, m_scoreColor{ 238, 228, 218 };

	sf::Vector2f m_windowSize;

	void initText();
	void initSprites();
	void center_origin(sf::Sprite& sprite);
	void justifyHorizontal(const sf::FloatRect& button, sf::Text& text);

public:
	// Constructors / Destructors
	LeaderboardViewGUI(sf::Vector2f windowSize);
	virtual ~LeaderboardViewGUI();


	bool update(const float dt);

	// Mutators
	void setScore(int value);
	void setBestScore(int value);
	void addScore(int value);

	// Accessors
	sf::FloatRect getReturnButton() { return m_returnButtonSprite.getGlobalBounds(); }

	// Render GUI
	void render(sf::RenderTarget& target);
};