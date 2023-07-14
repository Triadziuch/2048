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
		if (this->matrix[i][y_] == NULL)
			return i;
	return x_;
}

int TileMatrix::findFreeRight(int x_, int y_)
{
	for (int i = this->matrix_width - 1; i > x_; --i)
		if (this->matrix[i][y_] == NULL)
			return i;
	return x_;
}

int TileMatrix::findFreeUp(int x_, int y_)
{
	for (int i = 0; i < y_; ++i)
		if (this->matrix[x_][i] == NULL)
			return i;
	return y_;
}

int TileMatrix::findFreeDown(int x_, int y_)
{
	for (int i = this->matrix_height - 1; i > y_; --i)
		if (this->matrix[x_][i] == NULL)
			return i;
	return y_;
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

void TileMatrix::moveLeft()
{
	for (int i = 0; i < this->matrix_width; ++i)
		for (int j = 0; j < this->matrix_height; ++j) 
			if (this->matrix[i][j] != NULL) {
				sf::Vector2i new_pos = { this->findFreeLeft(i, j), j };
				int distance = i - new_pos.x;

				cout << "Tile: " << this->matrix[i][j]->getType() << endl;
				cout << "Old position: (" << i << ", " << j << ")" << endl;
				cout << "New position: (" << new_pos.x << ", " << new_pos.y << ")" << endl;
				cout << "Distance: " << distance << endl << endl;
			}
}

void TileMatrix::moveRight()
{
	for (int i = this->matrix_width - 1; i >= 0; --i)
		for (int j = 0; j < this->matrix_height; ++j)
			if (this->matrix[i][j] != NULL) {
				sf::Vector2i new_pos = { this->findFreeRight(i, j), j };
				int distance = new_pos.x - i;

				cout << "Tile: " << this->matrix[i][j]->getType() << endl;
				cout << "Old position: (" << i << ", " << j << ")" << endl;
				cout << "New position: (" << new_pos.x << ", " << new_pos.y << ")" << endl;
				cout << "Distance: " << distance << endl << endl;
			}
}

void TileMatrix::moveUp()
{
	for (int j = 0; j < this->matrix_height; ++j)
		for (int i = 0; i < this->matrix_width; ++i)
			if (this->matrix[i][j] != NULL) {
				sf::Vector2i new_pos = { i, this->findFreeUp(i, j) };
				int distance = j - new_pos.y;

				cout << "Tile: " << this->matrix[i][j]->getType() << endl;
				cout << "Old position: (" << i << ", " << j << ")" << endl;
				cout << "New position: (" << new_pos.x << ", " << new_pos.y << ")" << endl;
				cout << "Distance: " << distance << endl << endl;
			}
}

void TileMatrix::render(sf::RenderTarget& target)
{
	for (int i = 0; i < this->matrix_height; ++i)
		for (int j = 0; j < this->matrix_width; ++j)
			if (this->matrix[i][j] != NULL)
				this->matrix[i][j]->render(target);
}
