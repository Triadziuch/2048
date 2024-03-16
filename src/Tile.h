#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>
#include <utility>

class Tile {
private:
	// Private variables
	sf::Sprite m_sprite;
	float* m_scale;
	int	m_type = 2;

	bool m_isMoving   = false;
	bool m_isMerging  = false;
	bool m_isSpawning = true;

	float m_spawningTime = 0.f;
	float m_spawningTimeMax	= 0.2f;

	// Private functions
	void center_origin();
public:
	// Constructors / Destructors
	Tile() {}
	Tile(int type, sf::Texture* texture, float *scale);
	virtual ~Tile() {};

	// Update functions
	bool updateOpacity(const float& dt);

	// Functions
	void move(sf::Vector2f offset)			{ m_sprite.move(offset); }
	void increaseType()						{ m_type *= 2; }
	void gameOver();

	// Mutators
	void setScale(float scale)				{ m_sprite.setScale(scale, scale); }
	void setTexture(sf::Texture* texture)   { m_sprite.setTexture(*texture); }
	void setPosition(sf::Vector2f pos)		{ m_sprite.setPosition(pos); }
	void setType(int type)					{ m_type = type; }
	void setIsMoving(bool value)			{ m_isMoving = value; }
	void setMerging(bool value)				{ m_isMerging = value; }
	

	// Accessors
	const int getType()      const { return m_type; }
	const bool getIsMoving() const { return m_isMoving; }
	const bool getMerging()  const { return m_isMerging; }
	const bool getSpawning() const { return m_isSpawning; }
	sf::Sprite* getSprite()		   { return &m_sprite; }

	// Rendering tile
	void render(sf::RenderTarget& target);
};