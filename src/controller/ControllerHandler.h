#pragma once 

#include <unordered_map>
#include "IBaseController.h"
#include "IControllerFactory.h"
#include "../DataHandler.hpp"

class ControllerHandler : public DataHandler<std::string, std::shared_ptr<IControllerFactory>> {
private:
    std::string _curBaseRoute;
    std::string _curSubRoute;
    std::shared_ptr<IBaseController> _currentController;
    std::shared_ptr<ModelHandler> _modelHandler;
    std::shared_ptr<ViewHandler> _viewHandler;

    std::shared_ptr<IControllerFactory> getRouteControllerFactory(const std::string &route);

public:
    ControllerHandler() = delete;
    explicit ControllerHandler(std::shared_ptr<ModelHandler> modelHandler, std::shared_ptr<ViewHandler> viewHandler);
    void changeRoute(const std::string &route, const std::string &subRoute);
};