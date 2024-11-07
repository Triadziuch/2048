#pragma once
#include "BaseLeaderboardView.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include "ftxui/component/loop.hpp"

class LeaderboardViewCMD : public BaseLeaderboardView {
private:
	// Console Variables
	HWND consoleWindow = nullptr;
	FILE* m_stdout = nullptr;
	FILE* m_stderr = nullptr;
	FILE* m_stdin = nullptr;

	bool isRefreshing, needRefreshing;

	std::vector<LeaderboardEntry*>* v_leaderboardEntries;

	std::thread* ftxui_thread;
	std::mutex mtx, update_grid_mutex;
	std::condition_variable cv;

	ftxui::Loop* loop;
	ftxui::Component renderer;
	ftxui::ScreenInteractive* screen;

	void renderFTXUI();
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

	// Accessors / Mutators
	sf::RenderWindow* getWindow();

	// Render functions
	void render();
};