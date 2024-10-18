#pragma once
#include "TileModel.h"

// Constructors / Destructors
TileModel::TileModel(const int type) : m_type(type) {}

TileModel::~TileModel()
{
}

// Update functions
void TileModel::update(const float dt)
{
	/*if (m_isSpawning) {
		m_spawningTime += dt;

		if (m_spawningTime >= m_spawningTimeMax) {
			m_isSpawning = false;
			m_movementManager->unlinkScalingRoutine(&m_sprite, "TILE_SPAWNING");
			m_spawningTime = m_spawningTimeMax;
			m_sprite.setColor(sf::Color(255, 255, 255, 255));
		}
		else
			m_sprite.setColor(sf::Color(255, 255, 255, 255 * m_spawningTime / m_spawningTimeMax));
	}*/

	//if (m_isGameOver) {
	//	if (m_gameOverTime < m_gameOverTimeMax) {
	//		m_gameOverTime += dt;
	//		m_sprite.setColor(sf::Color(250, 248, 239, 255 - (95 * m_gameOverTime / m_gameOverTimeMax)));
	//	}
	//	else {
	//		//m_sprite.setColor(sf::Color(250, 248, 239, 160));
	//		m_isGameOver = false;
	//	}
	//}
}

void TileModel::startSpawning()
{
	//m_spawningTime = 0.f;
	m_isSpawning = true;
	//m_movementManager->linkScalingRoutine(m_sprite, "TILE_SPAWNING");
	//m_movementManager->startScalingRoutine(m_sprite, "TILE_SPAWNING");
}

void TileModel::startMerging()
{
	//m_movementManager->linkScalingRoutine(m_sprite, "TILE_MERGING");
	//m_movementManager->startScalingRoutine(m_sprite, "TILE_MERGING");
}

void TileModel::startGameOver()
{
	m_isSpawning = false;
	m_isMerging = false;
	m_isGameOver = true;
}

void TileModel::startWin()
{
	m_isSpawning = false;
	m_isMerging = false;
	m_isWin = true;
}

void TileModel::stopWin()
{
	m_isWin = false;
}

// Mutators
void TileModel::setIsMoving(bool value)
{
	m_isMoving = value;
}

void TileModel::setIsMerging(bool value)
{
	m_isMerging = value;
}

// Accessors
int TileModel::getType() const
{
	return m_type;
}

bool TileModel::getIsMoving() const
{
	return m_isMoving;
}

bool TileModel::getMerging() const
{
	return m_isMerging;
}

bool TileModel::getSpawning() const
{
	return m_isSpawning;
}