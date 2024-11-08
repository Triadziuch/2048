#pragma once
#include "src/model/BaseModel.h"  // Za³ó¿my, ¿e BaseModel jest klas¹ bazow¹
#include <string>
#include <fstream>
#include <sstream>

class GameModel;
struct LeaderboardEntry;
enum class LeaderboardMode;

struct LeaderboardEntry {
	std::string name{};
	int score{};
	std::string date{};
};

class LeaderboardModel : public BaseModel {
private:
	const std::string leaderboard_file_path{ "assets/leaderboard.txt" };
	std::vector<LeaderboardEntry*> v_leaderboard{};

	LeaderboardMode mode;
	int score;

	void initLeaderboard();

public:
	LeaderboardModel();
	~LeaderboardModel();

	void updateLeaderboard(LeaderboardEntry new_entry);
	const int& getBestScore() const;
	void setMode(LeaderboardMode mode);
	const LeaderboardMode getMode() const;
	const int getScore() const;

	std::vector<LeaderboardEntry*>& getLeaderboardEntries();
	
};