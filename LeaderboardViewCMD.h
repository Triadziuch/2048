#pragma once
#include "BaseLeaderboardView.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include "ftxui/component/loop.hpp"
#include <ftxui/dom/table.hpp>
#include "ftxui/dom/node.hpp"
#define byte win_byte_override
#include <Windows.h>

class LeaderboardViewCMD : public BaseLeaderboardView {
private:
	// Console Variables
	HWND consoleWindow = nullptr;
	FILE* m_stdout = nullptr;
	FILE* m_stderr = nullptr;
	FILE* m_stdin = nullptr;

	LeaderboardMode mode;
	std::vector< std::vector< std::string >> values;
	std::vector<LeaderboardEntry*>* v_leaderboardEntries;
	int score;
	std::string name{};

	// Renderer thread variables
	std::thread* ftxui_thread;
	std::mutex mtx, update_content_mutex;
	bool isRefreshing, needRefreshing;
	std::condition_variable cv;

	// FTXUI Leaderboard Variables
	ftxui::Component name_input, name_input_container, renderer;
	ftxui::Table* table;
	ftxui::InputOption input_option_enter;
	ftxui::ScreenInteractive* screen;
	ftxui::Element table_element;

	// Private functions
	void renderFTXUI();
	void updateTableElement();
	void updateContent();
	void refreshScreen();

public:
	LeaderboardViewCMD();

	const std::string& getViewPath() const override;

	void openWindow();
	void closeWindow();
	void initRenderer();
	void deleteRenderer();

	void setLeaderboardEntries(std::vector<LeaderboardEntry*>& v_leaderboardEntries);
	void setScore(int score);
	void setMode(LeaderboardMode mode);
	LeaderboardEntry getEntry();

	// Accessors / Mutators
	sf::RenderWindow* getWindow();

	// Render functions
	void render();
};