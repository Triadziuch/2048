#include "Leaderboard.h"

// = = = = = Constructors / Destructors  = = = = = //
LeaderboardCell::LeaderboardCell(std::string data, bool isHeader) : data{ data }, isHeader{ isHeader } 
{
	this->data = data;
	this->data.erase(std::remove(this->data.begin(), this->data.end(), '\r'), this->data.end());
	this->data.erase(std::remove(this->data.begin(), this->data.end(), '\n'), this->data.end());

	text.setString(this->data);
	text.setFont(AssetManager::GetFont("assets/Fonts/ClearSans-Bold.ttf"));

	if (isHeader) 
		text.setCharacterSize(headerTextSize);
	else
		text.setCharacterSize(textSize);

	text.setOrigin(static_cast<int>(text.getGlobalBounds().left + text.getGlobalBounds().width / 2.f),
				   static_cast<int>(text.getGlobalBounds().top + text.getGlobalBounds().height / 2.f));
	text.setFillColor(color);

	border.setSize(sf::Vector2f(text.getGlobalBounds().width + 2.f * padding_horizontal, text.getGlobalBounds().height + 2.f * padding_vertical));
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineThickness(border_thickness);
	border.setOutlineColor(color);
}



// = = = = = Accessors / Mutators  = = = = = //
float LeaderboardCell::getTextWidth()
{
	return text.getGlobalBounds().width + 2.f * padding_horizontal;
}

float LeaderboardCell::getTextHeight()
{
	return text.getGlobalBounds().height + 2.f * padding_vertical;
}

float LeaderboardCell::getBorderWidth()
{
	return border.getSize().x + border.getOutlineThickness();
}

float LeaderboardCell::getBorderHeight()
{
	return border.getSize().y + border.getOutlineThickness();
}

void LeaderboardCell::setBorderWidth(float width)
{
	border.setSize(sf::Vector2f(width, border.getSize().y));
}

void LeaderboardCell::setBorderHeight(float height)
{
	border.setSize(sf::Vector2f(border.getSize().x, height));
}

void LeaderboardCell::setPosition(float x, float y)
{
	border.setPosition(x, y);
	text.setPosition((int)(x + border.getSize().x / 2.f), (int)(y + border.getSize().y / 2.f));
}



// = = = = = Render functions  = = = = = //
void LeaderboardCell::render(sf::RenderTarget& target)
{
	target.draw(border);
	target.draw(text);
}



// = = = = = Constructors / Destructors  = = = = = //
LeaderboardRow::LeaderboardRow(std::vector<std::string> header_text) : place{ 0 }, isHeader{ true } 
{
	for (auto& text : header_text) 
		cells.emplace_back(new LeaderboardCell(text, true));
}

LeaderboardRow::LeaderboardRow(int place, LeaderboardEntry* entry) : place{ place }, isHeader{ false } 
{
	cells.emplace_back(new LeaderboardCell(std::to_string(place)));
	cells.emplace_back(new LeaderboardCell(entry->name));
	cells.emplace_back(new LeaderboardCell(std::to_string(entry->score)));
	cells.emplace_back(new LeaderboardCell(entry->date));
}

LeaderboardRow::~LeaderboardRow()
{
	for (auto& cell : cells)
		delete cell;
}



// = = = = = Accessors / Mutators  = = = = = //
float LeaderboardRow::getTextWidth(int column)
{
	if (column >= cells.size())
		return 0.f;

	return cells[column]->getTextWidth();
}

float LeaderboardRow::getBorderWidth(int column)
{
	if (column >= cells.size())
		return 0.f;

	return cells[column]->getBorderWidth();
}

float LeaderboardRow::getTextHeight()
{
	float max = 0.f;
	for (const auto& cell : cells) {
		float height = cell->getTextHeight();
		if (height > max) max = height;
	}
	return max;
}

float LeaderboardRow::getBorderHeight()
{
	float max = 0.f;
	for (const auto& cell : cells) {
		float height = cell->getBorderHeight();
		if (height > max) max = height;
	}
	return max;
}

float LeaderboardRow::getHeigth()
{
	if (this->cells.empty())
		return 0.f;

	return cells[0]->getBorderHeight();
}

bool LeaderboardRow::getIsHeader()
{
	return isHeader;
}

size_t LeaderboardRow::getColumnCount()
{
	return cells.size();
}

void LeaderboardRow::setWidth(int column, float width)
{
	if (column >= cells.size())
		return;

	cells[column]->setBorderWidth(width);
}

void LeaderboardRow::setHeight(float height)
{
	for (auto& cell : cells) 
		cell->setBorderHeight(height);
}

void LeaderboardRow::setPosition(const sf::Vector2f& position)
{
	this->setPosition(position.x, position.y);
}

void LeaderboardRow::setPosition(float x, float y)
{
	float offset = 0.f;
	float width_sum = 0.f;
	for (auto& cell : cells) width_sum += cell->getBorderWidth();

	for (auto& cell : cells) {
		cell->setPosition(x - (width_sum / 2.f) + offset, y);
		offset += cell->getBorderWidth();
	}
}



// = = = = = Render functions  = = = = = //
void LeaderboardRow::render(sf::RenderTarget& target)
{
	for (auto& cell : cells) 
		cell->render(target);
}



// Private functions
float Leaderboard::getMaxWidth(int column)
{
	float max = 0.f;
	for (auto& row : m_rows) {
		float width = row->getTextWidth(column);
		if (width > max) max = width;
	}
	return max;
}

void Leaderboard::adjustWidth()
{
	int columns = m_rows[0]->getColumnCount();
	for (int i = 0; i < columns; ++i) {
		float width = getMaxWidth(i);
		for (auto& row : m_rows) row->setWidth(i, width);
	}
}

void Leaderboard::adjustHeight()
{
	float max = 0.f;
	for (auto& row : m_rows) {
		if (row->getIsHeader())
			continue;
		float height = row->getTextHeight();
		if (height > max) max = height;
	}

	for (auto& row : m_rows) row->setHeight(max);
}



// = = = = = Constructors / Destructors  = = = = = //
Leaderboard::Leaderboard(std::vector<LeaderboardEntry*> m_entries)
{
	std::vector<std::string> header_text{ "Rank", "Nickname", "Score", "Date" };
	m_rows.emplace_back(new LeaderboardRow(header_text));

	int place = 1;
	for (auto& entry : m_entries) {
		m_rows.emplace_back(new LeaderboardRow(place++, entry));
		if (place > 10)
			break;
	}

	this->adjustWidth();
	this->adjustHeight();
}

Leaderboard::~Leaderboard()
{
	for (auto& row : m_rows) 
		delete row;
}



// Accessors / Mutators
void Leaderboard::setPosition(const sf::Vector2f& position)
{
	this->setPosition(position.x, position.y);
}

void Leaderboard::setPosition(float x, float y)
{
	float offset = 0.f;
	for (auto& row : m_rows) {
		row->setPosition(x, y + offset);
		offset += row->getBorderHeight();
	}
}

void Leaderboard::render(sf::RenderTarget& target)
{
	for (auto& row : m_rows) 
		row->render(target);
}