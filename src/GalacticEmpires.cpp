#include "GalacticEmpires.hpp"

//STD
#include <iostream>
#include <string>

GalacticEmpires::GalacticEmpires()
    : m_window(sf::VideoMode(1280, 720, 32), "Galactic Empires")
    , m_guiWindow(sfg::Window::Create(sfg::Window::Style::TOPLEVEL))
    , m_prevFrameTime(sf::seconds(1.f/60.f))
{
    m_window.resetGLStates(); //for SFGUI

    m_guiWindow->SetTitle("Galactic Empires");
    m_guiWindow->SetAllocation(sf::FloatRect(1280/4, 720/4, 1280/2, 720/2));
    luaL_openlibs(m_lua.getRawState());
}

void GalacticEmpires::run()
{
    if (m_lua.loadFile("settings.lua")) return;
    if (m_lua.executeFile("settings.lua")) return;

    gameLoop();
}

void GalacticEmpires::gameLoop()
{
    m_frameTime.restart();
    while (m_window.isOpen())
    {
        while (m_window.pollEvent(m_event))
        {
            handleEvent(m_event);
        }

        update(m_prevFrameTime.asSeconds());
        draw();

        m_prevFrameTime = m_frameTime.getElapsedTime();
        m_frameTime.restart();
    }

}

void GalacticEmpires::handleEvent(const sf::Event& e)
{
    m_guiWindow->HandleEvent(m_event);

    switch (e.type)
    {
        case sf::Event::Closed:
        {
            m_window.close();
            break;
        }

        default:
        {
            break;
        }
    }
}

void GalacticEmpires::update(float dt)
{
    m_guiWindow->Update(dt);
}

void GalacticEmpires::draw()
{
    m_window.clear(sf::Color(40, 40, 40));
    m_gui.Display(m_window);
    m_window.display();
}
