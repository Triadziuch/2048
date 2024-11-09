#pragma once

#include "../model/GameModel.h"
#include "../BaseGameView.h"
#include "../BaseViewCMD.h"
#include "../TileMatrix.h"

class GameViewCMD : public BaseViewCMD, public BaseGameView {
private:
	// Grid variables
	constexpr static int gridSize = 4;
	constexpr static int cellSize = 9;
	ftxui::Component grid_component;

	int getCell(int row, int col) const;
	ftxui::Color getCellColor(int row, int col) const;
	ftxui::Color getCellBorderColor(int row, int col) const;
	std::string displayCell(int row, int col) const;

	ftxui::Component initGrid();
	void renderFTXUI() override;
	void updateContent() override;
	

public:
	// Constructors / Destructors
	GameViewCMD();

	void openWindow() override { BaseViewCMD::openWindow(); }
	void closeWindow() override { BaseViewCMD::closeWindow(); }
	void initRenderer() override { BaseViewCMD::initRenderer(); }
	void deleteRenderer() override { BaseViewCMD::deleteRenderer(); }
	sf::RenderWindow* getWindow() override { return BaseViewCMD::getWindow(); }
	void render() override; // { BaseViewCMD::render(); } - sprawdziæ czy zadzia³a samo this->initRenderer albo to w po³¹czeniu z updateGrid i refreshScreen
	void reset() override;

	// Game view functions
	void syncMatrix(TileBase* const (&matrix)[4][4]);
	void startMove(const std::vector<MoveInstruction*>& moveInstructions);
	void startMerge(const std::vector<MergeInstruction*>& mergeInstructions);
	void startSpawn(const std::vector<SpawnInstruction*>& spawnInstructions);
	void startGameOver();
	void endSpawn();

	void updateMove(float dt);
	void updateSpawn(float dt);
	void updateGameOver(float dt);
	void updateScore(const int& score, const int& bestScore);

};