#pragma once

#include "../model/GameModel.h"
#include "../BaseGameView.h"
#include "../BaseViewGraphic.h"
#include "../TileMatrix.h"
#include "../GUI.h"


class GameViewGraphic : public BaseViewGraphic, public BaseGameView {
private:
	// Asset Manager
	AssetManager manager;

	// Background variables
	sf::Texture* m_texture{}, *m_tileTextures[14];
	sf::Sprite m_sprite{};
	sf::Vector2f m_playgroundPosition{};
	const float m_playgroundPadding{ 100.f };
	float m_scale{ 1.f }, m_outerEdgeWidth{ 37.f }, m_innerEdgeWidth{ 36.f }, m_tileWidth{ 215.f };
	bool m_isGameOver{ false };
	
	// Animation time variables
	const float m_timeSpawningMax = 0.2f, m_timeMovingMax = 0.2f, m_timeMergingMax = 0.2f;
	float m_timeMoving = 0.f, m_timeMerging = 0.f;

	Tile* tiles[4][4]{ {} };
	const std::vector <MoveInstruction*>* m_moveInstructions{};
	const std::vector <SpawnInstruction*>* m_spawnInstructions{};
	const std::vector <MergeInstruction*>* m_mergeInstructions{};

	// Initialization functions
	void initVariables();
	void initAssets();
	void initAnimations();

	// Utility functions
	sf::Vector2f calculateTilePos(const sf::Vector2i& pos) const;
	int findID(int type) const;

	// Private functions
	void updateTiles();

public:
	// Constructors / Destructors
	GameViewGraphic();
	~GameViewGraphic();

	void openWindow() override { BaseViewGraphic::openWindow(); }
	void closeWindow() override { BaseViewGraphic::closeWindow(); }
	void initRenderer() override { BaseViewGraphic::initRenderer(); }
	void deleteRenderer() override { BaseViewGraphic::deleteRenderer(); }
	sf::RenderWindow* getWindow() override { return BaseViewGraphic::getWindow(); }
	void render() override;

	// Public functions
	void syncMatrix(TileBase* const (&matrix)[4][4]);

	void startMove(const std::vector<MoveInstruction*>& moveInstructions);
	void startMerge(const std::vector<MergeInstruction*>& mergeInstructions);
	void startSpawn(const std::vector<SpawnInstruction*>& spawnInstructions);
	void endSpawn();

	// Update functions
	void updateMove(float dt);
	void updateSpawning(float dt);
	void updateScore(const int& score, const int& bestScore);
};