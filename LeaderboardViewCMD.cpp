#include "LeaderboardViewCMD.h"

using namespace ftxui;

void LeaderboardViewCMD::renderFTXUI()
{
	ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
	this->screen = &screen;

	this->loop = new Loop(&screen, renderer);
	exit_loop = screen.ExitLoopClosure();

	std::unique_lock<std::mutex> lock(mtx);

	while (isRefreshing) {
		if (enteringName) {
			while (enteringName)
				loop->RunOnce();
			//loop->Run();

			{
				std::lock_guard<std::mutex> lock(mtx_name_entered);
				this->nameentered = true;
			}

			cv_name_entered.notify_one();
		}
		else {
			update_grid_mutex.lock();
			loop->RunOnce();
			this->needRefreshing = false;
			update_grid_mutex.unlock();
		}


		cv.wait(lock, [this] { return needRefreshing; });
	}

	//ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
	//this->screen = &screen;

	//this->loop = new Loop(&screen, renderer);
	////exit_loop = screen.ExitLoopClosure();

	//std::unique_lock<std::mutex> lock(mtx);

	//while (isRefreshing) {
	//	update_grid_mutex.lock();
	//	loop->RunOnce();
	//	this->needRefreshing = false;
	//	update_grid_mutex.unlock();

	//	cv.wait(lock, [this] { return needRefreshing; });
	//}

	delete this->loop;
	this->loop = nullptr;
}

void LeaderboardViewCMD::updateContent()
{
	this->update_grid_mutex.lock();

	this->input_add = Input(&name, this->input_option_enter);
	this->input_add |= CatchEvent([&](Event event) {
		return !this->enteringName;
		});

	this->container = ftxui::Container::Vertical({
		input_add,
		});

	renderer = ftxui::Renderer(this->container, [&] {
		return ftxui::hbox({
			ftxui::filler(),
			ftxui::vbox({}),
			ftxui::filler(),

			ftxui::vbox({}) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 14),
			ftxui::filler(),
			ftxui::vbox({}),

			ftxui::filler(),
			ftxui::vbox({
				this->table_element,
			}),
			ftxui::filler(),

			ftxui::vbox({}),
			ftxui::filler(),
			this->enteringName
				? ftxui::vbox({
					  ftxui::text("Your score") | ftxui::hcenter,
					  ftxui::text("254") | ftxui::hcenter,
					  container->Render(), // Renderowanie komponentu input_add
				  })
				  | ftxui::border
				  | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 14)
				  | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 5)
				: ftxui::vbox({})
				  | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 14)
				  | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 2),

			ftxui::filler(),
			ftxui::vbox({}),
			ftxui::filler(),
			});
		});

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

void LeaderboardViewCMD::enteredName()
{
	this->enteringName = false;
	//exit_loop();
	//this->screen->Exit();
}

void LeaderboardViewCMD::updateTableElement()
{
	update_grid_mutex.lock();

	if (this->table)
		delete this->table;

	using namespace ftxui;

	
	values.clear();
	values.push_back({ { "   Rank   ", "       Nickname       ", "    Score    ", "    Date    " } });

	int place = 1;
	for (const auto& entry : *v_leaderboardEntries) {
		values.push_back({ {"", "", "", ""} });
		values.push_back({ {std::to_string(place++), entry->name, std::to_string(entry->score), entry->date} });
		values.push_back({ {"", "", "", ""} });
	}


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

	update_grid_mutex.unlock();
}

LeaderboardViewCMD::LeaderboardViewCMD()
{
	this->registerObserver("update_game", [&]() {
		printDebug("[LeaderboardView] Self Observer \"update_game\" triggered.");
		return (false);
		});

	this->input_option_enter.on_enter = [&] {
		this->enteredName();
		};

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
	this->updateContent();
}

void LeaderboardViewCMD::enterName(int score)
{
	this->score = score;
	this->enteringName = true;
	this->isRefreshing = true;

	this->updateTableElement();
	this->updateContent();

	this->refreshScreen();
	std::unique_lock<std::mutex> lock(mtx_name_entered);
	cv_name_entered.wait(lock, [this] { return nameentered; });
	this->nameentered = false;
	this->name = "";
	// Tutaj zrób czekanie a¿ wywo³any zostanie warunek enteredName

	this->updateTableElement();
	this->updateContent();

	this->refreshScreen();

	//this->deleteRenderer();
}

sf::RenderWindow* LeaderboardViewCMD::getWindow()
{
	return nullptr;
}

void LeaderboardViewCMD::render()
{
	this->initRenderer();
}
