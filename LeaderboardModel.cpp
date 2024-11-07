#include "LeaderboardModel.h"

void LeaderboardModel::initLeaderboard()
{
	std::ifstream leaderboard_file(this->leaderboard_file_path, std::ios::in);

	if (!leaderboard_file.is_open()) {
		std::cerr << "Nie udalo sie otworzyc pliku \"" << leaderboard_file_path << '\"' << std::endl;
		return;
	}

	std::string entry_string;
	while (std::getline(leaderboard_file, entry_string)) {
		LeaderboardEntry* entry = new LeaderboardEntry();

		std::stringstream ss(entry_string);
		std::getline(ss, entry->name, ';');
		ss >> entry->score;
		ss.ignore(1, ';');
		std::getline(ss, entry->date, ';');

		v_leaderboard.emplace_back(entry);
	}

	leaderboard_file.close();
}

LeaderboardModel::LeaderboardModel()
{
	this->initLeaderboard();
}

LeaderboardModel::~LeaderboardModel()
{
	for (auto& entry : v_leaderboard)
		delete entry;
	v_leaderboard.clear();
}

const int& LeaderboardModel::getBestScore() const
{
	if (!v_leaderboard.empty())
		return v_leaderboard.front()->score;
	return 0;
}
