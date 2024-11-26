#include "GameController.h"
#include "../../LeaderboardController.h"
#include "ControllerFactory.h"
#include "ControllerHandler.h"

std::shared_ptr<IControllerFactory> ControllerHandler::getRouteControllerFactory(const std::string &route) {
    auto pair = this->getData(route);
    if (pair.first) {
        return (pair.second);
    }
    return (nullptr);
}

void ControllerHandler::changeRoute(const std::string &baseRoute, const std::string &subRoute) {
    /*std::shared_ptr<IControllerFactory> pFactory = this->getRouteControllerFactory(baseRoute);
    if (pFactory == nullptr) {
        std::cerr << "invalid route: " << baseRoute << std::endl;
    }
    this->_currentController.reset();
    this->_currentController = nullptr;
    this->_curBaseRoute = baseRoute;
    this->_curSubRoute = subRoute;
    this->_currentController = pFactory->build(_modelHandler, _viewHandler);*/
    if (baseRoute == "-") {
        _currentController = _gameController;
    }
    else if (baseRoute == "leaderboard") {
        _currentController = _leaderboardController;
    }
    else {
        std::cerr << "invalid route: " << baseRoute << std::endl;
        return;
    }

    this->_curBaseRoute = baseRoute;
    this->_curSubRoute = subRoute;
}

ControllerHandler::ControllerHandler(std::shared_ptr<ModelHandler> modelHandler, std::shared_ptr<ViewHandler> viewHandler) {
    this->_modelHandler = modelHandler;
    this->_viewHandler = viewHandler;
    this->_currentController = nullptr;

    auto gameControllerFactory = std::make_shared<ControllerFactory<GameController>>();
    auto leaderboardControllerFactory = std::make_shared<ControllerFactory<LeaderboardController>>();

    this->_data = {
        {"-", gameControllerFactory},
        {"leaderboard", leaderboardControllerFactory}
    };

    this->_data = {
            {"-", std::shared_ptr<ControllerFactory<GameController>>(new ControllerFactory<GameController>())},
            {"leaderboard", std::shared_ptr<ControllerFactory<LeaderboardController>>(new ControllerFactory<LeaderboardController>())}
    };

    _gameController = gameControllerFactory->build(modelHandler, viewHandler);
    _leaderboardController = leaderboardControllerFactory->build(modelHandler, viewHandler);

    this->changeRoute("-", "Game");

    while (true) {
        ExitCode exitCode = this->_currentController->run();
        //system("cls");

        if (exitCode == ExitCode::GAME) {
            this->changeRoute("-", "Game");
        }
        else if (exitCode == ExitCode::LEADERBOARD) {
            this->changeRoute("leaderboard", "Leaderboard");
        }
        else if (exitCode == ExitCode::EXIT) {
            break;
        }
    }
}