#pragma once
#include "src/MovementManager/MovementManager.h"

class TileModel {
private:
	int	m_type{ 2 };

	bool m_isMoving{}, m_isMerging{}, m_isSpawning{}, m_isGameOver{}, m_isWin{};

public:
	// Constructors / Destructors
	TileModel(const int type);
	~TileModel();

	// Update functions
	void update(const float dt);

	// Functions
	void startSpawning();
	void startMerging();

	void startGameOver();
	void startWin();

	void stopWin();

	// Mutators
	void setIsMoving(const bool value);
	void setIsMerging(const bool value);

	// Accessors
	int getType() const;
	bool getIsMoving() const;
	bool getMerging() const;
	bool getSpawning() const;
};