#pragma once

#include <string>
#include "../model/GameModel.h"
#include "../view/GameView.h"
#include "../view/ViewHandler.h"
#include "IBaseController.h"

class GameController : public IBaseController {
private:
	std::shared_ptr<ModelHandler> _modelHandler;
	std::shared_ptr<ViewHandler> _viewHandler;
	std::shared_ptr<GameModel> _gameModel;
	std::shared_ptr<GameView> _gameView;

public:
	GameController();
	virtual ~GameController();

	void setModelHandler(std::shared_ptr<ModelHandler> modelHandler) override;
	void setViewHandler(std::shared_ptr<ViewHandler> viewHandler) override;
};