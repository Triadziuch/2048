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

	this->name_input_container |= ftxui::CatchEvent([&](Event event) {
		return event.is_character() && this->name.size() > 12;
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
				ftxui::filler(),
				text("L  E  A  D  E  R  B  O  A  R  D") | bold | hcenter | size(HEIGHT, EQUAL, 1) | ftxui::borderDouble | ftxui::blink,
				ftxui::filler(),
				this->table_element,
				ftxui::filler(),
				this->mode == LeaderboardMode::EDIT ?
					text("") | size(HEIGHT, EQUAL, 1)
				  : text("Press any key to continue...") | bold | hcenter | color(ftxui::Color::GrayDark) | size(HEIGHT, EQUAL, 1),

				ftxui::filler(),
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

void LeaderboardViewCMD::updateTableElement()
{
	update_content_mutex.lock();

	values.clear();
	values.push_back({ { "   Rank   ", "       Nickname       ", "    Score    ", "    Date    " } });

	int place = 1;
	for (const auto& entry : *v_leaderboardEntries) {
		if (place != 1)
			values.push_back({ {"", "", "", ""} });
		values.push_back({ {std::to_string(place++), entry->name, std::to_string(entry->score), entry->date} });

		if (place == 11)
			break;
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
	content.DecorateCellsAlternateRow(color(Color::Blue), 4, 1);
	content.DecorateCellsAlternateRow(color(Color::Cyan), 4, 3);

	this->table_element = table->Render();

	update_content_mutex.unlock();

	this->updateContent();
}

LeaderboardViewCMD::LeaderboardViewCMD() : BaseViewCMD()
{
	this->registerObserver("update_game", [&]() {
		printDebug("[LeaderboardView] Self Observer \"update_game\" triggered.");
		return (false);
		});

	this->input_option_enter.on_enter = [&] {
		this->mode = LeaderboardMode::VIEW;
		};
}

void LeaderboardViewCMD::initRenderer()
{
	if (this->mode == LeaderboardMode::EDIT) {
		this->renderFTXUI();
		this->isRefreshing = true;
		this->notify("entered_name");
		this->name = "";
		this->name_input.reset();
		std::this_thread::sleep_for(std::chrono::milliseconds(32));
	}
	else {
		this->isRefreshing = true;
		if (this->screen == nullptr)
			ftxui_thread = new std::thread([this]() {
			this->renderFTXUI();
				});
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
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

void LeaderboardViewCMD::render()
{
	this->initRenderer();
}