#pragma once
#include "src/view/BaseView.h"
#include "../LeaderboardModel.h"
#include "LeaderboardMode.h"

class BaseLeaderboardView : public BaseView
{
public:
	virtual void setLeaderboardEntries(std::vector<LeaderboardEntry*>& v_leaderboardEntries) = 0;
	virtual void setScore(int score) = 0;
	virtual void setMode(LeaderboardMode mode) = 0;
	virtual LeaderboardEntry getEntry() = 0;
};

