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

sf::Vector2f TileMatrix::calculateTilePos(int x_, int y_)
{
	sf::Vector2f tilePos = this->playground_pos;
	tilePos.x += *this->outer_edge;
	tilePos.y += *this->outer_edge;
	
	tilePos.x += *this->inner_edge * x_ + *this->tile_width * x_ + *this->tile_width / 2.f;
	tilePos.y += *this->inner_edge * y_ + *this->tile_width * y_ + *this->tile_width / 2.f;

	return tilePos;
}

int TileMatrix::mergeLeft(int x_, int y_)
{
	// Merge if both are moving
	if (this->move_tile_instructions.size() != 0 && this->move_tile_instructions.back()->old_pos.y == y_ && this->matrix[this->move_tile_instructions.back()->old_pos.x][this->move_tile_instructions.back()->old_pos.y]->getType() == this->matrix[x_][y_]->getType() && !this->matrix[this->move_tile_instructions.back()->old_pos.x][this->move_tile_instructions.back()->old_pos.y]->getMerging() && !this->matrix[x_][y_]->getMerging()) {
		this->MERGE_FLAG = true;
		this->matrix[this->move_tile_instructions.back()->old_pos.x][this->move_tile_instructions.back()->old_pos.y]->setMerging(true);
		this->matrix[x_][y_]->setMerging(true);
		return this->move_tile_instructions.back()->new_pos.x;
	}
	// Merge if only one is moving
	for (int i = x_ - 1; i >= 0; --i)
		if (this->matrix[i][y_] != NULL) {
			if (this->matrix[i][y_]->getType() == this->matrix[x_][y_]->getType() && !this->matrix[i][y_]->getMerging() && !this->matrix[x_][y_]->getMerging()) {
				this->MERGE_FLAG = true;
				this->matrix[i][y_]->setMerging(true);
				this->matrix[x_][y_]->setMerging(true);
				return i;
			}
			else
				break;
		}

	this->MERGE_FLAG = false;
	return -1;
}

int TileMatrix::mergeRight(int x_, int y_)
{
	// Merge if both are moving
	if (this->move_tile_instructions.size() != 0 && this->move_tile_instructions.back()->old_pos.y == y_ && this->matrix[this->move_tile_instructions.back()->old_pos.x][this->move_tile_instructions.back()->old_pos.y]->getType() == this->matrix[x_][y_]->getType() && !this->matrix[this->move_tile_instructions.back()->old_pos.x][this->move_tile_instructions.back()->old_pos.y]->getMerging() && !this->matrix[x_][y_]->getMerging()) {
		this->MERGE_FLAG = true;
		this->matrix[this->move_tile_instructions.back()->old_pos.x][this->move_tile_instructions.back()->old_pos.y]->setMerging(true);
		this->matrix[x_][y_]->setMerging(true);
		return this->move_tile_instructions.back()->new_pos.x;
	}
	// Merge if only one is moving
	for (int i = x_ + 1; i < this->matrix_width; ++i)
		if (this->matrix[i][y_] != NULL) {
			if (this->matrix[i][y_]->getType() == this->matrix[x_][y_]->getType() && !this->matrix[i][y_]->getMerging() && !this->matrix[x_][y_]->getMerging()) {
				this->MERGE_FLAG = true;
				this->matrix[i][y_]->setMerging(true);
				this->matrix[x_][y_]->setMerging(true);
				return i;
			}
			else
				break;
		}

	this->MERGE_FLAG = false;
	return -1;
}

int TileMatrix::mergeUp(int x_, int y_)
{
	// Merge if both are moving
	if (this->move_tile_instructions.size() != 0 && this->move_tile_instructions.back()->old_pos.x == x_ && this->matrix[this->move_tile_instructions.back()->old_pos.x][this->move_tile_instructions.back()->old_pos.y]->getType() == this->matrix[x_][y_]->getType() && !this->matrix[this->move_tile_instructions.back()->old_pos.x][this->move_tile_instructions.back()->old_pos.y]->getMerging() && !this->matrix[x_][y_]->getMerging()) {
		this->MERGE_FLAG = true;
		this->matrix[this->move_tile_instructions.back()->old_pos.x][this->move_tile_instructions.back()->old_pos.y]->setMerging(true);
		this->matrix[x_][y_]->setMerging(true);
		return this->move_tile_instructions.back()->new_pos.y;
	}
	// Merge if only one is moving
	for (int i = y_ - 1; i >= 0; --i)
		if (this->matrix[x_][i] != NULL) {
			if (this->matrix[x_][i]->getType() == this->matrix[x_][y_]->getType() && !this->matrix[x_][i]->getMerging() && !this->matrix[x_][y_]->getMerging()) {
				this->MERGE_FLAG = true;
				this->matrix[x_][i]->setMerging(true);
				this->matrix[x_][y_]->setMerging(true);
				return i;
			}
			else
				break;
		}

	this->MERGE_FLAG = false;
	return -1;
}

int TileMatrix::mergeDown(int x_, int y_)
{
	// Merge if both are moving
	if (this->move_tile_instructions.size() != 0 && this->move_tile_instructions.back()->old_pos.x == x_ && this->matrix[this->move_tile_instructions.back()->old_pos.x][this->move_tile_instructions.back()->old_pos.y]->getType() == this->matrix[x_][y_]->getType() && !this->matrix[this->move_tile_instructions.back()->old_pos.x][this->move_tile_instructions.back()->old_pos.y]->getMerging() && !this->matrix[x_][y_]->getMerging()) {
		this->MERGE_FLAG = true;
		this->matrix[this->move_tile_instructions.back()->old_pos.x][this->move_tile_instructions.back()->old_pos.y]->setMerging(true);
		this->matrix[x_][y_]->setMerging(true);
		return this->move_tile_instructions.back()->new_pos.y;
	}
	// Merge if only one is moving
	for (int i = y_ + 1; i < this->matrix_height; ++i)
		if (this->matrix[x_][i] != NULL) {
			if (this->matrix[x_][i]->getType() == this->matrix[x_][y_]->getType() && !this->matrix[x_][i]->getMerging() && !this->matrix[x_][y_]->getMerging()) {
				this->MERGE_FLAG = true;
				this->matrix[x_][i]->setMerging(true);
				this->matrix[x_][y_]->setMerging(true);
				return i;
			}
			else
				break;
		}

	this->MERGE_FLAG = false;
	return -1;
}

int TileMatrix::findFreeLeft(int x_, int y_)
{
	int new_x = this->mergeLeft(x_, y_);
	if (new_x != -1)
		return new_x;
	else {
		for (int i = 0; i < x_; ++i)
			if ((this->matrix[i][y_] == NULL || this->matrix[i][y_]->getIsMoving()) && !this->willBeOccupied(i, y_))
				return i;
		return x_;
	}
}

int TileMatrix::findFreeRight(int x_, int y_)
{
	int new_x = this->mergeRight(x_, y_);
	if (new_x != -1)
		return new_x;
	else {
		for (int i = this->matrix_width - 1; i > x_; --i)
			if ((this->matrix[i][y_] == NULL || this->matrix[i][y_]->getIsMoving()) && !this->willBeOccupied(i, y_))
				return i;
		return x_;
	}
	
}

int TileMatrix::findFreeUp(int x_, int y_)
{
	int new_y = this->mergeUp(x_, y_);
	if (new_y != -1)
		return new_y;
	else {
		for (int i = 0; i < y_; ++i)
			if ((this->matrix[x_][i] == NULL || this->matrix[x_][i]->getIsMoving()) && !this->willBeOccupied(x_, i))
				return i;
		return y_;
	}
	
}

int TileMatrix::findFreeDown(int x_, int y_)
{
	int new_y = this->mergeDown(x_, y_);
	if (new_y != -1)
		return new_y;
	else {
		for (int i = this->matrix_height - 1; i > y_; --i)
			if ((this->matrix[x_][i] == NULL || this->matrix[x_][i]->getIsMoving()) && !this->willBeOccupied(x_, i))
				return i;
		return y_;
	}
}

void TileMatrix::moveLeft()
{
	this->do_move = true;
	for (int j = 0; j < this->matrix_height; ++j)
		for (int i = 0; i < this->matrix_width; ++i)
			if (this->matrix[i][j] != NULL) {
				sf::Vector2i new_pos = { this->findFreeLeft(i, j), j };
				int distance = i - new_pos.x;
				this->addMoveInstructions(new_pos, { i, j }, distance);
			}
}

void TileMatrix::moveRight()
{
	this->do_move = true;
	for (int j = 0; j < this->matrix_height; ++j)
		for (int i = this->matrix_width - 1; i >= 0; --i)
			if (this->matrix[i][j] != NULL) {
				sf::Vector2i new_pos = { this->findFreeRight(i, j), j };
				int distance = new_pos.x - i;
				this->addMoveInstructions(new_pos, { i, j }, distance);
			}
}

void TileMatrix::moveUp()
{
	this->do_move = true;
	for (int i = 0; i < this->matrix_width; ++i)
		for (int j = 0; j < this->matrix_height; ++j)
			if (this->matrix[i][j] != NULL) {
				sf::Vector2i new_pos = { i, this->findFreeUp(i, j) };
				int distance = j - new_pos.y;
				this->addMoveInstructions(new_pos, { i, j }, distance);
			}
}

void TileMatrix::moveDown()
{
	this->do_move = true;
	for (int i = 0; i < this->matrix_width; ++i)
		for (int j = this->matrix_height - 1; j >= 0; --j)
			if (this->matrix[i][j] != NULL) {
				sf::Vector2i new_pos = { i, this->findFreeDown(i, j) };
				int distance = new_pos.y - j;
				this->addMoveInstructions(new_pos, { i, j }, distance);
			}
}

void TileMatrix::clearBoard()
{
	this->move_tile_instructions.clear();
	
	for (int i = 0; i < this->matrix_height; ++i)
		for (int j = 0; j < this->matrix_width; ++j) {
			if (this->matrix[i][j] != NULL)
				this->matrix[i][j]->~Tile();
				this->matrix[i][j] = NULL;
			}

	this->added_score = 0;
	this->current_moved_frames = 0;
	this->MOVE_FLAG = false;
	this->MERGE_FLAG = false;
	this->GAMEOVER_FLAG = false;
	this->tiles = 0;
}

bool TileMatrix::isGameOver()
{
	cout << "Tiles: " << this->tiles << endl;

	if (this->tiles != 16)
		return false;
	else {
		for (int i = 1; i < this->matrix_height - 1; ++i)
			for (int j = 1; j < this->matrix_width - 1; ++j)
				if (this->matrix[j][i]->getType() == this->matrix[j - 1][i]->getType() ||
					this->matrix[j][i]->getType() == this->matrix[j + 1][i]->getType() ||
					this->matrix[j][i]->getType() == this->matrix[j][i - 1]->getType() ||
					this->matrix[j][i]->getType() == this->matrix[j][i + 1]->getType())
					return false;

		for (int i = 0; i < this->matrix_width - 1; ++i)
			if (this->matrix[i][0]->getType() == this->matrix[i + 1][0]->getType() || this->matrix[i][this->matrix_height - 1]->getType() == this->matrix[i + 1][this->matrix_height - 1]->getType())
				return false;

		for (int i = 0; i < this->matrix_height - 1; ++i)
			if (this->matrix[0][i]->getType() == this->matrix[0][i + 1]->getType() || this->matrix[this->matrix_width - 1][i]->getType() == this->matrix[this->matrix_width - 1][i + 1]->getType())
				return false;

		for (int i = 0; i < this->matrix_height; ++i)
			for (int j = 0; j < this->matrix_width; ++j)
				this->matrix[i][j]->gameOver();

		return true;
	}

	return false;
}

void TileMatrix::addMoveInstructions(sf::Vector2i new_pos_, sf::Vector2i old_pos_, int distance_)
{
	if (distance_ > 0) {
		this->MOVE_FLAG = true;
		float pixel_distance = static_cast<float>(distance_) * (*this->inner_edge + *this->tile_width);
		float move_speed = pixel_distance / static_cast<float>(this->frames_to_move);
		this->matrix[old_pos_.x][old_pos_.y]->setIsMoving(true);
		this->move_tile_instructions.push_back(new MoveTile(distance_, pixel_distance, move_speed, new_pos_, old_pos_, this->MERGE_FLAG));
		this->MERGE_FLAG = false;
	}
}

bool TileMatrix::willBeOccupied(int x_, int y_)
{
	for (int i = this->move_tile_instructions.size() - 1; i >= 0; --i)
		if (this->move_tile_instructions[i]->new_pos.x == x_ && this->move_tile_instructions[i]->new_pos.y == y_)
				return true;
	return false;
}

TileMatrix::TileMatrix(float* scale_, float* outer_, float* inner_, float* tile_width_, sf::Vector2f playground_pos_)
{
	for (int i = 0; i < this->matrix_height; ++i)
		for (int j = 0; j < this->matrix_width; ++j)
			this->matrix[i][j] = NULL;

	this->scale = scale_;
	this->outer_edge = outer_;
	this->inner_edge = inner_;
	this->tile_width = tile_width_;
	this->playground_pos = playground_pos_;

	movement_manager = MovementManager::getInstance();
	scaling_routine = movement_manager->createScalingRoutine("TILE_SPAWNING");
	scaling_routine->addScaling(new scalingInfo(sf::Vector2f(0.1f, 0.1f) * *this->scale, sf::Vector2f(1.f, 1.f) * *this->scale, 0.2f, easeFunctions::getFunction(easeFunctions::OUT_QUAD), false, 0.f, 0.f));

	this->initTextures();
}

TileMatrix::~TileMatrix()
{
	for (int i = 0; i < this->matrix_height; ++i)
		for (int j = 0; j < this->matrix_width; ++j)
			if (this->matrix[i][j] != NULL)
				this->matrix[i][j]->~Tile();
}

void TileMatrix::update(float dt)
{
	if (this->do_move)
		this->updateMove();

	// Zmieni� tak aby tylko te kt�re pojawi�y si� by�y animowane
	for (size_t i = 0; i < this->spawning_tiles.size(); ++i)
		if (this->spawning_tiles[i]->getSpawning())
			this->spawning_tiles[i]->update(dt);
		else
			this->spawning_tiles.erase(this->spawning_tiles.begin() + i);

	movement_manager->update(dt);
}

void TileMatrix::spawn(unsigned amount_)
{
	for (unsigned i = 0; i < amount_; ++i) {
		sf::Vector2i pos = { rand() % 4, rand() % 4 };

		while (this->matrix[pos.x][pos.y] != NULL) {
			pos = { rand() % 4, rand() % 4 };
		}

		this->addTile(pos);
	}
	
}

void TileMatrix::addTile(sf::Vector2i pos_, int type_)
{
	if (pos_.x > this->matrix_width - 1 || pos_.y > this->matrix_height - 1) {
		std::cout << "Invalid tile spawning position" << std::endl;
		system("pause");
	}
	else {
		this->matrix[pos_.x][pos_.y] = new Tile(type_, this->textures[this->findID(type_)], this->scale);
		this->matrix[pos_.x][pos_.y]->setPosition(this->calculateTilePos(pos_.x, pos_.y));

		
		movement_manager->linkScalingRoutine(*this->matrix[pos_.x][pos_.y]->getSprite(), "TILE_SPAWNING");
		movement_manager->startScalingRoutine(*this->matrix[pos_.x][pos_.y]->getSprite(), "TILE_SPAWNING");
		//this->spawning_tiles.push_back(this->matrix[pos_.x][pos_.y]);
		++this->tiles;
	}
}

void TileMatrix::updateMove()
{
	if (this->current_moved_frames < this->frames_to_move) {
		for (auto& moveInstructions : this->move_tile_instructions) {

			// Tutaj trzeba doda� dt
			sf::Vector2i new_pos = moveInstructions->new_pos;
			sf::Vector2i old_pos = moveInstructions->old_pos;
			// Moving left
			if (new_pos.x < old_pos.x)
				this->matrix[old_pos.x][old_pos.y]->move({ -moveInstructions->move_speed, 0.f });
			// Moving right
			else if (new_pos.x > old_pos.x)
				this->matrix[old_pos.x][old_pos.y]->move({ moveInstructions->move_speed, 0.f });

			// Moving up
			if (new_pos.y < old_pos.y)
				this->matrix[old_pos.x][old_pos.y]->move({ 0.f,  -moveInstructions->move_speed });
			// Moving down
			else if (new_pos.y > old_pos.y)
				this->matrix[old_pos.x][old_pos.y]->move({ 0.f,  moveInstructions->move_speed });
		}
		++this->current_moved_frames;
	}
	else {
		this->do_move = false;
		this->current_moved_frames = 0;
		this->added_score = 0;

		for (size_t i = 0; i < this->move_tile_instructions.size(); ++i ){
			if (this->move_tile_instructions[i]->merge) {
				sf::Vector2i new_pos = this->move_tile_instructions[i]->new_pos;
				sf::Vector2i old_pos = this->move_tile_instructions[i]->old_pos;
				this->matrix[old_pos.x][old_pos.y]->~Tile();
				this->matrix[old_pos.x][old_pos.y] = NULL;
				this->matrix[new_pos.x][new_pos.y]->increaseType();
				this->matrix[new_pos.x][new_pos.y]->setTexture(this->textures[this->findID(this->matrix[new_pos.x][new_pos.y]->getType())]);
				this->matrix[new_pos.x][new_pos.y]->setMerging(false);
				--this->tiles;

				// Updating score
				this->added_score += this->matrix[new_pos.x][new_pos.y]->getType();
			}
			else {
				sf::Vector2i new_pos = this->move_tile_instructions[i]->new_pos;
				sf::Vector2i old_pos = this->move_tile_instructions[i]->old_pos;
				this->matrix[new_pos.x][new_pos.y] = this->matrix[old_pos.x][old_pos.y];
				this->matrix[new_pos.x][new_pos.y]->setIsMoving(false);
				this->matrix[old_pos.x][old_pos.y] = NULL;
				this->matrix[new_pos.x][new_pos.y]->setMerging(false);
			}
		}
		this->move_tile_instructions.clear();

		if (this->MOVE_FLAG)
			this->spawn();
		this->MOVE_FLAG = false;

		this->GAMEOVER_FLAG = this->isGameOver();
	}
}

void TileMatrix::render(sf::RenderTarget& target)
{
	for (int i = 0; i < this->matrix_height; ++i)
		for (int j = 0; j < this->matrix_width; ++j)
			if (this->matrix[i][j] != NULL)
				this->matrix[i][j]->render(target);
}
