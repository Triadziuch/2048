#pragma once
#include "MovementManager/MovementManager.h"

class Tile {
private:
	// Static variables
	constexpr static float m_spawningTimeMax{ 0.2f }, m_gameOverTimeMax{ 0.5f };

	// Movement manager signleton instances
	MovementContainer* m_movementContainer;
	MovementManager*   m_movementManager;

	// Private variables
	sf::Sprite m_sprite;
	const float* m_scale;
	int	m_type{ 2 };

	bool m_isMoving{}, m_isMerging{}, m_isSpawning{}, m_isGameOver{};

	float m_spawningTime{}, m_gameOverTime{};

public:
	// Constructors / Destructors
	Tile(const int type, const sf::Texture* texture, const float *m_scale, const sf::Vector2f& position);
	~Tile();

	// Update functions
	void update(const float dt);

	// Functions
	void smoothMove(const sf::Vector2f& offset, const float duration);
	void startSpawning();
	void startMerging();
	void startGameOver();

	// Mutators
	void setScale(const float m_scale);
	void setIsMoving(const bool value);
	void setIsMerging(const bool value);

	// Accessors
	int getType() const;
	bool getIsMoving() const;
	bool getMerging() const;
	bool getSpawning() const;
	sf::Sprite* getSprite();

	// Rendering functions
	void render(sf::RenderTarget& target);
};