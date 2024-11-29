#pragma once
#include <string>
#include "../pattern/Observator.hpp"

class IEventObserver {
public:
    virtual ~IEventObserver() {}

    virtual void disconnect(ListenerConnection id) = 0;
    virtual void notify() = 0;
    virtual void notifyAll() = 0;
    virtual void notify(const std::string &event) = 0;
};