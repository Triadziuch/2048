#pragma once
#include "src/model/BaseModel.h"
#include <fstream>
#include <sstream>

struct LeaderboardEntry {
	std::string name{};
	int score{};
	std::string date{};
};

class LeaderboardModel : public BaseModel {
private:
	const std::string leaderboard_file_path{ "assets/leaderboard.txt" };
	std::vector<LeaderboardEntry*> v_leaderboard{};

	void initLeaderboard();

public:
	LeaderboardModel();
	~LeaderboardModel();

	const int& getBestScore() const;
};