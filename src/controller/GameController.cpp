#include <string>
#include "../model/GameModel.h"
#include "../view/GameViewTwo.h"
#include "GameController.h"

GameController::~GameController() {
}

GameController::GameController() {

}

void GameController::setModelHandler(std::shared_ptr<ModelHandler> modelHandler) {
	this->_modelHandler = modelHandler;
	this->_gameModel = this->_modelHandler->getModel<GameModel>("game");
	this->_gameModel->connect([&] () {
            std::cout << "[GameController] GameModel has been updated." << std::endl;
            std::cout << "[GameController] GameModel id: " << this->_gameModel->getId() << std::endl;
            std::cout << "[GameController] GameModel name: " << this->_gameModel->getName() << std::endl;
            std::cout << std::endl;
		return false;
	});
}

void GameController::setViewHandler(std::shared_ptr<ViewHandler> viewHandler) {
	this->_viewHandler = viewHandler;
	this->_gameModel->connect([&] () {
		std::cout << "[GameController]	GameModel has been updated" << std::endl;
		std::cout << "[GameController]	Updating the GameViewTwo" << std::endl;
		std::cout << std::endl;
		this->_viewHandler->getView<GameViewTwo>("game_2")->notify("update_game");
		return (false);
	});

	this->_gameView = this->_viewHandler->getView<GameView>("game_1");
	this->_gameView->connect("form_submit", [&] () {
		std::cout << "[GameController] Game 1 View Form has been submit." << std::endl;
		const auto &form = this->_gameView->getForm();
		std::cout << "[GameController] Game Form name: " << form.name << std::endl;
		std::cout << "[GameController] Game Form age: " << std::to_string(form.age) << std::endl;
		std::cout << std::endl;
		this->_gameModel->setName(form.name);
		this->_gameModel->setId(std::to_string(form.age)); // yes id != age, but it's just an example !
        return (false);
    });
}