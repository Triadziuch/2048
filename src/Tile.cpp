#include "Tile.h"

void Tile::center_origin()
{
	this->sprite_tile.setOrigin(this->sprite_tile.getGlobalBounds().left + this->sprite_tile.getGlobalBounds().width / 2.f,
		this->sprite_tile.getGlobalBounds().top + this->sprite_tile.getGlobalBounds().height / 2.f);
}

Tile::Tile(int type_, sf::Texture* texture_tile_, float* scale_)
{
	this->type = type_;
	this->scale = scale_;
	this->sprite_tile.setTexture(*texture_tile_);
	this->center_origin();
	this->sprite_tile.setScale(*this->scale, *this->scale);
}

void Tile::update(const float& dt)
{
	if (this->spawning){
		this->spawning_time += dt;
		if (this->spawning_time >= this->spawning_time_max){
			this->spawning = false;
			this->spawning_time = this->spawning_time_max;
			this->sprite_tile.setScale(*this->scale, *this->scale);
			this->sprite_tile.setColor(sf::Color(255, 255, 255, 255));
		}
		else{
			this->sprite_tile.setScale(*this->scale * this->spawning_time / this->spawning_time_max, *this->scale * this->spawning_time / this->spawning_time_max);
			this->sprite_tile.setColor(sf::Color(255, 255, 255, 255 * this->spawning_time / this->spawning_time_max));
			//this->sprite_tile.setColor(sf::Color(250, 248, 239, 160 * this->spawning_time / this->spawning_time_max));
		}
	}
}

void Tile::gameOver()
{
	this->sprite_tile.setColor(sf::Color(250, 248, 239, 160));
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->sprite_tile);
}
