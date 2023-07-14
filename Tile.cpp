#include "Tile.h"

void Tile::center_origin()
{
	this->sprite_tile.setOrigin(this->sprite_tile.getGlobalBounds().left + this->sprite_tile.getGlobalBounds().width / 2.f,
		this->sprite_tile.getGlobalBounds().top + this->sprite_tile.getGlobalBounds().height / 2.f);
}

Tile::Tile(int type_, sf::Texture* texture_tile_, float* scale_)
{
	this->type = type_;
	this->sprite_tile.setTexture(*texture_tile_);
	this->center_origin();
	this->sprite_tile.setScale(*scale_, *scale_);
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->sprite_tile);
}
