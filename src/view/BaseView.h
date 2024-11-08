#pragma once

#include "../event/EventObserver.h"
#include "../model/GameModel.h"

class BaseView : public EventObserver {
public:
    virtual const std::string &getViewPath() const = 0;
	virtual void openWindow() = 0;
	virtual void closeWindow() = 0;
	virtual void initRenderer() = 0;
	virtual void deleteRenderer() = 0;

	// Accessors / Mutators
	virtual sf::RenderWindow* getWindow() = 0;

	// Render functions
	virtual void render() = 0;
};