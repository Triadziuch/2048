#include "LeaderboardModel.h"
#include "LeaderboardMode.h"
#include "src/model/GameModel.h"

void LeaderboardModel::initLeaderboard()
{
	
}

LeaderboardModel::LeaderboardModel() : BaseModel()
{
	this->score = 0;
	this->mode = LeaderboardMode::VIEW;

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

	//this->initLeaderboard();
}

LeaderboardModel::~LeaderboardModel()
{
	for (auto& entry : v_leaderboard)
		delete entry;
	v_leaderboard.clear();
}

void LeaderboardModel::updateLeaderboard(LeaderboardEntry new_entry)
{
	for (size_t i = 0; i < v_leaderboard.size(); ++i) 
		if (v_leaderboard[i]->score < new_entry.score) {
			v_leaderboard.insert(v_leaderboard.begin() + i, new LeaderboardEntry(new_entry));
			return;
		}
}

const int& LeaderboardModel::getBestScore() const
{
	if (!v_leaderboard.empty())
		return v_leaderboard.front()->score;
	return 0;
}

void LeaderboardModel::setMode(LeaderboardMode mode)
{
	this->mode = mode;
}

const LeaderboardMode LeaderboardModel::getMode() const
{
	return this->mode;
}

const int LeaderboardModel::getScore() const
{
	return this->score;
}

std::vector<LeaderboardEntry*>& LeaderboardModel::getLeaderboardEntries()
{
	return v_leaderboard;
}

void LeaderboardModel::setScore(int score)
{
	this->score = score;
}

void LeaderboardModel::adjustMode()
{
	if (this->v_leaderboard.size() >= 8)
		if (this->score >= this->v_leaderboard[8]->score)
			this->mode = LeaderboardMode::EDIT;
		else
			this->mode = LeaderboardMode::VIEW;
}
