#pragma once
#include "src/view/BaseView.h"
#include "SFML/Graphics.hpp"
#include <thread>
#include <future>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include "ftxui/component/loop.hpp"
#include <ftxui/dom/table.hpp>
#include "ftxui/dom/node.hpp"
#define byte win_byte_override
#include <Windows.h>

class BaseViewCMD : public virtual BaseView
{
protected:
    // Console Variables
    HWND consoleWindow = nullptr;
    FILE* m_stdout = nullptr, * m_stderr = nullptr, * m_stdin = nullptr;

    // Renderer thread variables
    std::thread* ftxui_thread = nullptr;
    std::mutex mtx, update_content_mutex;
    std::condition_variable cv;
    ftxui::Component renderer;
    ftxui::ScreenInteractive* screen{};

    bool isRefreshing = false, needRefreshing = false;

    // Private functions
    virtual void renderFTXUI() = 0;
    void refreshScreen();
    

public:
    // Constructors / Destructors
    BaseViewCMD();

    // BaseView member functions
    void openWindow() override;
    void closeWindow() override;
    void initRenderer() override;
    void deleteRenderer() override;
    sf::RenderWindow* getWindow() override;
    void render() override;
};

// TODO: UWAGA WYWALA B£¥D BO W MOMENCIE INICJALIZACJI RENDERERA W GAMEVIEWCMD JEST WINDOW Z SFML A NIE KONSOLA
// NAJPRAWDOPODOBNIEJ PO PRZENIESIENIU RZECZY Z LEADERBAORDCMD I LEADERBOARDGRAPHIC DO BASEVIEWGRAPHIC SIE NAPRAWI
// JAK NIE TO TRZEBA SPRAWDZIC DLACZEGO NIE OTWIERA SIE PRAWIDLOWE OKNO ALE PEWNIE DLATEGO ZE W
// LEADERBOARDGRAPHIC FUNKCJA CLOSEWINDOW NIC NIE ROBI