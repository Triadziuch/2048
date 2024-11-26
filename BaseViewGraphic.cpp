#include "BaseViewGraphic.h"

sf::RenderWindow* BaseViewGraphic::window = nullptr;
sf::StandardCursor::TYPE BaseViewGraphic::cursor_type = sf::StandardCursor::TYPE::NORMAL;

// = = = = = Initialization functions = = = = = //
void BaseViewGraphic::initVariables()
{
	this->m_movementManager = new MovementManager();
	this->m_movementContainer = MovementContainer::getInstance();
}



// = = = = = Constructors / Destructors = = = = = //
BaseViewGraphic::BaseViewGraphic() : BaseView()
{
	this->initVariables();
}


// = = = = = BaseView member functions = = = = = //
void BaseViewGraphic::openWindow()
{
	if (this->window != nullptr)
		return;

	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);

	sf::Image icon;
	icon.loadFromFile("assets/Textures/appicon.png");
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void BaseViewGraphic::closeWindow()
{
	if (this->window) {
		this->window->close();
		delete this->window;
		this->window = nullptr;
	}
}

void BaseViewGraphic::initRenderer() {}

void BaseViewGraphic::deleteRenderer() {}

sf::RenderWindow* BaseViewGraphic::getWindow()
{
	return this->window;
}