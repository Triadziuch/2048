#pragma once
#include "src/view/BaseView.h"
#include "SFML/Graphics.hpp"

class BaseViewCMD : public virtual BaseView
{
public:
    void openWindow() override { /* Implementacja CMD */ }
    void closeWindow() override { /* Implementacja CMD */ }
    void initRenderer() override { /* Implementacja CMD */ }
    void deleteRenderer() override { /* Implementacja CMD */ }
    sf::RenderWindow* getWindow() override { return nullptr; } // CMD nie potrzebuje sf::RenderWindow
    void render() override { /* Implementacja CMD */ }
};

