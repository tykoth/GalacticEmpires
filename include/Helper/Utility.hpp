#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <sstream>

#include <SFML/Graphics.hpp>

struct lua_State;

void drawLine(sf::RenderTarget& target, float x1, float y1, float x2, float y2, sf::Color c);

template<class T>
std::string toString(T var)
{
    std::stringstream ss;
    ss << var;
    return ss.str();
}

template<class T>
T fromString(std::string str)
{
    std::stringstream ss(str);
    T var;
    ss >> var;
    return var;
}

std::string luaErrorAsString(lua_State* L, int error);

#endif //UTILITY_HPP
