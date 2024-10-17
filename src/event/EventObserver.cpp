#include "EventObserver.h"

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