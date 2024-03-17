#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class GUI {
private:
	int					m_score				 = 0;
	int					m_bestScore			 = 9;
	float				m_scale				 = 0.25f;
	string				m_newGameString		 = "New Game";
	string				m_bestScoreString		 = "BEST";
	string				m_scoreString			 = "SCORE";
	string				m_titleString			 = "2048";
	string				m_gameOverString		 = "GAME OVER";
	string				m_bestScoreFilename  = "bestscore.txt";
	sf::Font			m_font;
	sf::Text			m_newGameText;
	sf::Text			m_bestScoreHeaderText;
	sf::Text			m_scoreHeaderText;
	sf::Text			m_titleText;
	sf::Text			m_scoreText;
	sf::Text			m_bestScoreText;
	sf::Text			m_gameOverText;
	unsigned			m_newGameSize		 = 20;
	unsigned			m_bestScoreSize		 = 12;
	unsigned			m_scoreSize			 = 12;
	unsigned			m_titleSize			 = 64;
	unsigned			m_gameOverSize		 = 60;
	sf::Sprite			m_newGameButtonSprite;
	sf::Sprite			m_bestScoreButtonSprite;
	sf::Sprite			m_scoreButtonSprite;
	sf::Texture			m_newGameTexture;
	sf::Texture			m_scoreTexture;
	sf::Color			m_titleColor			 = sf::Color(119, 110, 101);
	sf::Color			m_newGameColor		 = sf::Color(249, 246, 242);
	sf::Color			m_scoreColor			 = sf::Color(238, 228, 218);
	sf::Color			m_gameOverColor		 = sf::Color(110, 100, 90);
	sf::Vector2f		m_windowSize;
	sf::FloatRect		m_playgroundRect;

	void initText();
	void initSprites();
	void center_origin(sf::Sprite &sprite);
	void justifyHorizontal(sf::FloatRect button, sf::Text& text);

public:
	// Constructors / Destructors
	GUI(sf::Vector2f windowSize, sf::FloatRect playgroundRect);
	virtual ~GUI();

	// Functions
	void loadBestScore();
	void saveBestScore();
	
	// Mutators
	void setScore(int value_);
	void addScore(int value_);

	// Accessors
	sf::FloatRect getNewGameButton() { return this->m_newGameButtonSprite.getGlobalBounds(); }

	// Render GUI
	void render(sf::RenderTarget& target, bool is_game_over);
};