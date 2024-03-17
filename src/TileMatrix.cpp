#pragma once
#include "TileMatrix.h"

void TileMatrix::initTextures()
{
	for (int i = 1, k = 0; i < 13; i++, ++k) 
		m_textures[k] = &AssetManager::GetTexture("Textures/" + std::to_string(static_cast<int>(pow(2.f, static_cast<double>(i)))) + ".png");
}

int TileMatrix::findID(int type_)
{
	int ID = 0;
	while (type_ != 1) {
		type_ /= 2;
		++ID;
	}
	return ID - 1;
}

sf::Vector2f TileMatrix::calculateTilePos(int x, int y)
{
	sf::Vector2f tilePos = m_playgroundPosition;
	tilePos.x += *m_outerEdgeWidth;
	tilePos.y += *m_outerEdgeWidth;
	
	tilePos.x += *m_innerEdgeWidth * x + *m_tileWidth * x + *m_tileWidth / 2.f;
	tilePos.y += *m_innerEdgeWidth * y + *m_tileWidth * y + *m_tileWidth / 2.f;

	return tilePos;
}

int TileMatrix::mergeLeft(int x, int y)
{
	// Merge if both are moving
	if (move_tile_instructions.size() != 0 && move_tile_instructions.back()->getOldPos().y == y && matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getType() == matrix[x][y]->getType() && !matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getMerging() && !matrix[x][y]->getMerging()) {
		m_mergedTiles = true;
		matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->setIsMerging(true);
		matrix[x][y]->setIsMerging(true);
		return move_tile_instructions.back()->getNewPos().x;
	}
	// Merge if only one is moving
	for (int i = x - 1; i >= 0; --i)
		if (matrix[i][y] != nullptr) {
			if (matrix[i][y]->getType() == matrix[x][y]->getType() && !matrix[i][y]->getMerging() && !matrix[x][y]->getMerging()) {
				m_mergedTiles = true;
				matrix[i][y]->setIsMerging(true);
				matrix[x][y]->setIsMerging(true);
				return i;
			}
			else
				break;
		}

	m_mergedTiles = false;
	return -1;
}

int TileMatrix::mergeRight(int x, int y)
{
	// Merge if both are moving
	if (move_tile_instructions.size() != 0 && move_tile_instructions.back()->getOldPos().y == y && matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getType() == matrix[x][y]->getType() && !matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getMerging() && !matrix[x][y]->getMerging()) {
		m_mergedTiles = true;
		matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->setIsMerging(true);
		matrix[x][y]->setIsMerging(true);
		return move_tile_instructions.back()->getNewPos().x;
	}
	// Merge if only one is moving
	for (size_t i = x + 1; i < matrixwidth; ++i)
		if (matrix[i][y] != nullptr) {
			if (matrix[i][y]->getType() == matrix[x][y]->getType() && !matrix[i][y]->getMerging() && !matrix[x][y]->getMerging()) {
				m_mergedTiles = true;
				matrix[i][y]->setIsMerging(true);
				matrix[x][y]->setIsMerging(true);
				return i;
			}
			else
				break;
		}

	m_mergedTiles = false;
	return -1;
}

int TileMatrix::mergeUp(int x, int y)
{
	// Merge if both are moving
	if (move_tile_instructions.size() != 0 && move_tile_instructions.back()->getOldPos().x == x && matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getType() == matrix[x][y]->getType() && !matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getMerging() && !matrix[x][y]->getMerging()) {
		m_mergedTiles = true;
		matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->setIsMerging(true);
		matrix[x][y]->setIsMerging(true);
		return move_tile_instructions.back()->getNewPos().y;
	}
	// Merge if only one is moving
	for (int i = y - 1; i >= 0; --i)
		if (matrix[x][i] != nullptr) {
			if (matrix[x][i]->getType() == matrix[x][y]->getType() && !matrix[x][i]->getMerging() && !matrix[x][y]->getMerging()) {
				m_mergedTiles = true;
				matrix[x][i]->setIsMerging(true);
				matrix[x][y]->setIsMerging(true);
				return i;
			}
			else
				break;
		}

	m_mergedTiles = false;
	return -1;
}

int TileMatrix::mergeDown(int x, int y)
{
	// Merge if both are moving
	if (move_tile_instructions.size() != 0 && move_tile_instructions.back()->getOldPos().x == x && matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getType() == matrix[x][y]->getType() && !matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getMerging() && !matrix[x][y]->getMerging()) {
		m_mergedTiles = true;
		matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->setIsMerging(true);
		matrix[x][y]->setIsMerging(true);
		return move_tile_instructions.back()->getNewPos().y;
	}
	// Merge if only one is moving
	for (size_t i = y + 1; i < matrixheight; ++i)
		if (matrix[x][i] != nullptr) {
			if (matrix[x][i]->getType() == matrix[x][y]->getType() && !matrix[x][i]->getMerging() && !matrix[x][y]->getMerging()) {
				m_mergedTiles = true;
				matrix[x][i]->setIsMerging(true);
				matrix[x][y]->setIsMerging(true);
				return i;
			}
			else
				break;
		}

	m_mergedTiles = false;
	return -1;
}

int TileMatrix::findFreeLeft(int x, int y)
{
	const int new_x = mergeLeft(x, y);
	if (new_x != -1)
		return new_x;
	else {
		for (size_t i = 0; i < x; ++i)
			if ((matrix[i][y] == nullptr || matrix[i][y]->getIsMoving()) && !willBeOccupied(i, y))
				return i;
		return x;
	}
}

int TileMatrix::findFreeRight(int x, int y)
{
	const int new_x = mergeRight(x, y);
	if (new_x != -1)
		return new_x;
	else {
		for (size_t i = matrixwidth - 1; i > x; --i)
			if ((matrix[i][y] == nullptr || matrix[i][y]->getIsMoving()) && !willBeOccupied(i, y))
				return i;
		return x;
	}
	
}

int TileMatrix::findFreeUp(int x, int y)
{
	const int new_y = mergeUp(x, y);
	if (new_y != -1)
		return new_y;
	else {
		for (size_t i = 0; i < y; ++i)
			if ((matrix[x][i] == nullptr || matrix[x][i]->getIsMoving()) && !willBeOccupied(x, i))
				return i;
		return y;
	}
	
}

int TileMatrix::findFreeDown(int x, int y)
{
	const int new_y = mergeDown(x, y);
	if (new_y != -1)
		return new_y;
	else {
		for (int i = matrixheight - 1; i > y; --i)
			if ((matrix[x][i] == nullptr || matrix[x][i]->getIsMoving()) && !willBeOccupied(x, i))
				return i;
		return y;
	}
}

void TileMatrix::moveLeft()
{
	endMerge();
	for (int j = 0; j < matrixheight; ++j)
		for (int i = 0; i < matrixwidth; ++i)
			if (matrix[i][j] != nullptr) {
				const sf::Vector2i new_pos = { findFreeLeft(i, j), j };
				const int distance = i - new_pos.x;
				const float pixel_distance = static_cast<float>(distance) * (*m_innerEdgeWidth + *m_tileWidth);

				if (distance > 0) {
					m_isMoving = true;
					matrix[i][j]->smoothMove(sf::Vector2f(-pixel_distance, 0.f), m_timeMovingMax);
					addMoveInstructions(new_pos, { i, j }, distance);
				}
			}
}

void TileMatrix::moveRight()
{
	endMerge();
	for (int j = 0; j < matrixheight; ++j)
		for (int i = matrixwidth - 1; i >= 0; --i)
			if (matrix[i][j] != nullptr) {
				sf::Vector2i new_pos = { findFreeRight(i, j), j };
				int distance = new_pos.x - i;
				float pixel_distance = static_cast<float>(distance) * (*m_innerEdgeWidth + *m_tileWidth);

				if (distance > 0) {
					m_isMoving = true;
					matrix[i][j]->smoothMove(sf::Vector2f(pixel_distance, 0.f), m_timeMovingMax);
					addMoveInstructions(new_pos, { i, j }, distance);
				}
			}
}

void TileMatrix::moveUp()
{
	endMerge();
	for (int i = 0; i < matrixwidth; ++i)
		for (int j = 0; j < matrixheight; ++j)
			if (matrix[i][j] != nullptr) {
				sf::Vector2i new_pos = { i, findFreeUp(i, j) };
				int distance = j - new_pos.y;
				float pixel_distance = static_cast<float>(distance) * (*m_innerEdgeWidth + *m_tileWidth);

				if (distance > 0) {
					m_isMoving = true;
					matrix[i][j]->smoothMove(sf::Vector2f(0.f, -pixel_distance), m_timeMovingMax);
					addMoveInstructions(new_pos, { i, j }, distance);
				}
			}
}

void TileMatrix::moveDown()
{
	endMerge();
	for (int i = 0; i < matrixwidth; ++i)
		for (int j = matrixheight - 1; j >= 0; --j)
			if (matrix[i][j] != nullptr) {
				sf::Vector2i new_pos = { i, findFreeDown(i, j) };
				int distance = new_pos.y - j;
				float pixel_distance = static_cast<float>(distance) * (*m_innerEdgeWidth + *m_tileWidth);

				if (distance > 0) {
					m_isMoving = true;
					matrix[i][j]->smoothMove(sf::Vector2f(0.f, pixel_distance), m_timeMovingMax);
					addMoveInstructions(new_pos, { i, j }, distance);
				}
			}
}

void TileMatrix::clearBoard()
{
	move_tile_instructions.clear();
	
	for (int i = 0; i < matrixheight; ++i)
		for (int j = 0; j < matrixwidth; ++j) {
			if (matrix[i][j] != nullptr)
				delete matrix[i][j];
				matrix[i][j] = nullptr;
			}

	m_addedScore = 0;
	m_timeMoving = 0.f;
	m_mergedTiles = false;
	m_isGameOver = false;
	m_tiles = 0;
}

bool TileMatrix::isGameOver()
{
	if (m_tiles != 16)
		return false;
	else {
		for (int i = 1; i < matrixheight - 1; ++i)
			for (int j = 1; j < matrixwidth - 1; ++j)
				if (matrix[j][i]->getType() == matrix[j - 1][i]->getType() ||
					matrix[j][i]->getType() == matrix[j + 1][i]->getType() ||
					matrix[j][i]->getType() == matrix[j][i - 1]->getType() ||
					matrix[j][i]->getType() == matrix[j][i + 1]->getType())
					return false;

		for (size_t i = 0; i < matrixwidth - 1; ++i)
			if (matrix[i][0]->getType() == matrix[i + 1][0]->getType() || matrix[i][matrixheight - 1]->getType() == matrix[i + 1][matrixheight - 1]->getType())
				return false;

		for (size_t i = 0; i < matrixheight - 1; ++i)
			if (matrix[0][i]->getType() == matrix[0][i + 1]->getType() || matrix[matrixwidth - 1][i]->getType() == matrix[matrixwidth - 1][i + 1]->getType())
				return false;

		for (size_t i = 0; i < matrixheight; ++i)
			for (size_t j = 0; j < matrixwidth; ++j) {
				matrix[i][j]->setScale(*m_scale);
				matrix[i][j]->gameOver();
			}

		return true;
	}

	return false;
}

void TileMatrix::addMoveInstructions(sf::Vector2i new_pos_, sf::Vector2i old_pos_, int distance_)
{
	if (distance_ > 0) {
		matrix[old_pos_.x][old_pos_.y]->setIsMoving(true);
		move_tile_instructions.push_back(new MoveTile(new_pos_, old_pos_, m_mergedTiles));
		m_mergedTiles = false;
	}
}

bool TileMatrix::willBeOccupied(int x, int y)
{
	for (int i = move_tile_instructions.size() - 1; i >= 0; --i)
		if (move_tile_instructions[i]->getNewPos() == sf::Vector2i(x, y))
			return true;
	return false;
}

TileMatrix::TileMatrix(float* scale_, float* outer_, float* inner_, float* tile_width_, sf::Vector2f playground_pos_)
{
	for (int i = 0; i < matrixheight; ++i)
		for (int j = 0; j < matrixwidth; ++j)
			matrix[i][j] = nullptr;

	m_scale = scale_;
	m_outerEdgeWidth = outer_;
	m_innerEdgeWidth = inner_;
	m_tileWidth = tile_width_;
	m_playgroundPosition = playground_pos_;

	m_movementManager = MovementManager::getInstance();
	m_movementContainer = MovementContainer::getInstance();

	auto routine = m_movementManager->createScalingRoutine("TILE_SPAWNING");
	routine->addScaling(new scalingInfo(sf::Vector2f(0.1f, 0.1f) * *m_scale, sf::Vector2f(1.f, 1.f) * *m_scale, 0.2f, easeFunctions::getFunction(easeFunctions::OUT_QUAD), false, 0.f, 0.f));
	
	routine = m_movementManager->createScalingRoutine("TILE_MERGING");
	routine->addScaling(new scalingInfo(sf::Vector2f(0.1f, 0.1f) * *m_scale, sf::Vector2f(1.f, 1.f) * *m_scale, m_timeMergingMax, easeFunctions::getFunction(easeFunctions::OUT_BACK), false, 0.f, 0.f));
	initTextures();
}

TileMatrix::~TileMatrix()
{
	for (int i = 0; i < matrixheight; ++i)
		for (int j = 0; j < matrixwidth; ++j)
			if (matrix[i][j])
				delete matrix[i][j];
}

void TileMatrix::update(float dt)
{
	if (m_isMoving)
		updateMove(dt);

	if (m_isMerging)
		updateMerge(dt);

	for (size_t i = 0; i < matrixheight; ++i)
		for (size_t j = 0; j < matrixwidth; ++j)
			if (matrix[i][j])
				matrix[i][j]->update(dt);

	m_movementManager->update(dt);
	m_movementContainer->update(dt);
}

void TileMatrix::spawn(unsigned amount_)
{
	for (int i = 0; i < amount_; ++i) {
		sf::Vector2i pos = { rand() % 4, rand() % 4 };

		while (matrix[pos.x][pos.y] != nullptr) {
			pos = { rand() % 4, rand() % 4 };
		}

		addTile(pos);
	}
}

void TileMatrix::addTile(sf::Vector2i pos_, int type_)
{
	if (pos_.x > matrixwidth - 1 || pos_.y > matrixheight - 1) 
		printf("TileMatrix::addTile ERROR: Tile spawning position out of bounds\n");
	else {
		matrix[pos_.x][pos_.y] = new Tile(type_, m_textures[findID(type_)], m_scale, calculateTilePos(pos_.x, pos_.y));
		matrix[pos_.x][pos_.y]->startSpawning();
		++m_tiles;
	}
}

void TileMatrix::updateMove(float dt)
{
	if (m_timeMoving < m_timeMovingMax)
		m_timeMoving += dt;
	else {
		if (m_timeMerging == 0.f) {

			m_addedScore = 0;
			for (size_t i = 0; i < move_tile_instructions.size(); ++i) {
				if (move_tile_instructions[i]->m_merge) {
					m_isMerging = true;
					const sf::Vector2i new_pos = move_tile_instructions[i]->getNewPos();
					const sf::Vector2i old_pos = move_tile_instructions[i]->getOldPos();
					delete matrix[old_pos.x][old_pos.y];
					matrix[old_pos.x][old_pos.y] = nullptr;

					merge_tile_instructions.push_back(matrix[new_pos.x][new_pos.y]);
					matrix[new_pos.x][new_pos.y] = new Tile(merge_tile_instructions.back()->getType() * 2, m_textures[findID(merge_tile_instructions.back()->getType() * 2)], m_scale, calculateTilePos(new_pos.x, new_pos.y));
					matrix[new_pos.x][new_pos.y]->startMerging();
					--m_tiles;

					// Updating score
					m_addedScore += merge_tile_instructions.back()->getType() * 2;
				}
				else {
					const sf::Vector2i new_pos = move_tile_instructions[i]->getNewPos();
					const sf::Vector2i old_pos = move_tile_instructions[i]->getOldPos();
					matrix[new_pos.x][new_pos.y] = matrix[old_pos.x][old_pos.y];
					matrix[old_pos.x][old_pos.y] = nullptr;

					matrix[new_pos.x][new_pos.y]->setIsMoving(false);
					matrix[new_pos.x][new_pos.y]->setIsMerging(false);
				}
			}
			move_tile_instructions.clear();

			if (!m_isMerging) {
				m_timeMoving = 0.f;
				m_isGameOver = isGameOver();
			}

			m_isMoving = false;

			spawn();
		}
	}
}

void TileMatrix::updateMerge(float dt)
{
	if (m_timeMerging < m_timeMergingMax) {
		m_timeMerging += dt;
	}
	else {
		m_timeMoving = 0.f;
		m_timeMerging = 0.f;

		for (size_t i = 0; i < merge_tile_instructions.size(); ++i)
			delete merge_tile_instructions[i];
		merge_tile_instructions.clear();

		m_isMoving = false;
		m_isMerging = false;
		m_isGameOver = isGameOver();
	}
}

void TileMatrix::endMerge()
{
	if (m_isMerging) {
		m_timeMoving = 0.f;
		m_timeMerging = 0.f;

		for (size_t i = 0; i < merge_tile_instructions.size(); ++i) 
			delete merge_tile_instructions[i];
		merge_tile_instructions.clear();

		m_isMoving = false;
		m_isMerging = false;
	}
}

void TileMatrix::render(sf::RenderTarget& target)
{
	for (auto tile: merge_tile_instructions)
		tile->render(target);

	for (int i = 0; i < matrixheight; ++i)
		for (int j = 0; j < matrixwidth; ++j)
			if (matrix[i][j])
				matrix[i][j]->render(target);
}
