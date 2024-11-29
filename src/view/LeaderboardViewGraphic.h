#pragma once
#include "BaseLeaderboardView.h"
#include "BaseViewGraphic.h"
#include "LeaderboardViewGUI.h"
#include <ctime>
#include <iomanip>

class LeaderboardViewGraphic : public BaseViewGraphic, public BaseLeaderboardView {
private:
	// Private variables
	LeaderboardViewGUI* gui{};
	std::string name{};


	// Initialization functions
	void initVariables();
	void initAssets() {}
	void initAnimations() {}

public:
	// Constructors / Destructors
	LeaderboardViewGraphic();
	~LeaderboardViewGraphic();

	// Update functions
	sf::Event* update(float dt);

	// Inherited functions
	void openWindow() override { BaseViewGraphic::openWindow(); }
	void closeWindow() override { BaseViewGraphic::closeWindow(); }
	void initRenderer() override { BaseViewGraphic::initRenderer(); }
	void deleteRenderer() override { BaseViewGraphic::deleteRenderer(); }
	sf::RenderWindow* getWindow() override { return BaseViewGraphic::getWindow(); }

	// Accessors / Mutators
	LeaderboardEntry getEntry();
	void setLeaderboardEntries(std::vector<LeaderboardEntry*>& v_leaderboardEntries);
	void setScore(int score);
	void setMode(LeaderboardMode mode);
	
	// Render functions
	void render() override;

	
};