#pragma once

#include "../model/GameModel.h"
#include "BaseView.h"
#include "../TileMatrix.h"

class GameViewCMD : public BaseView {
private:
	TileBase* const (*m_matrix)[4];
	const std::vector <MoveInstruction*>* m_moveInstructions{};
	const std::vector <SpawnInstruction*>* m_spawnInstructions{};
	const std::vector <MergeInstruction*>* m_mergeInstructions{};
	std::vector <TileModel*> m_tilesToMerge;

public:
	GameViewCMD();

    const std::string &getViewPath() const override;

	void openWindow();
	void closeWindow();

	void syncMatrix(TileBase* const (&matrix)[4][4]);

	void startMove(const std::vector<MoveInstruction*>& moveInstructions);
	void startMerge(const std::vector<MergeInstruction*>& mergeInstructions);
	void startSpawn(const std::vector<SpawnInstruction*>& spawnInstructions);
	void endSpawn();

	// Update functions
	void updateMove(float dt);
	void updateSpawning(float dt);

	// Accessors / Mutators
	sf::RenderWindow* getWindow();

	// Render functions
	void render();
};