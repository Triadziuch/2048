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

sf::Event* LeaderboardViewGraphic::update(float dt)
{
	if (this->window == nullptr)
		return nullptr;

	this->gui->update();

	sf::Vector2i mouse_pos_window = sf::Mouse::getPosition(*window);
	sf::Vector2f mouse_pos_view = window->mapPixelToCoords(mouse_pos_window);

	sf::Event ev;
	if (window->pollEvent(ev)) {
		if (mode == LeaderboardMode::EDIT) {
			
			if (ev.type == sf::Event::KeyPressed) {
				if (ev.key.code == sf::Keyboard::Return) {
					this->notify("entered_name");
				}
				else if (ev.key.code == sf::Keyboard::BackSpace) {
					if (name.size() > 0)
						name.pop_back();
					this->gui->setName(name);
				}
			}

			if (ev.type == sf::Event::TextEntered) {
				if (ev.text.unicode < 128 && ev.text.unicode != 8 && gui->getEnteredNameRect().width + 100.f < window->getSize().x) {
					name += static_cast<char>(ev.text.unicode);
					this->gui->setName(name);
				}
			}
		}
		else if (mode == LeaderboardMode::VIEW) {
			if (this->gui->getReturnButton().contains(mouse_pos_view)) {
				if (cursor_type != sf::StandardCursor::HAND) {
					cursor_type = sf::StandardCursor::HAND;
					sf::StandardCursor Cursor(sf::StandardCursor::HAND);
					Cursor.set(window->getSystemHandle());
				}

				if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left) {
					if (this->gui->getReturnButton().contains(mouse_pos_view)) {
						this->notify("return");
					}
				}
			}
			else {
				if (cursor_type != sf::StandardCursor::NORMAL) {
					cursor_type = sf::StandardCursor::NORMAL;
					sf::StandardCursor Cursor(sf::StandardCursor::NORMAL);
					Cursor.set(window->getSystemHandle());
				}
			}
		}
	}

	return &ev;
}



void LeaderboardViewGraphic::setLeaderboardEntries(std::vector<LeaderboardEntry*>& v_leaderboardEntries)
{
	this->v_leaderboardEntries = &v_leaderboardEntries;
	this->gui->setLeaderboard(v_leaderboardEntries);
}

void LeaderboardViewGraphic::setScore(int score)
{
	this->score = score;
	this->gui->setScore(score);
}

void LeaderboardViewGraphic::setMode(LeaderboardMode mode)
{
	this->mode = mode;
	this->name = "";
	this->gui->setMode(mode);
}

LeaderboardEntry LeaderboardViewGraphic::getEntry()
{
	std::time_t t = std::time(nullptr);
	std::tm tm{};
	if (localtime_s(&tm, &t) != 0)
		throw std::runtime_error("Nie uda³o siê pobraæ lokalnej daty i czasu");
	std::ostringstream dateStream;
	dateStream << std::put_time(&tm, "%d.%m.%Y");

	return LeaderboardEntry{ this->name, this->score, dateStream.str() };
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
