#include "Helper/Utility.hpp"

#include <lua5.2/lua.hpp>

void drawLine(sf::RenderTarget& target, float x1, float y1, float x2, float y2, sf::Color c)
{
    sf::VertexArray line(sf::Lines, 2);
    line[0] = sf::Vertex(sf::Vector2f(x1, y1), c);
    line[1] = sf::Vertex(sf::Vector2f(x2, y2), c);
    target.draw(line);
}

std::string luaErrorAsString(int error)
{
    switch (error)
    {
        case LUA_OK:
        {
            return "No Error";
        }

        case LUA_YIELD:
        {
            return "Yield Error";
        }

        case LUA_ERRRUN:
        {
            return "Runtime Error";
        }

        case LUA_ERRSYNTAX:
        {
            return "Syntax Error";
        }

        case LUA_ERRMEM:
        {
            return "Memory Allocation Error";
        }

        case LUA_ERRGCMM:
        {
            return "Garbage Collector Error";
        }

        case LUA_ERRERR:
        {
            return "Error Handler Error";
        }

        case LUA_ERRFILE:
        {
            return "File Not Found Error";
        }

        default:
        {
            return std::string("Unknown Lua Error. Code = " + toString(error));
        }
    }
}
