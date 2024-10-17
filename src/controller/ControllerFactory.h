#pragma once

#include "IControllerFactory.h"

template <typename Controller>
class ControllerFactory : public IControllerFactory {
public:
    virtual std::shared_ptr<IBaseController> build(std::shared_ptr<ModelHandler> modelHandler, std::shared_ptr<ViewHandler> viewHandler) override {
        std::shared_ptr<Controller> controller(new Controller());
        controller->setModelHandler(modelHandler);
        controller->setViewHandler(viewHandler);
        return (controller);
    }

};