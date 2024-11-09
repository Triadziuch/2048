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
					}) | borderStyled(ftxui::LIGHT, Color::White) | size(WIDTH, EQUAL, cellSize + 4) | size(HEIGHT, EQUAL, cellSize);
				});
			cols.push_back(cell_content);
		}
		rows.push_back(Container::Horizontal(cols));
	}
	return Container::Vertical(rows);
}

void GameViewCMD::renderFTXUI()
{
	ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
	this->screen = &screen;

	update_content_mutex.lock();
	Loop loop(&screen, renderer);
	update_content_mutex.unlock();

	std::unique_lock<std::mutex> lock(mtx);

	while (isRefreshing) {
		cv.wait(lock, [this] { return needRefreshing; });

		update_content_mutex.lock();
		loop.RunOnce();
		this->needRefreshing = false;
		update_content_mutex.unlock();
	}
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

GameViewCMD::GameViewCMD() : BaseViewCMD() {
	this->updateContent();
}

void GameViewCMD::updateContent()
{
	update_content_mutex.lock();

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

	update_content_mutex.unlock();
}

void GameViewCMD::syncMatrix(TileBase* const(&matrix)[4][4])
{
	this->m_matrix = matrix;
}

void GameViewCMD::startMove(const std::vector<MoveInstruction*>& moveInstructions)
{
	BaseGameView::notify("started_move");
}

void GameViewCMD::startMerge(const std::vector<MergeInstruction*>& mergeInstructions)
{
	BaseGameView::notify("started_merging");
}

void GameViewCMD::startSpawn(const std::vector<SpawnInstruction*>& spawnInstructions)
{
	BaseGameView::notify("started_spawning");
}

void GameViewCMD::endSpawn()
{
	BaseGameView::notify("finished_spawning");
}

void GameViewCMD::updateMove(float dt)
{
	BaseGameView::notify("finished_move");
}

void GameViewCMD::updateSpawning(float dt)
{
	BaseGameView::notify("finished_spawning");
}

void GameViewCMD::render()
{
	this->initRenderer();

	this->updateContent();
	this->refreshScreen();
}

void GameViewCMD::updateScore(const int& score, const int& bestScore)
{
	this->score = score;
	this->bestScore = bestScore;
}
