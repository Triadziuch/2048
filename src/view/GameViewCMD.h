#pragma once

#include "../model/GameModel.h"
#include "../BaseGameView.h"
#include "../TileMatrix.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include "ftxui/component/loop.hpp"
#include <future>

class GameViewCMD : public BaseGameView {
private:
	TileBase* const (*m_matrix)[4];
	const std::vector <MoveInstruction*>* m_moveInstructions{};
	const std::vector <SpawnInstruction*>* m_spawnInstructions{};
	const std::vector <MergeInstruction*>* m_mergeInstructions{};
	std::vector <TileModel*> m_tilesToMerge;
	int score, bestScore;

	// Console Variables
	HWND consoleWindow = nullptr;
	FILE* m_stdout = nullptr;
	FILE* m_stderr = nullptr;
	FILE* m_stdin = nullptr;

	// Grid variables
	constexpr static int gridSize = 4;
	constexpr static int cellSize = 9;
	ftxui::Component grid_component;
	ftxui::ScreenInteractive* screen;
	ftxui::Loop *loop;

	bool isRefreshing, needRefreshing;
	std::mutex mtx, update_grid_mutex;
	std::condition_variable cv;

	std::thread* ftxui_thread;

	
	ftxui::Component renderer;

	int getCell(int row, int col) const;
	ftxui::Color getCellColor(int row, int col) const;
	ftxui::Color getCellBorderColor(int row, int col) const;
	std::string displayCell(int row, int col) const;

	ftxui::Component initGrid();
	void renderFTXUI();
	void updateGrid();
	void refreshScreen();
	

public:
	GameViewCMD();

    const std::string &getViewPath() const override;

	void openWindow();
	void closeWindow();
	void initRenderer();
	void deleteRenderer();

	void syncMatrix(TileBase* const (&matrix)[4][4]);

	void startMove(const std::vector<MoveInstruction*>& moveInstructions);
	void startMerge(const std::vector<MergeInstruction*>& mergeInstructions);
	void startSpawn(const std::vector<SpawnInstruction*>& spawnInstructions);
	void endSpawn();

	// Update functions
	void updateMove(float dt);
	void updateSpawning(float dt);
	void updateScore(const int& score, const int& bestScore);

	// Accessors / Mutators
	sf::RenderWindow* getWindow();

	// Render functions
	void render();
};