#include "EventObserver.h"

void EventObserver::printDebug(const std::string& info)
{
    if (isDebug)
        std::cout << info << std::endl;
}

void EventObserver::disconnect(ListenerConnection id) {
    Observator::unregisterObserver(id);
}

void EventObserver::notifyAll() {
    Observator::notifyAllObserver();
}

void EventObserver::notify(const std::string &event) {
    Observator::notifyObserver(event);
}

void EventObserver::notify() {
    Observator::notifyObserver("");
}