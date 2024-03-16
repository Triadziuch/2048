#pragma once
#include "TileMatrix.h"

void TileMatrix::initTextures()
{
	for (int i = 1, k = 0; i < 13; i++, ++k) 
		textures[k] = &AssetManager::GetTexture("Textures/" + std::to_string(static_cast<int>(pow(2.f, static_cast<double>(i)))) + ".png");
		//textures[k].loadFromFile("Textures/" + std::to_string(i) + ".png");
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
	sf::Vector2f tilePos = playground_pos;
	tilePos.x += *outer_edge;
	tilePos.y += *outer_edge;
	
	tilePos.x += *inner_edge * x + *tile_width * x + *tile_width / 2.f;
	tilePos.y += *inner_edge * y + *tile_width * y + *tile_width / 2.f;

	return tilePos;
}

int TileMatrix::mergeLeft(int x, int y)
{
	// Merge if both are moving
	if (move_tile_instructions.size() != 0 && move_tile_instructions.back()->getOldPos().y == y && matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getType() == matrix[x][y]->getType() && !matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getMerging() && !matrix[x][y]->getMerging()) {
		MERGE_FLAG = true;
		matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->setMerging(true);
		matrix[x][y]->setMerging(true);
		return move_tile_instructions.back()->getNewPos().x;
	}
	// Merge if only one is moving
	for (int i = x - 1; i >= 0; --i)
		if (matrix[i][y] != nullptr) {
			if (matrix[i][y]->getType() == matrix[x][y]->getType() && !matrix[i][y]->getMerging() && !matrix[x][y]->getMerging()) {
				MERGE_FLAG = true;
				matrix[i][y]->setMerging(true);
				matrix[x][y]->setMerging(true);
				return i;
			}
			else
				break;
		}

	MERGE_FLAG = false;
	return -1;
}

int TileMatrix::mergeRight(int x, int y)
{
	// Merge if both are moving
	if (move_tile_instructions.size() != 0 && move_tile_instructions.back()->getOldPos().y == y && matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getType() == matrix[x][y]->getType() && !matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getMerging() && !matrix[x][y]->getMerging()) {
		MERGE_FLAG = true;
		matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->setMerging(true);
		matrix[x][y]->setMerging(true);
		return move_tile_instructions.back()->getNewPos().x;
	}
	// Merge if only one is moving
	for (int i = x + 1; i < matrixwidth; ++i)
		if (matrix[i][y] != nullptr) {
			if (matrix[i][y]->getType() == matrix[x][y]->getType() && !matrix[i][y]->getMerging() && !matrix[x][y]->getMerging()) {
				MERGE_FLAG = true;
				matrix[i][y]->setMerging(true);
				matrix[x][y]->setMerging(true);
				return i;
			}
			else
				break;
		}

	MERGE_FLAG = false;
	return -1;
}

int TileMatrix::mergeUp(int x, int y)
{
	// Merge if both are moving
	if (move_tile_instructions.size() != 0 && move_tile_instructions.back()->getOldPos().x == x && matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getType() == matrix[x][y]->getType() && !matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getMerging() && !matrix[x][y]->getMerging()) {
		MERGE_FLAG = true;
		matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->setMerging(true);
		matrix[x][y]->setMerging(true);
		return move_tile_instructions.back()->getNewPos().y;
	}
	// Merge if only one is moving
	for (int i = y - 1; i >= 0; --i)
		if (matrix[x][i] != nullptr) {
			if (matrix[x][i]->getType() == matrix[x][y]->getType() && !matrix[x][i]->getMerging() && !matrix[x][y]->getMerging()) {
				MERGE_FLAG = true;
				matrix[x][i]->setMerging(true);
				matrix[x][y]->setMerging(true);
				return i;
			}
			else
				break;
		}

	MERGE_FLAG = false;
	return -1;
}

int TileMatrix::mergeDown(int x, int y)
{
	// Merge if both are moving
	if (move_tile_instructions.size() != 0 && move_tile_instructions.back()->getOldPos().x == x && matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getType() == matrix[x][y]->getType() && !matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->getMerging() && !matrix[x][y]->getMerging()) {
		MERGE_FLAG = true;
		matrix[move_tile_instructions.back()->getOldPos().x][move_tile_instructions.back()->getOldPos().y]->setMerging(true);
		matrix[x][y]->setMerging(true);
		return move_tile_instructions.back()->getNewPos().y;
	}
	// Merge if only one is moving
	for (int i = y + 1; i < matrixheight; ++i)
		if (matrix[x][i] != nullptr) {
			if (matrix[x][i]->getType() == matrix[x][y]->getType() && !matrix[x][i]->getMerging() && !matrix[x][y]->getMerging()) {
				MERGE_FLAG = true;
				matrix[x][i]->setMerging(true);
				matrix[x][y]->setMerging(true);
				return i;
			}
			else
				break;
		}

	MERGE_FLAG = false;
	return -1;
}

int TileMatrix::findFreeLeft(int x, int y)
{
	int new_x = mergeLeft(x, y);
	if (new_x != -1)
		return new_x;
	else {
		for (int i = 0; i < x; ++i)
			if ((matrix[i][y] == nullptr || matrix[i][y]->getIsMoving()) && !willBeOccupied(i, y))
				return i;
		return x;
	}
}

int TileMatrix::findFreeRight(int x, int y)
{
	int new_x = mergeRight(x, y);
	if (new_x != -1)
		return new_x;
	else {
		for (int i = matrixwidth - 1; i > x; --i)
			if ((matrix[i][y] == nullptr || matrix[i][y]->getIsMoving()) && !willBeOccupied(i, y))
				return i;
		return x;
	}
	
}

int TileMatrix::findFreeUp(int x, int y)
{
	int new_y = mergeUp(x, y);
	if (new_y != -1)
		return new_y;
	else {
		for (int i = 0; i < y; ++i)
			if ((matrix[x][i] == nullptr || matrix[x][i]->getIsMoving()) && !willBeOccupied(x, i))
				return i;
		return y;
	}
	
}

int TileMatrix::findFreeDown(int x, int y)
{
	int new_y = mergeDown(x, y);
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
				sf::Vector2i new_pos = { findFreeLeft(i, j), j };
				int distance = i - new_pos.x;
				float pixel_distance = static_cast<float>(distance) * (*inner_edge + *tile_width);

				if (distance > 0) {
					do_move = true;
					movement_container->addMovement(matrix[i][j]->getSprite(), new movementInfo(matrix[i][j]->getSprite()->getPosition(), sf::Vector2f(matrix[i][j]->getSprite()->getPosition().x - pixel_distance, matrix[i][j]->getSprite()->getPosition().y), time_to_move, easeFunctions::getFunction(easeFunctions::IN_OUT_SINE), false, 0.f, 0.f));
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
				float pixel_distance = static_cast<float>(distance) * (*inner_edge + *tile_width);

				if (distance > 0) {
					do_move = true;
					movement_container->addMovement(matrix[i][j]->getSprite(), new movementInfo(matrix[i][j]->getSprite()->getPosition(), sf::Vector2f(matrix[i][j]->getSprite()->getPosition().x + pixel_distance, matrix[i][j]->getSprite()->getPosition().y), time_to_move, easeFunctions::getFunction(easeFunctions::IN_OUT_SINE), false, 0.f, 0.f));
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
				float pixel_distance = static_cast<float>(distance) * (*inner_edge + *tile_width);

				if (distance > 0) {
					do_move = true;
					movement_container->addMovement(matrix[i][j]->getSprite(), new movementInfo(matrix[i][j]->getSprite()->getPosition(), sf::Vector2f(matrix[i][j]->getSprite()->getPosition().x, matrix[i][j]->getSprite()->getPosition().y - pixel_distance), time_to_move, easeFunctions::getFunction(easeFunctions::IN_OUT_SINE), false, 0.f, 0.f));
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
				float pixel_distance = static_cast<float>(distance) * (*inner_edge + *tile_width);

				if (distance > 0) {
					do_move = true;
					movement_container->addMovement(matrix[i][j]->getSprite(), new movementInfo(matrix[i][j]->getSprite()->getPosition(), sf::Vector2f(matrix[i][j]->getSprite()->getPosition().x, matrix[i][j]->getSprite()->getPosition().y + pixel_distance), time_to_move, easeFunctions::getFunction(easeFunctions::IN_OUT_SINE), false, 0.f, 0.f));
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
				matrix[i][j]->~Tile();
				matrix[i][j] = nullptr;
			}

	added_score = 0;
	current_move_time = 0.f;
	MOVE_FLAG = false;
	MERGE_FLAG = false;
	GAMEOVER_FLAG = false;
	tiles = 0;
}

bool TileMatrix::isGameOver()
{
	if (tiles != 16)
		return false;
	else {
		for (int i = 1; i < matrixheight - 1; ++i)
			for (int j = 1; j < matrixwidth - 1; ++j)
				if (matrix[j][i]->getType() == matrix[j - 1][i]->getType() ||
					matrix[j][i]->getType() == matrix[j + 1][i]->getType() ||
					matrix[j][i]->getType() == matrix[j][i - 1]->getType() ||
					matrix[j][i]->getType() == matrix[j][i + 1]->getType())
					return false;

		for (int i = 0; i < matrixwidth - 1; ++i)
			if (matrix[i][0]->getType() == matrix[i + 1][0]->getType() || matrix[i][matrixheight - 1]->getType() == matrix[i + 1][matrixheight - 1]->getType())
				return false;

		for (int i = 0; i < matrixheight - 1; ++i)
			if (matrix[0][i]->getType() == matrix[0][i + 1]->getType() || matrix[matrixwidth - 1][i]->getType() == matrix[matrixwidth - 1][i + 1]->getType())
				return false;

		for (int i = 0; i < matrixheight; ++i)
			for (int j = 0; j < matrixwidth; ++j) {
				matrix[i][j]->setScale(*scale);
				matrix[i][j]->gameOver();
			}
				

		return true;
	}

	return false;
}

void TileMatrix::addMoveInstructions(sf::Vector2i new_pos_, sf::Vector2i old_pos_, int distance_)
{
	if (distance_ > 0) {
		MOVE_FLAG = true;
		matrix[old_pos_.x][old_pos_.y]->setIsMoving(true);
		move_tile_instructions.push_back(new MoveTile(new_pos_, old_pos_, MERGE_FLAG));
		MERGE_FLAG = false;
	}
}

bool TileMatrix::willBeOccupied(int x, int y)
{
	for (int i = move_tile_instructions.size() - 1; i >= 0; --i)
		if (move_tile_instructions[i]->getNewPos().x == x && move_tile_instructions[i]->getNewPos().y == y)
				return true;
	return false;
}

TileMatrix::TileMatrix(float* scale_, float* outer_, float* inner_, float* tile_width_, sf::Vector2f playground_pos_)
{
	for (int i = 0; i < matrixheight; ++i)
		for (int j = 0; j < matrixwidth; ++j)
			matrix[i][j] = nullptr;

	scale = scale_;
	outer_edge = outer_;
	inner_edge = inner_;
	tile_width = tile_width_;
	playground_pos = playground_pos_;

	movement_manager = MovementManager::getInstance();
	movement_container = MovementContainer::getInstance();

	scaling_routine = movement_manager->createScalingRoutine("TILE_SPAWNING");
	scaling_routine->addScaling(new scalingInfo(sf::Vector2f(0.1f, 0.1f) * *scale, sf::Vector2f(1.f, 1.f) * *scale, 0.2f, easeFunctions::getFunction(easeFunctions::OUT_QUAD), false, 0.f, 0.f));
	
	merge_routine = movement_manager->createScalingRoutine("TILE_MERGING");
	merge_routine->addScaling(new scalingInfo(sf::Vector2f(0.1f, 0.1f) * *scale, sf::Vector2f(1.f, 1.f) * *scale, time_to_merge, easeFunctions::getFunction(easeFunctions::OUT_BACK), false, 0.f, 0.f));
	initTextures();
}

TileMatrix::~TileMatrix()
{
	for (int i = 0; i < matrixheight; ++i)
		for (int j = 0; j < matrixwidth; ++j)
			if (matrix[i][j])
				matrix[i][j]->~Tile();
}

void TileMatrix::update(float dt)
{
	movement_container->update(dt);
	if (do_move)
		updateMove(dt);

	if (m_isMerging)
		updateMerge(dt);

	for (size_t i = 0; i < matrixheight; ++i)
		for (size_t j = 0; j < matrixwidth; ++j)
			if (matrix[i][j])
				matrix[i][j]->update(dt);

	//for (auto& tile : spawning_tiles)
	//	if (tile->updateOpacity(dt) == false)
	//		spawning_tiles.erase(std::remove(spawning_tiles.begin(), spawning_tiles.end(), tile), spawning_tiles.end());

	movement_manager->update(dt);
}

void TileMatrix::spawn(unsigned amount_)
{
	for (unsigned i = 0; i < amount_; ++i) {
		sf::Vector2i pos = { rand() % 4, rand() % 4 };

		while (matrix[pos.x][pos.y] != nullptr) {
			pos = { rand() % 4, rand() % 4 };
		}

		addTile(pos);
	}
}

void TileMatrix::addTile(sf::Vector2i pos_, int type_)
{
	if (pos_.x > matrixwidth - 1 || pos_.y > matrixheight - 1) {
		std::cout << "Invalid tile spawning position" << std::endl;
		system("pause");
	}
	else {
		matrix[pos_.x][pos_.y] = new Tile(type_, textures[findID(type_)], scale, calculateTilePos(pos_.x, pos_.y));
		matrix[pos_.x][pos_.y]->startSpawning();
		++tiles;
	}
}

void TileMatrix::updateMove(float dt)
{
	if (current_move_time < time_to_move) 
		current_move_time += dt;
	else {
		added_score = 0;
		
		if (current_merge_time == 0.f) {
			for (size_t i = 0; i < move_tile_instructions.size(); ++i) {
				if (move_tile_instructions[i]->m_merge) {
					m_isMerging = true;
					const sf::Vector2i new_pos = move_tile_instructions[i]->getNewPos();
					const sf::Vector2i old_pos = move_tile_instructions[i]->getOldPos();

					movement_manager->unlinkScalingRoutine(matrix[old_pos.x][old_pos.y]->getSprite(), "TILE_SPAWNING");
					matrix[old_pos.x][old_pos.y]->~Tile();
					matrix[old_pos.x][old_pos.y] = nullptr;

					merge_tile_instructions.push_back(matrix[new_pos.x][new_pos.y]);
					matrix[new_pos.x][new_pos.y] = new Tile(merge_tile_instructions.back()->getType() * 2, textures[findID(merge_tile_instructions.back()->getType() * 2)], scale, calculateTilePos(new_pos.x, new_pos.y));
					matrix[new_pos.x][new_pos.y]->startMerging();
					--tiles;

					// Updating score
					added_score += merge_tile_instructions.back()->getType() * 2;
				}
				else {
					sf::Vector2i new_pos = move_tile_instructions[i]->getNewPos();
					sf::Vector2i old_pos = move_tile_instructions[i]->getOldPos();
					matrix[new_pos.x][new_pos.y] = matrix[old_pos.x][old_pos.y];
					matrix[new_pos.x][new_pos.y]->setIsMoving(false);
					matrix[old_pos.x][old_pos.y] = nullptr;
					matrix[new_pos.x][new_pos.y]->setMerging(false);
				}
			}
			move_tile_instructions.clear();

			if (!m_isMerging) {
				current_move_time = 0.f;
				GAMEOVER_FLAG = isGameOver();
			}

			do_move = false;

			if (MOVE_FLAG)
				spawn();
			MOVE_FLAG = false;
		}
	}
}

void TileMatrix::updateMerge(float dt)
{
	if (current_merge_time < time_to_merge) {
		current_merge_time += dt;
	}
	else {
		current_move_time = 0.f;
		current_merge_time = 0.f;

		for (size_t i = 0; i < merge_tile_instructions.size(); ++i)
			delete merge_tile_instructions[i];
		merge_tile_instructions.clear();

		do_move = false;
		m_isMerging = false;
		GAMEOVER_FLAG = isGameOver();
	}
}

void TileMatrix::endMerge()
{
	if (m_isMerging) {
		current_move_time = 0.f;
		current_merge_time = 0.f;

		for (size_t i = 0; i < merge_tile_instructions.size(); ++i) 
			delete merge_tile_instructions[i];
		merge_tile_instructions.clear();

		do_move = false;
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
