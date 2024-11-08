#pragma once
#include "BaseLeaderboardView.h"
#include "src/StandardCursor.h"

class LeaderboardViewGraphic : public BaseLeaderboardView {
private:
	//AssetManager manager;

	// Window variables
	const std::string WINDOW_TITLE = "2048";
	const unsigned int FRAMERATE = 60;
	const unsigned int WINDOW_WIDTH = 1280;
	const unsigned int WINDOW_HEIGHT = 720;
	const bool VERTICAL_SYNC = true;
	sf::StandardCursor::TYPE cursor_type = sf::StandardCursor::NORMAL;
	sf::Vector2i mouse_pos_window;
	sf::Vector2f mouse_pos_view;
	sf::RenderWindow* window;

	// Background variables
	const sf::Color m_backgroundColor{ 250, 248, 239 };
	sf::Texture* m_texture{};
	sf::Sprite m_sprite{};
	sf::Vector2f windowSize{ 1280.f, 720.f };
	sf::Vector2f m_playgroundPosition{};
	const float m_playgroundPadding{ 100.f };
	float m_scale{ 1.f };

	// Movement manager
	MovementManager* m_movementManager;		// Used for tile movement
	MovementContainer* m_movementContainer;	// Used for tile spawning and merging animations

	std::vector<LeaderboardEntry*>* v_leaderboardEntries;

	void updateContent();

	// Initialization functions
	void initWindow();
	void initVariables();
	void initAssets();
	void initAnimations();

public:
	LeaderboardViewGraphic();

	const std::string& getViewPath() const override;

	void openWindow();
	void closeWindow();
	void initRenderer();
	void deleteRenderer();

	void setLeaderboardEntries(std::vector<LeaderboardEntry*>& v_leaderboardEntries);
	void setScore(int score);
	void setMode(LeaderboardMode mode);
	LeaderboardEntry getEntry();

	// Accessors / Mutators
	sf::RenderWindow* getWindow();

	// Render functions
	void render();
};