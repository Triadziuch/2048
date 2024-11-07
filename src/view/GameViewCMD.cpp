#include <iostream>
#include "GameViewCMD.h"

using namespace ftxui;

Component GameViewCMD::initGrid()
{
	std::vector<Component> rows;

	for (int row = 0; row < gridSize; ++row) {
		std::vector<Component> cols;
		for (int col = 0; col < gridSize; ++col) {
			auto cell_content = Renderer([&, row, col] {
				return vbox({
					text(" ") | bgcolor(getCellColor(col, row)),
					text(" ") | bgcolor(getCellColor(col, row)),
					text(displayCell(col, row)) | bold | bgcolor(getCellColor(col, row)),
					text(" ") | bgcolor(getCellColor(col, row)),
					text(" ") | bgcolor(getCellColor(col, row)),
					}) | borderStyled(ftxui::LIGHT, Color::White/*getCellBorderColor(col, row)*/) | size(WIDTH, EQUAL, cellSize + 4) | size(HEIGHT, EQUAL, cellSize);
				});
			cols.push_back(cell_content);
		}
		rows.push_back(Container::Horizontal(cols));  // Uk³ad poziomy komórek w jednym wierszu
	}
	return Container::Vertical(rows);  // Uk³ad pionowy wierszy komórek
}

int GameViewCMD::getCell(int row, int col) const
{
	if (m_matrix[row][col])
		return *m_matrix[row][col];
	return 0;
}

ftxui::Color GameViewCMD::getCellColor(int row, int col) const
{
	if (m_matrix == nullptr)
		return Color::Black;

	if (m_matrix[row][col]) {
		int value = *m_matrix[row][col];

		if (value == 2)
			return Color(149, 165, 166);
		else if (value == 4 || value == 8)
			return Color(231, 76, 60);
		else if (value == 16 || value == 32 || value == 64)
			return Color(230, 126, 34);
		else if (value == 128 || value == 256 || value == 512)
			return Color(155, 89, 182);
	}

	return Color::Black;
}

ftxui::Color GameViewCMD::getCellBorderColor(int row, int col) const
{
	if (m_matrix == nullptr)
		return Color::Black;

	if (m_matrix[row][col]) {
		int value = *m_matrix[row][col];

		if (value == 2)
			return Color(149, 165, 166);
		else if (value == 4 || value == 8)
			return Color(231, 76, 60);
		else if (value == 16 || value == 32 || value == 64)
			return Color(230, 126, 34);
		else if (value == 128 || value == 256 || value == 512)
			return Color(155, 89, 182);
		else if (value == 1024 || value == 2048)
			return Color(52, 152, 219);
		else
			return Color(52, 73, 94);
	}

	return Color::White;
}

std::string GameViewCMD::displayCell(int row, int col) const
{
	int value = getCell(row, col);

	if (value == 0)
		return "";

	if (value % 1024 == 0)
		return "   " + std::to_string(value);
	else if (value % 128 == 0)
		return "    " + std::to_string(value);
	else if (value % 16 == 0)
		return "    " + std::to_string(value);
	else
		return "     " + std::to_string(value);
}

void GameViewCMD::renderFTXUI()
{
	ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
	this->screen = &screen;

	update_grid_mutex.lock();
	Loop loop(&screen, renderer);
	update_grid_mutex.unlock();

	std::unique_lock<std::mutex> lock(mtx);

	while (isRefreshing) {
		update_grid_mutex.lock();
		loop.RunOnce();
		this->needRefreshing = false;
		update_grid_mutex.unlock();

		cv.wait(lock, [this] { return needRefreshing; });
	}
}

GameViewCMD::GameViewCMD() {
	this->registerObserver("update_game", [&]() {
		printDebug("[GameViewCMD] Self Observer \"update_game\" triggered.");
		return (false);
		});

	this->updateGrid();
}

const std::string& GameViewCMD::getViewPath() const {
	return ("");
}

void GameViewCMD::refreshScreen()
{
	{
		std::lock_guard<std::mutex> lock(mtx);
		needRefreshing = true;
	}
	cv.notify_one();
}

void GameViewCMD::updateGrid()
{
	update_grid_mutex.lock();
	grid_component = initGrid();
	renderer = Renderer(grid_component, [&] {
		return
			hbox({ 
				filler(),
				vbox({
					text(""),
				}) | size(WIDTH, EQUAL, 9),
				vbox({
					text(""),
				}) | size(WIDTH, EQUAL, 14),
				filler(),

				vbox({
					text("2048 Game") | bold | hcenter,
					separator(),
					grid_component->Render() | hcenter
				}),

				filler(),
				vbox({
					text("Score") | hcenter,
					text(std::to_string(score)) | hcenter,
				}) | border | size(WIDTH, EQUAL, 9) | size(HEIGHT, EQUAL, 2),
				filler(),
				vbox({
					text("Best score") | hcenter,
					text(std::to_string(bestScore)) | hcenter,
				}) | border | size(WIDTH, EQUAL, 14) | size(HEIGHT, EQUAL, 2),
				filler(),
				});
		});
	update_grid_mutex.unlock();
}

void GameViewCMD::openWindow()
{
	if (AllocConsole()) {
		// Zapisz uchwyt do okna konsoli
		consoleWindow = GetConsoleWindow();

		if (freopen_s(&m_stdout, "CONOUT$", "w", stdout) != 0)
			printDebug("Nie mozna przekierowac stdout.");
		if (freopen_s(&m_stderr, "CONOUT$", "w", stderr) != 0)
			printDebug("Nie mo¿na przekierowaæ stderr.");
		if (freopen_s(&m_stdin, "CONIN$", "r", stdin) != 0)
			printDebug("Nie mo¿na przekierowaæ stdin.");

		std::cout.clear();
		std::cerr.clear();
		std::cin.clear();

		std::cout.setf(std::ios::unitbuf);
		setvbuf(stdout, nullptr, _IONBF, 0);

		// Uzyskaj wymiary okna konsoli
		RECT consoleRect;
		GetWindowRect(consoleWindow, &consoleRect);

		// Uzyskaj wymiary ekranu
		RECT screenRect;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &screenRect, 0);

		// Oblicz pozycjê na œrodku ekranu
		int screenWidth = screenRect.right - screenRect.left;
		int screenHeight = screenRect.bottom - screenRect.top;

		int consoleWidth = consoleRect.right - consoleRect.left;
		int consoleHeight = consoleRect.bottom - consoleRect.top;

		int posX = (screenWidth - consoleWidth) / 2 + screenRect.left;
		int posY = (screenHeight - consoleHeight) / 2 + screenRect.top;

		// Ustaw pozycjê okna konsoli na œrodku ekranu
		MoveWindow(consoleWindow, posX, posY, consoleWidth, consoleHeight, TRUE);
	}

	this->isRefreshing = true;
}

void GameViewCMD::closeWindow()
{
	this->isRefreshing = false;
	this->refreshScreen();

	if (ftxui_thread->joinable())
		ftxui_thread->join();

	delete ftxui_thread;
	ftxui_thread = nullptr;
	this->screen = nullptr;

	if (m_stdout) {
		fclose(m_stdout);
		m_stdout = nullptr;
	}
	if (m_stderr) {
		fclose(m_stderr);
		m_stderr = nullptr;
	}
	if (m_stdin) {
		fclose(m_stdin);
		m_stdin = nullptr;
	}

	freopen_s(&m_stdout, "NUL", "w", stdout);
	freopen_s(&m_stderr, "NUL", "w", stderr);
	freopen_s(&m_stdin, "NUL", "r", stdin);

	std::cout.clear();
	std::cerr.clear();
	std::cin.clear();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	HWND hWnd = GetConsoleWindow();
	if (hWnd) {
		FreeConsole();
		SendMessage(hWnd, WM_CLOSE, 0, 0);
	}
}

void GameViewCMD::syncMatrix(TileBase* const(&matrix)[4][4])
{
	update_grid_mutex.lock();
	this->m_matrix = matrix;
	update_grid_mutex.unlock();

	this->updateGrid();
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

	this->updateGrid();
	this->refreshScreen();
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
	if (this->screen == nullptr)
		ftxui_thread = new std::thread([this]() {
		this->renderFTXUI();
			});
}

void GameViewCMD::updateScore(const int& score, const int& bestScore)
{
	this->score = score;
	this->bestScore = bestScore;

	this->updateGrid();
	this->refreshScreen();
}
