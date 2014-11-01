#include "GalacticEmpires.hpp"

//STD
#include <iostream>
#include <string>

//3RD
//#include <ini_parser.hpp>
#include <ZGE/Utility.hpp>

//SELF
#include "TestState.hpp"

GalacticEmpires::GalacticEmpires()
    : m_window(sf::VideoMode(1280, 720, 32), "Galactic Empires")
    , m_curState(nullptr)
    , m_prevFrameTime(sf::seconds(1.f/60.f))
{
    std::cout << this << ", " << getStateManager() << ", " << getStateManager()->top() << "\n";
    m_stateMan.push<TestState>(this);

    loadSettings();
    m_guiDesktop.LoadThemeFromFile("data/default.theme");
}

void GalacticEmpires::run()
{
    gameLoop();
}

void GalacticEmpires::loadSettings()
{
    /*ini_parser iniParser("data/settings.ini");
    int width = iniParser.get_int("width", "Video");
    int height = iniParser.get_int("height", "Video");
    int bitDepth = iniParser.get_int("bitDepth", "Video");
    bool fullscreen = iniParser.get_bool("fullscreen", "Video");
    bool vsync = iniParser.get_bool("vsync", "Video");
    int maxFPS = iniParser.get_int("maxFPS", "Video");

    std::string version = "v";
    version += zge::toString(VERSION_MAJOR);
    version += ".";
    version += zge::toString(VERSION_MINOR);
    version += ".";
    version += zge::toString(VERSION_REVISION);

    m_window.create(sf::VideoMode(width, height, bitDepth), "Galactic Empires " + version, fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.setVerticalSyncEnabled(vsync);
    if (maxFPS) m_window.setFramerateLimit(maxFPS);*/
}

void GalacticEmpires::gameLoop()
{
    m_frameTime.restart();
    while (m_window.isOpen())
    {
        m_curState = m_stateMan.top();

        while (m_window.pollEvent(m_event))
        {
            handleEvent(m_event);
        }

        update(m_prevFrameTime.asSeconds());
        draw();
        postDraw();
    }
}

void GalacticEmpires::handleEvent(const sf::Event& e)
{
    m_curState->handleEvent(e);

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
    m_curState->update(dt);
}

void GalacticEmpires::draw()
{
    m_window.clear(sf::Color(40, 40, 40));
    m_stateMan.top()->draw(m_window);
    m_gui.Display(m_window);
    m_window.display();
}

void GalacticEmpires::postDraw()
{
    m_prevFrameTime = m_frameTime.getElapsedTime();
    m_frameTime.restart();
}
