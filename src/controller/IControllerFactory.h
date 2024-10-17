#pragma once

#include <memory>
#include "IBaseController.h"

class IControllerFactory {
public:
    virtual ~IControllerFactory() {}
    virtual std::shared_ptr<IBaseController> build(std::shared_ptr<ModelHandler> modelHandler, std::shared_ptr<ViewHandler> viewHandler) = 0;
};