#pragma once
#include "TileMatrix.h"

void TileMatrix::initTextures()
{
	for (int i = 1, k = 0; i < 15; i++, ++k)
		m_textures[k] = &AssetManager::GetTexture("assets/Textures/" + std::to_string(static_cast<int>(pow(2.f, static_cast<double>(i)))) + ".png");
}

int TileMatrix::findID(int type) const
{
	int ID = 0;
	while (type != 1) {
		type /= 2;
		++ID;
	}
	return ID - 1;
}

sf::Vector2f TileMatrix::calculateTilePos(const sf::Vector2i& pos) const
{
	sf::Vector2f tilePos{ m_playgroundPosition };

	tilePos.x += *m_outerEdgeWidth + *m_innerEdgeWidth * pos.x + *m_tileWidth * pos.x + *m_tileWidth / 2.f;
	tilePos.y += *m_outerEdgeWidth + *m_innerEdgeWidth * pos.y + *m_tileWidth * pos.y + *m_tileWidth / 2.f;

	return tilePos;
}

int TileMatrix::mergeLeft(const sf::Vector2i& pos)
{
	Tile& tile = *m_matrix[pos.x][pos.y];
	if (tile.getType() == m_maxType) return -1;

	// Merge if both are moving
	if (m_MoveInstructions1.size() != 0) {
		Tile& neighbourMovingTile = *m_matrix[m_MoveInstructions1.back()->getOldPos().x][m_MoveInstructions1.back()->getOldPos().y];

		if (m_MoveInstructions1.back()->getOldPos().y == pos.y &&
			neighbourMovingTile.getType() == tile.getType() &&
			neighbourMovingTile.getMerging() == false &&
			tile.getMerging() == false) {

			checkWin(tile);

			m_mergedTiles = true;
			neighbourMovingTile.setIsMerging(true);
			tile.setIsMerging(true);
			return m_MoveInstructions1.back()->getNewPos().x;
		}
	}

	// Merge if only one is moving
	for (int i = pos.x - 1; i >= 0; --i)
		if (m_matrix[i][pos.y] != nullptr) {
			if (m_matrix[i][pos.y]->getType() == tile.getType() && !m_matrix[i][pos.y]->getMerging() && !tile.getMerging()) {

				checkWin(tile);
				m_mergedTiles = true;
				m_matrix[i][pos.y]->setIsMerging(true);
				tile.setIsMerging(true);
				return i;
			}
			else
				break;
		}

	m_mergedTiles = false;
	return -1;
}

int TileMatrix::mergeRight(const sf::Vector2i& pos)
{
	Tile& tile = *m_matrix[pos.x][pos.y];
	if (tile.getType() == m_maxType) return -1;

	// Merge if both are moving
	if (m_MoveInstructions1.size() != 0) {
		Tile& neighbourMovingTile = *m_matrix[m_MoveInstructions1.back()->getOldPos().x][m_MoveInstructions1.back()->getOldPos().y];

		if (m_MoveInstructions1.back()->getOldPos().y == pos.y &&
			neighbourMovingTile.getType() == tile.getType() &&
			neighbourMovingTile.getMerging() == false &&
			tile.getMerging() == false) {

			checkWin(tile);

			m_mergedTiles = true;
			neighbourMovingTile.setIsMerging(true);
			tile.setIsMerging(true);
			return m_MoveInstructions1.back()->getNewPos().x;
		}
	}

	// Merge if only one is moving
	for (int i = pos.x + 1; i < m_matrixWidth; ++i)
		if (m_matrix[i][pos.y] != nullptr) {
			if (m_matrix[i][pos.y]->getType() == tile.getType() && !m_matrix[i][pos.y]->getMerging() && !tile.getMerging()) {
				
				checkWin(tile);
				m_mergedTiles = true;
				m_matrix[i][pos.y]->setIsMerging(true);
				tile.setIsMerging(true);
				return i;
			}
			else
				break;
		}

	m_mergedTiles = false;
	return -1;
}

int TileMatrix::mergeUp(const sf::Vector2i& pos)
{
	Tile& tile = *m_matrix[pos.x][pos.y];
	if (tile.getType() == m_maxType) return -1;

	// Merge if both are moving
	if (m_MoveInstructions1.size() != 0) {
		Tile& neighbourMovingTile = *m_matrix[m_MoveInstructions1.back()->getOldPos().x][m_MoveInstructions1.back()->getOldPos().y];

		if (m_MoveInstructions1.back()->getOldPos().x == pos.x &&
			neighbourMovingTile.getType() == tile.getType() &&
			neighbourMovingTile.getMerging() == false &&
			tile.getMerging() == false) {

			checkWin(tile);
			m_mergedTiles = true;
			neighbourMovingTile.setIsMerging(true);
			tile.setIsMerging(true);
			return m_MoveInstructions1.back()->getNewPos().y;
		}
	}

	// Merge if only one is moving
	for (int i = pos.y - 1; i >= 0; --i)
		if (m_matrix[pos.x][i] != nullptr) {
			if (m_matrix[pos.x][i]->getType() == tile.getType() && !m_matrix[pos.x][i]->getMerging() && !tile.getMerging()) {
				
				checkWin(tile);
				m_mergedTiles = true;
				m_matrix[pos.x][i]->setIsMerging(true);
				tile.setIsMerging(true);
				return i;
			}
			else
				break;
		}

	m_mergedTiles = false;
	return -1;
}

int TileMatrix::mergeDown(const sf::Vector2i& pos)
{
	Tile& tile = *m_matrix[pos.x][pos.y];
	if (tile.getType() == m_maxType) return -1;

	// Merge if both are moving
	if (m_MoveInstructions1.size() != 0) {
		Tile& neighbourMovingTile = *m_matrix[m_MoveInstructions1.back()->getOldPos().x][m_MoveInstructions1.back()->getOldPos().y];

		if (m_MoveInstructions1.back()->getOldPos().x == pos.x &&
			neighbourMovingTile.getType() == tile.getType() &&
			neighbourMovingTile.getMerging() == false &&
			tile.getMerging() == false) {

			checkWin(tile);
			m_mergedTiles = true;
			neighbourMovingTile.setIsMerging(true);
			tile.setIsMerging(true);
			return m_MoveInstructions1.back()->getNewPos().y;
		}
	}

	// Merge if only one is moving
	for (int i = pos.y + 1; i < m_matrixHeight; ++i)
		if (m_matrix[pos.x][i] != nullptr) {
			if (m_matrix[pos.x][i]->getType() == tile.getType() && !m_matrix[pos.x][i]->getMerging() && !tile.getMerging()) {
				
				checkWin(tile);
				m_mergedTiles = true;
				m_matrix[pos.x][i]->setIsMerging(true);
				tile.setIsMerging(true);
				return i;
			}
			else
				break;
		}

	m_mergedTiles = false;
	return -1;
}

int TileMatrix::findFreeLeft(const sf::Vector2i& pos)
{
	const int new_x = mergeLeft(pos);
	if (new_x != -1)
		return new_x;
	else {
		for (size_t i = 0; i < pos.x; ++i)
			if ((m_matrix[i][pos.y] == nullptr || m_matrix[i][pos.y]->getIsMoving()) && !willBeOccupied(sf::Vector2i(i, pos.y)))
				return i;
		return pos.x;
	}
}

void TileMatrix::checkWin(const Tile& tile)
{
	if (tile.getType() == 1024 && !m_isWin) {
		m_isWin = true;

		for (size_t x = 0; x < m_matrixWidth; ++x)
			for (size_t y = 0; y < m_matrixHeight; ++y)
				if (m_matrix[x][y])
					m_matrix[x][y]->startWin();
	}
}

int TileMatrix::findFreeRight(const sf::Vector2i& pos)
{
	const int new_x = mergeRight(pos);
	if (new_x != -1)
		return new_x;
	else {
		for (size_t i = m_matrixWidth - 1; i > pos.x; --i)
			if ((m_matrix[i][pos.y] == nullptr || m_matrix[i][pos.y]->getIsMoving()) && !willBeOccupied(sf::Vector2i(i, pos.y)))
				return i;
		return pos.x;
	}

}

int TileMatrix::findFreeUp(const sf::Vector2i& pos)
{
	const int new_y = mergeUp(pos);
	if (new_y != -1)
		return new_y;
	else {
		for (size_t i = 0; i < pos.y; ++i)
			if ((m_matrix[pos.x][i] == nullptr || m_matrix[pos.x][i]->getIsMoving()) && !willBeOccupied(sf::Vector2i(pos.x, i)))
				return i;
		return pos.y;
	}

}

int TileMatrix::findFreeDown(const sf::Vector2i& pos)
{
	const int new_y = mergeDown(pos);
	if (new_y != -1)
		return new_y;
	else {
		for (int i = m_matrixHeight - 1; i > pos.y; --i)
			if ((m_matrix[pos.x][i] == nullptr || m_matrix[pos.x][i]->getIsMoving()) && !willBeOccupied(sf::Vector2i(pos.x, i)))
				return i;
		return pos.y;
	}
}

void TileMatrix::moveLeft()
{
	endMerge();
	for (int j = 0; j < m_matrixHeight; ++j)
		for (int i = 0; i < m_matrixWidth; ++i)
			if (m_matrix[i][j] != nullptr) {
				const sf::Vector2i new_pos{ findFreeLeft(sf::Vector2i(i, j)), j };
				const int distance = i - new_pos.x;

				if (distance > 0) {
					const float pixel_distance = static_cast<float>(distance) * (*m_innerEdgeWidth + *m_tileWidth);
					m_matrix[i][j]->smoothMove(sf::Vector2f(-pixel_distance, 0.f), m_timeMovingMax);
					addMoveInstructions1(new_pos, sf::Vector2i{ i, j });
				}
			}
}

void TileMatrix::moveRight()
{
	endMerge();
	for (int j = 0; j < m_matrixHeight; ++j)
		for (int i = m_matrixWidth - 1; i >= 0; --i)
			if (m_matrix[i][j] != nullptr) {
				const sf::Vector2i new_pos{ findFreeRight(sf::Vector2i(i, j)), j };
				const int distance = new_pos.x - i;

				if (distance > 0) {
					const float pixel_distance = static_cast<float>(distance) * (*m_innerEdgeWidth + *m_tileWidth);
					m_matrix[i][j]->smoothMove(sf::Vector2f(pixel_distance, 0.f), m_timeMovingMax);
					addMoveInstructions1(new_pos, sf::Vector2i{ i, j });
				}
			}
}

void TileMatrix::moveUp()
{
	endMerge();
	for (int i = 0; i < m_matrixWidth; ++i)
		for (int j = 0; j < m_matrixHeight; ++j)
			if (m_matrix[i][j] != nullptr) {
				const sf::Vector2i new_pos{ i, findFreeUp(sf::Vector2i(i, j)) };
				const int distance = j - new_pos.y;

				if (distance > 0) {
					const float pixel_distance = static_cast<float>(distance) * (*m_innerEdgeWidth + *m_tileWidth);
					m_matrix[i][j]->smoothMove(sf::Vector2f(0.f, -pixel_distance), m_timeMovingMax);
					addMoveInstructions1(new_pos, sf::Vector2i{ i, j });
				}
			}
}

void TileMatrix::moveDown()
{
	endMerge();
	for (int i = 0; i < m_matrixWidth; ++i)
		for (int j = m_matrixHeight - 1; j >= 0; --j)
			if (m_matrix[i][j] != nullptr) {
				const sf::Vector2i new_pos{ i, findFreeDown(sf::Vector2i(i, j)) };
				const int distance = new_pos.y - j;

				if (distance > 0) {
					const float pixel_distance = static_cast<float>(distance) * (*m_innerEdgeWidth + *m_tileWidth);
					m_matrix[i][j]->smoothMove(sf::Vector2f(0.f, pixel_distance), m_timeMovingMax);
					addMoveInstructions1(new_pos, sf::Vector2i{ i, j });
				}
			}
}

void TileMatrix::addMoveInstructions1(const sf::Vector2i& newPos, const sf::Vector2i& oldPos)
{
	m_state = Tstate::MOVING;
	m_matrix[oldPos.x][oldPos.y]->setIsMoving(true);
	m_MoveInstructions1.push_back(new MoveInstructions1{ newPos, oldPos, m_mergedTiles });
	m_mergedTiles = false;
}

bool TileMatrix::willBeOccupied(const sf::Vector2i& pos) const
{
	for (const auto& instruction : m_MoveInstructions1)
		if (instruction->getNewPos() == pos)
			return true;
	return false;
}

void TileMatrix::endMove()
{
	if (m_state == Tstate::MOVING) {

		m_addedScore = 0;
		for (size_t i = 0; i < m_MoveInstructions1.size(); ++i) {
			if (m_MoveInstructions1[i]->m_merge) {
				m_state = Tstate::MERGING;
				const sf::Vector2i new_pos = m_MoveInstructions1[i]->getNewPos();
				const sf::Vector2i old_pos = m_MoveInstructions1[i]->getOldPos();
				delete m_matrix[old_pos.x][old_pos.y];
				m_matrix[old_pos.x][old_pos.y] = nullptr;

				m_tilesToMerge.push_back(m_matrix[new_pos.x][new_pos.y]);
				m_matrix[new_pos.x][new_pos.y] = new Tile(m_tilesToMerge.back()->getType() * 2, m_textures[findID(m_tilesToMerge.back()->getType() * 2)], m_scale, calculateTilePos(new_pos), m_movementManager);
				m_matrix[new_pos.x][new_pos.y]->startMerging();
				--m_tiles;

				m_addedScore += m_tilesToMerge.back()->getType() * 2;
			}
			else {
				const sf::Vector2i new_pos = m_MoveInstructions1[i]->getNewPos();
				const sf::Vector2i old_pos = m_MoveInstructions1[i]->getOldPos();
				m_matrix[new_pos.x][new_pos.y] = m_matrix[old_pos.x][old_pos.y];
				m_matrix[old_pos.x][old_pos.y] = nullptr;

				m_matrix[new_pos.x][new_pos.y]->setIsMoving(false);
				m_matrix[new_pos.x][new_pos.y]->setIsMerging(false);
			}
		}
		m_MoveInstructions1.clear();

		if (m_state == Tstate::MOVING) {
			m_state = Tstate::IDLE;
			m_timeMoving = 0.f;
		}

		spawn();
	}
}

void TileMatrix::endMerge()
{
	if (m_state == Tstate::MERGING) {
		m_timeMoving = 0.f;
		m_timeMerging = 0.f;

		for (size_t i = 0; i < m_tilesToMerge.size(); ++i)
			delete m_tilesToMerge[i];
		m_tilesToMerge.clear();

		m_state = Tstate::IDLE;
	}
}

TileMatrix::TileMatrix(const float* scale, const float* outer, const float* inner, const float* tileWidth, const sf::Vector2f& playgroundPos) :
	m_scale{ scale }, m_outerEdgeWidth{ outer }, m_innerEdgeWidth{ inner }, m_tileWidth{ tileWidth }, m_playgroundPosition{ playgroundPos }
{
	m_movementManager = new MovementManager();
	m_movementContainer = MovementContainer::getInstance();

	auto routine = m_movementManager->createScalingRoutine("TILE_SPAWNING");
	routine->addScaling(new scalingInfo(sf::Vector2f(0.1f, 0.1f) * *m_scale, sf::Vector2f(1.f, 1.f) * *m_scale, m_timeSpawningMax, easeFunctions::getFunction(easeFunctions::OUT_QUAD), false, 0.f, 0.f));

	routine = m_movementManager->createScalingRoutine("TILE_MERGING");
	routine->addScaling(new scalingInfo(sf::Vector2f(0.1f, 0.1f) * *m_scale, sf::Vector2f(1.f, 1.f) * *m_scale, m_timeMergingMax, easeFunctions::getFunction(easeFunctions::OUT_BACK), false, 0.f, 0.f));

	initTextures();
}

TileMatrix::~TileMatrix()
{
	for (int i = 0; i < m_matrixHeight; ++i)
		for (int j = 0; j < m_matrixWidth; ++j)
			if (m_matrix[i][j])
				delete m_matrix[i][j];
}

void TileMatrix::update(float dt)
{
	for (size_t i = 0; i < m_matrixHeight; ++i)
		for (size_t j = 0; j < m_matrixWidth; ++j)
			if (m_matrix[i][j])
				m_matrix[i][j]->update(dt);

	if (!m_isGameOver) {
		if (m_state == Tstate::MOVING)
			updateMove(dt);

		if (m_state == Tstate::MERGING)
			updateMerge(dt);

		m_movementManager->update(dt);
		m_movementContainer->update(dt);
	}
}

void TileMatrix::updateMove(float dt)
{
	if (m_timeMoving < m_timeMovingMax)
		m_timeMoving += dt;
	else
		endMove();
}

void TileMatrix::updateMerge(float dt)
{
	if (m_timeMerging < m_timeMergingMax) {
		m_timeMerging += dt;
	}
	else
		endMerge();
}

void TileMatrix::spawn(const int amount)
{
	for (int i = 0; i < amount; ++i) {
		sf::Vector2i pos{ rand() % 4, rand() % 4 };

		while (m_matrix[pos.x][pos.y])
			pos = { rand() % 4, rand() % 4 };

		addTile(pos);
	}
}

void TileMatrix::addTile(const sf::Vector2i& pos, const int type)
{
	if (pos.x > m_matrixWidth - 1 || pos.y > m_matrixHeight - 1)
		printf("TileMatrix::addTile ERROR: Tile spawning position out of bounds\n");
	else {
		m_matrix[pos.x][pos.y] = new Tile(type, m_textures[findID(type)], m_scale, calculateTilePos(pos), m_movementManager);
		m_matrix[pos.x][pos.y]->startSpawning();
		++m_tiles;

		m_isGameOver = isGameOver();
	}
}

void TileMatrix::clearBoard()
{
	m_MoveInstructions1.clear();

	for (int i = 0; i < m_matrixHeight; ++i)
		for (int j = 0; j < m_matrixWidth; ++j) {
			if (m_matrix[i][j])
				delete m_matrix[i][j];
			m_matrix[i][j] = nullptr;
		}

	m_addedScore = 0;
	m_timeMoving = 0.f;
	m_timeMerging = 0.f;
	m_mergedTiles = false;
	m_isGameOver = false;
	m_tiles = 0;
}

bool TileMatrix::isGameOver()
{
	if (m_tiles < m_maxTiles)
		return false;
	else {
		for (int i = 1; i < m_matrixHeight - 1; ++i)
			for (int j = 1; j < m_matrixWidth - 1; ++j)
				if (m_matrix[j][i]->getType() == m_matrix[j - 1][i]->getType() ||
					m_matrix[j][i]->getType() == m_matrix[j + 1][i]->getType() ||
					m_matrix[j][i]->getType() == m_matrix[j][i - 1]->getType() ||
					m_matrix[j][i]->getType() == m_matrix[j][i + 1]->getType())
					return false;

		for (size_t i = 0; i < m_matrixWidth - 1; ++i)
			if (m_matrix[i][0]->getType() == m_matrix[i + 1][0]->getType() || m_matrix[i][m_matrixHeight - 1]->getType() == m_matrix[i + 1][m_matrixHeight - 1]->getType())
				return false;

		for (size_t i = 0; i < m_matrixHeight - 1; ++i)
			if (m_matrix[0][i]->getType() == m_matrix[0][i + 1]->getType() || m_matrix[m_matrixWidth - 1][i]->getType() == m_matrix[m_matrixWidth - 1][i + 1]->getType())
				return false;

		// Game Over
		for (size_t i = 0; i < m_matrixHeight; ++i)
			for (size_t j = 0; j < m_matrixWidth; ++j) {
				m_matrix[i][j]->setScale(*m_scale);
				m_matrix[i][j]->startGameOver();
			}

		endMove();
		endMerge();
		return true;
	}

	return false;
}

// Accessors / Mutators
bool TileMatrix::getIsMoving() const
{
	return m_state == Tstate::MOVING;
}

bool TileMatrix::getIsGameOver() const
{
	return m_isGameOver;
}

int TileMatrix::getAddedScore() const
{
	return m_addedScore;
}

void TileMatrix::setAddedScore(const int value)
{
	m_addedScore = value;
}

// Rendering tiles
void TileMatrix::render(sf::RenderTarget& target)
{
	for (auto tile : m_tilesToMerge)
		tile->render(target);

	for (int i = 0; i < m_matrixHeight; ++i)
		for (int j = 0; j < m_matrixWidth; ++j)
			if (m_matrix[i][j])
				m_matrix[i][j]->render(target);
}
