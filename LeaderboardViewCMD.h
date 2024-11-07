#pragma once
#include "BaseLeaderboardView.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include "ftxui/component/loop.hpp"
#include <ftxui/dom/table.hpp>
#include "ftxui/dom/node.hpp"

class LeaderboardViewCMD : public BaseLeaderboardView {
private:
	// Console Variables
	HWND consoleWindow = nullptr;
	FILE* m_stdout = nullptr;
	FILE* m_stderr = nullptr;
	FILE* m_stdin = nullptr;

	bool enteringName = false;
	bool isRefreshing, needRefreshing;
	int score;

	std::vector<LeaderboardEntry*>* v_leaderboardEntries;

	std::thread* ftxui_thread;
	std::mutex mtx, update_grid_mutex;
	std::condition_variable cv;

	bool nameentered = false;
	std::mutex mtx_name_entered;
	std::condition_variable cv_name_entered;

	ftxui::Loop *loop;
	ftxui::Closure exit_loop;
	ftxui::Component renderer;
	ftxui::Table* table;
	ftxui::InputOption input_option_enter;
	ftxui::ScreenInteractive* screen;
	ftxui::Component input_add;
	ftxui::Component container;
	ftxui::Element table_element;
	std::vector< std::vector< std::string >> values;

	std::string name{};

	void renderFTXUI();
	void updateTableElement();
	void updateContent();
	void refreshScreen();
	void enteredName();

public:
	LeaderboardViewCMD();

	const std::string& getViewPath() const override;

	void openWindow();
	void closeWindow();
	void initRenderer();
	void deleteRenderer();

	void setLeaderboardEntries(std::vector<LeaderboardEntry*>& v_leaderboardEntries);
	void enterName(int score);

	// Accessors / Mutators
	sf::RenderWindow* getWindow();

	// Render functions
	void render();
};