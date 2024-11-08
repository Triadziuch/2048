#include "ModelHandler.h"
#include "GameModel.h"
#include "../LeaderboardModel.h"

ModelHandler::ModelHandler() {
    this->_data.insert({ "leaderboard", std::shared_ptr<BaseModel>(new LeaderboardModel()) });
    this->_data.insert({"game", std::shared_ptr<BaseModel>(new GameModel(this->getModel<LeaderboardModel>("leaderboard")))});
}