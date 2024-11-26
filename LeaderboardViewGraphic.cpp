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

	/*if (cursor_type != sf::StandardCursor::NORMAL) {
		cursor_type = sf::StandardCursor::NORMAL;
		sf::StandardCursor Cursor(sf::StandardCursor::NORMAL);
		Cursor.set(window->getSystemHandle());
	}*/

	window->clear(m_backgroundColor);

	sf::Text text;
	text.setFont(AssetManager::GetFont("assets/Fonts/ClearSans-Bold.ttf"));
	text.setString("LEADERBOARD");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::White);
	text.setPosition(windowSize.x / 2 - text.getGlobalBounds().width / 2, 50);
	window->draw(text);

	window->display();
}
