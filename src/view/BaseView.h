#pragma once

#include "../event/EventObserver.h"

class BaseView : public EventObserver {
public:
    virtual const std::string &getViewPath() const = 0;
};