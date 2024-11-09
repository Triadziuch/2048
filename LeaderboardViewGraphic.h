#pragma once
#include "BaseLeaderboardView.h"
#include "BaseViewGraphic.h"

class LeaderboardViewGraphic : public BaseViewGraphic, public BaseLeaderboardView {
private:
	// Initialization functions
	void initVariables() {}
	void initAssets() {}
	void initAnimations() {}

public:
	LeaderboardViewGraphic();
	~LeaderboardViewGraphic();

	void openWindow() override { BaseViewGraphic::openWindow(); }
	void closeWindow() override { BaseViewGraphic::closeWindow(); }
	void initRenderer() override { BaseViewGraphic::initRenderer(); }
	void deleteRenderer() override { BaseViewGraphic::deleteRenderer(); }
	sf::RenderWindow* getWindow() override { return BaseViewGraphic::getWindow(); }
	void render() override;

	void setLeaderboardEntries(std::vector<LeaderboardEntry*>& v_leaderboardEntries);
	void setScore(int score);
	void setMode(LeaderboardMode mode);
	LeaderboardEntry getEntry();
};