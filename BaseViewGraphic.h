#pragma once
#include "src/view/BaseView.h"
#include "SFML/Graphics.hpp"

class BaseViewGraphic : public virtual BaseView
{
public:
    void openWindow() override { /* Implementacja graficzna */ }
    void closeWindow() override { /* Implementacja graficzna */ }
    void initRenderer() override { /* Implementacja graficzna */ }
    void deleteRenderer() override { /* Implementacja graficzna */ }
    sf::RenderWindow* getWindow() override { return &window; }
    void render() override { /* Implementacja graficzna */ }
    
protected:
    sf::RenderWindow window;
};

