#include "ViewHandler.h"
#include "GameView.h"
#include "GameViewTwo.h"

ViewHandler::ViewHandler() {
    this->_data = {
            {"game_1", std::shared_ptr<BaseView>(new GameView())},
            {"game_2", std::shared_ptr<BaseView>(new GameViewTwo())}
    };
}