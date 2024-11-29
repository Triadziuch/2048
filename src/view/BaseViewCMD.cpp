#include "BaseViewCMD.h"

void BaseViewCMD::disableResize()
{
	HWND hwnd = GetConsoleWindow();
	LONG style = GetWindowLong(hwnd, GWL_STYLE);
	style &= ~WS_SIZEBOX;
	SetWindowLong(hwnd, GWL_STYLE, style);

	RECT r;
	GetWindowRect(hwnd, &r);
	MoveWindow(hwnd, r.left, r.top, r.right - r.left, r.bottom - r.top, TRUE);
}

// = = = = = Private functions = = = = = //
void BaseViewCMD::refreshScreen()
{
	if (this->screen != nullptr)
		this->screen->PostEvent(ftxui::Event::Custom);

	{
		std::lock_guard<std::mutex> lock(mtx);
		needRefreshing = true;
	}
	cv.notify_one();
}



// = = = = = Constructors / Destructors = = = = = //
BaseViewCMD::BaseViewCMD() : BaseView() {}



// = = = = = BaseView member functions = = = = = //
void BaseViewCMD::openWindow()
{
	HWND window = GetConsoleWindow();
	if (window != nullptr) {
		this->consoleWindow = window;

		if (freopen_s(&m_stdout, "CONOUT$", "w", stdout) != 0)
			printDebug("Nie mozna przekierowac stdout.");
		if (freopen_s(&m_stderr, "CONOUT$", "w", stderr) != 0)
			printDebug("Nie mo¿na przekierowaæ stderr.");
		if (freopen_s(&m_stdin, "CONIN$", "r", stdin) != 0)
			printDebug("Nie mo¿na przekierowaæ stdin.");
	}
	else {
		if (AllocConsole()) {
			this->consoleWindow = GetConsoleWindow();

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

	this->disableResize();
	this->isRefreshing = true;
}

void BaseViewCMD::closeWindow()
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

	std::this_thread::sleep_for(std::chrono::milliseconds(16));
	HWND hWnd = GetConsoleWindow();
	if (hWnd) {
		FreeConsole();
		SendMessage(hWnd, WM_CLOSE, 0, 0);
	}
}

void BaseViewCMD::initRenderer()
{
	this->isRefreshing = true;
	if (this->screen == nullptr)
		ftxui_thread = new std::thread([this]() {
		this->renderFTXUI();
			});
}

void BaseViewCMD::deleteRenderer()
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

sf::RenderWindow* BaseViewCMD::getWindow()
{
	return nullptr;
}

void BaseViewCMD::render()
{
	this->initRenderer();
}
