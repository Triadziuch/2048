#pragma once
#include "TileMatrixModel.h"

int TileMatrixModel::findID(int type) const
{
	int ID = 0;
	while (type != 1) {
		type /= 2;
		++ID;
	}
	return ID - 1;
}

int TileMatrixModel::mergeLeft(const sf::Vector2i& pos)
{
	TileModel& tile = *m_matrix[pos.x][pos.y];
	if (tile.getType() == m_maxType) return -1;

	// Merge if both are moving
	if (m_moveInstructions.size() != 0) {
		TileModel& neighbourMovingTile = *m_matrix[m_moveInstructions.back()->getOldPos().x][m_moveInstructions.back()->getOldPos().y];

		if (m_moveInstructions.back()->getOldPos().y == pos.y &&
			neighbourMovingTile.getType() == tile.getType() &&
			neighbourMovingTile.getIsMerging() == false &&
			tile.getIsMerging() == false) {

			checkWin(tile);

			m_mergedTiles = true;
			neighbourMovingTile.setIsMerging(true);
			tile.setIsMerging(true);
			return m_moveInstructions.back()->getNewPos().x;
		}
	}

	// Merge if only one is moving
	for (int i = pos.x - 1; i >= 0; --i)
		if (m_matrix[i][pos.y] != nullptr) {
			if (m_matrix[i][pos.y]->getType() == tile.getType() && !m_matrix[i][pos.y]->getIsMerging() && !tile.getIsMerging()) {

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

int TileMatrixModel::mergeRight(const sf::Vector2i& pos)
{
	TileModel& tile = *m_matrix[pos.x][pos.y];
	if (tile.getType() == m_maxType) return -1;

	// Merge if both are moving
	if (m_moveInstructions.size() != 0) {
		TileModel& neighbourMovingTile = *m_matrix[m_moveInstructions.back()->getOldPos().x][m_moveInstructions.back()->getOldPos().y];

		if (m_moveInstructions.back()->getOldPos().y == pos.y &&
			neighbourMovingTile.getType() == tile.getType() &&
			neighbourMovingTile.getIsMerging() == false &&
			tile.getIsMerging() == false) {

			checkWin(tile);

			m_mergedTiles = true;
			neighbourMovingTile.setIsMerging(true);
			tile.setIsMerging(true);
			return m_moveInstructions.back()->getNewPos().x;
		}
	}

	// Merge if only one is moving
	for (int i = pos.x + 1; i < m_matrixWidth; ++i)
		if (m_matrix[i][pos.y] != nullptr) {
			if (m_matrix[i][pos.y]->getType() == tile.getType() && !m_matrix[i][pos.y]->getIsMerging() && !tile.getIsMerging()) {
				
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

int TileMatrixModel::mergeUp(const sf::Vector2i& pos)
{
	TileModel& tile = *m_matrix[pos.x][pos.y];
	if (tile.getType() == m_maxType) return -1;

	// Merge if both are moving
	if (m_moveInstructions.size() != 0) {
		TileModel& neighbourMovingTile = *m_matrix[m_moveInstructions.back()->getOldPos().x][m_moveInstructions.back()->getOldPos().y];

		if (m_moveInstructions.back()->getOldPos().x == pos.x &&
			neighbourMovingTile.getType() == tile.getType() &&
			neighbourMovingTile.getIsMerging() == false &&
			tile.getIsMerging() == false) {

			checkWin(tile);
			m_mergedTiles = true;
			neighbourMovingTile.setIsMerging(true);
			tile.setIsMerging(true);
			return m_moveInstructions.back()->getNewPos().y;
		}
	}

	// Merge if only one is moving
	for (int i = pos.y - 1; i >= 0; --i)
		if (m_matrix[pos.x][i] != nullptr) {
			if (m_matrix[pos.x][i]->getType() == tile.getType() && !m_matrix[pos.x][i]->getIsMerging() && !tile.getIsMerging()) {
				
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

int TileMatrixModel::mergeDown(const sf::Vector2i& pos)
{
	TileModel& tile = *m_matrix[pos.x][pos.y];
	if (tile.getType() == m_maxType) return -1;

	// Merge if both are moving
	if (m_moveInstructions.size() != 0) {
		TileModel& neighbourMovingTile = *m_matrix[m_moveInstructions.back()->getOldPos().x][m_moveInstructions.back()->getOldPos().y];

		if (m_moveInstructions.back()->getOldPos().x == pos.x &&
			neighbourMovingTile.getType() == tile.getType() &&
			neighbourMovingTile.getIsMerging() == false &&
			tile.getIsMerging() == false) {

			checkWin(tile);
			m_mergedTiles = true;
			neighbourMovingTile.setIsMerging(true);
			tile.setIsMerging(true);
			return m_moveInstructions.back()->getNewPos().y;
		}
	}

	// Merge if only one is moving
	for (int i = pos.y + 1; i < m_matrixHeight; ++i)
		if (m_matrix[pos.x][i] != nullptr) {
			if (m_matrix[pos.x][i]->getType() == tile.getType() && !m_matrix[pos.x][i]->getIsMerging() && !tile.getIsMerging()) {
				
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

int TileMatrixModel::findFreeLeft(const sf::Vector2i& pos)
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

void TileMatrixModel::checkWin(const TileModel& tile)
{
	if (tile.getType() == 1024 && !m_isWin) {
		m_isWin = true;

		for (size_t x = 0; x < m_matrixWidth; ++x)
			for (size_t y = 0; y < m_matrixHeight; ++y)
				if (m_matrix[x][y])
					m_matrix[x][y]->startWin();
	}
}

int TileMatrixModel::findFreeRight(const sf::Vector2i& pos)
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

int TileMatrixModel::findFreeUp(const sf::Vector2i& pos)
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

int TileMatrixModel::findFreeDown(const sf::Vector2i& pos)
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

void TileMatrixModel::moveLeft()
{
	//endMerge();
	for (int j = 0; j < m_matrixHeight; ++j)
		for (int i = 0; i < m_matrixWidth; ++i)
			if (m_matrix[i][j] != nullptr) {
				const sf::Vector2i new_pos{ findFreeLeft(sf::Vector2i(i, j)), j };
				const int distance = i - new_pos.x;

				if (distance > 0) {
					addMoveInstructions(new_pos, sf::Vector2i{ i, j });
				}
			}

	if (!m_moveInstructions.empty())
		this->notify("STARTED_MOVE");
}

void TileMatrixModel::moveRight()
{
	//endMerge();
	for (int j = 0; j < m_matrixHeight; ++j)
		for (int i = m_matrixWidth - 1; i >= 0; --i)
			if (m_matrix[i][j] != nullptr) {
				const sf::Vector2i new_pos{ findFreeRight(sf::Vector2i(i, j)), j };
				const int distance = new_pos.x - i;

				if (distance > 0) {
					addMoveInstructions(new_pos, sf::Vector2i{ i, j });
				}
			}

	if (!m_moveInstructions.empty())
		this->notify("STARTED_MOVE");
}

void TileMatrixModel::moveUp()
{
	//endMerge();
	for (int i = 0; i < m_matrixWidth; ++i)
		for (int j = 0; j < m_matrixHeight; ++j)
			if (m_matrix[i][j] != nullptr) {
				const sf::Vector2i new_pos{ i, findFreeUp(sf::Vector2i(i, j)) };
				const int distance = j - new_pos.y;

				if (distance > 0) {
					addMoveInstructions(new_pos, sf::Vector2i{ i, j });
				}
			}
	
	if (!m_moveInstructions.empty())
		this->notify("STARTED_MOVE");
}

void TileMatrixModel::moveDown()
{
	//endMerge();
	for (int i = 0; i < m_matrixWidth; ++i)
		for (int j = m_matrixHeight - 1; j >= 0; --j)
			if (m_matrix[i][j] != nullptr) {
				const sf::Vector2i new_pos{ i, findFreeDown(sf::Vector2i(i, j)) };
				const int distance = new_pos.y - j;

				if (distance > 0) {
					addMoveInstructions(new_pos, sf::Vector2i{ i, j });
				}
			}
	
	if (!m_moveInstructions.empty())
		this->notify("STARTED_MOVE");
}

void TileMatrixModel::addMoveInstructions(const sf::Vector2i& newPos, const sf::Vector2i& oldPos)
{
	m_state = Tstate::MOVING;
	m_matrix[oldPos.x][oldPos.y]->setIsMoving(true);
	m_moveInstructions.push_back(new MoveInstructions{ newPos, oldPos, m_mergedTiles });
	m_mergedTiles = false;
}

bool TileMatrixModel::willBeOccupied(const sf::Vector2i& pos) const
{
	for (const auto& instruction : m_moveInstructions)
		if (instruction->getNewPos() == pos)
			return true;
	return false;
}

// Wywo³ywane przez widok po zakoñczeniu graficznego ruchu bloków w m_movementInstructions
void TileMatrixModel::endMove()
{
	m_addedScore = 0;

	for (size_t i = 0; i < m_moveInstructions.size(); ++i) {
		if (m_moveInstructions[i]->m_merge) {
			m_state = Tstate::MERGING;
			const sf::Vector2i new_pos = m_moveInstructions[i]->getNewPos();
			const sf::Vector2i old_pos = m_moveInstructions[i]->getOldPos();
			delete m_matrix[old_pos.x][old_pos.y];
			m_matrix[old_pos.x][old_pos.y] = nullptr;

			m_mergeInstructions.emplace_back(new MergeInstruction{ new_pos, m_matrix[new_pos.x][new_pos.y] });
			m_matrix[new_pos.x][new_pos.y] = new TileModel(m_mergeInstructions.back()->tile->getType() * 2);
			--m_tiles;

			m_addedScore += m_mergeInstructions.back()->tile->getType() * 2;
		}
		else {
			const sf::Vector2i new_pos = m_moveInstructions[i]->getNewPos();
			const sf::Vector2i old_pos = m_moveInstructions[i]->getOldPos();
			m_matrix[new_pos.x][new_pos.y] = m_matrix[old_pos.x][old_pos.y];
			m_matrix[old_pos.x][old_pos.y] = nullptr;

			m_matrix[new_pos.x][new_pos.y]->setIsMoving(false);
			m_matrix[new_pos.x][new_pos.y]->setIsMerging(false);
		}
	}
	m_moveInstructions.clear();

	if (m_state == Tstate::MOVING) {
		m_state = Tstate::IDLE;
	}

	spawn();

	printf("\n\t\tAdded score: %d\n\n", m_addedScore);
}

void TileMatrixModel::endMerge()
{
	for (size_t i = 0; i < m_mergeInstructions.size(); ++i)
		delete m_mergeInstructions[i];
	m_mergeInstructions.clear();

	m_state = Tstate::IDLE;
}

TileMatrixModel::TileMatrixModel() : BaseModel() {}

TileMatrixModel::~TileMatrixModel()
{
	for (int i = 0; i < m_matrixHeight; ++i)
		for (int j = 0; j < m_matrixWidth; ++j)
			if (m_matrix[i][j])
				delete m_matrix[i][j];
}

void TileMatrixModel::spawn(const int amount)
{
	m_spawnInstructions.clear();

	for (int i = 0; i < amount; ++i) {
		sf::Vector2i pos{ rand() % 4, rand() % 4 };

		while (m_matrix[pos.x][pos.y])
			pos = { rand() % 4, rand() % 4 };

		addTile(pos);
	}

	this->notify("STARTED_SPAWN");	
}

void TileMatrixModel::addTile(const sf::Vector2i& pos, const int type)
{
	if (pos.x > m_matrixWidth - 1 || pos.y > m_matrixHeight - 1)
		printf("TileMatrixModel::addTile ERROR: Tile spawning position out of bounds\n");
	else {
		m_matrix[pos.x][pos.y] = new TileModel(type);
		this->m_spawnInstructions.emplace_back(new SpawnInstruction(pos, type));
		++m_tiles;

		m_isGameOver = isGameOver();
	}
}

void TileMatrixModel::clearBoard()
{
	m_moveInstructions.clear();

	for (int i = 0; i < m_matrixHeight; ++i)
		for (int j = 0; j < m_matrixWidth; ++j) {
			if (m_matrix[i][j])
				delete m_matrix[i][j];
			m_matrix[i][j] = nullptr;
		}

	m_addedScore = 0;
	m_mergedTiles = false;
	m_isGameOver = false;
	m_tiles = 0;
}

bool TileMatrixModel::isGameOver()
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
				m_matrix[i][j]->startGameOver();
			}

		//endMove();
		//endMerge();
		this->notify("GAME_OVER");
		return true;
	}

	return false;
}

// Accessors / Mutators
bool TileMatrixModel::getIsMoving() const
{
	return m_state == Tstate::MOVING;
}

bool TileMatrixModel::getIsGameOver() const
{
	return m_isGameOver;
}

int TileMatrixModel::getAddedScore() const
{
	return m_addedScore;
}

const std::vector<MoveInstructions*> &TileMatrixModel::getMoveInstructions() const
{
	return m_moveInstructions;
}

const std::vector<SpawnInstruction*>& TileMatrixModel::getSpawnInstructions() const
{
	return m_spawnInstructions;
}

const std::vector<MergeInstruction*>& TileMatrixModel::getMergeInstructions() const
{
	return m_mergeInstructions;
}

TileModel* const (&TileMatrixModel::getMatrix() const)[4][4]
{
	return m_matrix;
}

void TileMatrixModel::setAddedScore(const int value)
{
	m_addedScore = value;
}