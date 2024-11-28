#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include "src/AssetManager.h"
#include "LeaderboardEntry.h"
#include "LeaderboardMode.h"

class LeaderboardCell {
	std::string data;
	bool isHeader;

	sf::Text text;
	unsigned textSize{ 24u };
	unsigned headerTextSize{ 32u };
	sf::Color color{ 119, 110, 101 };
	float padding_vertical{ 12.5f }, padding_horizontal{ 25.f };

	// borders
	sf::RectangleShape border;
	sf::Color borderColor{ 238, 228, 218 };


public:
	LeaderboardCell(std::string data, bool isHeader = false) : data(data), isHeader(isHeader) {
		this->data = data;
		this->data.erase(std::remove(this->data.begin(), this->data.end(), '\r'), this->data.end());
		this->data.erase(std::remove(this->data.begin(), this->data.end(), '\n'), this->data.end());

		text.setString(this->data);
		text.setFont(AssetManager::GetFont("assets/Fonts/ClearSans-Bold.ttf"));
		
		if (isHeader) {
			text.setCharacterSize(headerTextSize);
		}
		else
			text.setCharacterSize(textSize);

		text.setOrigin((int)(text.getGlobalBounds().left + text.getGlobalBounds().width / 2.f), (int)(text.getGlobalBounds().top + text.getGlobalBounds().height / 2.f));
		text.setFillColor(color);
		

		border.setSize(sf::Vector2f(200.f, 50.f));
		border.setFillColor(sf::Color::Transparent);
		border.setOutlineThickness(2.f);
		border.setOutlineColor(color);
	}

	float getTextWidth() { return text.getGlobalBounds().width + 2 * padding_horizontal; }
	float getTextHeight() { return text.getGlobalBounds().height + 2 * padding_vertical; }
	float getBorderWidth() { return border.getSize().x + border.getOutlineThickness(); }
	float getBorderHeight() { return border.getSize().y + border.getOutlineThickness(); }

	void setBorderWidth(float width) { border.setSize(sf::Vector2f(width, border.getSize().y)); }
	void setBorderHeight(float height) { border.setSize(sf::Vector2f(border.getSize().x, height)); }

	void setPosition(float x, float y) {
		border.setPosition(x, y);
		text.setPosition((int)(x + border.getSize().x / 2.f), (int)(y + border.getSize().y / 2.f));
	}

	void render(sf::RenderTarget& target) {
		target.draw(border);
		target.draw(text);
	}
};


class LeaderboardRow {
	int place;
	bool isHeader;
	std::vector<LeaderboardCell*> cells;


public:
	LeaderboardRow(std::vector<std::string> header_text) : place(0) {
		for (auto& text : header_text) cells.emplace_back(new LeaderboardCell(text, true));
		this->isHeader = true;
	}

	LeaderboardRow(int place, LeaderboardEntry* entry) : place(place) {
		cells.emplace_back(new LeaderboardCell(std::to_string(place)));
		cells.emplace_back(new LeaderboardCell(entry->name));
		cells.emplace_back(new LeaderboardCell(std::to_string(entry->score)));
		cells.emplace_back(new LeaderboardCell(entry->date));
		this->isHeader = false;
	}

	~LeaderboardRow() { for (auto& cell : cells) delete cell; }

	float getTextWidth(int column) {
		return cells[column]->getTextWidth();
	}

	float getBorderWidth(int column) {
		return cells[column]->getBorderWidth();
	}

	float getTextHeight() {
		float max = 0.f;
		for (auto& cell : cells) {
			float height = cell->getTextHeight();
			if (height > max) max = height;
		}
		return max;
	}

	float getBorderHeight() {
		float max = 0.f;
		for (auto& cell : cells) {
			float height = cell->getBorderHeight();
			if (height > max) max = height;
		}
		return max;
	}

	float getHeigth() {
		return cells[0]->getBorderHeight();
	}

	bool getIsHeader() { return isHeader; }

	void setWidth(int column, float width) {
		cells[column]->setBorderWidth(width);
	}

	void setHeight(float height) {
		if (isHeader)
			return;

		for (auto& cell : cells) cell->setBorderHeight(height);
	}

	int getColumnCount() { return cells.size(); }

	void setPosition(float x, float y) {
		float offset = 0.f;
		float width_sum = 0.f;
		for (auto& cell : cells) width_sum += cell->getBorderWidth();

		for (auto& cell : cells) {
			cell->setPosition(x - (width_sum / 2.f) + offset, y);
			offset += cell->getBorderWidth();
		}
	}

	void render(sf::RenderTarget& target) {
		for (auto& cell : cells) cell->render(target);
	}
};

class Leaderboard {
	std::vector<LeaderboardRow*> m_rows;

	float getMaxWidth(int column) {
		float max = 0.f;
		for (auto& row : m_rows) {
			float width = row->getTextWidth(column);
			if (width > max) max = width;
		}
		return max;
	}

	void adjustWidth() {
		int columns = m_rows[0]->getColumnCount();
		for (int i = 0; i < columns; ++i) {
			float width = getMaxWidth(i);
			for (auto& row : m_rows) row->setWidth(i, width);
		}
	}

	void adjustHeight() {
		float max = 0.f;
		for (auto& row : m_rows) {
			if (row->getIsHeader())
				continue;
			float height = row->getTextHeight();
			if (height > max) max = height;
		}

		for (auto& row : m_rows) row->setHeight(max);
	}

public:
	Leaderboard(std::vector<LeaderboardEntry*> m_entries) {
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

	~Leaderboard() { for (auto& row : m_rows) delete row; }

	void setPosition(float x, float y) {
		float offset = 0.f;
		for (auto& row : m_rows) {
			row->setPosition(x, y + offset);
			offset += row->getBorderHeight();
		}
	}

	void render(sf::RenderTarget& target) {
		for (auto& row : m_rows) row->render(target);
	}

};

class LeaderboardViewGUI {
private:
	int m_score{}, m_bestScore{};
	float m_scale{ 0.25f };

	float m_gameOverTime{};
	const float m_gameOverTimeMax{ 0.5f };

	bool m_isGameOver{};

	const std::string m_returnString{ "Return to game" }, m_leaderboardString{ "Leaderboard" }, m_bestScoreString{ "BEST" }, m_scoreString{ "SCORE" };
	const std::string m_bestScoreFilename{ "assets/best_score.txt" };
	const std::string m_congratulationsString{ "Congratulations, " };
	sf::Font* m_font;
	sf::Text m_returnText, m_leaderboardText, m_bestScoreHeaderText, m_scoreHeaderText, m_scoreText, m_bestScoreText, m_congratulationsText;

	const unsigned m_returnSize{ 20u }, m_bestScoreSize{ 12u }, m_scoreSize{ 12u }, m_leaderboardSize{ 64u }, m_congratulationsSize{ 64u };
	sf::Sprite m_returnButtonSprite, m_bestScoreButtonSprite, m_scoreButtonSprite;

	sf::Texture* m_returnTexture, * m_scoreTexture;
	sf::Color m_leaderboardColor{ 119, 110, 101 }, m_returnColor{ 249, 246, 242 }, m_scoreColor{ 238, 228, 218 };

	sf::Vector2f m_windowSize;

	Leaderboard* m_leaderboard;
	LeaderboardMode mode;

	sf::Clock cursor_clock;
	bool show_cursor = false;

	void initText();
	void initSprites();
	void center_origin(sf::Sprite& sprite);
	void justifyHorizontal(const sf::FloatRect& button, sf::Text& text);

public:
	// Constructors / Destructors
	LeaderboardViewGUI(sf::Vector2f windowSize);
	virtual ~LeaderboardViewGUI();


	void update();

	// Mutators
	void setMode(LeaderboardMode mode);
	void setScore(int value);
	void setBestScore(int value);
	void addScore(int value);
	void setName(std::string name);
	void setLeaderboard(std::vector<LeaderboardEntry*> entries);

	// Accessors
	sf::FloatRect getReturnButton() { return m_returnButtonSprite.getGlobalBounds(); }
	sf::FloatRect getEnteredNameRect() { return m_congratulationsText.getGlobalBounds(); }

	// Render GUI
	void render(sf::RenderTarget& target);
};