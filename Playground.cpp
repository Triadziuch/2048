#include "Playground.h"

Playground::Playground(sf::Vector2f window_size_)
{
	// Playground initialization
	this->texture_playground.loadFromFile("Textures/playground.png");
	this->sprite_playground.setTexture(this->texture_playground);
	this->sprite_playground.setOrigin(this->sprite_playground.getPosition().x + this->sprite_playground.getGlobalBounds().width / 2.f,
									  this->sprite_playground.getPosition().y + this->sprite_playground.getGlobalBounds().height / 2.f);
	this->sprite_playground.setPosition(window_size_ / 2.f);
	this->scale = (window_size_.y - this->playground_top_bottom_space * 2) / this->sprite_playground.getGlobalBounds().height;
	this->sprite_playground.setScale(this->scale, this->scale);

	this->inner_edge_width	*= this->scale;
	this->outer_edge_width	*= this->scale;
	this->tile_width		*= this->scale;

	sf::Vector2f playground_pos = this->sprite_playground.getPosition();
	playground_pos.x -= this->sprite_playground.getLocalBounds().width / 4.f;
	playground_pos.y -= this->sprite_playground.getLocalBounds().height / 4.f;
	this->matrix = new TileMatrix(&this->scale, &this->outer_edge_width, &this->inner_edge_width, &this->tile_width, playground_pos);
	this->matrix->addTile(0, 0, 2);
	this->matrix->addTile(1, 1, 4);
	this->matrix->addTile(2, 2, 8);
	this->matrix->addTile(3, 1, 4);
	this->matrix->addTile(1, 2, 16);
	this->matrix->addTile(0, 3, 2);
	this->matrix->addTile(3, 3, 16);

	this->gui = new GUI(window_size_, this->sprite_playground.getGlobalBounds());
}

Playground::~Playground()
{
	this->texture_playground.~Texture();
}

void Playground::update(float dt)
{
	this->matrix->update(dt);
	this->updateScore();
}

void Playground::updateScore()
{
	int added_score = this->matrix->getAddedScore();
	this->matrix->setAddedScore(0);

	if (added_score != 0) {
		this->score += added_score;
		this->gui->addScore(added_score);
	}
}

void Playground::move(char direction_)
{
	if (direction_ == 'U')
		this->matrix->moveUp();
	else if (direction_ == 'D')
		this->matrix->moveDown();
	else if (direction_ == 'L')
		this->matrix->moveLeft();
	else if (direction_ == 'R')
		this->matrix->moveRight();
}

void Playground::render(sf::RenderTarget& target)
{
	target.clear(this->color_background);
	target.draw(this->sprite_playground);
	this->matrix->render(target);
	this->gui->render(target);
}
