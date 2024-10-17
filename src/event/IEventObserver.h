#pragma once

#include <string>
#include "../pattern/Observator.hpp"

class IEventObserver {
public:
    virtual ~IEventObserver() {}

    // todo force implementation
    /*template<typename Observer>
    virtual Observator::ListenerConnection connect(const std::string &event, Observer &&observer) = 0;
    template<typename Observer>
    virtual Observator::ListenerConnection connect(Observer &&observer) = 0;*/

    virtual void disconnect(ListenerConnection id) = 0;
    virtual void notify() = 0;
    virtual void notifyAll() = 0;
    virtual void notify(const std::string &event) = 0;
};