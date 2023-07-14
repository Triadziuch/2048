#include "TileMatrix.h"

void TileMatrix::initTextures()
{
	for (int i = 2, k = 0; i <= this->max_type; i *= 2, ++k) 
		this->textures[k].loadFromFile("Textures/" + std::to_string(i) + ".png");
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

int TileMatrix::findFreeLeft(int x_, int y_)
{
	for (int i = 0; i < x_; ++i)
		if (this->matrix[i][y_] == NULL && !this->willBeOccupied(i, y_))
			return i;
	return x_;
}

int TileMatrix::findFreeRight(int x_, int y_)
{
	for (int i = this->matrix_width - 1; i > x_; --i)
		if (this->matrix[i][y_] == NULL && !this->willBeOccupied(i, y_))
			return i;
	return x_;
}

int TileMatrix::findFreeUp(int x_, int y_)
{
	for (int i = 0; i < y_; ++i)
		if (this->matrix[x_][i] == NULL && !this->willBeOccupied(x_, i))
			return i;
	return y_;
}

int TileMatrix::findFreeDown(int x_, int y_)
{
	for (int i = this->matrix_height - 1; i > y_; --i)
		if (this->matrix[x_][i] == NULL && !this->willBeOccupied(x_, i))
			return i;
	return y_;
}

bool TileMatrix::willBeOccupied(int x_, int y_)
{
	for (int i = 0; i < this->matrix_width; ++i)
		for (int j = 0; j < this->matrix_height; ++j)
			if (this->moveTile[i][j].new_pos.x == x_ && this->moveTile[i][j].new_pos.y == y_)
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

	this->initTextures();
}

TileMatrix::~TileMatrix()
{
	for (int i = 0; i < this->matrix_height; ++i)
		for (int j = 0; j < this->matrix_width; ++j)
			if (this->matrix[i][j] != NULL)
				this->matrix[i][j]->~Tile();

	delete[]this->matrix;
	delete this->matrix;
}

void TileMatrix::update(float dt)
{
	if (this->do_move)
		this->updateMove();
}

void TileMatrix::addTile(int x_, int y_, int type_)
{
	if (x_ > 3 || y_ > 3) {
		std::cout << "Invalid tile spawning position" << std::endl;
		system("pause");
	}
	else {
		this->matrix[x_][y_] = new Tile(type_, &this->textures[this->findID(type_)], this->scale);
		this->matrix[x_][y_]->setPosition(this->calculateTilePos(x_, y_));
	}
}

void TileMatrix::updateMove()
{
	if (this->current_moved_frames < this->frames_to_move) {
		for (int i = 0; i < this->matrix_width; ++i)
			for (int j = 0; j < this->matrix_height; ++j)
				if (this->moveTile[i][j].move) {
					// Moving left
					if (this->moveTile[i][j].new_pos.x < i) 
						this->matrix[i][j]->move({ -this->moveTile[i][j].move_speed, 0.f });
					// Moving right
					else if (this->moveTile[i][j].new_pos.x > i) 
						this->matrix[i][j]->move({ this->moveTile[i][j].move_speed, 0.f });
					// Moving up
					if (this->moveTile[i][j].new_pos.y < j) 
						this->matrix[i][j]->move({ 0.f,  -this->moveTile[i][j].move_speed });
					// Moving down
					else if (this->moveTile[i][j].new_pos.y > j) 
						this->matrix[i][j]->move({ 0.f,  this->moveTile[i][j].move_speed });
				}
		++this->current_moved_frames;
	}
	else {
		this->do_move = false;
		this->current_moved_frames = 0;

		for (int i = 0; i < this->matrix_width; ++i)
			for (int j = 0; j < this->matrix_height; ++j) 
				if (this->moveTile[i][j].move) {
					this->matrix[this->moveTile[i][j].new_pos.x][this->moveTile[i][j].new_pos.y] = this->matrix[i][j];
					this->matrix[i][j] = NULL;
					this->moveTile[i][j].move = false;
					this->moveTile[i][j].new_pos = { -1, -1 };
				}
	}
}

void TileMatrix::moveLeft()
{
	this->do_move = true;
	for (int i = 0; i < this->matrix_width; ++i)
		for (int j = 0; j < this->matrix_height; ++j) 
			if (this->matrix[i][j] != NULL) {
				sf::Vector2i new_pos = { this->findFreeLeft(i, j), j };
				if (i - new_pos.x > 0) {
					this->moveTile[i][j].move = true;
					this->moveTile[i][j].distance = i - new_pos.x;
					this->moveTile[i][j].pixel_distance = static_cast<float>(this->moveTile[i][j].distance) * (*this->inner_edge + *this->tile_width);
					this->moveTile[i][j].new_pos = new_pos;
					this->moveTile[i][j].move_speed = this->moveTile[i][j].pixel_distance / this->frames_to_move;
				}
				else
					this->moveTile[i][j].move = false;
			}
}

void TileMatrix::moveRight()
{
	this->do_move = true;
	for (int i = this->matrix_width - 1; i >= 0; --i)
		for (int j = 0; j < this->matrix_height; ++j)
			if (this->matrix[i][j] != NULL) {
				sf::Vector2i new_pos = { this->findFreeRight(i, j), j };
				if (new_pos.x - i > 0) {
					this->moveTile[i][j].move = true;
					this->moveTile[i][j].distance = new_pos.x - i;
					this->moveTile[i][j].pixel_distance = static_cast<float>(this->moveTile[i][j].distance) * (*this->inner_edge + *this->tile_width);
					this->moveTile[i][j].new_pos = new_pos;
					this->moveTile[i][j].move_speed = this->moveTile[i][j].pixel_distance / this->frames_to_move;
				}
				else
					this->moveTile[i][j].move = false;
			}
}

void TileMatrix::moveUp()
{
	this->do_move = true;
	for (int j = 0; j < this->matrix_height; ++j)
		for (int i = 0; i < this->matrix_width; ++i)
			if (this->matrix[i][j] != NULL) {
				sf::Vector2i new_pos = { i, this->findFreeUp(i, j) };
				if (j - new_pos.y > 0) {
					this->moveTile[i][j].move = true;
					this->moveTile[i][j].distance = j - new_pos.y;
					this->moveTile[i][j].pixel_distance = static_cast<float>(this->moveTile[i][j].distance) * (*this->inner_edge + *this->tile_width);
					this->moveTile[i][j].new_pos = new_pos;
					this->moveTile[i][j].move_speed = this->moveTile[i][j].pixel_distance / this->frames_to_move;
				}
				else
					this->moveTile[i][j].move = false;
			}
}

void TileMatrix::moveDown()
{
	this->do_move = true;
	for (int j = this->matrix_height - 1; j >= 0; --j)
		for (int i = 0; i < this->matrix_width; ++i)
			if (this->matrix[i][j] != NULL) {
				sf::Vector2i new_pos = { i, this->findFreeDown(i, j) };
				if (new_pos.y - j > 0) {
					this->moveTile[i][j].move = true;
					this->moveTile[i][j].distance = new_pos.y - j;
					this->moveTile[i][j].pixel_distance = static_cast<float>(this->moveTile[i][j].distance) * (*this->inner_edge + *this->tile_width);
					this->moveTile[i][j].new_pos = new_pos;
					this->moveTile[i][j].move_speed = this->moveTile[i][j].pixel_distance / this->frames_to_move;
				}
				else
					this->moveTile[i][j].move = false;
			}
}

void TileMatrix::render(sf::RenderTarget& target)
{
	for (int i = 0; i < this->matrix_height; ++i)
		for (int j = 0; j < this->matrix_width; ++j)
			if (this->matrix[i][j] != NULL)
				this->matrix[i][j]->render(target);
}
