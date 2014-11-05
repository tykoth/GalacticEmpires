#include "GalacticEmpires.hpp"

#include <iostream>
#include <string>

#include <Helper/Utility.hpp>
#include <ini_parser.hpp>

#include "State/SplashState.hpp"

GalacticEmpires::GalacticEmpires()
    : m_window(sf::VideoMode(1280, 720, 32), "Galactic Empires")
    , m_curState(nullptr)
    , m_errorWindow(sfg::Window::Create(sfg::Window::BACKGROUND))
    , m_prevFrameTime(sf::seconds(1.f/60.f))
    , m_settings("data/settings.ini")
{
    m_errorWindow->Show(false);

    loadSettings();

    m_guiDesktop.LoadThemeFromFile("data/default.theme");
    m_stateMan.push<SplashState>(this);
}

void GalacticEmpires::run()
{
    gameLoop();
}

sf::RenderWindow* GalacticEmpires::getWindow()
{
    return &m_window;
}

StateManager<GalacticEmpires>* GalacticEmpires::getStateManager()
{
    return &m_stateMan;
}

void GalacticEmpires::loadSettings()
{
    int width = m_settings.getInt("width", "Video");
    int height = m_settings.getInt("height", "Video");
    int bitDepth = m_settings.getInt("bitDepth", "Video");
    bool fullscreen = m_settings.getBool("fullscreen", "Video");
    bool vsync = m_settings.getBool("vsync", "Video");
    int maxFPS = m_settings.getInt("maxFPS", "Video");

    std::string version = "v";
    version += toString(VERSION_MAJOR);
    version += ".";
    version += toString(VERSION_MINOR);
    version += ".";
    version += toString(VERSION_REVISION);

    sf::VideoMode vm(width, height, bitDepth);

    if (!vm.isValid())
    {
        if (fullscreen)
        {
            throw std::runtime_error("Invalid Video Settings for Fullscreen (Width, Height, or BitDepth)");
        }
        else if (width == 0 || height == 0)
        {
            vm = sf::VideoMode::getDesktopMode();
            m_settings.setValue("width", int(vm.width), "Video");
            m_settings.setValue("height", int(vm.height), "Video");
            m_settings.setValue("bitDepth", int(vm.bitsPerPixel), "Video");
            fullscreen = true;
            m_settings.setValue("fullscreen", fullscreen, "Video");
            m_settings.save();
        }
    }

    m_window.create(vm, "Galactic Empires " + version, fullscreen ? sf::Style::Fullscreen : sf::Style::Default);

    m_window.setVerticalSyncEnabled(vsync);

    if (maxFPS)
    {
        m_window.setFramerateLimit(maxFPS);
    }

    m_window.resetGLStates(); //This is required to show SFGUI if we don't draw with SFML at any point
}

void GalacticEmpires::handleError(std::string err)
{
    if (!m_exceptionErrorMessage.empty())
    {
        return;
    }

    m_exceptionErrorMessage = err;
    sfg::Label::Ptr lbl = sfg::Label::Create(err);
    m_errorWindow->Add(lbl);
    m_errorWindow->Show(true);
    std::cout << err << "\n";
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

        m_prevFrameTime = m_frameTime.getElapsedTime();
        m_frameTime.restart();
    }
}

void GalacticEmpires::handleEvent(const sf::Event& e)
{
    try
    {
        m_curState->handleEvent(e);
    }
    catch (const std::exception& e)
    {
        handleError(e.what());
    }

    m_errorWindow->HandleEvent(e);

    switch (e.type)
    {
        case sf::Event::Closed:
        {
            m_window.close();
            break;
        }

        case sf::Event::KeyPressed:
        {
            if (e.key.code == sf::Keyboard::Escape)
            {
                m_window.close();
            }

            if (e.key.code == sf::Keyboard::F12)
            {
               loadSettings();
            }

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
    try
    {
        m_curState->update(dt);
    }
    catch (const std::exception& e)
    {
        handleError(e.what()); //Bug: called every frame? why does the exception keep getting catched, there should only be one.
    }

    m_errorWindow->Update(dt);
}

void GalacticEmpires::draw()
{
    m_window.clear(sf::Color(40, 40, 40));
    m_curState->draw(m_window);
    m_gui.Display(m_window);
    m_window.display();
}
