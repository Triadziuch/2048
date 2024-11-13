#define WIN32_LEAN_AND_MEAN

#include <memory>
#include "controller/GameController.h"
#include "controller/ControllerHandler.h"

int main() {
	std::shared_ptr<ModelHandler> modelHandler(new ModelHandler());
	std::shared_ptr<ViewHandler> viewHandler(new ViewHandler());
	ControllerHandler controllerHandler(modelHandler, viewHandler);

	return 0;
}