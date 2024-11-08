#pragma once
#include "src/view/BaseView.h"

class BaseGameView : public virtual BaseView {
public:
	virtual void syncMatrix(TileBase* const (&matrix)[4][4]) = 0;

	virtual void startMove(const std::vector<MoveInstruction*>& moveInstructions) = 0;
	virtual void startMerge(const std::vector<MergeInstruction*>& mergeInstructions) = 0;
	virtual void startSpawn(const std::vector<SpawnInstruction*>& spawnInstructions) = 0;
	virtual void endSpawn() = 0;

	// Update functions
	virtual void updateMove(float dt) = 0;
	virtual void updateSpawning(float dt) = 0;
	virtual void updateScore(const int& score, const int& bestScore) = 0;
};