#pragma once
#include "BaseModel.h"
#include <string>
#include <fstream>
#include <sstream>

class GameModel;
struct LeaderboardEntry;
enum class LeaderboardMode;

class LeaderboardModel : public BaseModel {
private:
	const std::string leaderboard_file_path{ "assets/leaderboard.txt" };
	std::vector<LeaderboardEntry*> v_leaderboard{};

	LeaderboardMode mode;
	int score;

	void initLeaderboard();
	void saveLeaderboard();

public:
	LeaderboardModel();
	~LeaderboardModel();

	void updateLeaderboard(LeaderboardEntry new_entry);
	const int& getBestScore() const;
	const LeaderboardMode getMode() const;
	const int getScore() const;

	void setMode(LeaderboardMode mode);
	void adjustMode();
	void setScore(int score);

	std::vector<LeaderboardEntry*>& getLeaderboardEntries();
	
};