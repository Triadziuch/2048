#include "ViewHandler.h"
#include "GameViewGraphic.h"
#include "GameViewCMD.h"

ViewHandler::ViewHandler() {
    this->_data = {
            {"game_graphic", std::shared_ptr<BaseView>(new GameViewGraphic())},
            {"game_cmd", std::shared_ptr<BaseView>(new GameViewCMD())}
    };
}