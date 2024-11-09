#pragma once
#include "src/view/BaseView.h"
#include "SFML/Graphics.hpp"
#include "src/AssetManager.h"
#include "src/StandardCursor.h"
#include "src/MovementManager/MovementManager.h"

class BaseViewGraphic : public virtual BaseView
{
private:
	// Initialization functions
	void initVariables();

protected:
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
	sf::Vector2f windowSize{ 1280.f, 720.f };

	// Movement manager
	MovementManager* m_movementManager;		// Used for tile movement
	MovementContainer* m_movementContainer;	// Used for tile spawning and merging animations

public:
	// Constructors / Destructors
	BaseViewGraphic();

	// BaseView member functions
    void openWindow() override;
    void closeWindow() override;
    void initRenderer() override;
    void deleteRenderer() override;
    sf::RenderWindow* getWindow() override;
    virtual void render() = 0;
};

