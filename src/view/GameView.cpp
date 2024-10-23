#include <iostream>
#include "GameView.h"

// = = = = = Initialization funcitons = = = = = //
void GameView::initAssets()
{
	for (int i = 1, k = 0; i < 15; ++i, ++k)
		m_tileTextures[k] = &AssetManager::GetTexture("assets/Textures/" + std::to_string(static_cast<int>(pow(2.f, static_cast<double>(i)))) + ".png");
        
    AssetManager::GetTexture("assets/Textures/button_newgame.png");
    AssetManager::GetTexture("assets/Textures/button_score.png");
}

void GameView::initVariables()
{
	// Playground sprite initialization
	m_texture = &AssetManager::GetTexture("assets/Textures/playground.png");
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2.f,
		m_sprite.getPosition().y + m_sprite.getGlobalBounds().height / 2.f);
	m_sprite.setPosition(windowSize / 2.f);
	m_scale = (windowSize.y - m_playgroundPadding * 2) / m_sprite.getGlobalBounds().height;
	m_sprite.setScale(m_scale, m_scale);

	m_innerEdgeWidth *= m_scale;
	m_outerEdgeWidth *= m_scale;
	m_tileWidth *= m_scale;

	m_movementManager = new MovementManager();
	m_movementContainer = MovementContainer::getInstance();

	sf::Vector2f playground_pos = m_sprite.getPosition();
	playground_pos.x -= m_sprite.getLocalBounds().width / 4.f;
	playground_pos.y -= m_sprite.getLocalBounds().height / 4.f;
	m_playgroundPosition = playground_pos;

	//m_gui = new GUI(windowSize, m_sprite.getGlobalBounds());
}

void GameView::initAnimations()
{
	auto routine = m_movementManager->createScalingRoutine("TILE_SPAWNING");
	routine->addScaling(new scalingInfo(sf::Vector2f(0.1f, 0.1f) * m_scale, sf::Vector2f(1.f, 1.f) * m_scale, m_timeSpawningMax, easeFunctions::getFunction(easeFunctions::OUT_QUAD), false, 0.f, 0.f));

	routine = m_movementManager->createScalingRoutine("TILE_MERGING");
	routine->addScaling(new scalingInfo(sf::Vector2f(0.1f, 0.1f) * m_scale, sf::Vector2f(1.f, 1.f) * m_scale, m_timeMergingMax, easeFunctions::getFunction(easeFunctions::OUT_BACK), false, 0.f, 0.f));
}



// = = = = = Utility funcitons = = = = = //
sf::Vector2f GameView::calculateTilePos(const sf::Vector2i& pos) const
{
	sf::Vector2f tilePos{ m_playgroundPosition };

	tilePos.x += m_outerEdgeWidth + m_innerEdgeWidth * pos.x + m_tileWidth * pos.x + m_tileWidth / 2.f;
	tilePos.y += m_outerEdgeWidth + m_innerEdgeWidth * pos.y + m_tileWidth * pos.y + m_tileWidth / 2.f;

	return tilePos;
}

int GameView::findID(int type) const
{
	int ID = 0;
	while (type != 1) {
		type /= 2;
		++ID;
	}
	return ID - 1;
}



// = = = = = Private funcitons = = = = = //
void GameView::drawMatrixCMD()
{
	printf("\n\nMATRIX:\n");
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (m_matrix[i][j] != nullptr) {
				printf("%-3d", m_matrix[i][j]->getType());
			}
			else
				printf("%-3d", 0);
		}
		printf("\n");
	}
	printf("\n\n");
}

void GameView::updateTiles()
{
	for (size_t j = 0; j < 4; ++j)
		for (size_t i = 0; i < 4; ++i) {
			delete tiles[i][j];
			tiles[i][j] = nullptr;
		}

	for (size_t j = 0; j < 4; ++j)
		for (size_t i = 0; i < 4; ++i) {
			if (m_matrix[i][j] != nullptr) {
				tiles[i][j] = new Tile(m_matrix[i][j]->getType(), m_tileTextures[findID(m_matrix[i][j]->getType())], &m_scale, calculateTilePos(sf::Vector2i{ static_cast<int>(i), static_cast<int>(j) }), m_movementManager);
			}
		}
}



// = = = = = Constructors / Destructors = = = = = //
GameView::GameView() {
	initAssets();
	initVariables();
	initAnimations();
}

GameView::~GameView()
{
	delete m_gui;
}



// = = = = = Public functions = = = = = //
void GameView::syncMatrix(TileModel* const (&matrix)[4][4])
{
	this->m_matrix = matrix;
	this->updateTiles();
	this->drawMatrixCMD();
}

void GameView::startMove(const std::vector<MoveInstructions*>& moveInstructions)
{
	this->m_moveInstructions = &moveInstructions;

	for (const auto& instruction : *m_moveInstructions) {
		sf::Vector2i old_pos = instruction->getOldPos();
		sf::Vector2i new_pos = instruction->getNewPos();
		sf::Vector2i distance = new_pos - old_pos;
		const sf::Vector2f pixel_distance = sf::Vector2f{ static_cast<float>(distance.x) * (m_innerEdgeWidth + m_tileWidth),
														  static_cast<float>(distance.y) * (m_innerEdgeWidth + m_tileWidth) };
		printf("Move pixel distance: %f %f\n", pixel_distance.x, pixel_distance.y);
		this->tiles[old_pos.x][old_pos.y]->setIsMoving(true);
		this->tiles[old_pos.x][old_pos.y]->smoothMove(pixel_distance, m_timeMovingMax);
	}
	this->notify("started_move");
}

void GameView::startMerge(const std::vector<MergeInstruction*>& mergeInstructions)
{
	if (mergeInstructions.empty())
		return;

	this->m_mergeInstructions = &mergeInstructions;

	for (const auto& instruction : *this->m_mergeInstructions) {
		const sf::Vector2i pos = instruction->pos;
		tiles[pos.x][pos.y]->startMerging();
	}
	this->notify("started_merging");
}

void GameView::startSpawn(const std::vector<SpawnInstruction*>& spawnInstructions)
{
	this->m_spawnInstructions = &spawnInstructions;

	for (const auto& instruction : *this->m_spawnInstructions) {
		this->tiles[instruction->pos.x][instruction->pos.y] = new Tile(instruction->type, m_tileTextures[findID(instruction->type)], &m_scale, calculateTilePos(instruction->pos), m_movementManager);
		this->tiles[instruction->pos.x][instruction->pos.y]->startSpawning();
	}
	this->notify("started_spawning");
}

void GameView::endSpawn()
{
	m_movementManager->update(1.f);

	for (auto& instruction : *m_spawnInstructions) 
		tiles[instruction->pos.x][instruction->pos.y]->update(1.f);
	
	this->notify("finished_spawning");
}



// = = = = = Update functions = = = = = //
void GameView::updateMove(float dt)
{
	this->m_movementManager->update(dt);
	this->m_movementContainer->update(dt);

	if (m_timeMoving < m_timeMovingMax)
		m_timeMoving += dt;
	else {
		m_timeMoving = 0.f;
		this->notify("finished_move");
	}
}

void GameView::updateSpawning(float dt)
{
	this->m_movementManager->update(dt);

	bool finishedSpawning = false;
	for (auto& instruction : *m_spawnInstructions) {
		tiles[instruction->pos.x][instruction->pos.y]->update(dt);
		finishedSpawning = !tiles[instruction->pos.x][instruction->pos.y]->getSpawning();
	}

	if (finishedSpawning) {
		this->m_mergeInstructions = nullptr;
		this->notify("finished_spawning");
	}
}



// = = = = = Render functions = = = = = //
void GameView::render(sf::RenderTarget& window)
{
	window.clear(m_backgroundColor);
	window.draw(m_sprite);

	if (m_mergeInstructions)
		for (const auto& instruction : *m_mergeInstructions) {
			int type = instruction->tile->getType();
			sf::Vector2i pos = instruction->pos;
			Tile tile(type, m_tileTextures[findID(type)], &m_scale, calculateTilePos(pos), m_movementManager);
			tile.render(window);
		}

	for (size_t j = 0; j < 4; ++j)
		for (size_t i = 0; i < 4; ++i) 
			if (tiles[i][j])
				tiles[i][j]->render(window);
}