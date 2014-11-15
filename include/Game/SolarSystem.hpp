#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include <unordered_map>
#include <tuple>

#include <SFML/Graphics.hpp>

#include "GalacticEmpires.hpp"

typedef sf::Vector2i coordinates;

namespace std
{
    template <>
    struct hash<coordinates>
    {
        std::size_t operator()(const coordinates& coord) const
        {
            return coord.x ^ coord.y;
        }
    };
}

typedef std::unordered_map<coordinates, sf::CircleShape> HexMap;

class SolarSystem : public sf::Drawable
{
public:
    SolarSystem(GalacticEmpires* galemp);
    bool handleEvent(const sf::Event& e);
    void update(double dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void genMap();
    void genHexLine(int lineHeight, int radius);

    GalacticEmpires* m_galemp;

    int m_systemRadius;
    float m_hexRadius;

    HexMap m_map;
    sf::CircleShape m_shape;
    coordinates m_hoverHex;
};

#endif //SOLARSYSTEM_HPP
