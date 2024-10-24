#pragma once
#include "TileModel.h"

TileBase::TileBase(const int type) : m_type{ type } {};


// Constructors / Destructors
TileModel::TileModel(const int type) : TileBase{ type } {}

void TileModel::startGameOver()
{
	m_isMerging = false;
	m_isGameOver = true;
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
bool TileModel::isMoving() const
{
	return m_isMoving;
}

bool TileModel::isMerging() const
{
	return m_isMerging;
}