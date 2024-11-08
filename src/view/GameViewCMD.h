#pragma once

#include "../model/GameModel.h"
#include "../BaseGameView.h"
#include "../BaseViewCMD.h"
#include "../TileMatrix.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include "ftxui/component/loop.hpp"
#include <future>
#define byte win_byte_override
#include <Windows.h>

class GameViewCMD : public BaseViewCMD, public BaseGameView {
private:
	TileBase* const (*m_matrix)[4];
	int score, bestScore;

	// Console Variables
	HWND consoleWindow = nullptr;
	FILE* m_stdout = nullptr, *m_stderr = nullptr, *m_stdin = nullptr;

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
	// Constructors / Destructors
	GameViewCMD();

	// Window and renderer manipulation functions
	/*void openWindow();
	void closeWindow();
	void initRenderer();
	void deleteRenderer();*/

	void openWindow() override { BaseViewCMD::openWindow(); }
	void closeWindow() override { BaseViewCMD::closeWindow(); }
	void initRenderer() override { BaseViewCMD::initRenderer(); }
	void deleteRenderer() override { BaseViewCMD::deleteRenderer(); }
	sf::RenderWindow* getWindow() override { return BaseViewCMD::getWindow(); }
	void render() override { BaseViewCMD::render(); }

	// Game view functions
	void syncMatrix(TileBase* const (&matrix)[4][4]);
	void startMove(const std::vector<MoveInstruction*>& moveInstructions);
	void startMerge(const std::vector<MergeInstruction*>& mergeInstructions);
	void startSpawn(const std::vector<SpawnInstruction*>& spawnInstructions);
	void endSpawn();

	void updateMove(float dt);
	void updateSpawning(float dt);
	void updateScore(const int& score, const int& bestScore);

	//// Accessors / Mutators
	//sf::RenderWindow* getWindow();

	//// Render functions
	//void render();
};