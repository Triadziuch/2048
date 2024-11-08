#pragma once

#include "../CoreView.h"

class BaseView : public CoreView {
public:
	virtual void openWindow() = 0;
	virtual void closeWindow() = 0;
	virtual void initRenderer() = 0;
	virtual void deleteRenderer() = 0;

	// Accessors / Mutators
	virtual sf::RenderWindow* getWindow() = 0;

	// Render functions
	virtual void render() = 0;
};