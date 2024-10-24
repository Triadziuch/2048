#include <string>
#include "GameModel.h"

// = = = = = Constructors / Destructors = = = = = // 
GameModel::GameModel() : BaseModel() {
	m_tileMatrix = new TileMatrixModel();
	
	m_tileMatrix->connect("STARTED_SPAWN", [&]() {
			printf("[GameModel]: TileMatrixModel has started spawning new tile.\n");
			this->notify("STARTED_SPAWN");
		return false;
		});

	m_tileMatrix->connect("STARTED_MOVE", [&]() {
			printf("[GameModel]: TileMatrixModel has started move.\n");
			this->notify("STARTED_MOVE");
		return false;
		});

	m_tileMatrix->connect("GAME_OVER", [&]() {
			printf("[GameModel]: TileMatrixModel has informed about game over.\n");
			this->notify("GAME_OVER");
		return false;
		});

	m_tileMatrix->connect("GAME_WON", [&]() {
			printf("[GameModel]: TileMatrixModel has informed about winning a game.\n");
			this->notify("GAME_WON");
		return false;
		});

	m_tileMatrix->spawn(2);

}

GameModel::~GameModel()
{
	delete m_tileMatrix;
}



// = = = = = Public functions = = = = = // 
void GameModel::updateScore()
{
	const int added_m_score = m_tileMatrix->getAddedScore();
	m_tileMatrix->setAddedScore(0);
	m_score += added_m_score;
}

void GameModel::move(const sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Key::Up:
	case sf::Keyboard::Key::W:
		m_tileMatrix->moveUp();
		break;
	case sf::Keyboard::Key::Down:
	case sf::Keyboard::Key::S:
		m_tileMatrix->moveDown();
		break;
	case sf::Keyboard::Key::Left:
	case sf::Keyboard::Key::A:
		m_tileMatrix->moveLeft();
		break;
	case sf::Keyboard::Key::Right:
	case sf::Keyboard::Key::D:
		m_tileMatrix->moveRight();
		break;
	}
}

void GameModel::endMove()
{
	this->m_tileMatrix->endMove();
}

void GameModel::endMerge()
{
	this->updateScore();
	this->m_tileMatrix->endMerge();
}

void GameModel::clearBoard()
{
	//m_isGameOver = false;
	m_tileMatrix->clearBoard();
	m_tileMatrix->spawn(2);
}



// = = = = = Accessors / Mutators = = = = = // 
TileBase* const (&GameModel::getMatrix() const)[4][4]
{
	return this->m_tileMatrix->getMatrix();
}

const std::vector<MoveInstruction*>& GameModel::getMoveInstructions() const
{
	return this->m_tileMatrix->getMoveInstructions();
}

const std::vector<SpawnInstruction*>& GameModel::getSpawnInstructions() const
{
	return this->m_tileMatrix->getSpawnInstructions();
}

const std::vector<MergeInstruction*>& GameModel::getMergeInstructions() const
{
	return this->m_tileMatrix->getMergeInstructions();
}