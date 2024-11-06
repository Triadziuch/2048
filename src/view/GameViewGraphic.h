#pragma once

#include "../model/GameModel.h"
#include "BaseView.h"
#include "../AssetManager.h"
#include "../TileMatrix.h"
#include "../GUI.h"
#include "../StandardCursor.h"

class GameViewGraphic : public BaseView {
private:
	AssetManager manager;

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
	sf::Texture* m_tileTextures[14];
	sf::Sprite m_sprite{};
	sf::Vector2f windowSize{ 1280.f, 720.f };
	sf::Vector2f m_playgroundPosition{};
	const float m_playgroundPadding{ 100.f };
	float m_scale{ 1.f }, m_outerEdgeWidth{ 37.f }, m_innerEdgeWidth{ 36.f }, m_tileWidth{ 215.f };
	bool m_isGameOver{ false };

	int m_score{};
	
	// Animation time variables
	const float m_timeSpawningMax = 0.2f;
	float m_timeMoving = 0.f;
	const float m_timeMovingMax = 0.2f;
	float m_timeMerging = 0.f;
	const float m_timeMergingMax = 0.2f;

	// Movement manager
	MovementManager* m_movementManager;		// Used for tile movement
	MovementContainer* m_movementContainer;	// Used for tile spawning and merging animations



	Tile* tiles[4][4]{ {} };
	TileBase* const (*m_matrix)[4];
	const std::vector <MoveInstruction*>* m_moveInstructions{};
	const std::vector <SpawnInstruction*>* m_spawnInstructions{};
	const std::vector <MergeInstruction*>* m_mergeInstructions{};

	std::vector <TileModel*> m_tilesToMerge;

	GUI* m_gui{};

	// Initialization functions
	void initWindow();
	void initVariables();
	void initAssets();
	void initAnimations();

	// Utility functions
	sf::Vector2f calculateTilePos(const sf::Vector2i& pos) const;
	int findID(int type) const;

	// Private functions
	void drawMatrixCMD();
	void updateTiles();

public:
	// Constructors / Destructors
	GameViewGraphic();
	~GameViewGraphic();

	// Public functions
	void syncMatrix(TileBase* const (&matrix)[4][4]);

	void startMove(const std::vector<MoveInstruction*>& moveInstructions);
	void startMerge(const std::vector<MergeInstruction*>& mergeInstructions);
	void startSpawn(const std::vector<SpawnInstruction*>& spawnInstructions);
	void endSpawn();

	const std::string& getViewPath() const;
	void openWindow();
	void closeWindow();

	// Update functions
	void updateMove(float dt);
	void updateSpawning(float dt);
	void updateScore(const int& score, const int& bestScore);

	// Accessors / Mutators
	sf::RenderWindow* getWindow();

	// Render functions
	void render();
};