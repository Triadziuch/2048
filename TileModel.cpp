#pragma once
#include "TileModel.h"

// Constructors / Destructors
TileModel::TileModel(const int type) : m_type(type) {}

TileModel::~TileModel()
{
}

void TileModel::startSpawning()
{
	m_isSpawning = true;
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

bool TileModel::getIsMerging() const
{
	return m_isMerging;
}

bool TileModel::getSpawning() const
{
	return m_isSpawning;
}