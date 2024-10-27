#include <iostream>
#include "GameViewCMD.h"

GameViewCMD::GameViewCMD() {
    this->registerObserver("update_game", [&] () {
			printDebug("[GameViewCMD] Self Observer \"update_game\" triggered.");
        return (false);
    });
}

const std::string & GameViewCMD::getViewPath() const {
    return ("");
}

void GameViewCMD::openWindow()
{
	FILE* file;

	if (AllocConsole()) {
		if (freopen_s(&file, "CONOUT$", "w", stdout) != 0) 
			printDebug("Nie mozna przekierowac stdout.");

		if (freopen_s(&file, "CONOUT$", "w", stderr) != 0) 
			printDebug("Nie mo¿na przekierowaæ stderr.");

		if (freopen_s(&file, "CONIN$", "r", stdin) != 0) 
			printDebug("Nie mo¿na przekierowaæ stdin.");

		std::cout.setf(std::ios::unitbuf);
		setvbuf(stdout, nullptr, _IONBF, 0);
	}
}

void GameViewCMD::closeWindow()
{
	FreeConsole();
}

void GameViewCMD::syncMatrix(TileBase* const(&matrix)[4][4])
{
	this->m_matrix = matrix;
}

void GameViewCMD::startMove(const std::vector<MoveInstruction*>& moveInstructions)
{
	//this->m_moveInstructions = &moveInstructions;

	//for (const auto& instruction : *m_moveInstructions) {
	//	sf::Vector2i old_pos = instruction->getOldPos();
	//	sf::Vector2i new_pos = instruction->getNewPos();
	//	sf::Vector2i distance = new_pos - old_pos;
	//	const sf::Vector2f pixel_distance = sf::Vector2f{ static_cast<float>(distance.x) * (m_innerEdgeWidth + m_tileWidth),
	//													  static_cast<float>(distance.y) * (m_innerEdgeWidth + m_tileWidth) };
	//	printf("Move pixel distance: %f %f\n", pixel_distance.x, pixel_distance.y);
	//	this->tiles[old_pos.x][old_pos.y]->setIsMoving(true);
	//	this->tiles[old_pos.x][old_pos.y]->smoothMove(pixel_distance, m_timeMovingMax);
	//}
	this->notify("started_move");
}

void GameViewCMD::startMerge(const std::vector<MergeInstruction*>& mergeInstructions)
{
	if (mergeInstructions.empty())
		return;

	this->m_mergeInstructions = &mergeInstructions;

	/*for (const auto& instruction : *this->m_mergeInstructions) {
		const sf::Vector2i pos = instruction->pos;
		tiles[pos.x][pos.y]->startMerging();
	}*/

	this->notify("started_merging");
}

void GameViewCMD::startSpawn(const std::vector<SpawnInstruction*>& spawnInstructions)
{
	this->m_spawnInstructions = &spawnInstructions;

	/*for (const auto& instruction : *this->m_spawnInstructions) {
		this->tiles[instruction->pos.x][instruction->pos.y] = new Tile(instruction->type, m_tileTextures[findID(instruction->type)], &m_scale, calculateTilePos(instruction->pos), m_movementManager);
		this->tiles[instruction->pos.x][instruction->pos.y]->startSpawning();
	}*/

	this->notify("started_spawning");
}

void GameViewCMD::endSpawn()
{
	/*m_movementManager->update(1.f);

	for (auto& instruction : *m_spawnInstructions)
		tiles[instruction->pos.x][instruction->pos.y]->update(1.f);*/

	this->notify("finished_spawning");
}

void GameViewCMD::updateMove(float dt)
{
	/*this->m_movementManager->update(dt);
	this->m_movementContainer->update(dt);

	if (m_timeMoving < m_timeMovingMax)
		m_timeMoving += dt;
	else {
		m_timeMoving = 0.f;
		this->notify("finished_move");
	}*/

	this->notify("finished_move");
}

void GameViewCMD::updateSpawning(float dt)
{
	/*this->m_movementManager->update(dt);

	bool finishedSpawning = false;
	for (auto& instruction : *m_spawnInstructions) {
		tiles[instruction->pos.x][instruction->pos.y]->update(dt);
		finishedSpawning = !tiles[instruction->pos.x][instruction->pos.y]->getSpawning();
	}

	if (finishedSpawning) {
		this->m_mergeInstructions = nullptr;
		this->notify("finished_spawning");
	}*/

	this->notify("finished_spawning");
}

sf::RenderWindow* GameViewCMD::getWindow()
{
	return nullptr;
}

void GameViewCMD::render()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == nullptr) return;

	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	DWORD charsWritten;
	DWORD consoleSize;
	COORD topLeft = { 0, 0 };

	// Pobranie rozmiaru bufora konsoli
	if (!GetConsoleScreenBufferInfo(hConsole, &consoleInfo)) return;
	consoleSize = consoleInfo.dwSize.X * consoleInfo.dwSize.Y;

	// Wype³nienie bufora pustymi znakami
	FillConsoleOutputCharacter(hConsole, ' ', consoleSize, topLeft, &charsWritten);

	// Przywrócenie domyœlnych atrybutów (kolory znaków i t³a)
	FillConsoleOutputAttribute(hConsole, consoleInfo.wAttributes, consoleSize, topLeft, &charsWritten);

	// Ustawienie kursora na pocz¹tek
	SetConsoleCursorPosition(hConsole, topLeft);

	//system("cls");

	printf("\n\nMATRIX:\n");
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (m_matrix[i][j]) {
				printf("%-3d", *m_matrix[i][j]);
			}
			else
				printf("%-3d", 0);
		}
		printf("\n");
	}
	printf("\n\n");
}
