#include "LeaderboardViewCMD.h"

using namespace ftxui;

void LeaderboardViewCMD::renderFTXUI()
{
	if (this->mode == LeaderboardMode::EDIT) {
		ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
		Loop loop(&screen, renderer);

		while (this->mode == LeaderboardMode::EDIT)
			loop.RunOnce();
	}
	else {
		ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
		this->screen = &screen;

		Loop loop{ &screen, renderer };

		std::unique_lock<std::mutex> lock(mtx);

		while (isRefreshing) {
			update_content_mutex.lock();
			loop.RunOnce();
			this->needRefreshing = false;
			update_content_mutex.unlock();

			cv.wait(lock, [this] { return needRefreshing; });
		}
	}
}

void LeaderboardViewCMD::updateContent()
{
	this->update_content_mutex.lock();

	this->name_input = Input(&this->name, this->input_option_enter);

	this->name_input_container = ftxui::Container::Vertical({
		this->name_input,
		});

	renderer = ftxui::Renderer(this->name_input_container, [&] {
		return ftxui::hbox({
			ftxui::filler(),
			ftxui::vbox({}),
			ftxui::filler(),

			ftxui::vbox({}) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20),
			ftxui::filler(),
			ftxui::vbox({}),

			ftxui::filler(),
			ftxui::vbox({
				this->table_element,
			}),
			ftxui::filler(),

			ftxui::vbox({}),
			ftxui::filler(),
			this->mode == LeaderboardMode::EDIT
				? ftxui::vbox({
					ftxui::vbox({
						ftxui::text("Your score") | ftxui::hcenter,
						ftxui::text(std::to_string(this->score)) | ftxui::hcenter,
						}) | ftxui::border | ftxui::hcenter | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 4),
						ftxui::vbox({}) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 4),
					ftxui::vbox({
						ftxui::text("Type your name") | ftxui::hcenter,
						this->name_input_container->Render(),
								}) | ftxui::border | ftxui::hcenter | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 4),
								ftxui::filler(),

				  }) | ftxui::hcenter
				: ftxui::vbox({})
				  | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20)
				  | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 4),

			ftxui::filler(),
			ftxui::vbox({}),
			ftxui::filler(),
			});
		});

	update_content_mutex.unlock();
}

void LeaderboardViewCMD::refreshScreen()
{
	{
		std::lock_guard<std::mutex> lock(mtx);
		needRefreshing = true;
	}
	cv.notify_one();
}

void LeaderboardViewCMD::updateTableElement()
{
	update_content_mutex.lock();

	values.clear();
	values.push_back({ { "   Rank   ", "       Nickname       ", "    Score    ", "    Date    " } });

	int place = 1;
	for (const auto& entry : *v_leaderboardEntries) {
		values.push_back({ {"", "", "", ""} });
		values.push_back({ {std::to_string(place++), entry->name, std::to_string(entry->score), entry->date} });
		values.push_back({ {"", "", "", ""} });
	}

	if (this->table)
		delete this->table;
	this->table = new Table(values);

	table->SelectAll().Decorate(center);
	table->SelectAll().Decorate(bold);
	table->SelectAll().Border(LIGHT);

	table->SelectColumn(0).Border(LIGHT);

	table->SelectRow(0).Decorate(bold);
	table->SelectRow(0).Decorate(color(Color::Yellow));
	table->SelectRow(0).SeparatorVertical(LIGHT);
	table->SelectRow(0).Border(ftxui::DOUBLE);

	table->SelectRows(0, -1).SeparatorVertical(LIGHT);

	auto content = table->SelectRows(1, -1);
	content.DecorateCellsAlternateRow(color(Color::Blue), 2, 0);
	content.DecorateCellsAlternateRow(color(Color::Cyan), 2, 1);
	content.DecorateCellsAlternateRow(color(Color::White), 2, 2);

	this->table_element = table->Render();

	update_content_mutex.unlock();

	this->updateContent();
}

LeaderboardViewCMD::LeaderboardViewCMD()
{
	this->registerObserver("update_game", [&]() {
		printDebug("[LeaderboardView] Self Observer \"update_game\" triggered.");
		return (false);
		});

	this->input_option_enter.on_enter = [&] {
		this->mode = LeaderboardMode::VIEW;
		};

}

void LeaderboardViewCMD::openWindow()
{
	HWND consoleWindow = GetConsoleWindow();

	if (consoleWindow) {
		this->consoleWindow = consoleWindow;

		if (freopen_s(&m_stdout, "CONOUT$", "w", stdout) != 0)
			printDebug("Nie mozna przekierowac stdout.");
		if (freopen_s(&m_stderr, "CONOUT$", "w", stderr) != 0)
			printDebug("Nie mo¿na przekierowaæ stderr.");
		if (freopen_s(&m_stdin, "CONIN$", "r", stdin) != 0)
			printDebug("Nie mo¿na przekierowaæ stdin.");
	}
	else {
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
	if (this->mode == LeaderboardMode::EDIT) {
		this->renderFTXUI();
		this->isRefreshing = true;
		this->notify("entered_name");
		this->name = "";
		this->name_input.reset();
	}
	else {
		this->isRefreshing = true;
		if (this->screen == nullptr)
			ftxui_thread = new std::thread([this]() {
			this->renderFTXUI();
				});
	}
}

void LeaderboardViewCMD::deleteRenderer()
{
	if (this->ftxui_thread == nullptr)
		return;

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
	this->updateTableElement();
}

void LeaderboardViewCMD::setScore(int score)
{
	this->score = score;
	this->updateContent();
}

void LeaderboardViewCMD::setMode(LeaderboardMode mode)
{
	this->mode = mode;
	this->updateContent();
}

LeaderboardEntry LeaderboardViewCMD::getEntry()
{
	std::time_t t = std::time(nullptr);
	std::tm tm{};
	if (localtime_s(&tm, &t) != 0)
		throw std::runtime_error("Nie uda³o siê pobraæ lokalnej daty i czasu");
	std::ostringstream dateStream;
	dateStream << std::put_time(&tm, "%d.%m.%Y");

	return LeaderboardEntry{ this->name, this->score, dateStream.str() };
}

sf::RenderWindow* LeaderboardViewCMD::getWindow()
{
	return nullptr;
}

void LeaderboardViewCMD::render()
{
	this->initRenderer();
}