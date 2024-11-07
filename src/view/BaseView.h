#pragma once

#include "../event/EventObserver.h"
#include "../model/GameModel.h"
#include <Windows.h>

class BaseView : public EventObserver {
public:
    virtual const std::string &getViewPath() const = 0;
	virtual void openWindow() = 0;
	virtual void closeWindow() = 0;
	virtual void initRenderer() = 0;
	virtual void deleteRenderer() = 0;

	virtual void syncMatrix(TileBase* const (&matrix)[4][4]) = 0;

	virtual void startMove(const std::vector<MoveInstruction*>& moveInstructions) = 0;
	virtual void startMerge(const std::vector<MergeInstruction*>& mergeInstructions) = 0;
	virtual void startSpawn(const std::vector<SpawnInstruction*>& spawnInstructions) = 0;
	virtual void endSpawn() = 0;

	// Update functions
	virtual void updateMove(float dt) = 0;
	virtual void updateSpawning(float dt) = 0;
	virtual void updateScore(const int& score, const int& bestScore) = 0;

	// Accessors / Mutators
	virtual sf::RenderWindow* getWindow() = 0;

	// Render functions
	virtual void render() = 0;
};