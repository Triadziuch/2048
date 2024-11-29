#pragma once
#include "BaseLeaderboardView.h"
#include "BaseViewCMD.h"
#include "../LeaderboardEntry.h"
#include <ctime>

class LeaderboardViewCMD : public BaseViewCMD, public BaseLeaderboardView {
private:
	// Leaderboard values
	std::vector< std::vector< std::string >> values;

	// FTXUI Leaderboard Variables
	ftxui::Component name_input, name_input_container;
	ftxui::Table* table{};
	ftxui::InputOption input_option_enter;
	ftxui::Element table_element;
	ftxui::Component container, main_container, scroller;

	// Private functions
	void renderFTXUI() override;
	void updateContent();
	void updateTableElement();

public:
	// Constructors / Destructors
	LeaderboardViewCMD();
	~LeaderboardViewCMD();

	// Update functions
	sf::Event* update(float dt);

	// Inherited public functions
	void openWindow() override { BaseViewCMD::openWindow(); }
	void closeWindow() override { BaseViewCMD::closeWindow(); }
	void initRenderer() override;
	void deleteRenderer() override { BaseViewCMD::deleteRenderer(); }
	sf::RenderWindow* getWindow() override { return BaseViewCMD::getWindow(); }
	void render() override;

	// Accessors / Mutators
	LeaderboardEntry getEntry();
	void setLeaderboardEntries(std::vector<LeaderboardEntry*>& v_leaderboardEntries);
	void setScore(int score);
	void setMode(LeaderboardMode mode);
};