#pragma once
#include "BaseView.h"
#include "../model/LeaderboardModel.h"
#include "../LeaderboardMode.h"

class BaseLeaderboardView : public virtual BaseView
{
protected:
	std::vector<LeaderboardEntry*>* v_leaderboardEntries;
	LeaderboardMode mode{};
	int score{};
	std::string name;

public:
	virtual sf::Event* update(float dt) = 0;
	virtual void setLeaderboardEntries(std::vector<LeaderboardEntry*>& v_leaderboardEntries) = 0;
	virtual void setScore(int score) = 0;
	virtual void setMode(LeaderboardMode mode) = 0;
	virtual LeaderboardEntry getEntry() = 0;
};

