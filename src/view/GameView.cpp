#include <iostream>
#include "GameView.h"

GameView::GameView() {

}

void GameView::onFormSubmit() {
    this->_form.age = 1337;
    this->_form.name = "Leet";
    std::cout << "[GameView] form has been submitted." << std::endl;
    this->notify("form_submit");
}

const std::string & GameView::getViewPath() const {
    return ("game.html");
}

const StudentForm & GameView::getForm() const {
    return (this->_form);
}

StudentForm::StudentForm() {
    this->name = "No Name";
    this->age = -1;
}