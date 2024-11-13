#include "ViewHandler.h"
#include "GameViewCMD.h"
#include "../LeaderboardViewCMD.h"

ViewHandler::ViewHandler() {
    this->_data = {
            {"game_cmd", std::shared_ptr<CoreView>(new GameViewCMD())},
            {"leaderboard_cmd", std::shared_ptr<CoreView>(new LeaderboardViewCMD())}
    };
}