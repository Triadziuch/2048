#include "TileMatrix.h"
#include "GUI.h"

using namespace std;

class Playground {
private:
	// Background variables
	const sf::Color m_backgroundColor{ 250, 248, 239 };
	sf::Texture* m_texture{};
	sf::Sprite m_sprite{};

	const float m_playgroundPadding{ 100.f };
	float m_outerEdgeWidth{ 37.f }, m_innerEdgeWidth{ 36.f }, m_tileWidth{ 215.f };
	float m_scale{ 1.f };
	bool m_isGameOver{ false };

	int m_score{};
	TileMatrix* m_tileMatrix{};
	GUI* m_gui{};

public:
	// Constructors / Destructors
	Playground(const sf::Vector2f& windowSize);
	virtual ~Playground();

	void update(float dt);
	void updateScore();

	void move(const sf::Keyboard::Key key);
	void clearBoard();

	// Accessors
	const float& getOuterEdgeWidth() const { return m_outerEdgeWidth; }
	const float& getInnerEdgeWidth() const { return m_innerEdgeWidth; }
	const float& getTileWidth() const { return m_tileWidth; }
	const float& getScale() const { return m_scale; }
	const bool getIsMoving() const { return m_tileMatrix->getIsMoving(); }
	sf::FloatRect getNewGameButton() { return m_gui->getNewGameButton(); }
	const bool getIsGameOver() const { return m_tileMatrix->getIsGameOver(); }

	// Rendering playground
	void render (sf::RenderTarget& target);
};