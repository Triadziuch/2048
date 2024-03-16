#pragma once
#include "MovementManager/MovementManager.h"

class Tile {
private:
	MovementContainer* m_movementContainer;
	MovementManager*   m_movementManager;

	// Private variables
	sf::Sprite m_sprite;
	const float* m_scale;
	int	m_type = 2;

	bool m_isMoving   = false;
	bool m_isMerging  = false;
	bool m_isSpawning = false;

	float m_spawningTime = 0.f;
	float m_spawningTimeMax	= 0.2f;

public:
	// Constructors / Destructors
	Tile(const int type, const sf::Texture* texture, const float *scale, const sf::Vector2f& position);
	~Tile();

	// Update functions
	void update(const float dt);

	// Functions
	void move(sf::Vector2f offset)			{ m_sprite.move(offset); }
	void increaseType()						{ m_type *= 2; }
	void gameOver();

	void startSpawning();
	void startMerging();

	// Mutators
	void setScale(float scale)				{ m_sprite.setScale(scale, scale); }
	void setTexture(sf::Texture* texture)   { m_sprite.setTexture(*texture); }
	void setPosition(sf::Vector2f pos)		{ m_sprite.setPosition(pos); }
	void setType(int type)					{ m_type = type; }
	void setIsMoving(bool value)			{ m_isMoving = value; }
	void setMerging(bool value)				{ m_isMerging = value; }
	

	// Accessors
	const int getType() const;
	const bool getIsMoving() const;
	const bool getMerging() const;
	const bool getSpawning() const;
	sf::Sprite* getSprite();

	// Rendering functions
	void render(sf::RenderTarget& target);
};