#include "TileMatrix.h"

void TileMatrix::initTextures()
{
	for (int i = 1, k = 0; i < 13; i++, ++k) 
		this->textures[k] = &AssetManager::GetTexture("Textures/" + std::to_string(static_cast<int>(pow(2.f, static_cast<double>(i)))) + ".png");
		//this->textures[k].loadFromFile("Textures/" + std::to_string(i) + ".png");
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
	sf::Vector2f tilePos = this->playground_pos;
	tilePos.x += *this->outer_edge;
	tilePos.y += *this->outer_edge;
	
	tilePos.x += *this->inner_edge * x + *this->tile_width * x + *this->tile_width / 2.f;
	tilePos.y += *this->inner_edge * y + *this->tile_width * y + *this->tile_width / 2.f;

	return tilePos;
}

int TileMatrix::mergeLeft(int x, int y)
{
	// Merge if both are moving
	if (this->move_tile_instructions.size() != 0 && this->move_tile_instructions.back()->getOldPos().y == y && this->matrix[this->move_tile_instructions.back()->getOldPos().x][this->move_tile_instructions.back()->getOldPos().y]->getType() == this->matrix[x][y]->getType() && !this->matrix[this->move_tile_instructions.back()->getOldPos().x][this->move_tile_instructions.back()->getOldPos().y]->getMerging() && !this->matrix[x][y]->getMerging()) {
		this->MERGE_FLAG = true;
		this->matrix[this->move_tile_instructions.back()->getOldPos().x][this->move_tile_instructions.back()->getOldPos().y]->setMerging(true);
		this->matrix[x][y]->setMerging(true);
		return this->move_tile_instructions.back()->getNewPos().x;
	}
	// Merge if only one is moving
	for (int i = x - 1; i >= 0; --i)
		if (this->matrix[i][y] != nullptr) {
			if (this->matrix[i][y]->getType() == this->matrix[x][y]->getType() && !this->matrix[i][y]->getMerging() && !this->matrix[x][y]->getMerging()) {
				this->MERGE_FLAG = true;
				this->matrix[i][y]->setMerging(true);
				this->matrix[x][y]->setMerging(true);
				return i;
			}
			else
				break;
		}

	this->MERGE_FLAG = false;
	return -1;
}

int TileMatrix::mergeRight(int x, int y)
{
	// Merge if both are moving
	if (this->move_tile_instructions.size() != 0 && this->move_tile_instructions.back()->getOldPos().y == y && this->matrix[this->move_tile_instructions.back()->getOldPos().x][this->move_tile_instructions.back()->getOldPos().y]->getType() == this->matrix[x][y]->getType() && !this->matrix[this->move_tile_instructions.back()->getOldPos().x][this->move_tile_instructions.back()->getOldPos().y]->getMerging() && !this->matrix[x][y]->getMerging()) {
		this->MERGE_FLAG = true;
		this->matrix[this->move_tile_instructions.back()->getOldPos().x][this->move_tile_instructions.back()->getOldPos().y]->setMerging(true);
		this->matrix[x][y]->setMerging(true);
		return this->move_tile_instructions.back()->getNewPos().x;
	}
	// Merge if only one is moving
	for (int i = x + 1; i < this->matrixwidth; ++i)
		if (this->matrix[i][y] != nullptr) {
			if (this->matrix[i][y]->getType() == this->matrix[x][y]->getType() && !this->matrix[i][y]->getMerging() && !this->matrix[x][y]->getMerging()) {
				this->MERGE_FLAG = true;
				this->matrix[i][y]->setMerging(true);
				this->matrix[x][y]->setMerging(true);
				return i;
			}
			else
				break;
		}

	this->MERGE_FLAG = false;
	return -1;
}

int TileMatrix::mergeUp(int x, int y)
{
	// Merge if both are moving
	if (this->move_tile_instructions.size() != 0 && this->move_tile_instructions.back()->getOldPos().x == x && this->matrix[this->move_tile_instructions.back()->getOldPos().x][this->move_tile_instructions.back()->getOldPos().y]->getType() == this->matrix[x][y]->getType() && !this->matrix[this->move_tile_instructions.back()->getOldPos().x][this->move_tile_instructions.back()->getOldPos().y]->getMerging() && !this->matrix[x][y]->getMerging()) {
		this->MERGE_FLAG = true;
		this->matrix[this->move_tile_instructions.back()->getOldPos().x][this->move_tile_instructions.back()->getOldPos().y]->setMerging(true);
		this->matrix[x][y]->setMerging(true);
		return this->move_tile_instructions.back()->getNewPos().y;
	}
	// Merge if only one is moving
	for (int i = y - 1; i >= 0; --i)
		if (this->matrix[x][i] != nullptr) {
			if (this->matrix[x][i]->getType() == this->matrix[x][y]->getType() && !this->matrix[x][i]->getMerging() && !this->matrix[x][y]->getMerging()) {
				this->MERGE_FLAG = true;
				this->matrix[x][i]->setMerging(true);
				this->matrix[x][y]->setMerging(true);
				return i;
			}
			else
				break;
		}

	this->MERGE_FLAG = false;
	return -1;
}

int TileMatrix::mergeDown(int x, int y)
{
	// Merge if both are moving
	if (this->move_tile_instructions.size() != 0 && this->move_tile_instructions.back()->getOldPos().x == x && this->matrix[this->move_tile_instructions.back()->getOldPos().x][this->move_tile_instructions.back()->getOldPos().y]->getType() == this->matrix[x][y]->getType() && !this->matrix[this->move_tile_instructions.back()->getOldPos().x][this->move_tile_instructions.back()->getOldPos().y]->getMerging() && !this->matrix[x][y]->getMerging()) {
		this->MERGE_FLAG = true;
		this->matrix[this->move_tile_instructions.back()->getOldPos().x][this->move_tile_instructions.back()->getOldPos().y]->setMerging(true);
		this->matrix[x][y]->setMerging(true);
		return this->move_tile_instructions.back()->getNewPos().y;
	}
	// Merge if only one is moving
	for (int i = y + 1; i < this->matrixheight; ++i)
		if (this->matrix[x][i] != nullptr) {
			if (this->matrix[x][i]->getType() == this->matrix[x][y]->getType() && !this->matrix[x][i]->getMerging() && !this->matrix[x][y]->getMerging()) {
				this->MERGE_FLAG = true;
				this->matrix[x][i]->setMerging(true);
				this->matrix[x][y]->setMerging(true);
				return i;
			}
			else
				break;
		}

	this->MERGE_FLAG = false;
	return -1;
}

int TileMatrix::findFreeLeft(int x, int y)
{
	int new_x = this->mergeLeft(x, y);
	if (new_x != -1)
		return new_x;
	else {
		for (int i = 0; i < x; ++i)
			if ((this->matrix[i][y] == nullptr || this->matrix[i][y]->getIsMoving()) && !this->willBeOccupied(i, y))
				return i;
		return x;
	}
}

int TileMatrix::findFreeRight(int x, int y)
{
	int new_x = this->mergeRight(x, y);
	if (new_x != -1)
		return new_x;
	else {
		for (int i = this->matrixwidth - 1; i > x; --i)
			if ((this->matrix[i][y] == nullptr || this->matrix[i][y]->getIsMoving()) && !this->willBeOccupied(i, y))
				return i;
		return x;
	}
	
}

int TileMatrix::findFreeUp(int x, int y)
{
	int new_y = this->mergeUp(x, y);
	if (new_y != -1)
		return new_y;
	else {
		for (int i = 0; i < y; ++i)
			if ((this->matrix[x][i] == nullptr || this->matrix[x][i]->getIsMoving()) && !this->willBeOccupied(x, i))
				return i;
		return y;
	}
	
}

int TileMatrix::findFreeDown(int x, int y)
{
	int new_y = this->mergeDown(x, y);
	if (new_y != -1)
		return new_y;
	else {
		for (int i = this->matrixheight - 1; i > y; --i)
			if ((this->matrix[x][i] == nullptr || this->matrix[x][i]->getIsMoving()) && !this->willBeOccupied(x, i))
				return i;
		return y;
	}
}

void TileMatrix::moveLeft()
{
	endMerge();
	for (int j = 0; j < this->matrixheight; ++j)
		for (int i = 0; i < this->matrixwidth; ++i)
			if (this->matrix[i][j] != nullptr) {
				sf::Vector2i new_pos = { this->findFreeLeft(i, j), j };
				int distance = i - new_pos.x;
				float pixel_distance = static_cast<float>(distance) * (*this->inner_edge + *this->tile_width);

				if (distance > 0) {
					this->do_move = true;
					movement_container->addMovement(this->matrix[i][j]->getSprite(), new movementInfo(this->matrix[i][j]->getSprite()->getPosition(), sf::Vector2f(this->matrix[i][j]->getSprite()->getPosition().x - pixel_distance, this->matrix[i][j]->getSprite()->getPosition().y), time_to_move, easeFunctions::getFunction(easeFunctions::IN_OUT_SINE), false, 0.f, 0.f));
					this->addMoveInstructions(new_pos, { i, j }, distance);
				}
			}
}

void TileMatrix::moveRight()
{
	endMerge();
	for (int j = 0; j < this->matrixheight; ++j)
		for (int i = this->matrixwidth - 1; i >= 0; --i)
			if (this->matrix[i][j] != nullptr) {
				sf::Vector2i new_pos = { this->findFreeRight(i, j), j };
				int distance = new_pos.x - i;
				float pixel_distance = static_cast<float>(distance) * (*this->inner_edge + *this->tile_width);

				if (distance > 0) {
					this->do_move = true;
					movement_container->addMovement(this->matrix[i][j]->getSprite(), new movementInfo(this->matrix[i][j]->getSprite()->getPosition(), sf::Vector2f(this->matrix[i][j]->getSprite()->getPosition().x + pixel_distance, this->matrix[i][j]->getSprite()->getPosition().y), time_to_move, easeFunctions::getFunction(easeFunctions::IN_OUT_SINE), false, 0.f, 0.f));
					this->addMoveInstructions(new_pos, { i, j }, distance);
				}
			}
}

void TileMatrix::moveUp()
{
	endMerge();
	for (int i = 0; i < this->matrixwidth; ++i)
		for (int j = 0; j < this->matrixheight; ++j)
			if (this->matrix[i][j] != nullptr) {
				sf::Vector2i new_pos = { i, this->findFreeUp(i, j) };
				int distance = j - new_pos.y;
				float pixel_distance = static_cast<float>(distance) * (*this->inner_edge + *this->tile_width);

				if (distance > 0) {
					this->do_move = true;
					movement_container->addMovement(this->matrix[i][j]->getSprite(), new movementInfo(this->matrix[i][j]->getSprite()->getPosition(), sf::Vector2f(this->matrix[i][j]->getSprite()->getPosition().x, this->matrix[i][j]->getSprite()->getPosition().y - pixel_distance), time_to_move, easeFunctions::getFunction(easeFunctions::IN_OUT_SINE), false, 0.f, 0.f));
					this->addMoveInstructions(new_pos, { i, j }, distance);
				}
			}
}

void TileMatrix::moveDown()
{
	endMerge();
	for (int i = 0; i < this->matrixwidth; ++i)
		for (int j = this->matrixheight - 1; j >= 0; --j)
			if (this->matrix[i][j] != nullptr) {
				sf::Vector2i new_pos = { i, this->findFreeDown(i, j) };
				int distance = new_pos.y - j;
				float pixel_distance = static_cast<float>(distance) * (*this->inner_edge + *this->tile_width);

				if (distance > 0) {
					this->do_move = true;
					movement_container->addMovement(this->matrix[i][j]->getSprite(), new movementInfo(this->matrix[i][j]->getSprite()->getPosition(), sf::Vector2f(this->matrix[i][j]->getSprite()->getPosition().x, this->matrix[i][j]->getSprite()->getPosition().y + pixel_distance), time_to_move, easeFunctions::getFunction(easeFunctions::IN_OUT_SINE), false, 0.f, 0.f));
					this->addMoveInstructions(new_pos, { i, j }, distance);
				}
			}
}

void TileMatrix::clearBoard()
{
	this->move_tile_instructions.clear();
	
	for (int i = 0; i < this->matrixheight; ++i)
		for (int j = 0; j < this->matrixwidth; ++j) {
			if (this->matrix[i][j] != nullptr)
				this->matrix[i][j]->~Tile();
				this->matrix[i][j] = nullptr;
			}

	this->added_score = 0;
	this->current_move_time = 0.f;
	this->MOVE_FLAG = false;
	this->MERGE_FLAG = false;
	this->GAMEOVER_FLAG = false;
	this->tiles = 0;
}

bool TileMatrix::isGameOver()
{
	if (this->tiles != 16)
		return false;
	else {
		for (int i = 1; i < this->matrixheight - 1; ++i)
			for (int j = 1; j < this->matrixwidth - 1; ++j)
				if (this->matrix[j][i]->getType() == this->matrix[j - 1][i]->getType() ||
					this->matrix[j][i]->getType() == this->matrix[j + 1][i]->getType() ||
					this->matrix[j][i]->getType() == this->matrix[j][i - 1]->getType() ||
					this->matrix[j][i]->getType() == this->matrix[j][i + 1]->getType())
					return false;

		for (int i = 0; i < this->matrixwidth - 1; ++i)
			if (this->matrix[i][0]->getType() == this->matrix[i + 1][0]->getType() || this->matrix[i][this->matrixheight - 1]->getType() == this->matrix[i + 1][this->matrixheight - 1]->getType())
				return false;

		for (int i = 0; i < this->matrixheight - 1; ++i)
			if (this->matrix[0][i]->getType() == this->matrix[0][i + 1]->getType() || this->matrix[this->matrixwidth - 1][i]->getType() == this->matrix[this->matrixwidth - 1][i + 1]->getType())
				return false;

		for (int i = 0; i < this->matrixheight; ++i)
			for (int j = 0; j < this->matrixwidth; ++j) {
				this->matrix[i][j]->setScale(*this->scale);
				this->matrix[i][j]->gameOver();
			}
				

		return true;
	}

	return false;
}

void TileMatrix::addMoveInstructions(sf::Vector2i new_pos_, sf::Vector2i old_pos_, int distance_)
{
	if (distance_ > 0) {
		this->MOVE_FLAG = true;
		this->matrix[old_pos_.x][old_pos_.y]->setIsMoving(true);
		this->move_tile_instructions.push_back(new MoveTile(new_pos_, old_pos_, this->MERGE_FLAG));
		this->MERGE_FLAG = false;
	}
}

bool TileMatrix::willBeOccupied(int x, int y)
{
	for (int i = this->move_tile_instructions.size() - 1; i >= 0; --i)
		if (this->move_tile_instructions[i]->getNewPos().x == x && this->move_tile_instructions[i]->getNewPos().y == y)
				return true;
	return false;
}

TileMatrix::TileMatrix(float* scale_, float* outer_, float* inner_, float* tile_width_, sf::Vector2f playground_pos_)
{
	for (int i = 0; i < this->matrixheight; ++i)
		for (int j = 0; j < this->matrixwidth; ++j)
			this->matrix[i][j] = nullptr;

	this->scale = scale_;
	this->outer_edge = outer_;
	this->inner_edge = inner_;
	this->tile_width = tile_width_;
	this->playground_pos = playground_pos_;

	movement_manager = MovementManager::getInstance();
	movement_container = MovementContainer::getInstance();
	scaling_routine = movement_manager->createScalingRoutine("TILE_SPAWNING");
	scaling_routine->addScaling(new scalingInfo(sf::Vector2f(0.1f, 0.1f) * *this->scale, sf::Vector2f(1.f, 1.f) * *this->scale, 0.2f, easeFunctions::getFunction(easeFunctions::OUT_QUAD), false, 0.f, 0.f));
	
	merge_routine = movement_manager->createScalingRoutine("TILE_SPAWNING_MERGE");
	merge_routine->addScaling(new scalingInfo(sf::Vector2f(0.1f, 0.1f) * *this->scale, sf::Vector2f(1.f, 1.f) * *this->scale, time_to_merge, easeFunctions::getFunction(easeFunctions::OUT_BACK), false, 0.f, 0.f));
	this->initTextures();
}

TileMatrix::~TileMatrix()
{
	for (int i = 0; i < this->matrixheight; ++i)
		for (int j = 0; j < this->matrixwidth; ++j)
			if (this->matrix[i][j] != nullptr)
				this->matrix[i][j]->~Tile();
}

void TileMatrix::update(float dt)
{
	movement_container->update(dt);
	if (this->do_move)
		this->updateMove(dt);

	if (m_isMerging)
		this->updateMerge(dt);

	for (auto& tile : spawning_tiles)
		if (tile->updateOpacity(dt) == false)
			spawning_tiles.erase(std::remove(spawning_tiles.begin(), spawning_tiles.end(), tile), spawning_tiles.end());

	movement_manager->update(dt);
}

void TileMatrix::spawn(unsigned amount_)
{
	for (unsigned i = 0; i < amount_; ++i) {
		sf::Vector2i pos = { rand() % 4, rand() % 4 };

		while (this->matrix[pos.x][pos.y] != nullptr) {
			pos = { rand() % 4, rand() % 4 };
		}

		this->addTile(pos);
	}
	
}

void TileMatrix::addTile(sf::Vector2i pos_, int type_)
{
	if (pos_.x > this->matrixwidth - 1 || pos_.y > this->matrixheight - 1) {
		std::cout << "Invalid tile spawning position" << std::endl;
		system("pause");
	}
	else {
		this->matrix[pos_.x][pos_.y] = new Tile(type_, this->textures[this->findID(type_)], this->scale);
		this->matrix[pos_.x][pos_.y]->setPosition(this->calculateTilePos(pos_.x, pos_.y));
		movement_manager->linkScalingRoutine(*this->matrix[pos_.x][pos_.y]->getSprite(), "TILE_SPAWNING");
		movement_manager->startScalingRoutine(*this->matrix[pos_.x][pos_.y]->getSprite(), "TILE_SPAWNING");
		spawning_tiles.push_back(this->matrix[pos_.x][pos_.y]);
		++this->tiles;
	}
}

void TileMatrix::updateMove(float dt)
{
	if (this->current_move_time < this->time_to_move) 
		this->current_move_time += dt;
	else {
		this->added_score = 0;
		
		if (current_merge_time == 0.f) {
			for (size_t i = 0; i < this->move_tile_instructions.size(); ++i) {
				if (this->move_tile_instructions[i]->m_merge) {
					m_isMerging = true;
					const sf::Vector2i new_pos = this->move_tile_instructions[i]->getNewPos();
					const sf::Vector2i old_pos = this->move_tile_instructions[i]->getOldPos();

					movement_manager->unlinkScalingRoutine(this->matrix[old_pos.x][old_pos.y]->getSprite(), "TILE_SPAWNING");
					this->matrix[old_pos.x][old_pos.y]->~Tile();
					this->matrix[old_pos.x][old_pos.y] = nullptr;

					merge_tile_instructions.push_back(this->matrix[new_pos.x][new_pos.y]);
					this->matrix[new_pos.x][new_pos.y] = nullptr;
					this->matrix[new_pos.x][new_pos.y] = new Tile(merge_tile_instructions.back()->getType() * 2, this->textures[this->findID(merge_tile_instructions.back()->getType() * 2)], this->scale);
					this->matrix[new_pos.x][new_pos.y]->setPosition(this->calculateTilePos(new_pos.x, new_pos.y));
					movement_manager->linkScalingRoutine(*this->matrix[new_pos.x][new_pos.y]->getSprite(), "TILE_SPAWNING_MERGE");
					movement_manager->startScalingRoutine(*this->matrix[new_pos.x][new_pos.y]->getSprite(), "TILE_SPAWNING_MERGE");
					--this->tiles;

					// Updating score
					this->added_score += merge_tile_instructions.back()->getType() * 2;
				}
				else {
					sf::Vector2i new_pos = this->move_tile_instructions[i]->getNewPos();
					sf::Vector2i old_pos = this->move_tile_instructions[i]->getOldPos();
					this->matrix[new_pos.x][new_pos.y] = this->matrix[old_pos.x][old_pos.y];
					this->matrix[new_pos.x][new_pos.y]->setIsMoving(false);
					this->matrix[old_pos.x][old_pos.y] = nullptr;
					this->matrix[new_pos.x][new_pos.y]->setMerging(false);
				}
			}
			this->move_tile_instructions.clear();

			if (!m_isMerging) {
				this->current_move_time = 0.f;
				this->GAMEOVER_FLAG = this->isGameOver();
			}

			this->do_move = false;

			if (this->MOVE_FLAG)
				this->spawn();
			this->MOVE_FLAG = false;
		}
	}
}

void TileMatrix::updateMerge(float dt)
{
	if (current_merge_time < this->time_to_merge) {
		this->current_merge_time += dt;
	}
	else {
		this->current_move_time = 0.f;
		this->current_merge_time = 0.f;

		for (size_t i = 0; i < merge_tile_instructions.size(); ++i) {
			movement_manager->unlinkScalingRoutine(merge_tile_instructions[i]->getSprite(), "TILE_SPAWNING");
			merge_tile_instructions[i]->~Tile();
		}
		merge_tile_instructions.clear();
		this->do_move = false;
		m_isMerging = false;
		this->GAMEOVER_FLAG = this->isGameOver();
	}
}

void TileMatrix::endMerge()
{
	if (m_isMerging) {
		this->current_move_time = 0.f;
		this->current_merge_time = 0.f;

		for (size_t i = 0; i < merge_tile_instructions.size(); ++i) {
			movement_manager->unlinkScalingRoutine(merge_tile_instructions[i]->getSprite(), "TILE_SPAWNING");
			merge_tile_instructions[i]->~Tile();
		}

		merge_tile_instructions.clear();
		this->do_move = false;
		m_isMerging = false;
	}
}

void TileMatrix::render(sf::RenderTarget& target)
{
	for (auto tile: merge_tile_instructions)
		tile->render(target);

	for (int i = 0; i < this->matrixheight; ++i)
		for (int j = 0; j < this->matrixwidth; ++j)
			if (this->matrix[i][j] != nullptr)
				this->matrix[i][j]->render(target);
}
