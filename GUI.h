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
	int					score				 = 0;
	int					best_score			 = 9;
	float				scale				 = 0.25f;
	string				str_new_game		 = "New Game";
	string				str_best_score		 = "BEST";
	string				str_score			 = "SCORE";
	string				str_title			 = "2048";
	string				best_score_filename = "bestscore.txt";
	sf::Font			font;
	sf::Text			text_new_game;
	sf::Text			text_best_score_header;
	sf::Text			text_score_header;
	sf::Text			text_title;
	sf::Text			text_score;
	sf::Text			text_best_score;
	unsigned			size_new_game		 = 20;
	unsigned			size_best_score		 = 12;
	unsigned			size_score			 = 12;
	unsigned			size_title			 = 64;
	sf::Sprite			button_new_game;
	sf::Sprite			button_best_score;
	sf::Sprite			button_score;
	sf::Texture			texture_new_game;
	sf::Texture			texture_score;
	sf::Color			color_title			 = sf::Color(119, 110, 101);
	sf::Color			color_new_game		 = sf::Color(249, 246, 242);
	sf::Color			color_score			 = sf::Color(238, 228, 218);
	sf::Vector2f		window_size;
	sf::FloatRect		shape_playground;

	void initText();
	void initSprites();
	void center_origin(sf::Sprite &sprite);
	void justifyHorizontal(sf::FloatRect button, sf::Text& text);

	void loadBestScore();
	void saveBestScore();

public:
	// Constructors / Destructors
	GUI(sf::Vector2f window_size_, sf::FloatRect shape_playground_);
	virtual ~GUI();

	// Mutators
	void addScore(int value_);

	// Render GUI
	void render(sf::RenderTarget& target);
};