#include "LeaderboardViewGraphic.h"


void LeaderboardViewGraphic::initVariables()
{
	this->score = 0;
	this->mode = LeaderboardMode::VIEW;
	this->v_leaderboardEntries = nullptr;

	this->gui = new LeaderboardViewGUI(windowSize);
}

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

	/*if (cursor_type != sf::StandardCursor::NORMAL) {
		cursor_type = sf::StandardCursor::NORMAL;
		sf::StandardCursor Cursor(sf::StandardCursor::NORMAL);
		Cursor.set(window->getSystemHandle());
	}*/

	window->clear(m_backgroundColor);

	this->gui->render(*window);

	window->display();
}
