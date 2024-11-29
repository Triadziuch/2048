#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "LeaderboardEntry.h"

class LeaderboardCell {
private:
	// Private variables
	std::string data;
	bool isHeader;

	sf::Text text;
	unsigned textSize{ 24u }, headerTextSize{ 32u };
	sf::Color color{ 119, 110, 101 };
	float padding_vertical{ 12.5f }, padding_horizontal{ 25.f };
	float border_thickness{ 2.f };

	sf::RectangleShape border;
	sf::Color borderColor{ 238, 228, 218 };

public:
	// Constructors / Destructors
	LeaderboardCell(std::string data, bool isHeader = false);

	// Accessors / Mutators
	float getTextWidth();
	float getTextHeight();
	float getBorderWidth();
	float getBorderHeight();

	void setBorderWidth(float width);
	void setBorderHeight(float height);
	void setPosition(float x, float y);

	// Render functions
	void render(sf::RenderTarget& target);
};



class LeaderboardRow {
private:
	// Private variables
	int place;
	bool isHeader;
	std::vector<LeaderboardCell*> cells;

public:
	// Constructors / Destructors
	LeaderboardRow(std::vector<std::string> header_text);
	LeaderboardRow(int place, LeaderboardEntry* entry);
	~LeaderboardRow();

	// Accessors / Mutators
	float getTextWidth(int column);
	float getBorderWidth(int column);
	float getTextHeight();
	float getBorderHeight();
	float getHeigth();
	bool getIsHeader();
	size_t getColumnCount();

	void setWidth(int column, float width);
	void setHeight(float height);
	void setPosition(const sf::Vector2f& position);
	void setPosition(float x, float y);

	// Render functions
	void render(sf::RenderTarget& target);
};



class Leaderboard {
private:
	// Private variables
	std::vector<LeaderboardRow*> m_rows;

	// Private functions
	float getMaxWidth(int column);
	void adjustWidth();
	void adjustHeight();

public:
	// Constructors / Destructors
	Leaderboard(std::vector<LeaderboardEntry*> m_entries);
	~Leaderboard();

	// Accessors / Mutators
	void setPosition(const sf::Vector2f& position);
	void setPosition(float x, float y);

	// Render functions
	void render(sf::RenderTarget& target);
};