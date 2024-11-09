#pragma once
#include "BaseLeaderboardView.h"
#include "BaseViewCMD.h"
#include <ctime>

class LeaderboardViewCMD : public BaseViewCMD, public BaseLeaderboardView {
private:
	std::vector< std::vector< std::string >> values;

	// FTXUI Leaderboard Variables
	ftxui::Component name_input, name_input_container, renderer;
	ftxui::Table* table{};
	ftxui::InputOption input_option_enter;
	ftxui::Element table_element;

	// Private functions
	void renderFTXUI() override;
	void updateContent() override;
	void updateTableElement();
	

public:
	LeaderboardViewCMD();


	void openWindow() override { BaseViewCMD::openWindow(); }
	void closeWindow() override { BaseViewCMD::closeWindow(); }
	void initRenderer() override;
	void deleteRenderer() override { BaseViewCMD::deleteRenderer(); }
	sf::RenderWindow* getWindow() override { return BaseViewCMD::getWindow(); }
	void render() override; //{ BaseViewCMD::render(); } - sprawdziæ czy zadzia³a samo this->initRenderer albo to w po³¹czeniu z updateGrid i refreshScreen

	void setLeaderboardEntries(std::vector<LeaderboardEntry*>& v_leaderboardEntries);
	void setScore(int score);
	void setMode(LeaderboardMode mode);
	LeaderboardEntry getEntry();
};