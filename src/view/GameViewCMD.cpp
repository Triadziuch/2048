#include <iostream>
#include "GameViewCMD.h"

using namespace ftxui;

// = = = = = Private functions  = = = = = //
Component GameViewCMD::initGrid()
{
	std::vector<Component> rows;

	if (isDesaturated == false) {
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
	}
	else {
		for (int row = 0; row < gridSize; ++row) {
			std::vector<Component> cols;
			for (int col = 0; col < gridSize; ++col) {
				auto cell_content = Renderer([&, row, col] {
					return vbox({
						text(" ") | bgcolor(getCellColorDesaturated(col, row)),
						text(" ") | bgcolor(getCellColorDesaturated(col, row)),
						text(displayCell(col, row)) | bold | bgcolor(getCellColorDesaturated(col, row)),
						text(" ") | bgcolor(getCellColorDesaturated(col, row)),
						text(" ") | bgcolor(getCellColorDesaturated(col, row)),
						}) | borderStyled(ftxui::LIGHT, Color::White) | size(WIDTH, EQUAL, cellSize + 4) | size(HEIGHT, EQUAL, cellSize);
					});
				cols.push_back(cell_content);
			}
			rows.push_back(Container::Horizontal(cols));
		}
	}

	return Container::Vertical(rows);
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
		else if (value == 1024 || value == 2048)
			return Color(52, 152, 219);
		else if (value == 4096 || value == 8192)
			return Color(52, 73, 94);
	}

	return Color::Black;
}

ftxui::Color GameViewCMD::getCellColorDesaturated(int row, int col) const
{
	if (m_matrix == nullptr)
		return Color::Black;

	if (m_matrix[row][col]) {
		int value = *m_matrix[row][col];

		if (value == 2)
			return Color(119, 125, 125);
		else if (value == 4 || value == 8)
			return Color(173, 116, 110);
		else if (value == 16 || value == 32 || value == 64)
			return Color(173, 134, 99);
		else if (value == 128 || value == 256 || value == 512)
			return Color(126, 102, 137);
		else if (value == 1024 || value == 2048)
			return Color(102, 140, 164);
		else
			return Color(55, 63, 71);
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



// = = = = = FTXUI Rendering functions  = = = = = //
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

void GameViewCMD::updateContent()
{
	update_content_mutex.lock();

	grid_component = initGrid();
	renderer = Renderer(grid_component, [&] {
		return
			hbox({
				filler(),
				vbox({
					hbox({
						filler(),
							vbox({

								filler(),
								vbox({
									text("How to play:") | hcenter,
									text(""),
									paragraphAlignJustify("Use your arrow keys to move the tiles. When two tiles with the same number touch, they merge into one!"),
									}),
								filler(),
								text(""),
								text(""),
								text(""),
								text(""),
								text(""),
								filler(),
								vbox({
									text("Controls:") | hcenter | bold,
									text(""),
									hbox({
										text("Arrows") | bold,
										text(" - Move board") | hcenter
									}),
									hbox({
										text("L") | bold,
										text(" - Show leaderboard") | hcenter
									}),
									/*hbox({
										text("C") | bold,
										text(" - Switch to graphic mode") | hcenter
									}),*/
									hbox({
										text("R") | bold,
										text(" - Reset game") | hcenter
									}),
									hbox({
										text("ESC") | bold,
										text(" - Quit Game") | hcenter
									}),
								}) | hcenter,
								filler(),


							}) | hcenter | vcenter | bold | size(WIDTH, EQUAL, 30),
						filler(),


					}) | hcenter | size(WIDTH, EQUAL, 35) | size(HEIGHT, EQUAL, 40),

				}) /*| border*/ | hcenter,
				filler(),

				vbox({
					text("2048 Game") | bold | hcenter,
					separator(),
					grid_component->Render() | hcenter
				}),

				filler(),
				vbox({
					hbox({
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
					}) | size(HEIGHT, EQUAL, 4),

					filler(),

					this->isGameOver == true ?
					vbox({
						text("G A M E   O V E R") | hcenter | bold,
						text(""),
						text("Press return key to continue...") | bold | blink | hcenter,
					}) | size(WIDTH, EQUAL, 35) | size(HEIGHT, EQUAL, 3)
					:
					vbox({
					}) | size(WIDTH, EQUAL, 35) | size(HEIGHT, EQUAL, 3),

					filler(),

					vbox({

					}) | size(HEIGHT, EQUAL, 4),
				}) /*| border*/,

				filler(),
				});
		});

	update_content_mutex.unlock();
}


// = = = = = Constructors / Destructors  = = = = = //
GameViewCMD::GameViewCMD() : BaseViewCMD() 
{
	this->updateContent();
}

GameViewCMD::~GameViewCMD()
{
	this->deleteRenderer();
}


// = = = = = Inherited public functions  = = = = = //
void GameViewCMD::render()
{
	this->initRenderer();
	this->updateContent();
	std::this_thread::sleep_for(std::chrono::milliseconds(4));
	this->refreshScreen();
}

void GameViewCMD::reset()
{
	this->m_timeGameOver = 0.f;
	this->m_gameOverCycle = 0;
	this->isDesaturated = false;
	this->isGameOver = false;
	this->isGameOverAnimation = false;
}

// = = = = = Game view functions  = = = = = //
void GameViewCMD::syncMatrix(TileBase* const(&matrix)[4][4])
{
	this->m_matrix = matrix;
}

void GameViewCMD::startMove(const std::vector<MoveInstruction*>& moveInstructions) { BaseGameView::notify("started_move"); }

void GameViewCMD::startMerge(const std::vector<MergeInstruction*>& mergeInstructions) { BaseGameView::notify("started_merging"); }

void GameViewCMD::startSpawn(const std::vector<SpawnInstruction*>& spawnInstructions) { BaseGameView::notify("started_spawning"); }

void GameViewCMD::startGameOver()
{
	this->isGameOver = true;
	this->isGameOverAnimation = true;
}

void GameViewCMD::endSpawn() { BaseGameView::notify("finished_spawning"); }

void GameViewCMD::endGameOver()
{
	this->startGameOver();
	while (isGameOverAnimation)
		this->updateGameOver(10.f);
	this->refreshScreen();
}


// = = = = = Update functions  = = = = = //
sf::Event* GameViewCMD::update(float dt)
{
	return nullptr;
}

void GameViewCMD::updateMove(float dt) { BaseGameView::notify("finished_move"); }

void GameViewCMD::updateSpawn(float dt) { BaseGameView::notify("finished_spawning"); }

void GameViewCMD::updateGameOver(float dt)
{
	if (isGameOver && isGameOverAnimation) {
		m_timeGameOver += dt;

		if (m_timeGameOver > m_timeGameOverCycleMax) {
			m_gameOverCycle++;
			m_timeGameOver = 0.f;
			this->isDesaturated = !this->isDesaturated;
		}

		if (m_gameOverCycle >= m_gameOverCyclesMax)
			this->isGameOverAnimation = false;
	}	
}

void GameViewCMD::updateScore(const int& score, const int& bestScore)
{
	this->score = score;
	this->bestScore = bestScore;
}
