#ifndef NEWGAMESTATE_HPP
#define NEWGAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "State/BaseState.hpp"
#include "GalacticEmpires.hpp"

class NewGameState : public BaseState
{
public:
    NewGameState(GalacticEmpires* galemp);
    void handleEvent(const sf::Event& e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;
    void onActive() override;
    void onInactive() override;

private:
    GalacticEmpires* m_galemp;

    sfg::Window::Ptr m_guiWindow;
};

#endif // NEWGAMESTATE_HPP
