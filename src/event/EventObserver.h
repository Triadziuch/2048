#pragma once
#include <string>
#include "IEventObserver.h"
#include "../pattern/Observator.hpp"

class EventObserver : public IEventObserver, protected Observator<std::string> {
protected:
    bool isDebug{ false };
    void printDebug(const std::string& info);

public:

    template<typename Observer>
    ListenerConnection connect(const std::string &event, Observer &&observer) {
        return (this->registerObserver(event, observer));
    }

    template<typename Observer>
    ListenerConnection connect(Observer &&observer) {
        return (this->registerObserver("", observer));
    }

    virtual void disconnect(ListenerConnection id) override;
    virtual void notifyAll() override;
    virtual void notify(const std::string &event) override;
    virtual void notify() override;
};