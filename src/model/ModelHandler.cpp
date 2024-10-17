#include "GameModel.h"
#include "ModelHandler.h"

ModelHandler::ModelHandler() {
    this->_data.insert({"game", std::shared_ptr<BaseModel>(new GameModel())});
}