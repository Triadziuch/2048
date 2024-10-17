#pragma once

#include <unordered_map>
#include <memory>
#include "../DataHandler.hpp"
#include "BaseModel.h"

class ModelHandler : public DataHandler<std::string, std::shared_ptr<BaseModel>> {
public:
    ModelHandler();

    template<typename Model>
    std::shared_ptr<Model> getModel(const std::string &name) {

        auto pair = this->getData(name);
        if (pair.first) {
            return (std::dynamic_pointer_cast<Model>(pair.second));
        }
        return (std::shared_ptr<Model>(nullptr));
    }
};