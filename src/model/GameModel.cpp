#include <string>
#include "GameModel.h"

const std::string& GameModel::getName() const {
	return this->_name;
}

void GameModel::setName(const std::string& name) {
	this->_name = name;
    this->notify();
}

const std::string& GameModel::getId() const {
	return _id;
}

void GameModel::setId(const std::string &id) {
	this->_id = id;
    this->notify("event");
}

GameModel::GameModel() : BaseModel() {
	this->_id = "Default Id";
	this->_name = "Default Name";
}