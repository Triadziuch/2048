#pragma once

#include "../model/GameModel.h"
#include "BaseGameView.h"
#include "BaseViewCMD.h"
#include "../TileMatrix.h"

class GameViewCMD : public BaseViewCMD, public BaseGameView {
private:
	// Grid variables
	constexpr static int gridSize{ 4 };
	constexpr static int cellSize{ 9 };
	ftxui::Component grid_component;

	// Game over animation variables
	int m_gameOverCycle{};
	const int m_gameOverCyclesMax{ 5 };
	const float m_timeGameOverCycleMax{ 0.1f };

	float m_timeGameOver{};
	bool isGameOver{ false }, isGameOverAnimation{ false }, isDesaturated{ false };

	// Private functions
	ftxui::Component initGrid();
	int getCell(int row, int col) const;
	ftxui::Color getCellColor(int row, int col) const;
	ftxui::Color getCellColorDesaturated(int row, int col) const;
	ftxui::Color getCellBorderColor(int row, int col) const;
	std::string displayCell(int row, int col) const;

	// FTXUI Rendering functions
	void renderFTXUI() override;
	void updateContent();

public:
	// Constructors / Destructors
	GameViewCMD();
	~GameViewCMD();

	// Inherited public functions
	void openWindow() override { BaseViewCMD::openWindow(); }
	void closeWindow() override { BaseViewCMD::closeWindow(); }
	void initRenderer() override { BaseViewCMD::initRenderer(); }
	void deleteRenderer() override { BaseViewCMD::deleteRenderer(); }
	sf::RenderWindow* getWindow() override { return BaseViewCMD::getWindow(); }
	void render() override;
	void reset() override;

	// Game view functions
	void syncMatrix(TileBase* const (&matrix)[4][4]);
	void startMove(const std::vector<MoveInstruction*>& moveInstructions);
	void startMerge(const std::vector<MergeInstruction*>& mergeInstructions);
	void startSpawn(const std::vector<SpawnInstruction*>& spawnInstructions);
	void startGameOver();
	void endSpawn();
	void endGameOver();
	
	// Update functions
	sf::Event* update(float dt);
	void updateMove(float dt);
	void updateSpawn(float dt);
	void updateGameOver(float dt);
	void updateScore(const int& score, const int& bestScore);
};