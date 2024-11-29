#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include "src/AssetManager.h"
#include "Leaderboard.h"
#include "LeaderboardMode.h"

class LeaderboardViewGUI {
private:
	// Private variables
	int m_score{}, m_bestScore{};
	float m_scale{ 0.25f };

	const std::string m_returnString{ "Return to game" }, m_leaderboardString{ "Leaderboard" }, m_bestScoreString{ "BEST" }, m_scoreString{ "SCORE" };
	const std::string m_bestScoreFilename{ "assets/best_score.txt" };
	const std::string m_congratulationsString{ "Congratulations, " };
	sf::Font* m_font;
	sf::Text m_returnText, m_leaderboardText, m_bestScoreHeaderText, m_scoreHeaderText, m_scoreText, m_bestScoreText, m_congratulationsText;

	const unsigned m_returnSize{ 20u }, m_bestScoreSize{ 12u }, m_scoreSize{ 12u }, m_leaderboardSize{ 64u }, m_congratulationsSize{ 64u };
	sf::Sprite m_returnButtonSprite, m_bestScoreButtonSprite, m_scoreButtonSprite;

	sf::Texture* m_returnTexture, * m_scoreTexture;
	sf::Color m_leaderboardColor{ 119, 110, 101 }, m_returnColor{ 249, 246, 242 }, m_scoreColor{ 238, 228, 218 };

	sf::Vector2f m_windowSize;

	Leaderboard* m_leaderboard;
	LeaderboardMode mode;

	sf::Clock cursor_clock;
	bool show_cursor = false;

	// Initialization functions
	void initText();
	void initSprites();

	// Utility functions
	void center_origin(sf::Sprite& sprite);
	void justifyHorizontal(const sf::FloatRect& button, sf::Text& text);

public:
	// Constructors / Destructors
	LeaderboardViewGUI(sf::Vector2f windowSize);
	~LeaderboardViewGUI();

	// Update functions
	void update();

	// Mutators
	void setMode(LeaderboardMode mode);
	void setScore(int value);
	void setName(std::string name);
	void setLeaderboard(std::vector<LeaderboardEntry*> entries);

	// Accessors
	sf::FloatRect getReturnButton();
	sf::FloatRect getEnteredNameRect();

	// Render functions
	void render(sf::RenderTarget& target);
};