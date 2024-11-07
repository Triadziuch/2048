#pragma once
#include "src/view/BaseView.h"
#include "../LeaderboardModel.h"

class BaseLeaderboardView : public BaseView
{
public:
	virtual void setLeaderboardEntries(std::vector<LeaderboardEntry*>& v_leaderboardEntries) = 0;
	virtual void enterName(int score) = 0;
};

