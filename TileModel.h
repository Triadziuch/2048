#pragma once
#include "src/MovementManager/MovementManager.h"


class TileBase {
protected:
	int m_type{ 2 };

	TileBase(const int type);

public:
	operator int() const { return m_type; }
};

class TileModel : public TileBase {
private:
	bool m_isMoving{}, m_isMerging{}, m_isGameOver{};

public:
	// Constructors / Destructors
	TileModel(const int type);

	// Functions
	void startGameOver();

	// Mutators
	void setIsMoving(const bool value);
	void setIsMerging(const bool value);

	// Accessors
	bool isMoving() const;
	bool isMerging() const;
};