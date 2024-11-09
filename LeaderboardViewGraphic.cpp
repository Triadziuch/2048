#include "LeaderboardViewGraphic.h"


LeaderboardViewGraphic::LeaderboardViewGraphic() : BaseViewGraphic()
{
	initAssets();
	initVariables();
	initAnimations();
}

LeaderboardViewGraphic::~LeaderboardViewGraphic()
{
}



void LeaderboardViewGraphic::setLeaderboardEntries(std::vector<LeaderboardEntry*>& v_leaderboardEntries)
{
	this->v_leaderboardEntries = &v_leaderboardEntries;
}

void LeaderboardViewGraphic::setScore(int score)
{
	this->score = score;
	//this->updateContent();
}

void LeaderboardViewGraphic::setMode(LeaderboardMode mode)
{
	this->score = score;
	//this->updateContent();
}

LeaderboardEntry LeaderboardViewGraphic::getEntry()
{
	return LeaderboardEntry();
}


void LeaderboardViewGraphic::render()
{
	if (window == nullptr)
		return;

	window->clear(m_backgroundColor);
	window->display();
}
