#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>
#include <utility>

using namespace std;

struct Tile {
private:
	sf::Sprite		sprite_tile;
	float* scale;
	int				type			= 2;
	bool			moving			= false;
	bool			merging			= false;

	bool			spawning		= true;
	float			spawning_time	= 0.f;
	float			spawning_time_max	= 0.1f;

	void center_origin();
public:
	// Constructors / Destructors
	Tile() {}
	Tile(int type_, sf::Texture* texture_tile_, float *scale_);
	virtual ~Tile() {};

	// Update functions
	void update(const float& dt);

	// Functions
	void move(sf::Vector2f value_)			{ this->sprite_tile.move(value_); }
	void increaseType()						{ this->type *= 2; }
	void gameOver();

	// Mutators
	void setScale(float scale_)				{ this->sprite_tile.setScale(scale_, scale_); }
	void setTexture(sf::Texture* texture_)  { this->sprite_tile.setTexture(*texture_); }
	void setPosition(sf::Vector2f pos_)		{ this->sprite_tile.setPosition(pos_); }
	void setType(int type_)					{ this->type = type_; }
	void setIsMoving(bool value_)			{ this->moving = value_; }
	void setMerging(bool value_)			{ this->merging = value_; }
	

	// Accessors
	int getType()						  { return this->type; }
	const bool& getIsMoving()		const { return this->moving; }
	const bool& getMerging()		const { return this->merging; }
	const bool& getSpawning()		const { return this->spawning; }
	sf::Sprite* getSprite()				{ return &this->sprite_tile; }

	// Rendering tile
	void render(sf::RenderTarget& target);
};