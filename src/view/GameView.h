#pragma once

#include "../model/GameModel.h"
#include "BaseView.h"

class StudentForm {
public:
	std::string name;
	int age;

public:
	StudentForm();
};

class GameView : public BaseView {
private:
	StudentForm _form;
public:
	GameView();
    const std::string &getViewPath() const override;
    void onFormSubmit();
	const StudentForm &getForm() const;
};