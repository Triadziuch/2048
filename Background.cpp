#include "Background.h"

Background::Background(sf::Vector2f window_size_)
{
	// Playground initialization
	this->texture_playground.loadFromFile("Textures/playground.png");
	this->sprite_playground.setTexture(this->texture_playground);
	this->sprite_playground.setOrigin(this->sprite_playground.getPosition().x + this->sprite_playground.getGlobalBounds().width / 2.f,
									  this->sprite_playground.getPosition().y + this->sprite_playground.getGlobalBounds().height / 2.f);
	this->sprite_playground.setPosition(window_size_ / 2.f);
	const float scale = (window_size_.y - this->playground_top_bottom_space * 2) / this->sprite_playground.getGlobalBounds().height;
	this->sprite_playground.setScale(scale, scale);
}

Background::~Background()
{
	this->texture_playground.~Texture();
}

void Background::render(sf::RenderTarget& target)
{
	target.clear(this->color_background);
	target.draw(this->sprite_playground);
}
