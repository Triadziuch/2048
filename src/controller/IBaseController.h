#pragma once 

#include <unordered_map>
#include <vector>
#include <string>
#include "../model/ModelHandler.h"
#include "../view/ViewHandler.h"
#include "../ExitCode.h"

class IBaseController {
protected:
    bool isDebug{ false };
    void printDebug(const std::string& info);

public:
    virtual ~IBaseController() {}
    IBaseController() {}
    IBaseController(const IBaseController &) {}
    IBaseController & operator = (const IBaseController &) {return (*this);}
    virtual const ExitCode run() = 0;
    virtual void setModelHandler(std::shared_ptr<ModelHandler> modelHandler) = 0;
    virtual void setViewHandler(std::shared_ptr<ViewHandler> viewHandler) = 0;
};