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
	file.open(this->best_score_filename, ios::out);

	if (file.good())
		file << to_string(this->best_score);
}

void GUI::loadBestScore()
{
	fstream file;
	file.open(this->best_score_filename);

	if (file.good()) {
		string str_best_score;
		stringstream ss_best_score;
		int int_best_score;
		file >> str_best_score;
		ss_best_score << str_best_score;
		ss_best_score >> int_best_score;
		this->best_score = int_best_score;
	}
}

GUI::GUI(sf::Vector2f window_size_, sf::FloatRect shape_playground_)
{
	this->window_size = window_size_;
	this->shape_playground = shape_playground_;

	this->loadBestScore();
	this->initSprites();
	this->initText();
}

void GUI::setScore(int value_)
{
	this->score = value_;

	float old_width = this->text_score.getGlobalBounds().width;
	this->text_score.setString(to_string(this->score));
	float new_width = this->text_score.getGlobalBounds().width;

	if (old_width != new_width)
		this->text_score.move((old_width - new_width) / 2.f, 0.f);

	if (this->best_score < this->score) {
		sf::Vector2f old_pos = this->text_best_score.getPosition();
		this->best_score = this->score;
		this->text_best_score = this->text_score;
		this->text_best_score.setPosition(old_pos);

		if (old_width != new_width)
			this->text_best_score.move((old_width - new_width) / 2.f, 0.f);
	}
}

GUI::~GUI()
{
	this->saveBestScore();
}

void GUI::initText()
{
	if (!this->font.loadFromFile("Fonts/ClearSans-Bold.ttf"))
		cout << "Couldn't load font: /Fonts/ClearSans-Bold.ttf" << endl;

	this->text_new_game.setFont(this->font);
	this->text_best_score_header.setFont(this->font);
	this->text_score_header.setFont(this->font);
	this->text_title.setFont(this->font);

	this->text_new_game.setCharacterSize(this->size_new_game);
	this->text_best_score_header.setCharacterSize(this->size_best_score);
	this->text_score_header.setCharacterSize(this->size_score);
	this->text_title.setCharacterSize(this->size_title);

	this->text_new_game.setFillColor(sf::Color::White);
	this->text_best_score_header.setFillColor(this->color_score);
	this->text_score_header.setFillColor(this->color_score);
	this->text_title.setFillColor(this->color_title);

	this->text_new_game.setString(this->str_new_game);
	this->text_best_score_header.setString(this->str_best_score);
	this->text_score_header.setString(this->str_score);
	this->text_title.setString(this->str_title);

	this->text_new_game.setOrigin(this->text_new_game.getLocalBounds().left + this->text_new_game.getGlobalBounds().width / 2.f, this->text_new_game.getLocalBounds().top + this->text_new_game.getGlobalBounds().height / 2.f);
	this->text_best_score_header.setOrigin(this->text_best_score_header.getLocalBounds().left + this->text_best_score_header.getGlobalBounds().width / 2.f, this->text_best_score_header.getLocalBounds().top + this->text_best_score_header.getGlobalBounds().height / 2.f);
	this->text_score_header.setOrigin(this->text_score_header.getLocalBounds().left + this->text_score_header.getGlobalBounds().width / 2.f, this->text_score_header.getLocalBounds().top + this->text_score_header.getGlobalBounds().height / 2.f);

	this->text_new_game.setPosition(this->button_new_game.getGlobalBounds().left + this->button_new_game.getGlobalBounds().width / 2.f, this->button_new_game.getGlobalBounds().top + this->button_new_game.getGlobalBounds().height / 2.f);
	this->text_best_score_header.setPosition(this->button_best_score.getGlobalBounds().left + this->button_best_score.getGlobalBounds().width / 2.f, this->button_best_score.getGlobalBounds().top + this->text_best_score_header.getGlobalBounds().height * 2);
	this->text_score_header.setPosition(this->button_score.getGlobalBounds().left + this->button_score.getGlobalBounds().width / 2.f, this->button_score.getGlobalBounds().top + this->text_score_header.getGlobalBounds().height * 2);
	this->text_title.setPosition(this->shape_playground.left, this->shape_playground.top - this->text_title.getGlobalBounds().height * 1.75f);



	this->text_score.setFont(this->font);
	this->text_best_score.setFont(this->font);

	this->text_score.setCharacterSize(20);
	this->text_best_score.setCharacterSize(20);

	this->text_score.setFillColor(sf::Color::White);
	this->text_best_score.setFillColor(sf::Color::White);

	this->text_score.setString(to_string(this->score));
	this->text_best_score.setString(to_string(this->best_score));

	this->text_score.setOrigin(this->text_score.getLocalBounds().left + this->text_score.getGlobalBounds().width / 2.f, this->text_score.getLocalBounds().top + this->text_score.getGlobalBounds().height / 2.f);
	this->text_best_score.setOrigin(this->text_best_score.getLocalBounds().left + this->text_best_score.getGlobalBounds().width / 2.f, this->text_best_score.getLocalBounds().top + this->text_best_score.getGlobalBounds().height / 2.f);

	this->text_score.setPosition(this->text_score_header.getPosition().x, this->text_score_header.getGlobalBounds().top + this->text_score_header.getGlobalBounds().height + 15.f);
	this->text_best_score.setPosition(this->text_best_score_header.getPosition().x, this->text_best_score_header.getGlobalBounds().top + this->text_best_score_header.getGlobalBounds().height + 15.f);
}

void GUI::initSprites()
{
	if (!this->texture_new_game.loadFromFile("Textures/button_newgame.png"))
		cout << "Couldn't load texture: /Textures/button_newgame.png" << endl;
	if (!this->texture_score.loadFromFile("Textures/button_score.png"))
		cout << "Couldn't load texture: /Textures/button_score.png" << endl;

	this->button_new_game.setTexture(this->texture_new_game);
	this->button_best_score.setTexture(this->texture_score);
	this->button_score.setTexture(this->texture_score);

	this->button_new_game.setScale(this->scale, this->scale);
	this->button_best_score.setScale(this->scale, this->scale);
	this->button_score.setScale(this->scale, this->scale);

	this->button_new_game.setPosition(this->window_size.x - this->button_new_game.getGlobalBounds().width * 1.25f, this->shape_playground.top + this->button_new_game.getGlobalBounds().height / 4.f );
	this->button_best_score.setPosition(this->button_new_game.getPosition().x + this->button_new_game.getGlobalBounds().width - this->button_best_score.getGlobalBounds().width, this->shape_playground.top - this->button_new_game.getGlobalBounds().height / 4.f - this->button_best_score.getGlobalBounds().height);
	this->button_score.setPosition(this->button_best_score.getPosition().x - this->button_score.getGlobalBounds().width - 10.f, this->button_best_score.getPosition().y);
}


void GUI::addScore(int value_) {
	this->score += value_;
	
	float old_width = this->text_score.getGlobalBounds().width;
	this->text_score.setString(to_string(this->score));
	float new_width = this->text_score.getGlobalBounds().width;
	
	if (old_width != new_width)
		this->text_score.move((old_width - new_width) / 2.f, 0.f);

	if (this->best_score < this->score) {
		this->best_score = this->score;
		this->text_best_score.setString(to_string(this->best_score));
		this->justifyHorizontal(this->button_best_score.getGlobalBounds(), this->text_best_score);
		this->text_best_score.setPosition(this->text_best_score.getPosition().x, this->text_score.getPosition().y - this->text_score.getOrigin().y);
	}
}

void GUI::render(sf::RenderTarget& target)
{
	// Drawing buttons
	target.draw(this->button_new_game);
	target.draw(this->button_best_score);
	target.draw(this->button_score);

	// Drawing text
	target.draw(this->text_new_game);
	target.draw(this->text_best_score_header);
	target.draw(this->text_score_header);
	target.draw(this->text_title);

	// Drawing score
	target.draw(this->text_best_score);
	target.draw(this->text_score);
}
