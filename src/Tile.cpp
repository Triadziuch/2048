#pragma once
#include "Tile.h"

// Constructors / Destructors
Tile::Tile(const int type, const sf::Texture* texture, const float* scale, const sf::Vector2f& position) : m_type(type), m_scale(scale)
{
	m_movementContainer = MovementContainer::getInstance();
	m_movementManager = MovementManager::getInstance();

	m_sprite.setTexture(*texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width / 2.f,
		               m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height / 2.f);
	m_sprite.setScale(*m_scale, *m_scale);
	m_sprite.setPosition(position);
}

Tile::~Tile()
{
	m_movementManager->unlinkScalingRoutine(&m_sprite, "TILE_SPAWNING");
	m_movementManager->unlinkScalingRoutine(&m_sprite, "TILE_MERGING");
	m_scale = nullptr;
}

// Update functions
void Tile::update(const float dt)
{
	if (m_isSpawning) {
		m_spawningTime += dt;

		if (m_spawningTime >= m_spawningTimeMax) {
			m_isSpawning = false;
			m_movementManager->unlinkScalingRoutine(&m_sprite, "TILE_SPAWNING");
			m_spawningTime = m_spawningTimeMax;
			m_sprite.setColor(sf::Color(255, 255, 255, 255));
		}
		else
			m_sprite.setColor(sf::Color(255, 255, 255, 255 * m_spawningTime / m_spawningTimeMax));
	}
}

void Tile::gameOver()
{
	m_sprite.setColor(sf::Color(250, 248, 239, 160));
}

void Tile::startSpawning()
{
	m_spawningTime = 0.f;
	m_isSpawning = true;
	m_movementManager->linkScalingRoutine(m_sprite, "TILE_SPAWNING");
	m_movementManager->startScalingRoutine(m_sprite, "TILE_SPAWNING");
}

void Tile::startMerging()
{
	m_movementManager->linkScalingRoutine(m_sprite, "TILE_MERGING");
	m_movementManager->startScalingRoutine(m_sprite, "TILE_MERGING");
}

// Accessors
const int Tile::getType() const
{
	return m_type;
}

const bool Tile::getIsMoving() const
{
	return m_isMoving;
}

const bool Tile::getMerging() const
{
	return m_isMerging;
}

const bool Tile::getSpawning() const
{
	return m_isSpawning;
}

sf::Sprite* Tile::getSprite()
{
	return &m_sprite;
}

// Rendering functions
void Tile::render(sf::RenderTarget& target)
{
	target.draw(m_sprite);
}
