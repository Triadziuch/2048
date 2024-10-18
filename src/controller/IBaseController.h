#pragma once 

#include <unordered_map>
#include <vector>
#include <string>
#include "../model/ModelHandler.h"
#include "../view/ViewHandler.h"

class IBaseController {
public:
    virtual ~IBaseController() {}
    IBaseController() {}
    IBaseController(const IBaseController &) {}
    IBaseController & operator = (const IBaseController &) {return (*this);}
    virtual const std::string run() = 0;
    virtual void setModelHandler(std::shared_ptr<ModelHandler> modelHandler) = 0;
    virtual void setViewHandler(std::shared_ptr<ViewHandler> viewHandler) = 0;
};