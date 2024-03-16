#include "GUI.h"

void GUI::center_origin(sf::Sprite& sprite)
{
	sprite.setOrigin(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2.f,
		sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2.f);
}

void GUI::justifyHorizontal(sf::FloatRect button, sf::Text& text)
{
	text.setOrigin(0.f, 0.f);
	text.setPosition(button.left + (button.width - text.getGlobalBounds().width) / 2.f, text.getPosition().y);
}

void GUI::saveBestScore()
{
	ofstream file;
	file.open(best_score_filename, ios::out);

	if (file.good())
		file << to_string(best_score);
}

void GUI::loadBestScore()
{
	fstream file;
	file.open(best_score_filename);

	if (file.good()) {
		string str_best_score;
		stringstream ss_best_score;
		int int_best_score;
		file >> str_best_score;
		ss_best_score << str_best_score;
		ss_best_score >> int_best_score;
		best_score = int_best_score;
	}
}

GUI::GUI(sf::Vector2f window_size_, sf::FloatRect shape_playground_)
{
	window_size = window_size_;
	shape_playground = shape_playground_;

	loadBestScore();
	initSprites();
	initText();
}

void GUI::setScore(int value_)
{
	score = value_;

	float old_width = text_score.getGlobalBounds().width;
	text_score.setString(to_string(score));
	float new_width = text_score.getGlobalBounds().width;

	if (old_width != new_width)
		text_score.move((old_width - new_width) / 2.f, 0.f);

	if (best_score < score) {
		sf::Vector2f old_pos = text_best_score.getPosition();
		best_score = score;
		text_best_score = text_score;
		text_best_score.setPosition(old_pos);

		if (old_width != new_width)
			text_best_score.move((old_width - new_width) / 2.f, 0.f);
	}
}

GUI::~GUI()
{
	saveBestScore();
}

void GUI::initText()
{
	if (!font.loadFromFile("Fonts/ClearSans-Bold.ttf"))
		cout << "Couldn't load font: /Fonts/ClearSans-Bold.ttf" << endl;

	text_new_game.setFont(font);
	text_best_score_header.setFont(font);
	text_score_header.setFont(font);
	text_title.setFont(font);
	text_game_over.setFont(font);

	text_new_game.setCharacterSize(size_new_game);
	text_best_score_header.setCharacterSize(size_best_score);
	text_score_header.setCharacterSize(size_score);
	text_title.setCharacterSize(size_title);
	text_game_over.setCharacterSize(size_game_over);

	text_new_game.setFillColor(sf::Color::White);
	text_best_score_header.setFillColor(color_score);
	text_score_header.setFillColor(color_score);
	text_title.setFillColor(color_title);
	text_game_over.setFillColor(color_game_over);

	text_new_game.setString(str_new_game);
	text_best_score_header.setString(str_best_score);
	text_score_header.setString(str_score);
	text_title.setString(str_title);
	text_game_over.setString(str_game_over);

	text_game_over.setOutlineThickness(1.f);
	
	text_game_over.setOutlineColor(color_title);

	text_new_game.setOrigin(text_new_game.getLocalBounds().left + text_new_game.getGlobalBounds().width / 2.f, text_new_game.getLocalBounds().top + text_new_game.getGlobalBounds().height / 2.f);
	text_best_score_header.setOrigin(text_best_score_header.getLocalBounds().left + text_best_score_header.getGlobalBounds().width / 2.f, text_best_score_header.getLocalBounds().top + text_best_score_header.getGlobalBounds().height / 2.f);
	text_score_header.setOrigin(text_score_header.getLocalBounds().left + text_score_header.getGlobalBounds().width / 2.f, text_score_header.getLocalBounds().top + text_score_header.getGlobalBounds().height / 2.f);
	text_game_over.setOrigin(text_game_over.getLocalBounds().left + text_game_over.getGlobalBounds().width / 2.f, text_game_over.getLocalBounds().top + text_game_over.getGlobalBounds().height / 2.f);

	text_new_game.setPosition(button_new_game.getGlobalBounds().left + button_new_game.getGlobalBounds().width / 2.f, button_new_game.getGlobalBounds().top + button_new_game.getGlobalBounds().height / 2.f);
	text_best_score_header.setPosition(button_best_score.getGlobalBounds().left + button_best_score.getGlobalBounds().width / 2.f, button_best_score.getGlobalBounds().top + text_best_score_header.getGlobalBounds().height * 2);
	text_score_header.setPosition(button_score.getGlobalBounds().left + button_score.getGlobalBounds().width / 2.f, button_score.getGlobalBounds().top + text_score_header.getGlobalBounds().height * 2);
	text_title.setPosition(shape_playground.left, shape_playground.top - text_title.getGlobalBounds().height * 1.75f);
	text_game_over.setPosition(shape_playground.left + shape_playground.width / 2.f, shape_playground.top + shape_playground.height / 2.f);

	text_score.setFont(font);
	text_best_score.setFont(font);

	text_score.setCharacterSize(20);
	text_best_score.setCharacterSize(20);

	text_score.setFillColor(sf::Color::White);
	text_best_score.setFillColor(sf::Color::White);

	text_score.setString(to_string(score));
	text_best_score.setString(to_string(best_score));

	text_score.setOrigin(text_score.getLocalBounds().left + text_score.getGlobalBounds().width / 2.f, text_score.getLocalBounds().top + text_score.getGlobalBounds().height / 2.f);
	text_best_score.setOrigin(text_best_score.getLocalBounds().left + text_best_score.getGlobalBounds().width / 2.f, text_best_score.getLocalBounds().top + text_best_score.getGlobalBounds().height / 2.f);

	text_score.setPosition(text_score_header.getPosition().x, text_score_header.getGlobalBounds().top + text_score_header.getGlobalBounds().height + 15.f);
	text_best_score.setPosition(text_best_score_header.getPosition().x, text_best_score_header.getGlobalBounds().top + text_best_score_header.getGlobalBounds().height + 15.f);
}

void GUI::initSprites()
{
	if (!texture_new_game.loadFromFile("Textures/button_newgame.png"))
		cout << "Couldn't load texture: /Textures/button_newgame.png" << endl;
	if (!texture_score.loadFromFile("Textures/button_score.png"))
		cout << "Couldn't load texture: /Textures/button_score.png" << endl;

	button_new_game.setTexture(texture_new_game);
	button_best_score.setTexture(texture_score);
	button_score.setTexture(texture_score);

	button_new_game.setScale(scale, scale);
	button_best_score.setScale(scale, scale);
	button_score.setScale(scale, scale);

	button_new_game.setPosition(window_size.x - button_new_game.getGlobalBounds().width * 1.25f, shape_playground.top + button_new_game.getGlobalBounds().height / 4.f );
	button_best_score.setPosition(button_new_game.getPosition().x + button_new_game.getGlobalBounds().width - button_best_score.getGlobalBounds().width, shape_playground.top - button_new_game.getGlobalBounds().height / 4.f - button_best_score.getGlobalBounds().height);
	button_score.setPosition(button_best_score.getPosition().x - button_score.getGlobalBounds().width - 10.f, button_best_score.getPosition().y);
}


void GUI::addScore(int value_) {
	score += value_;
	
	float old_width = text_score.getGlobalBounds().width;
	text_score.setString(to_string(score));
	float new_width = text_score.getGlobalBounds().width;
	
	if (old_width != new_width)
		text_score.move((old_width - new_width) / 2.f, 0.f);

	if (best_score < score) {
		best_score = score;
		text_best_score.setString(to_string(best_score));
		justifyHorizontal(button_best_score.getGlobalBounds(), text_best_score);
		text_best_score.setPosition(text_best_score.getPosition().x, text_score.getPosition().y - text_score.getOrigin().y);
	}
}

void GUI::render(sf::RenderTarget& target, bool is_game_over)
{
	// Drawing buttons
	target.draw(button_new_game);
	target.draw(button_best_score);
	target.draw(button_score);

	// Drawing text
	target.draw(text_new_game);
	target.draw(text_best_score_header);
	target.draw(text_score_header);
	target.draw(text_title);

	// Drawing score
	target.draw(text_best_score);
	target.draw(text_score);

	// Drawing game over
	if (is_game_over)
		target.draw(text_game_over);
}
