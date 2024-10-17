#pragma once

#include "../model/GameModel.h"
#include "BaseView.h"

class GameViewTwo : public BaseView {
public:
	GameViewTwo();

	void addGame(GameModel &gameModel);
    const std::string &getViewPath() const override;
};