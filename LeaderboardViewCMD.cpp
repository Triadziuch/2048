#include "LeaderboardViewCMD.h"

using namespace ftxui;

void LeaderboardViewCMD::renderFTXUI()
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

void LeaderboardViewCMD::updateContent()
{
	update_grid_mutex.lock();

	// Tworzymy nag³ówek tabeli
	auto header = hbox({
		text("Miejsce") | bold | border,
		separator() | color(Color::White),
		text("Nazwa") | bold | border,
		separator() | color(Color::White),
		text("Wynik") | bold | border,
		separator() | color(Color::White),
		text("Data") | bold | border
		});

	// Tworzymy zawartoœæ tabeli
	std::vector<Element> rows;
	rows.push_back(header);

	// Dodajemy wpisy z leaderboard
	int rank = 1;
	for (const auto& entry : *v_leaderboardEntries) {
		auto row = hbox({
			text(std::to_string(rank++)) | border,
			separator() | color(Color::White),
			text(entry->name) | border,
			separator() | color(Color::White),
			text(std::to_string(entry->score)) | border,
			separator() | color(Color::White),
			text(entry->date) | border
			});
		rows.push_back(row);
	}

	// Tworzymy tabelê jako komponent
	auto leaderboard_table = Renderer([rows] {
		return vbox(std::move(rows)) | border;
		});

	this->renderer = leaderboard_table;
	update_grid_mutex.unlock();
}

void LeaderboardViewCMD::refreshScreen()
{
	{
		std::lock_guard<std::mutex> lock(mtx);
		needRefreshing = true;
	}
	cv.notify_one();
}

LeaderboardViewCMD::LeaderboardViewCMD()
{
	this->registerObserver("update_game", [&]() {
		printDebug("[LeaderboardView] Self Observer \"update_game\" triggered.");
		return (false);
		});
}

const std::string& LeaderboardViewCMD::getViewPath() const
{
	return ("");
}

void LeaderboardViewCMD::openWindow()
{
	HWND window = GetConsoleWindow();

	if (window)
		consoleWindow = window;
	else if (AllocConsole()) {
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

		RECT consoleRect;
		GetWindowRect(consoleWindow, &consoleRect);

		RECT screenRect;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &screenRect, 0);

		int screenWidth = screenRect.right - screenRect.left;
		int screenHeight = screenRect.bottom - screenRect.top;

		int consoleWidth = consoleRect.right - consoleRect.left;
		int consoleHeight = consoleRect.bottom - consoleRect.top;

		int posX = (screenWidth - consoleWidth) / 2 + screenRect.left;
		int posY = (screenHeight - consoleHeight) / 2 + screenRect.top;

		MoveWindow(consoleWindow, posX, posY, consoleWidth, consoleHeight, TRUE);
	}

	this->isRefreshing = true;
}

void LeaderboardViewCMD::closeWindow()
{
	this->deleteRenderer();

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

void LeaderboardViewCMD::initRenderer()
{
	this->isRefreshing = true;
	if (this->screen == nullptr)
		ftxui_thread = new std::thread([this]() {
		this->renderFTXUI();
			});
	this->isRefreshing = true;
}

void LeaderboardViewCMD::deleteRenderer()
{
	this->isRefreshing = false;
	this->refreshScreen();

	if (ftxui_thread->joinable())
		ftxui_thread->join();

	delete ftxui_thread;
	ftxui_thread = nullptr;
	this->screen = nullptr;
}

void LeaderboardViewCMD::setLeaderboardEntries(std::vector<LeaderboardEntry*>& v_leaderboardEntries)
{
	this->v_leaderboardEntries = &v_leaderboardEntries;
	this->updateContent();
}

sf::RenderWindow* LeaderboardViewCMD::getWindow()
{
	return nullptr;
}

void LeaderboardViewCMD::render()
{
	this->initRenderer();
}
