#pragma once

#include <string>
#include <functional>
#include <list>
#include "BaseModel.h"

class GameModel : public BaseModel {
private:
    std::string _id;
    std::string _name;

public:
    GameModel();

    const std::string &getName() const;
    void setName(const std::string &name);
    const std::string &getId() const;
    void setId(const std::string &id);
};