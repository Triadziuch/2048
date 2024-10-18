//#include "Game.h"
#include <memory>
#include "controller/GameController.h"
#include "view/GameViewTwo.h"
#include "controller/ControllerHandler.h"


int main() {
	//Game game;
	//game.run();

	std::shared_ptr<ModelHandler> modelHandler(new ModelHandler());
	std::shared_ptr<ViewHandler> viewHandler(new ViewHandler());
	ControllerHandler controllerHandler(modelHandler, viewHandler);

	std::shared_ptr<GameView> view = viewHandler->getView<GameView>("game_1");
	auto gameModel = modelHandler->getModel<GameModel>("game");
	

	return 0;
}