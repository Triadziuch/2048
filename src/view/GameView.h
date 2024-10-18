#pragma once

#include "../model/GameModel.h"
#include "BaseView.h"
#include "../AssetManager.h"
#include "../TileMatrix.h"
#include "../GUI.h"

class StudentForm {
public:
	std::string name;
	int age;

public:
	StudentForm();
};

class GameView : public BaseView {
private:
	AssetManager manager;

	// Background variables
	const sf::Color m_backgroundColor{ 250, 248, 239 };
	sf::Texture* m_texture{};
	sf::Sprite m_sprite{};
	sf::Vector2f windowSize{ 1280.f, 720.f };

	const float m_playgroundPadding{ 100.f };
	float m_outerEdgeWidth{ 37.f }, m_innerEdgeWidth{ 36.f }, m_tileWidth{ 215.f };
	float m_scale{ 1.f };
	bool m_isGameOver{ false };

	int m_score{};
	TileMatrix* m_tileMatrix{};
	GUI* m_gui{};

	// Initialization functions
	void initAssets();
public:
	GameView();
	~GameView();

    const std::string &getViewPath() const override;
    void onFormSubmit();
	const StudentForm &getForm() const;
};