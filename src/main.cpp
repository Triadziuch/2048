//#include "Game.h"
#include <memory>
#include "controller/GameController.h"
#include "view/GameViewCMD.h"
#include "controller/ControllerHandler.h"


int main() {
	//Game game;
	//game.run();

	std::shared_ptr<ModelHandler> modelHandler(new ModelHandler());
	std::shared_ptr<ViewHandler> viewHandler(new ViewHandler());
	ControllerHandler controllerHandler(modelHandler, viewHandler);

	return 0;
}